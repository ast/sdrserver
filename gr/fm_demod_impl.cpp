/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>

#include <gnuradio/analog/quadrature_demod_cf.h>
#include <gnuradio/filter/firdes.h>
#include <gnuradio/filter/fir_filter_fff.h>

#include "fm_demod_impl.h"

namespace gr {
namespace sm6wjm {

fm_demod::sptr
fm_demod::make(float channel_rate, int audio_decim, float deviation, float audio_pass, float audio_stop, float gain, float tau)
{
    return gnuradio::get_initial_sptr
            (new fm_demod_impl(channel_rate, audio_decim, deviation, audio_pass, audio_stop, gain, tau));
}

/*
     * The private constructor
     */
fm_demod_impl::fm_demod_impl(float channel_rate, int audio_decim, float deviation, float audio_pass, float audio_stop, float gain, float tau)
    : gr::hier_block2("fm_demod",
                      gr::io_signature::make(1, 1, sizeof(gr_complex)),
                      gr::io_signature::make(1, 1, sizeof(float)))
{

    float k = channel_rate / (2 * M_PI * deviation);
    auto quad = gr::analog::quadrature_demod_cf::make(k);

    auto taps = gr::filter::firdes::low_pass(gain, channel_rate, audio_pass, 1000.0);
    auto lpf = gr::filter::fir_filter_fff::make(audio_decim, taps);

    connect(self(), 0, quad, 0);
    connect(quad, 0, lpf, 0);
    connect(lpf, 0, self(), 0);
}

/*
     * Our virtual destructor.
     */
fm_demod_impl::~fm_demod_impl()
{
}


} /* namespace sm6wjm */
} /* namespace gr */

