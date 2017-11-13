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

#include <gnuradio/io_signature.h>
#include "weaver_impl.h"

#include <gnuradio/analog/sig_source_c.h>
#include <gnuradio/blocks/complex_to_float.h>
#include <gnuradio/blocks/multiply_cc.h>
#include <gnuradio/blocks/add_ff.h>
#include <gnuradio/blocks/multiply_const_ff.h>
#include <gnuradio/filter/firdes.h>

namespace gr {
namespace sm6wjm {

weaver::sptr
weaver::make(double channel_rate, int audio_decim, double center_freq)
{
    return gnuradio::get_initial_sptr
            (new weaver_impl(channel_rate, audio_decim, center_freq));
}

/*
     * The private constructor
     */
weaver_impl::weaver_impl(double channel_rate, int audio_decim, double center_freq)
    : gr::hier_block2("weaver",
                      gr::io_signature::make(1, 1, sizeof(gr_complex)),
                      gr::io_signature::make(1, 1, sizeof(float)))
{

    auto taps = gr::filter::firdes::low_pass(1.0, channel_rate, 2000.0, 100.0);
    d_xfir = gr::filter::freq_xlating_fir_filter_ccf::make(audio_decim, taps, 0, channel_rate);

    //mixer
    auto mul = gr::blocks::multiply_cc::make();
    auto bfo = gr::analog::sig_source_c::make(channel_rate/audio_decim,gr::analog::GR_SIN_WAVE,1500.0,1.0);

    auto c2f = gr::blocks::complex_to_float::make();
    auto add = gr::blocks::add_ff::make();

    connect(self(), 0, d_xfir, 0);
    connect(bfo, 0, mul, 0);
    connect(d_xfir, 0, mul, 1);
    connect(mul, 0, c2f, 0);
    connect(c2f, 0, add, 0);
    connect(c2f, 1, add, 1);
    connect(add, 0, self(), 0);
}

/*
     * Our virtual destructor.
     */
weaver_impl::~weaver_impl()
{
}

void weaver_impl::set_center_frequency(double center_frequency) {
    printf("serwer\n");
    d_xfir->set_center_freq(center_frequency);
}


} /* namespace sm6wjm */
} /* namespace gr */

