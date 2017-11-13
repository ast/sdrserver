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

#ifndef INCLUDED_SM6WJM_WEAVER_IMPL_H
#define INCLUDED_SM6WJM_WEAVER_IMPL_H

#include "weaver.h"

#include <gnuradio/filter/freq_xlating_fir_filter_ccf.h>

namespace gr {
namespace sm6wjm {

class weaver_impl : public weaver
{
private:
    // Nothing to declare in this block.
    gr::filter::freq_xlating_fir_filter_ccf::sptr d_xfir;

public:
    weaver_impl(double channel_rate, int audio_decim, double center_freq);
    ~weaver_impl();

    void set_center_frequency(double center_frequency);
};

} // namespace sm6wjm
} // namespace gr

#endif /* INCLUDED_SM6WJM_WEAVER_IMPL_H */

