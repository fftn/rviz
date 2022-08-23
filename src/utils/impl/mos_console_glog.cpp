#include "mos_console.h"
#define MOSCONSOLE_CONSOLE_IMPL_EXPORTS
#include "mos/console_impl.h"

#include <glog/logging.h>

namespace mos
{
namespace console
{
namespace impl
{

std::vector<std::pair<std::string, levels::Level> > mosconsole_glog_log_levels;
LogAppender* mosconsole_glog_appender = 0;

void initialize()
{
  google::InitGoogleLogging("mosconsole");
}

void print(void* handle, ::mos::console::Level level, const char* str, const char* file, const char* function, int line)
{
  // still printing to console
  ::mos::console::backend::print(0, level, str, file, function, line);

  // pass log message to appender
  if(mosconsole_glog_appender)
  {
    mosconsole_glog_appender->log(level, str, file, function, line);
  }

  google::LogSeverity glog_level;
  if(level == ::mos::console::levels::Info)
  {
    glog_level = google::GLOG_INFO;
  }
  else if(level == ::mos::console::levels::Warn)
  {
    glog_level = google::GLOG_WARNING;
  }
  else if(level == ::mos::console::levels::Error)
  {
    glog_level = google::GLOG_ERROR;
  }
  else if(level == ::mos::console::levels::Fatal)
  {
    glog_level = google::GLOG_FATAL;
  }
  else
  {
    // ignore debug
    return;
  }
  std::string name = getName(handle);
  google::LogMessage(file, line, glog_level).stream() << name << ": " << str;
}

bool isEnabledFor(void* handle, ::mos::console::Level level)
{
  size_t index = (size_t)handle;
  if(index < mosconsole_glog_log_levels.size())
  {
    return level >= mosconsole_glog_log_levels[index].second;
  }
  return false;
}

void* getHandle(const std::string& name)
{
  size_t count = mosconsole_glog_log_levels.size();
  for(size_t index = 0; index < count; index++)
  {
    if(name == mosconsole_glog_log_levels[index].first)
    {
      return (void*)index;
    }
  }
  // add unknown names on demand with default level
  mosconsole_glog_log_levels.push_back(std::pair<std::string, levels::Level>(name, ::mos::console::levels::Info));
  return (void*)(mosconsole_glog_log_levels.size() - 1);
}

std::string getName(void* handle)
{
  size_t index = (size_t)handle;
  if(index < mosconsole_glog_log_levels.size())
  {
    return mosconsole_glog_log_levels[index].first;
  }
  return "";
}

void register_appender(LogAppender* appender)
{
  mosconsole_glog_appender = appender;
}

void deregister_appender(LogAppender* appender)
{
  if(mosconsole_glog_appender == appender)
  {
    mosconsole_glog_appender = 0;
  }
}

void shutdown()
{}

bool get_loggers(std::map<std::string, levels::Level>& loggers)
{
  for(std::vector<std::pair<std::string, levels::Level> >::const_iterator it = mosconsole_glog_log_levels.begin(); it != mosconsole_glog_log_levels.end(); it++)
  {
    loggers[it->first] = it->second;
  }
  return true;
}

bool set_logger_level(const std::string& name, levels::Level level)
{
  for(std::vector<std::pair<std::string, levels::Level> >::iterator it = mosconsole_glog_log_levels.begin(); it != mosconsole_glog_log_levels.end(); it++)
  {
    if(name == it->first)
    {
      it->second = level;
      return true;
    }
  }
  return false;
}

} // namespace impl
} // namespace console
} // namespace mos
