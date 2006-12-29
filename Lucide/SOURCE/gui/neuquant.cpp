/* NeuQuant Neural-Net Quantization Algorithm
 * ------------------------------------------
 *
 * Copyright (c) 1994 Anthony Dekker
 *
 * NEUQUANT Neural-Net quantization algorithm by Anthony Dekker, 1994.
 * See "Kohonen neural networks for optimal colour quantization"
 * in "Network: Computation in Neural Systems" Vol. 5 (1994) pp 351-367.
 * for a discussion of the algorithm.
 *
 * Any party obtaining a copy of these files from the author, directly or
 * indirectly, is granted, free of charge, a full and unrestricted irrevocable,
 * world-wide, paid up, royalty-free, nonexclusive right and license to deal
 * in this software and documentation files (the "Software"), including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons who receive
 * copies from any such party to do so, with the only requirement being
 * that this copyright notice remain intact.
 */

#include <os2.h>

#include <lupixbuf.xh>

#include "neuquant.h"
#include "globals.h"


// Four primes near 500 - assume no image has a length so large
// that it is divisible by all four primes
// ==========================================================

#define prime1      499
#define prime2      491
#define prime3      487
#define prime4      503

// ----------------------------------------------------------------

NeuQuantizer::NeuQuantizer( LuPixbuf *pb, int PaletteSize )
{
    netsize = PaletteSize;
    maxnetpos = netsize - 1;
    initrad = netsize < 8 ? 1 : (netsize >> 3);
    initradius = (initrad * radiusbias);

    network = NULL;

    network = (pixel *)malloc(netsize * sizeof(pixel));
    bias = (int *)malloc(netsize * sizeof(int));
    freq = (int *)malloc(netsize * sizeof(int));
    radpower = (int *)malloc(initrad * sizeof(int));

    pixbuf = pb;
    bpp        = pixbuf->getBpp(ev);
    img_width  = pixbuf->getWidth(ev);
    img_height = pixbuf->getHeight(ev);
    // DIB line length in bytes (should be equal to 3 x W)
    img_line   = img_width * bpp;
    img_line_len = pixbuf->getRowSize(ev);
    pixbits    = (unsigned char *)pixbuf->getDataPtr(ev);
}

NeuQuantizer::~NeuQuantizer()
{
    if(network) free(network);
    if(bias) free(bias);
    if(freq) free(freq);
    if(radpower) free(radpower);
}

///////////////////////////////////////////////////////////////////////////
// Initialise network in range (0,0,0) to (255,255,255) and set parameters
// -----------------------------------------------------------------------

void NeuQuantizer::initnet()
{
    int i, *p;

    for (i = 0; i < netsize; i++)
    {
        p = network[i];
        p[FI_RGBA_BLUE] = p[FI_RGBA_GREEN] = p[FI_RGBA_RED] = (i << (netbiasshift+8))/netsize;
        freq[i] = intbias/netsize;  /* 1/netsize */
        bias[i] = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////
// Unbias network to give byte values 0..255 and record position i to prepare for sort
// ------------------------------------------------------------------------------------

void NeuQuantizer::unbiasnet()
{
    int i, j, temp;

    for (i = 0; i < netsize; i++)
    {
        for (j = 0; j < 3; j++)
        {
            // OLD CODE: network[i][j] >>= netbiasshift;
            // Fix based on bug report by Juergen Weigert jw@suse.de
            temp = (network[i][j] + (1 << (netbiasshift - 1))) >> netbiasshift;
            if (temp > 255) temp = 255;
            network[i][j] = temp;
        }
        network[i][3] = i;          // record colour no
    }
}

//////////////////////////////////////////////////////////////////////////////////
// Insertion sort of network and building of netindex[0..255] (to do after unbias)
// -------------------------------------------------------------------------------

void NeuQuantizer::inxbuild()
{
    int i,j,smallpos,smallval;
    int *p,*q;
    int previouscol,startpos;

    previouscol = 0;
    startpos = 0;
    for (i = 0; i < netsize; i++)
    {
        p = network[i];
        smallpos = i;
        smallval = p[FI_RGBA_GREEN];            // index on g
        // find smallest in i..netsize-1
        for (j = i+1; j < netsize; j++)
        {
            q = network[j];
            if (q[FI_RGBA_GREEN] < smallval) {  // index on g
                smallpos = j;
                smallval = q[FI_RGBA_GREEN];    // index on g
            }
        }
        q = network[smallpos];
        // swap p (i) and q (smallpos) entries
        if (i != smallpos)
        {
            j = q[FI_RGBA_BLUE];  q[FI_RGBA_BLUE]  = p[FI_RGBA_BLUE];  p[FI_RGBA_BLUE]  = j;
            j = q[FI_RGBA_GREEN]; q[FI_RGBA_GREEN] = p[FI_RGBA_GREEN]; p[FI_RGBA_GREEN] = j;
            j = q[FI_RGBA_RED];   q[FI_RGBA_RED]   = p[FI_RGBA_RED];   p[FI_RGBA_RED]   = j;
            j = q[3];   q[3] = p[3];   p[3] = j;
        }
        // smallval entry is now in position i
        if (smallval != previouscol)
        {
            netindex[previouscol] = (startpos+i)>>1;
            for (j = previouscol+1; j < smallval; j++) {
                netindex[j] = i;
            }
            previouscol = smallval;
            startpos = i;
        }
    }
    netindex[previouscol] = (startpos+maxnetpos)>>1;
    for (j = previouscol+1; j < 256; j++)
        netindex[j] = maxnetpos; // really 256
}

///////////////////////////////////////////////////////////////////////////////
// Search for BGR values 0..255 (after net is unbiased) and return colour index
// ----------------------------------------------------------------------------

int NeuQuantizer::inxsearch(int b, int g, int r)
{
    int i, j, dist, a, bestd;
    int *p;
    int best;

    bestd = 1000;       // biggest possible dist is 256*3
    best = -1;
    i = netindex[g];    // index on g
    j = i-1;            // start at netindex[g] and work outwards

    while ((i < netsize) || (j >= 0))
    {
        if (i < netsize)
        {
            p = network[i];
            dist = p[FI_RGBA_GREEN] - g;                // inx key
            if (dist >= bestd)
                i = netsize;    // stop iter
            else
            {
                i++;
                if (dist < 0)
                    dist = -dist;
                a = p[FI_RGBA_BLUE] - b;
                if (a < 0)
                    a = -a;
                dist += a;
                if (dist < bestd)
                {
                    a = p[FI_RGBA_RED] - r;
                    if (a<0)
                        a = -a;
                    dist += a;
                    if (dist < bestd) {
                        bestd = dist;
                        best = p[3];
                    }
                }
            }
        }
        if (j >= 0)
        {
            p = network[j];
            dist = g - p[FI_RGBA_GREEN];            // inx key - reverse dif
            if (dist >= bestd)
                j = -1; // stop iter
            else
            {
                j--;
                if (dist < 0)
                    dist = -dist;
                a = p[FI_RGBA_BLUE] - b;
                if (a<0)
                    a = -a;
                dist += a;
                if (dist < bestd)
                {
                    a = p[FI_RGBA_RED] - r;
                    if (a<0)
                        a = -a;
                    dist += a;
                    if (dist < bestd) {
                        bestd = dist;
                        best = p[3];
                    }
                }
            }
        }
    }
    return best;
}

///////////////////////////////
// Search for biased BGR values
// ----------------------------

int NeuQuantizer::contest(int b, int g, int r)
{
    // finds closest neuron (min dist) and updates freq
    // finds best neuron (min dist-bias) and returns position
    // for frequently chosen neurons, freq[i] is high and bias[i] is negative
    // bias[i] = gamma*((1/netsize)-freq[i])

    int i,dist,a,biasdist,betafreq;
    int bestpos,bestbiaspos,bestd,bestbiasd;
    int *p,*f, *n;

    bestd = ~(((int) 1)<<31);
    bestbiasd = bestd;
    bestpos = -1;
    bestbiaspos = bestpos;
    p = bias;
    f = freq;

    for (i = 0; i < netsize; i++)
    {
        n = network[i];
        dist = n[FI_RGBA_BLUE] - b;
        if (dist < 0)
            dist = -dist;
        a = n[FI_RGBA_GREEN] - g;
        if (a < 0)
            a = -a;
        dist += a;
        a = n[FI_RGBA_RED] - r;
        if (a < 0)
            a = -a;
        dist += a;
        if (dist < bestd) {
            bestd = dist;
            bestpos = i;
        }
        biasdist = dist - ((*p)>>(intbiasshift-netbiasshift));
        if (biasdist < bestbiasd) {
            bestbiasd = biasdist;
            bestbiaspos = i;
        }
        betafreq = (*f >> betashift);
        *f++ -= betafreq;
        *p++ += (betafreq << gammashift);
    }
    freq[bestpos] += beta;
    bias[bestpos] -= betagamma;
    return bestbiaspos;
}

///////////////////////////////////////////////////////
// Move neuron i towards biased (b,g,r) by factor alpha
// ----------------------------------------------------

void NeuQuantizer::altersingle(int alpha, int i, int b, int g, int r)
{
    int *n;

    n = network[i];             // alter hit neuron
    n[FI_RGBA_BLUE]  -= (alpha * (n[FI_RGBA_BLUE]  - b)) / initalpha;
    n[FI_RGBA_GREEN] -= (alpha * (n[FI_RGBA_GREEN] - g)) / initalpha;
    n[FI_RGBA_RED]   -= (alpha * (n[FI_RGBA_RED]   - r)) / initalpha;
}

////////////////////////////////////////////////////////////////////////////////////
// Move adjacent neurons by precomputed alpha*(1-((i-j)^2/[r]^2)) in radpower[|i-j|]
// ---------------------------------------------------------------------------------

void NeuQuantizer::alterneigh(int rad, int i, int b, int g, int r)
{
    int j, k, lo, hi, a;
    int *p, *q;

    lo = i - rad;   if (lo < -1) lo = -1;
    hi = i + rad;   if (hi > netsize) hi = netsize;

    j = i+1;
    k = i-1;
    q = radpower;
    while ((j < hi) || (k > lo))
    {
        a = (*(++q));
        if (j < hi)
        {
            p = network[j];
            p[FI_RGBA_BLUE]  -= (a * (p[FI_RGBA_BLUE] - b)) / alpharadbias;
            p[FI_RGBA_GREEN] -= (a * (p[FI_RGBA_GREEN] - g)) / alpharadbias;
            p[FI_RGBA_RED]   -= (a * (p[FI_RGBA_RED] - r)) / alpharadbias;
            j++;
        }
        if (k > lo)
        {
            p = network[k];
            p[FI_RGBA_BLUE]  -= (a * (p[FI_RGBA_BLUE] - b)) / alpharadbias;
            p[FI_RGBA_GREEN] -= (a * (p[FI_RGBA_GREEN] - g)) / alpharadbias;
            p[FI_RGBA_RED]   -= (a * (p[FI_RGBA_RED] - r)) / alpharadbias;
            k--;
        }
    }
}

/////////////////////
// Main Learning Loop
// ------------------

void NeuQuantizer::learn(int sampling_factor)
{
    int i, j, b, g, r;
    int radius, rad, alpha, step, delta, samplepixels;
    int alphadec; // biased by 10 bits
    long pos, lengthcount;

    // image size as viewed by the scan algorithm
    lengthcount = img_width * img_height * bpp;

    // number of samples used for the learning phase
    samplepixels = lengthcount / (3 * sampling_factor);

    // decrease learning rate after delta pixel presentations
    delta = samplepixels / ncycles;
    if(delta == 0) {
        // avoid a 'divide by zero' error with very small images
        delta = 1;
    }

    // initialize learning parameters
    alphadec = 30 + ((sampling_factor - 1) / 3);
    alpha = initalpha;
    radius = initradius;

    rad = radius >> radiusbiasshift;
    if (rad <= 1) rad = 0;
    for (i = 0; i < rad; i++)
        radpower[i] = alpha*(((rad*rad - i*i)*radbias)/(rad*rad));

    // initialize pseudo-random scan
    if ((lengthcount % prime1) != 0)
        step = bpp*prime1;
    else {
        if ((lengthcount % prime2) != 0)
            step = bpp*prime2;
        else {
            if ((lengthcount % prime3) != 0)
                step = bpp*prime3;
            else
                step = bpp*prime4;
        }
    }

    i = 0;      // iteration
    pos = 0;    // pixel position

    while (i < samplepixels)
    {
        // get next learning sample
        getSample(pos, &b, &g, &r);

        // find winning neuron
        j = contest(b, g, r);

        // alter winner
        altersingle(alpha, j, b, g, r);

        // alter neighbours
        if (rad) alterneigh(rad, j, b, g, r);

        // next sample
        pos += step;
        while (pos >= lengthcount) pos -= lengthcount;

        i++;
        if (i % delta == 0)
        {
            // decrease learning rate and also the neighborhood
            alpha -= alpha / alphadec;
            radius -= radius / radiusdec;
            rad = radius >> radiusbiasshift;
            if (rad <= 1) rad = 0;
            for (j = 0; j < rad; j++)
                radpower[j] = alpha * (((rad*rad - j*j) * radbias) / (rad*rad));
        }
    }
}


