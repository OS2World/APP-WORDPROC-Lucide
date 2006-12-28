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

#ifndef __NEUQUANT_H
#define __NEUQUANT_H


// NEUQUANT Neural-Net quantization algorithm by Anthony Dekker


class LuPixbuf;


class NeuQuantizer
{

    protected:
        LuPixbuf *pixbuf;
        unsigned char *pixbits;
        /// image width
        int img_width;
        /// image height
        int img_height;
        /// image line length
        int img_line;
        int img_line_len;
        int bpp;

        int netsize, maxnetpos, initrad, initradius;

        /// BGRc
        typedef int pixel[4];
        /// the network itself
        pixel *network;

        /// for network lookup - really 256
        int netindex[256];

        /// bias array for learning
        int *bias;
        /// freq array for learning
        int *freq;
        /// radpower for precomputation
        int *radpower;

    protected:

        /// Search for biased BGR values
        int contest(int b, int g, int r);

        /// Move neuron i towards biased (b,g,r) by factor alpha
        void altersingle(int alpha, int i, int b, int g, int r);

        /// Move adjacent neurons by precomputed alpha*(1-((i-j)^2/[r]^2)) in radpower[|i-j|]
        void alterneigh(int rad, int i, int b, int g, int r);

        /// Get a pixel sample at position pos. Handle 4-byte boundary alignment.
        void getSample(long pos, int *b, int *g, int *r);

    public:
        /// Constructor
        NeuQuantizer( LuPixbuf *pb, int PaletteSize );

        /// Destructor
        ~NeuQuantizer();

        /// Initialise network in range (0,0,0) to (255,255,255) and set parameters
        void initnet();

        /// Unbias network to give byte values 0..255 and record position i to prepare for sort
        void unbiasnet();

        /// Insertion sort of network and building of netindex[0..255] (to do after unbias)
        void inxbuild();

        /// Search for BGR values 0..255 (after net is unbiased) and return colour index
        int inxsearch(int b, int g, int r);

        /// Main Learning Loop  sampling factor in [1..30]
        void learn(int sampling_factor);

        pixel *getNetwork() {
            return network;
        }
};

#endif // __NEUQUANT_H
