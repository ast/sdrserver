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
#include <gnuradio/blocks/stream_to_vector.h>
#include <gnuradio/blocks/keep_one_in_n.h>
#include <gnuradio/fft/fft_vcc.h>
#include <gnuradio/fft/window.h>
#include <gnuradio/blocks/nlog10_ff.h>
#include <gnuradio/blocks/complex_to_mag_squared.h>
#include <gnuradio/filter/single_pole_iir_filter_ff.h>

#include <cmath>
#include <numeric>

#include "qtfft_impl.h"

namespace gr {
  namespace sm6wjm {

    qtfft::sptr
    qtfft::make(int vec_length)
    {
      return gnuradio::get_initial_sptr
        (new qtfft_impl(vec_length));
    }

    qtfft_impl::qtfft_impl(int vec_length)
        : gr::hier_block2("qtfft",
                          gr::io_signature::make(1, 1, sizeof(gr_complex)),
                          gr::io_signature::make(1, 1, sizeof(float) * vec_length)),
          d_vec_length(vec_length)
    {
        //fprintf(stderr, "%d\n", d_vec_length);

        auto stv = gr::blocks::stream_to_vector::make(sizeof(gr_complex), d_vec_length);
        auto decim = gr::blocks::keep_one_in_n::make(sizeof(gr_complex) * d_vec_length, 4);

        std::vector<float> win = gr::fft::window::blackmanharris(d_vec_length);
        float win_power = std::accumulate(win.begin(), win.end(), 0., square);
        auto fft = gr::fft::fft_vcc::make(vec_length, true, win, true, 2);
        auto mag_squared = gr::blocks::complex_to_mag_squared::make(d_vec_length);
        auto avg = gr::filter::single_pole_iir_filter_ff::make(0.7, d_vec_length);

        float k = -20*log10f(d_vec_length) - 10*log10f(win_power/d_vec_length);
        auto log_power = gr::blocks::nlog10_ff::make(10.0, d_vec_length, k);

        connect(self(), 0, stv, 0);
        connect(stv, 0, decim, 0);
        connect(decim, 0, fft, 0);
        connect(fft, 0, mag_squared, 0);
        connect(mag_squared, 0, avg, 0);
        connect(avg, 0, log_power, 0);
        connect(log_power, 0, self(), 0);
    }

    /*
     * Our virtual destructor.
     */
    qtfft_impl::~qtfft_impl()
    {
    }


  } /* namespace sm6wjm */
} /* namespace gr */

