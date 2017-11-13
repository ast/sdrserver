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


#ifndef INCLUDED_SM6WJM_WEAVER_H
#define INCLUDED_SM6WJM_WEAVER_H

#include "api.h"
#include <gnuradio/hier_block2.h>

namespace gr {
namespace sm6wjm {

/*!
     * \brief <+description of block+>
     * \ingroup sm6wjm
     *
     */
class SM6WJM_API weaver : virtual public gr::hier_block2
{
public:
    typedef boost::shared_ptr<weaver> sptr;

    /*!
       * \brief Return a shared_ptr to a new instance of sm6wjm::weaver.
       *
       * To avoid accidental use of raw pointers, sm6wjm::weaver's
       * constructor is in a private implementation
       * class. sm6wjm::weaver::make is the public interface for
       * creating new instances.
       */
    static sptr make(double channel_rate, int audio_decim, double center_freq);

    virtual void set_center_frequency(double center_frequency) = 0;
};

} // namespace sm6wjm
} // namespace gr

#endif /* INCLUDED_SM6WJM_WEAVER_H */

