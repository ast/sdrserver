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

#ifndef INCLUDED_SM6WJM_QTFFT_IMPL_H
#define INCLUDED_SM6WJM_QTFFT_IMPL_H

#include "qtfft.h"

namespace gr {
  namespace sm6wjm {

    class qtfft_impl : public qtfft
    {
     private:
        int d_vec_length;
        static inline float square (float sum, float x) { return sum + x * x; }

     public:
        qtfft_impl(int vec_length);
        ~qtfft_impl();

        // Where all the action really happens
    };

  } // namespace sm6wjm
} // namespace gr

#endif /* INCLUDED_SM6WJM_QTFFT_IMPL_H */

