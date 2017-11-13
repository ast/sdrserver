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


#ifndef INCLUDED_SM6WJM_FM_DEMOD_H
#define INCLUDED_SM6WJM_FM_DEMOD_H

#include <gr/api.h>
#include <gnuradio/hier_block2.h>

namespace gr {
  namespace sm6wjm {

    /*!
     * \brief <+description of block+>
     * \ingroup sm6wjm
     *
     */
    class SM6WJM_API fm_demod : virtual public gr::hier_block2
    {
     public:
      typedef boost::shared_ptr<fm_demod> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of sm6wjm::fm_demod.
       *
       * To avoid accidental use of raw pointers, sm6wjm::fm_demod's
       * constructor is in a private implementation
       * class. sm6wjm::fm_demod::make is the public interface for
       * creating new instances.
       */
      static sptr make(float channel_rate, int audio_decim, float deviation, float audio_pass, float audio_stop, float gain=1.0, float tau=75e-6);
    };

  } // namespace sm6wjm
} // namespace gr

#endif /* INCLUDED_SM6WJM_FM_DEMOD_H */

