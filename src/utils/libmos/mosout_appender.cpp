/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
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
 *   * Neither the name of Willow Garage, Inc. nor the names of its
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
 */

#include "mos_mosout_appender.h"
#include "mos_this_node.h"
#include "mos_node_handle.h"
#include "mos_topic_manager.h"
#include "mos_advertise_options.h"
#include "mos_names.h"
#include "mos_param.h"

#include "mos_graph_msgs/Log.h"

namespace mos
{

MOSOutAppender::MOSOutAppender()
: shutting_down_(false)
, disable_topics_(false)
, publish_thread_(boost::bind(&MOSOutAppender::logThread, this))
{
  AdvertiseOptions ops;
  ops.init<mosgraph_msgs::Log>(names::resolve("/mosout"), 0);
  ops.latch = true;
  SubscriberCallbacksPtr cbs(boost::make_shared<SubscriberCallbacks>());
  TopicManager::instance()->advertise(ops, cbs);
}

MOSOutAppender::~MOSOutAppender()
{
  shutting_down_ = true;

  {
    boost::mutex::scoped_lock lock(queue_mutex_);
    queue_condition_.notify_all();
  }

  publish_thread_.join();
}

const std::string&  MOSOutAppender::getLastError() const
{
  return last_error_;
}

void MOSOutAppender::log(::mos::console::Level level, const char* str, const char* file, const char* function, int line)
{
  mosgraph_msgs::LogPtr msg(boost::make_shared<mosgraph_msgs::Log>());

  msg->header.stamp = mos::Time::now();
  if (level == mos::console::levels::Debug)
  {
    msg->level = mosgraph_msgs::Log::DEBUG;
  }
  else if (level == mos::console::levels::Info)
  {
    msg->level = mosgraph_msgs::Log::INFO;
  }
  else if (level == mos::console::levels::Warn)
  {
    msg->level = mosgraph_msgs::Log::WARN;
  }
  else if (level == mos::console::levels::Error)
  {
    msg->level = mosgraph_msgs::Log::ERROR;
  }
  else if (level == mos::console::levels::Fatal)
  {
    msg->level = mosgraph_msgs::Log::FATAL;
  }
  msg->name = this_node::getName();
  msg->msg = str;
  msg->file = file;
  msg->function = function;
  msg->line = line;
  
  // check parameter server/cache for omit_topics flag
  // the same parameter is checked in mosout.py for the same purpose
  mos::param::getCached("/mosout_disable_topics_generation", disable_topics_);

  if (!disable_topics_){
    this_node::getAdvertisedTopics(msg->topics);
  }

  if (level == ::mos::console::levels::Fatal || level == ::mos::console::levels::Error)
  {
    last_error_ = str;
  }

  boost::mutex::scoped_lock lock(queue_mutex_);
  log_queue_.push_back(msg);
  queue_condition_.notify_all();
}

void MOSOutAppender::logThread()
{
  while (!shutting_down_)
  {
    V_Log local_queue;

    {
      boost::mutex::scoped_lock lock(queue_mutex_);

      if (shutting_down_)
      {
        return;
      }

      if (log_queue_.empty())
      {
        queue_condition_.wait(lock);
      }

      if (shutting_down_)
      {
        return;
      }

      local_queue.swap(log_queue_);
    }

    V_Log::iterator it = local_queue.begin();
    V_Log::iterator end = local_queue.end();
    for (; it != end; ++it)
    {
      TopicManager::instance()->publish(names::resolve("/mosout"), *(*it));
    }
  }
}

} // namespace mos
