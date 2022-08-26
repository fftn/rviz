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

#ifndef MOSCPP_MOSOUT_APPENDER_H
#define MOSCPP_MOSOUT_APPENDER_H

#include "mos_message_forward.h"
#include "mos_common.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/weak_ptr.hpp>

#include <boost/thread.hpp>

namespace mosgraph_msgs
{
MOS_DECLARE_MESSAGE(Log);
}

namespace mos
{

class Publication;
typedef boost::shared_ptr<Publication> PublicationPtr;
typedef boost::weak_ptr<Publication> PublicationWPtr;

class MOSCPP_DECL MOSOutAppender : public mos::console::LogAppender
{
public:
  MOSOutAppender();
  ~MOSOutAppender();

  const std::string& getLastError() const;

  virtual void log(::mos::console::Level level, const char* str, const char* file, const char* function, int line);

protected:
  void logThread();

  std::string last_error_;

  typedef std::vector<mosgraph_msgs::LogPtr> V_Log;
  V_Log log_queue_;
  boost::mutex queue_mutex_;
  boost::condition_variable queue_condition_;
  bool shutting_down_;
  bool disable_topics_;

  boost::thread publish_thread_;
};

} // namespace mos

#endif
