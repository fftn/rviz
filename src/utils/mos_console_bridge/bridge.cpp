/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2011, Willow Garage, Inc.
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

/* Author: Ioan Sucan */

#include "mos_console.h"
#include "mos_console_bridge/console.h"
#include "mos_console_bridge/bridge.h"

namespace mosconsole_bridge
{

OutputHandlerMOS::OutputHandlerMOS(void) : OutputHandler()
{
}

void OutputHandlerMOS::log(const std::string &text, console_bridge::LogLevel level, const char *filename, int line)
{
  std::string prefix;

  // Check for fake subprefix name defined as text output "package.prefix: message"
  // Rejects something like "foo bar: message" because of the space
  static const std::string NEEDLE_STRING = ": ";
  size_t sub_index = text.find(NEEDLE_STRING);
  size_t space_index = text.find(" ");

  if (sub_index != std::string::npos && // needle is found
      sub_index > 0 && // does not start with needle
      space_index > sub_index && // no spaces before needle (": ")
      text.length() > space_index + 1) // remaining text is not empty
  {
    prefix = std::string(MOSCONSOLE_NAME_PREFIX) + "." + text.substr(0, sub_index);
    // update the sub_index to allow us to later remove the prefix from the message
    sub_index += NEEDLE_STRING.length();
  }
  else
  {
    prefix = std::string(MOSCONSOLE_NAME_PREFIX) + ".console_bridge";
    sub_index = 0;
  }

  // Handle different logging levels
  switch (level)
  {
  case console_bridge::CONSOLE_BRIDGE_LOG_INFO:
    {
      MOSCONSOLE_DEFINE_LOCATION(true, ::mos::console::levels::Info, prefix);
      if (MOS_UNLIKELY(__mosconsole_define_location__enabled))
      {
        ::mos::console::print(NULL, __mosconsole_define_location__loc.logger_, __mosconsole_define_location__loc.level_, filename, line, "", "%s",
          text.substr(sub_index, std::string::npos).c_str());
      }
    }
    break;
  case console_bridge::CONSOLE_BRIDGE_LOG_WARN:
    {
      MOSCONSOLE_DEFINE_LOCATION(true, ::mos::console::levels::Warn, prefix);
      if (MOS_UNLIKELY(__mosconsole_define_location__enabled))
      {
        ::mos::console::print(NULL, __mosconsole_define_location__loc.logger_, __mosconsole_define_location__loc.level_, filename, line, "", "%s",
          text.substr(sub_index, std::string::npos).c_str());
      }
    }
    break;
  case console_bridge::CONSOLE_BRIDGE_LOG_ERROR:
    {
      MOSCONSOLE_DEFINE_LOCATION(true, ::mos::console::levels::Error, prefix);
      if (MOS_UNLIKELY(__mosconsole_define_location__enabled))
      {
        ::mos::console::print(NULL, __mosconsole_define_location__loc.logger_, __mosconsole_define_location__loc.level_, filename, line, "", "%s",
          text.substr(sub_index, std::string::npos).c_str());
      }
    }
    break;
  default:
    // debug
    {
      MOSCONSOLE_DEFINE_LOCATION(true, ::mos::console::levels::Debug, prefix);
      if (MOS_UNLIKELY(__mosconsole_define_location__enabled))
      {
        ::mos::console::print(NULL, __mosconsole_define_location__loc.logger_, __mosconsole_define_location__loc.level_, filename, line, "", "%s",
          text.substr(sub_index, std::string::npos).c_str());
      }
    }
    break;
  }
}

RegisterOutputHandlerProxy::RegisterOutputHandlerProxy(void)
{
  static OutputHandlerMOS oh_mos;
  console_bridge::useOutputHandler(&oh_mos);

  // we want the output level to be decided by mosconsole, so we bring all messages to mosconsole
  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_DEBUG);
}

RegisterOutputHandlerProxy::~RegisterOutputHandlerProxy()
{
  console_bridge::restorePreviousOutputHandler();
}

}
