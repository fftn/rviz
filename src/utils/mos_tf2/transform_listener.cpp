/*
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \author Tully Foote */

#include "mos_tf2/transform_listener.h"


using namespace tf2_mos;


TransformListener::TransformListener(tf2::BufferCore& buffer, bool spin_thread, mos::TransportHints transport_hints):
  dedicated_listener_thread_(NULL), buffer_(buffer), using_dedicated_thread_(false), transport_hints_(transport_hints)
{
  if (spin_thread)
    initWithThread();
  else
    init();
}

TransformListener::TransformListener(tf2::BufferCore& buffer, const mos::NodeHandle& nh, bool spin_thread,
    mos::TransportHints transport_hints)
: dedicated_listener_thread_(NULL)
, node_(nh)
, buffer_(buffer)
, using_dedicated_thread_(false)
, transport_hints_(transport_hints)
{
  if (spin_thread)
    initWithThread();
  else
    init();
}

TransformListener::~TransformListener()
{
  using_dedicated_thread_ = false;
  if (dedicated_listener_thread_)
  {
    dedicated_listener_thread_->join();
    delete dedicated_listener_thread_;
  }
}

void TransformListener::init()
{
  message_subscriber_tf_ = node_.subscribe<tf2_msgs::TFMessage>("/tf", 100, boost::bind(&TransformListener::subscription_callback, this, _1), mos::VoidConstPtr(), transport_hints_); ///\todo magic number
  message_subscriber_tf_static_ = node_.subscribe<tf2_msgs::TFMessage>("/tf_static", 100, boost::bind(&TransformListener::static_subscription_callback, this, _1)); ///\todo magic number
}

void TransformListener::initWithThread()
{
  using_dedicated_thread_ = true;
  mos::SubscribeOptions ops_tf = mos::SubscribeOptions::create<tf2_msgs::TFMessage>("/tf", 100, boost::bind(&TransformListener::subscription_callback, this, _1), mos::VoidPtr(), &tf_message_callback_queue_); ///\todo magic number
  ops_tf.transport_hints = transport_hints_;
  message_subscriber_tf_ = node_.subscribe(ops_tf);
  
  mos::SubscribeOptions ops_tf_static = mos::SubscribeOptions::create<tf2_msgs::TFMessage>("/tf_static", 100, boost::bind(&TransformListener::static_subscription_callback, this, _1), mos::VoidPtr(), &tf_message_callback_queue_); ///\todo magic number
  message_subscriber_tf_static_ = node_.subscribe(ops_tf_static);

  dedicated_listener_thread_ = new boost::thread(boost::bind(&TransformListener::dedicatedListenerThread, this));

  //Tell the buffer we have a dedicated thread to enable timeouts
  buffer_.setUsingDedicatedThread(true);
}



void TransformListener::subscription_callback(const mos::MessageEvent<tf2_msgs::TFMessage const>& msg_evt)
{
  subscription_callback_impl(msg_evt, false);
}
void TransformListener::static_subscription_callback(const mos::MessageEvent<tf2_msgs::TFMessage const>& msg_evt)
{
  subscription_callback_impl(msg_evt, true);
}

void TransformListener::subscription_callback_impl(const mos::MessageEvent<tf2_msgs::TFMessage const>& msg_evt, bool is_static)
{
  mos::Time now = mos::Time::now();
  if(now < last_update_){
    MOS_WARN_STREAM("Detected jump back in time of " << (last_update_ - now).toSec() << "s. Clearing TF buffer.");
    buffer_.clear();
  }
  last_update_ = now;



  const tf2_msgs::TFMessage& msg_in = *(msg_evt.getConstMessage());
  std::string authority = msg_evt.getPublisherName(); // lookup the authority
  for (unsigned int i = 0; i < msg_in.transforms.size(); i++)
  {
    try
    {
      buffer_.setTransform(msg_in.transforms[i], authority, is_static);
    }
    
    catch (tf2::TransformException& ex)
    {
      ///\todo Use error reporting
      std::string temp = ex.what();
      MOS_ERROR("Failure to set recieved transform from %s to %s with error: %s\n", msg_in.transforms[i].child_frame_id.c_str(), msg_in.transforms[i].header.frame_id.c_str(), temp.c_str());
    }
  }
};




