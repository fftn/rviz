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
 *     * Neither the name of Willow Garage, Inc. nor the names of its
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

// Author: Josh Faust

#ifndef MOSCONSOLE_MOSCONSOLE_H
#define MOSCONSOLE_MOSCONSOLE_H

#include "mos_console_backend.h"

#include <cstdio>
#include <sstream>
#include <mos_time.h>
#include <cstdarg>
#include <mos_macros.h>
#include <map>
#include <vector>

#ifdef MOSCONSOLE_BACKEND_LOG4CXX
#include "log4cxx/level.h"
#endif

// Import/export for windows dll's and visibility for gcc shared libraries.

#ifdef MOS_BUILD_SHARED_LIBS // mos is being built around shared libraries
  #ifdef mosconsole_EXPORTS // we are building a shared lib/dll
    #define MOSCONSOLE_DECL MOS_HELPER_EXPORT
  #else // we are using shared lib/dll
    #define MOSCONSOLE_DECL MOS_HELPER_IMPORT
  #endif
#else // mos is being built around static libraries
  #define MOSCONSOLE_DECL
#endif

#ifdef __GNUC__
#if __GNUC__ >= 3
#define MOSCONSOLE_PRINTF_ATTRIBUTE(a, b) __attribute__ ((__format__ (__printf__, a, b)))
#endif
#endif

#ifndef MOSCONSOLE_PRINTF_ATTRIBUTE
#define MOSCONSOLE_PRINTF_ATTRIBUTE(a, b)
#endif

namespace boost
{
template<typename T> class shared_array;
}

namespace mos
{
namespace console
{

MOSCONSOLE_DECL void shutdown();

#ifdef MOSCONSOLE_BACKEND_LOG4CXX
extern MOSCONSOLE_DECL log4cxx::LevelPtr g_level_lookup[];
#endif

extern MOSCONSOLE_DECL bool get_loggers(std::map<std::string, levels::Level>& loggers);
extern MOSCONSOLE_DECL bool set_logger_level(const std::string& name, levels::Level level);

/**
 * \brief Only exported because the macros need it.  Do not use directly.
 */
extern MOSCONSOLE_DECL bool g_initialized;

/**
 * \brief Only exported because the TopicManager need it.  Do not use directly.
 */
extern MOSCONSOLE_DECL std::string g_last_error_message;

class LogAppender
{
public:

  virtual ~LogAppender() {}

  virtual void log(::mos::console::Level level, const char* str, const char* file, const char* function, int line) = 0;

};

MOSCONSOLE_DECL void register_appender(LogAppender* appender);

MOSCONSOLE_DECL void deregister_appender(LogAppender* appender);

struct Token
{
  virtual ~Token() {}
  /*
   * @param level
   * @param message
   * @param file
   * @param function
   * @param  line
   */
  virtual std::string getString(void*, ::mos::console::Level, const char*, const char*, const char*, int) = 0;
};
typedef boost::shared_ptr<Token> TokenPtr;
typedef std::vector<TokenPtr> V_Token;

struct Formatter
{
  void init(const char* fmt);
  void print(void* logger_handle, ::mos::console::Level level, const char* str, const char* file, const char* function, int line);
  std::string format_;
  V_Token tokens_;
};

/**
 * \brief Only exported because the implementation need it.  Do not use directly.
 */
extern MOSCONSOLE_DECL Formatter g_formatter;

/**
 * \brief Don't call this directly.  Performs any required initialization/configuration.  Happens automatically when using the macro API.
 *
 * If you're going to be using log4cxx or any of the ::mos::console functions, and need the system to be initialized, use the
 * MOSCONSOLE_AUTOINIT macro.
 */
MOSCONSOLE_DECL void initialize();

class FilterBase;
/**
 * \brief Don't call this directly.  Use the MOS_LOG() macro instead.
 * @param level Logging level
 * @param file File this logging statement is from (usually generated with __FILE__)
 * @param line Line of code this logging statement is from (usually generated with __LINE__)
 * @param fmt Format string
 */
MOSCONSOLE_DECL void print(FilterBase* filter, void* logger, Level level,
	   const char* file, int line, 
	   const char* function, const char* fmt, ...) MOSCONSOLE_PRINTF_ATTRIBUTE(7, 8);

MOSCONSOLE_DECL void print(FilterBase* filter, void* logger, Level level,
	   const std::stringstream& str, const char* file, int line, const char* function);

struct MOSCONSOLE_DECL LogLocation;

/**
 * \brief Registers a logging location with the system.
 *
 * This is used for the case where a logger's verbosity level changes, and we need to reset the enabled status of
 * all the logging statements.
 * @param loc The location to add
 */
MOSCONSOLE_DECL void registerLogLocation(LogLocation* loc);

/**
 * \brief Tells the system that a logger's level has changed
 *
 * This must be called if a log4cxx::Logger's level has been changed in the middle of an application run.
 * Because of the way the static guard for enablement works, if a logger's level is changed and this
 * function is not called, only logging statements which are first hit *after* the change will be correct wrt
 * that logger.
 */
MOSCONSOLE_DECL void notifyLoggerLevelsChanged();

MOSCONSOLE_DECL void setFixedFilterToken(const std::string& key, const std::string& val);

/**
 * \brief Parameter structure passed to FilterBase::isEnabled(...);.  Includes both input and output parameters
 */
struct FilterParams
{
  // input parameters
  const char* file;                         ///< [input] File the message came from
  int line;                                 ///< [input] Line the message came from
  const char* function;                     ///< [input] Function the message came from
  const char* message;                      ///< [input] The formatted message that will be output

  // input/output parameters
  void* logger;                             ///< [input/output] Handle identifying logger that this message will be output to.  If changed, uses the new logger
  Level level;                              ///< [input/output] Severity level.  If changed, uses the new level

  // output parameters
  std::string out_message;                  ///< [output] If set, writes this message instead of the original
};

/**
 * \brief Base-class for filters.  Filters allow full user-defined control over whether or not a message should print.
 * The MOS_X_FILTER... macros provide the filtering functionality.
 *
 * Filters get a chance to veto the message from printing at two times: first before the message arguments are
 * evaluated and the message is formatted, and then once the message is formatted before it is printed.  It is also possible
 * to change the message, logger and severity level at this stage (see the FilterParams struct for more details).
 *
 * When a MOS_X_FILTER... macro is called, here is the high-level view of how it uses the filter passed in:
\verbatim
if (<logging level is enabled> && filter->isEnabled())
{
  <format message>
  <fill out FilterParams>
  if (filter->isEnabled(params))
  {
    <print message>
  }
}
\endverbatim
 */
class FilterBase
{
public:
  virtual ~FilterBase() {}
  /**
   * \brief Returns whether or not the log statement should be printed.  Called before the log arguments are evaluated
   * and the message is formatted.
   */
  inline virtual bool isEnabled() { return true; }
  /**
   * \brief Returns whether or not the log statement should be printed.  Called once the message has been formatted,
   * and allows you to change the message, logger and severity level if necessary.
   */
  inline virtual bool isEnabled(FilterParams&) { return true; }
};

struct MOSCONSOLE_DECL LogLocation;
/**
 * \brief Internal
 */
MOSCONSOLE_DECL void initializeLogLocation(LogLocation* loc, const std::string& name, Level level);
/**
 * \brief Internal
 */
MOSCONSOLE_DECL void setLogLocationLevel(LogLocation* loc, Level level);
/**
 * \brief Internal
 */
MOSCONSOLE_DECL void checkLogLocationEnabled(LogLocation* loc);

/**
 * \brief Internal
 */
struct LogLocation
{
  bool initialized_;
  bool logger_enabled_;
  ::mos::console::Level level_;
  void* logger_;
};

MOSCONSOLE_DECL void vformatToBuffer(boost::shared_array<char>& buffer, size_t& buffer_size, const char* fmt, va_list args);
MOSCONSOLE_DECL void formatToBuffer(boost::shared_array<char>& buffer, size_t& buffer_size, const char* fmt, ...);
MOSCONSOLE_DECL std::string formatToString(const char* fmt, ...);

} // namespace console
} // namespace mos

#ifdef WIN32
#define MOS_LIKELY(x)       (x)
#define MOS_UNLIKELY(x)     (x)
#else
#define MOS_LIKELY(x)       __builtin_expect((x),1)
#define MOS_UNLIKELY(x)     __builtin_expect((x),0)
#endif

#if defined(MSVC)
  #define __MOSCONSOLE_FUNCTION__ __FUNCSIG__
#elif defined(__GNUC__)
  #define __MOSCONSOLE_FUNCTION__ __PRETTY_FUNCTION__
#else
  #define __MOSCONSOLE_FUNCTION__ ""
#endif


#ifdef MOS_PACKAGE_NAME
#define MOSCONSOLE_PACKAGE_NAME MOS_PACKAGE_NAME
#else
#define MOSCONSOLE_PACKAGE_NAME "unknown_package"
#endif

#define MOSCONSOLE_ROOT_LOGGER_NAME "mos"
#define MOSCONSOLE_NAME_PREFIX MOSCONSOLE_ROOT_LOGGER_NAME "." MOSCONSOLE_PACKAGE_NAME
#define MOSCONSOLE_DEFAULT_NAME MOSCONSOLE_NAME_PREFIX

// These allow you to compile-out everything below a certain severity level if necessary
#define MOSCONSOLE_SEVERITY_DEBUG 0
#define MOSCONSOLE_SEVERITY_INFO 1
#define MOSCONSOLE_SEVERITY_WARN 2
#define MOSCONSOLE_SEVERITY_ERROR 3
#define MOSCONSOLE_SEVERITY_FATAL 4
#define MOSCONSOLE_SEVERITY_NONE 5

/**
 * \def MOSCONSOLE_MIN_SEVERITY
 *
 * Define MOSCONSOLE_MIN_SEVERITY=MOSCONSOLE_SEVERITY_[DEBUG|INFO|WARN|ERROR|FATAL] in your build options to compile out anything below that severity
 */
#ifndef MOSCONSOLE_MIN_SEVERITY
#define MOSCONSOLE_MIN_SEVERITY MOSCONSOLE_SEVERITY_DEBUG
#endif

/**
 * \def MOSCONSOLE_AUTOINIT
 * \brief Initializes the mosconsole library.  Usually unnecessary to call directly.
 */
#define MOSCONSOLE_AUTOINIT \
  do \
  { \
    if (MOS_UNLIKELY(!::mos::console::g_initialized)) \
    { \
      ::mos::console::initialize(); \
    } \
  } while(false)

#define MOSCONSOLE_DEFINE_LOCATION(cond, level, name) \
  MOSCONSOLE_AUTOINIT; \
  static ::mos::console::LogLocation __mosconsole_define_location__loc = {false, false, ::mos::console::levels::Count, NULL}; /* Initialized at compile-time */ \
  if (MOS_UNLIKELY(!__mosconsole_define_location__loc.initialized_)) \
  { \
    initializeLogLocation(&__mosconsole_define_location__loc, name, level); \
  } \
  if (MOS_UNLIKELY(__mosconsole_define_location__loc.level_ != level)) \
  { \
    setLogLocationLevel(&__mosconsole_define_location__loc, level); \
    checkLogLocationEnabled(&__mosconsole_define_location__loc); \
  } \
  bool __mosconsole_define_location__enabled = __mosconsole_define_location__loc.logger_enabled_ && (cond);

#define MOSCONSOLE_PRINT_AT_LOCATION_WITH_FILTER(filter, ...) \
    ::mos::console::print(filter, __mosconsole_define_location__loc.logger_, __mosconsole_define_location__loc.level_, __FILE__, __LINE__, __MOSCONSOLE_FUNCTION__, __VA_ARGS__)

#define MOSCONSOLE_PRINT_AT_LOCATION(...) \
    MOSCONSOLE_PRINT_AT_LOCATION_WITH_FILTER(NULL, __VA_ARGS__)

// inside a macro which uses args use only well namespaced variable names in order to not overlay variables coming in via args
#define MOSCONSOLE_PRINT_STREAM_AT_LOCATION_WITH_FILTER(filter, args) \
  do \
  { \
    std::stringstream __mosconsole_print_stream_at_location_with_filter__ss__; \
    __mosconsole_print_stream_at_location_with_filter__ss__ << args; \
    ::mos::console::print(filter, __mosconsole_define_location__loc.logger_, __mosconsole_define_location__loc.level_, __mosconsole_print_stream_at_location_with_filter__ss__, __FILE__, __LINE__, __MOSCONSOLE_FUNCTION__); \
  } while (0)

#define MOSCONSOLE_PRINT_STREAM_AT_LOCATION(args) \
    MOSCONSOLE_PRINT_STREAM_AT_LOCATION_WITH_FILTER(NULL, args)

/**
 * \brief Used internally in throttle macros to determine if a new message should be logged.
 * \note If MOS time has moved backwards, will evaluate to true
 */
#define MOSCONSOLE_THROTTLE_CHECK(now, last, period) (MOS_UNLIKELY(last + period <= now) || MOS_UNLIKELY(now < last))

/**
 * \brief Log to a given named logger at a given verbosity level, only if a given condition has been met, with printf-style formatting
 *
 * \note The condition will only be evaluated if this logging statement is enabled
 *
 * \param cond Boolean condition to be evaluated
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define MOS_LOG_COND(cond, level, name, ...) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(cond, level, name); \
    \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled)) \
    { \
      MOSCONSOLE_PRINT_AT_LOCATION(__VA_ARGS__); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, only if a given condition has been met, with stream-style formatting
 *
 * \note The condition will only be evaluated if this logging statement is enabled
 *
 * \param cond Boolean condition to be evaluated
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define MOS_LOG_STREAM_COND(cond, level, name, args) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(cond, level, name); \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled)) \
    { \
      MOSCONSOLE_PRINT_STREAM_AT_LOCATION(args); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, only the first time it is hit when enabled, with printf-style formatting
 *
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define MOS_LOG_ONCE(level, name, ...) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(true, level, name); \
    static bool hit = false; \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled) && MOS_UNLIKELY(!hit)) \
    { \
      hit = true; \
      MOSCONSOLE_PRINT_AT_LOCATION(__VA_ARGS__); \
    } \
  } while(false)

// inside a macro which uses args use only well namespaced variable names in order to not overlay variables coming in via args
/**
 * \brief Log to a given named logger at a given verbosity level, only the first time it is hit when enabled, with printf-style formatting
 *
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define MOS_LOG_STREAM_ONCE(level, name, args) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(true, level, name); \
    static bool __mos_log_stream_once__hit__ = false; \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled) && MOS_UNLIKELY(!__mos_log_stream_once__hit__)) \
    { \
      __mos_log_stream_once__hit__ = true; \
      MOSCONSOLE_PRINT_STREAM_AT_LOCATION(args); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, limited to a specific rate of printing, with printf-style formatting
 *
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 * \param period The period it should actually trigger at most. If MOS time has moved backwards, it will trigger regardless.
 */
#define MOS_LOG_THROTTLE(period, level, name, ...) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(true, level, name); \
    static double __mos_log_throttle_last_hit__ = 0.0; \
    double __mos_log_throttle_now__ = ::mos::Time::now().toSec(); \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled) && MOSCONSOLE_THROTTLE_CHECK(__mos_log_throttle_now__, __mos_log_throttle_last_hit__, period))\
    { \
      __mos_log_throttle_last_hit__ = __mos_log_throttle_now__; \
      MOSCONSOLE_PRINT_AT_LOCATION(__VA_ARGS__); \
    } \
  } while(false)

// inside a macro which uses args use only well namespaced variable names in order to not overlay variables coming in via args
/**
 * \brief Log to a given named logger at a given verbosity level, limited to a specific rate of printing, with printf-style formatting
 *
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 * \param period The period it should actually trigger at most. If MOS time has moved backwards, it will trigger regardless.
 */
#define MOS_LOG_STREAM_THROTTLE(period, level, name, args) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(true, level, name); \
    static double __mos_log_stream_throttle__last_hit__ = 0.0; \
    double __mos_log_stream_throttle__now__ = ::mos::Time::now().toSec(); \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled) && \
        MOSCONSOLE_THROTTLE_CHECK(__mos_log_stream_throttle__now__, __mos_log_stream_throttle__last_hit__, period))\
    { \
      __mos_log_stream_throttle__last_hit__ = __mos_log_stream_throttle__now__; \
      MOSCONSOLE_PRINT_STREAM_AT_LOCATION(args); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, limited to a specific rate of printing, with printf-style formatting
 *
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 * \param period The period it should actually trigger at most, and the delay before which no message will be shown. If MOS time has moved backwards, it will trigger regardless.
 */
#define MOS_LOG_DELAYED_THROTTLE(period, level, name, ...) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(true, level, name); \
    double __mos_log_delayed_throttle__now__ = ::mos::Time::now().toSec(); \
    static double __mos_log_delayed_throttle__last_hit__ = __mos_log_delayed_throttle__now__; \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled) && \
        MOSCONSOLE_THROTTLE_CHECK(__mos_log_delayed_throttle__now__, __mos_log_delayed_throttle__last_hit__, period))\
    { \
      __mos_log_delayed_throttle__last_hit__ = __mos_log_delayed_throttle__now__; \
      MOSCONSOLE_PRINT_AT_LOCATION(__VA_ARGS__); \
    } \
  } while(false)

// inside a macro which uses args use only well namespaced variable names in order to not overlay variables coming in via args
/**
 * \brief Log to a given named logger at a given verbosity level, limited to a specific rate of printing and postponed first message
 *
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 * \param period The period it should actually trigger at most, and the delay before which no message will be shown. If MOS time has moved backwards, it will trigger regardless.
 */
#define MOS_LOG_STREAM_DELAYED_THROTTLE(period, level, name, args) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(true, level, name); \
    double __mos_log_stream_delayed_throttle__now__ = ::mos::Time::now().toSec(); \
    static double __mos_log_stream_delayed_throttle__last_hit__ = __mos_log_stream_delayed_throttle__now__; \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled) && \
        MOSCONSOLE_THROTTLE_CHECK(__mos_log_stream_delayed_throttle__now__, __mos_log_stream_delayed_throttle__last_hit__, period)) \
    { \
      __mos_log_stream_delayed_throttle__last_hit__ = __mos_log_stream_delayed_throttle__now__; \
      MOSCONSOLE_PRINT_STREAM_AT_LOCATION(args); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, with user-defined filtering, with printf-style formatting
 *
 * \param filter pointer to the filter to be used
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define MOS_LOG_FILTER(filter, level, name, ...) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(true, level, name); \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled) && (filter)->isEnabled()) \
    { \
      MOSCONSOLE_PRINT_AT_LOCATION_WITH_FILTER(filter, __VA_ARGS__); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, with user-defined filtering, with stream-style formatting
 *
 * \param cond Boolean condition to be evaluated
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define MOS_LOG_STREAM_FILTER(filter, level, name, args) \
  do \
  { \
    MOSCONSOLE_DEFINE_LOCATION(true, level, name); \
    if (MOS_UNLIKELY(__mosconsole_define_location__enabled) && (filter)->isEnabled()) \
    { \
      MOSCONSOLE_PRINT_STREAM_AT_LOCATION_WITH_FILTER(filter, args); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, with printf-style formatting
 *
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define MOS_LOG(level, name, ...) MOS_LOG_COND(true, level, name, __VA_ARGS__)
/**
 * \brief Log to a given named logger at a given verbosity level, with stream-style formatting
 *
 * \param level One of the levels specified in ::mos::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "mos.<package_name>".  Use MOSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define MOS_LOG_STREAM(level, name, args) MOS_LOG_STREAM_COND(true, level, name, args)

#include "mos_macros_generated.h"

#endif // MOSCONSOLE_MOSCONSOLE_H
