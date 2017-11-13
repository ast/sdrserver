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

#ifndef INCLUDED_SM6WJM_QTFFT_SINK_IMPL_H
#define INCLUDED_SM6WJM_QTFFT_SINK_IMPL_H

#include "qtfft_sink.h"

extern "C" {
#include <sys/socket.h>
#include <sys/un.h>
}

namespace gr {
namespace sm6wjm {

class qtfft_sink_impl : public qtfft_sink
{
private:
    const int d_send_buf_periods = 4;
    int d_vec_length;
    char *d_socketpath = "/tmp/sdrserver";
    int d_socket = 0;
    struct sockaddr_un d_addr;
    struct sockaddr_un d_client_addr;

public:
    qtfft_sink_impl(int vec_length);
    ~qtfft_sink_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star &input_items,
             gr_vector_void_star &output_items);
};

} // namespace sm6wjm
} // namespace gr

#endif /* INCLUDED_SM6WJM_QTFFT_SINK_IMPL_H */

