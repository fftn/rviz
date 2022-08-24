/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2009, Willow Garage, Inc.
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#ifndef IMAGE_TRANSPORT_TRANSPORT_HINTS_H
#define IMAGE_TRANSPORT_TRANSPORT_HINTS_H

#include "mos.h"

namespace image_transport {

/**
 * \brief Stores transport settings for an image topic subscription.
 */
class TransportHints
{
public:
  /**
   * \brief Constructor.
   *
   * The default transport can be overridden by setting a certain parameter to the
   * name of the desired transport. By default this parameter is named "image_transport"
   * in the node's local namespace. For consistency across MOS applications, the
   * name of this parameter should not be changed without good reason.
   *
   * @param default_transport Preferred transport to use
   * @param mos_hints Hints to pass through to MOS subscriptions
   * @param parameter_nh Node handle to use when looking up the transport parameter.
   * Defaults to the local namespace.
   * @param parameter_name The name of the transport parameter
   */
  TransportHints(const std::string& default_transport = "raw",
                 const mos::TransportHints& mos_hints = mos::TransportHints(),
                 const mos::NodeHandle& parameter_nh = mos::NodeHandle("~"),
                 const std::string& parameter_name = "image_transport")
    : mos_hints_(mos_hints), parameter_nh_(parameter_nh)
  {
    parameter_nh_.param(parameter_name, transport_, default_transport);
  }

  const std::string& getTransport() const
  {
    return transport_;
  }

  const mos::TransportHints& getMosHints() const
  {
    return mos_hints_;
  }

  const mos::NodeHandle& getParameterNH() const
  {
    return parameter_nh_;
  }
  
private:
  std::string transport_;
  mos::TransportHints mos_hints_;
  mos::NodeHandle parameter_nh_;
};

} //namespace image_transport

#endif
