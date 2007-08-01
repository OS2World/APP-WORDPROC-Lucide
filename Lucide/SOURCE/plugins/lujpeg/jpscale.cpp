/* ***** BEGIN LICENSE BLOCK *****
 * Version: CDDL 1.0/LGPL 2.1
 *
 * The contents of this file are subject to the COMMON DEVELOPMENT AND
 * DISTRIBUTION LICENSE (CDDL) Version 1.0 (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.sun.com/cddl/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Initial Developer of the Original Code is
 * Eugene Romanenko, netlabs.org.
 * Portions created by the Initial Developer are Copyright (C) 2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the LGPL are applicable instead of those
 * above. If you wish to allow use of your version of this file only under the
 * terms of the LGPL, and not to allow others to use your version of this file
 * under the terms of the CDDL, indicate your decision by deleting the
 * provisions above and replace them with the notice and other provisions
 * required by the LGPL. If you do not delete the provisions above, a recipient
 * may use your version of this file under the terms of any one of the CDDL
 * or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

// This file based on public domain code.
// Original code by Dale Schumacher, public domain 1991
// See _Graphics Gems III_ "General Filtered Image Rescaling", Dale A. Schumacher


#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <vector>

#include <LuPixbuf.xh>


#define ceilf ceil
#define floorf floor

inline int iclamp( int i, int min, int max ) {
    assert( min <= max );
    return __max( min, __min(i, max) );
}

inline int frnd( float f ) { return (int)( f + 0.5f ); }

inline void *my_calloc( int count, int size )
{
    void *mem = (void *)new char[ count * size ];
    memset( mem, 0, count * size );
    return mem;
}

inline void my_cfree( void* mem )
{
    delete [] (char*)mem;
}


// Copy RGB data from the specified row into the given buffer.
void get_row( Environment *ev, uint8_t* row, LuPixbuf *image, int x0, int xsize, int y )
{
    long m_width    = image->getWidth( ev );
    long m_height   = image->getHeight( ev );
    long m_pitch    = image->getRowSize( ev );
    uint8_t *m_data = (uint8_t*)image->getDataPtr( ev );

    y = iclamp( y, 0, m_height - 1 );
    int x1 = x0 + xsize - 1;
    if ( x1 >= m_width )
    {
        // clip, then extend.
        int extra_pixels = x1 - m_width + 1;
        uint8_t*  p = m_data + (y * m_pitch);
        memcpy( row, p + x0 * 3, (3 * (m_width - x0)) );
        // repeat last pixel
        p = p + (m_width - 1) * 3;
        uint8_t* q = row + (m_width - x0) * 3;
        while (extra_pixels > 0)
        {
            *(q + 0) = *(p + 0);
            *(q + 1) = *(p + 1);
            *(q + 2) = *(p + 2);
            q += 3;
            extra_pixels--;
        }
    }
    else {
        memcpy( row, m_data + (y * m_pitch) + x0 * 3, (3 * xsize) );
    }
}



// Copy RGB data from the specified column into the given buffer.
void get_column( Environment *ev, uint8_t* column, LuPixbuf *image, int x )
{
    long m_width    = image->getWidth( ev );
    long m_height   = image->getHeight( ev );
    long m_pitch    = image->getRowSize( ev );
    uint8_t *m_data = (uint8_t*)image->getDataPtr( ev );

    if ((x < 0) || (x >= m_width)) {
        assert(0);
        x = iclamp(x, 0, m_width - 1);
    }

    int d = m_pitch;
    uint8_t* p = m_data + x * 3;
    for (int i = m_height; i-- > 0; p += d) {
        *column++ = *p;
        *column++ = *(p + 1);
        *column++ = *(p + 2);
    }
}



// Clamp {r, g, b} to [0,255], and write pixel data to the given image at (x, y).
void put_pixel( Environment *ev, LuPixbuf *image, int x, int y, float r, float g, float b )
{
    long m_width    = image->getWidth( ev );
    long m_height   = image->getHeight( ev );
    long m_pitch    = image->getRowSize( ev );
    uint8_t *m_data = (uint8_t*)image->getDataPtr( ev );

    if ((x < 0) || (x >= m_width) || (y < 0) || (y >= m_height)) {
        assert(0);
        return;
    }

    uint8_t *p = m_data + (y * m_pitch);

    p[x * 3 + 0] = iclamp(frnd(r), 0, 255);
    p[x * 3 + 1] = iclamp(frnd(g), 0, 255);
    p[x * 3 + 2] = iclamp(frnd(b), 0, 255);
}



/*
 *   filter function definitions
 */

// MITCHELL

#define SUPPORT (2.0f)

#define B       (1.0f / 3.0f)
#define C       (1.0f / 3.0f)

float Mitchell_filter(float t)
{
    float tt = t * t;
    if (t < 0.0f) t = -t;
    if (t < 1.0f) {
        t = (((12.0f - 9.0f * B - 6.0f * C) * (t * tt))
             + ((-18.0f + 12.0f * B + 6.0f * C) * tt)
             + (6.0f - 2.0f * B));
        return(t / 6.0f);
    } else if(t < 2.0f) {
        t = (((-1.0f * B - 6.0f * C) * (t * tt))
             + ((6.0f * B + 30.0f * C) * tt)
             + ((-12.0f * B - 48.0f * C) * t)
             + (8.0f * B + 24 * C));
        return(t / 6.0f);
    }
    return(0.0f);
}


struct CONTRIB
{
    int   pixel;
    float weight;

    CONTRIB() : pixel(0), weight(0.f) {}

    CONTRIB(int p, float w) : pixel(p), weight(w) {}
};


// Rescale the specified portion of the input image into the specified
// portion of the output image.  Coordinates are *inclusive*.
void resample( Environment *ev,
               LuPixbuf *out, int out_x0, int out_y0, int out_x1, int out_y1,
               LuPixbuf *in, float in_x0, float in_y0, float in_x1, float in_y1 )
{
    long out_m_width  = out->getWidth( ev );
    long out_m_height = out->getHeight( ev );

    assert(out_x0 <= out_x1);
    assert(out_y0 <= out_y1);
    assert(out_x0 >= 0 && out_x0 < out_m_width);
    assert(out_x1 >= 0 && out_x1 < out_m_width);
    assert(out_y0 >= 0 && out_y0 < out_m_height);
    assert(out_y1 >= 0 && out_y1 < out_m_height);


    int i, k;                   /* loop variables */
    unsigned int j;                     /* loop variables */
    int n;                              /* pixel number */
    float center; int left, right;      /* filter calculation variables */
    float width, fscale, weight;        /* filter calculation variables */
    uint8_t*    raster;                 /* a row or column of pixels */

    std::vector< std::vector<CONTRIB> > contrib;

    int out_width = out_x1 - out_x0 + 1;
    int out_height = out_y1 - out_y0 + 1;
    assert(out_width > 0);
    assert(out_height > 0);

    float       in_width = in_x1 - in_x0;
    float       in_height = in_y1 - in_y0;
    assert(in_width > 0);
    assert(in_height > 0);

    int in_window_w = int(ceilf(in_x1) - floorf(in_x0) + 1);
    int in_window_h = int(ceilf(in_y1) - floorf(in_y0) + 1);

    /* create intermediate image to hold horizontal zoom */
    LuPixbuf *tmp = new LuPixbuf( ev, out_width, in_window_h, 3 );
    long tmp_m_width   = tmp->getWidth( ev );
    long tmp_m_height  = tmp->getHeight( ev );

    float xscale = (float) (out_width - 1) / in_width;
    float yscale = (float) (out_height - 1) / in_height;

    // xxxx protect against division by 0
    if (yscale == 0) { yscale = 1.0f; }
    if (xscale == 0) { xscale = 1.0f; }

    /* pre-calculate filter contributions for a row */
    contrib.resize(tmp_m_width);
    if(xscale < 1.0f)
    {
        width = SUPPORT / xscale;
        fscale = 1.0f / xscale;
        for (i = 0; i < tmp_m_width; ++i)
        {
            contrib[i].resize(0);

            center = (float) i / xscale;
            left = int(ceilf(center - width));
            right = int(floorf(center + width));
            for (k = left; k <= right; ++k)
            {
                weight = center - (float) k;
                weight = Mitchell_filter(weight / fscale) / fscale;
                n = iclamp(k, 0, in_window_w - 1);
                contrib[i].push_back(CONTRIB(n, weight));
            }
        }
    }
    else
    {
        for (i = 0; i < tmp_m_width; ++i)
        {
            contrib[i].resize(0);
            center = (float) i / xscale;
            left = int(ceilf(center - SUPPORT));
            right = int(floorf(center + SUPPORT));
            for(k = left; k <= right; ++k)
            {
                weight = center - (float) k;
                weight = Mitchell_filter(weight);
                n = iclamp(k, 0, in_window_w - 1);
                contrib[i].push_back(CONTRIB(n, weight));
            }
        }
    }

    /* apply filter to zoom horizontally from src to tmp */
    raster = (uint8_t*) my_calloc(in_window_w, 3);
    for (k = 0; k < tmp_m_height; ++k)
    {
        get_row( ev, raster, in, int(floorf(in_x0)), in_window_w, k );
        for (i = 0; i < tmp_m_width; ++i)
        {
            float       red = 0.0f;
            float       green = 0.0f;
            float       blue = 0.0f;
            for(j = 0; j < contrib[i].size(); ++j)
            {
                int     pixel = contrib[i][j].pixel;
                red     += raster[pixel * 3 + 0] * contrib[i][j].weight;
                green   += raster[pixel * 3 + 1] * contrib[i][j].weight;
                blue    += raster[pixel * 3 + 2] * contrib[i][j].weight;
            }
            put_pixel( ev, tmp, i, k, red, green, blue );
        }
    }
    my_cfree(raster);

    contrib.resize(out_height);

    if (yscale < 1.0f)
    {
        width = SUPPORT / yscale;
        fscale = 1.0f / yscale;
        for (i = 0; i < out_height; ++i)
        {
            contrib[i].resize(0);

            center = (float) i / yscale;
            left = int(ceilf(center - width));
            right = int(floorf(center + width));
            for (k = left; k <= right; ++k)
            {
                weight = center - (float) k;
                weight = Mitchell_filter(weight / fscale) / fscale;
                n = iclamp(k, 0, tmp_m_height - 1);
                contrib[i].push_back(CONTRIB(n, weight));
            }
        }
    }
    else
    {
        for (i = 0; i < out_height; ++i)
        {
            contrib[i].resize(0);
            center = (float) i / yscale;
            left = int(ceilf(center - SUPPORT));
            right = int(floorf(center + SUPPORT));
            for(k = left; k <= right; ++k)
            {
                weight = center - (float) k;
                weight = Mitchell_filter(weight);
                n = iclamp(k, 0, tmp_m_height - 1);
                contrib[i].push_back(CONTRIB(n, weight));
            }
        }
    }

    /* apply filter to zoom vertically from tmp to dst */
    raster = (uint8_t*) my_calloc(tmp_m_height, 3);
    for (k = 0; k < tmp_m_width; ++k)
    {
        get_column( ev, raster, tmp, k );
        for (i = 0; i < out_height; ++i)
        {
            float       red = 0.0f;
            float       green = 0.0f;
            float       blue = 0.0f;
            for (j = 0; j < contrib[i].size(); ++j)
            {
                int     pixel = contrib[i][j].pixel;
                red     += raster[pixel * 3 + 0] * contrib[i][j].weight;
                green   += raster[pixel * 3 + 1] * contrib[i][j].weight;
                blue    += raster[pixel * 3 + 2] * contrib[i][j].weight;
            }
            put_pixel( ev, out, k + out_x0, i + out_y0, red, green, blue );
        }
    }
    my_cfree(raster);

    contrib.resize(0);

    delete tmp;
}


