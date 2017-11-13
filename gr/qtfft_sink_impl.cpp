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
#include "qtfft_sink_impl.h"

namespace gr {
namespace sm6wjm {

qtfft_sink::sptr
qtfft_sink::make(int vec_length)
{
    return gnuradio::get_initial_sptr
            (new qtfft_sink_impl(vec_length));
}

/*
     * The private constructor
     */
qtfft_sink_impl::qtfft_sink_impl(int vec_length)
    : gr::sync_block("qtfft_sink",
                     gr::io_signature::make(1, 1, sizeof(float) * vec_length),
                     gr::io_signature::make(0, 0, 0)),
      d_vec_length(vec_length)
{
    int err;
    d_socket = socket(AF_UNIX, SOCK_DGRAM, 0);

    d_client_addr.sun_family = AF_UNIX;
    strcpy(d_client_addr.sun_path, "/tmp/sdrclient");

    if(d_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int send_buf = d_vec_length * sizeof(float) * d_send_buf_periods;
    err = setsockopt(d_socket, SOL_SOCKET, SO_SNDBUF, &send_buf, sizeof(send_buf));
    if(err < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}

/*
     * Our virtual destructor.
     */
qtfft_sink_impl::~qtfft_sink_impl()
{
    close(d_socket);
}


int
qtfft_sink_impl::work(int noutput_items,
                      gr_vector_const_void_star &input_items,
                      gr_vector_void_star &output_items)
{
    float *in = (float*)input_items[0];

    //fprintf(stderr, "%f\n", in[1024].real());

    int err = 0;
    err = sendto(d_socket,
                 in,
                 d_vec_length * sizeof(float),
                 MSG_DONTWAIT,
                 (struct sockaddr*) &d_client_addr,
                 sizeof(struct sockaddr));

    if(err < 0) {
        //perror("send");
    }

    // TODO: fix me
    return noutput_items;
}


} /* namespace sm6wjm */
} /* namespace gr */

