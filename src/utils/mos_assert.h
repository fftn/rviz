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

#ifndef MOSCONSOLE_MOSASSERT_H
#define MOSCONSOLE_MOSASSERT_H

#include "mos_console.h"
#include "mos_static_assert.h"

/** \file */

/** \def MOS_ASSERT(cond)
 * \brief Asserts that the provided condition evaluates to true.
 *
 * If it is false, program execution will abort, with an informative
 * statement about which assertion failed, in what file.  Use MOS_ASSERT
 * instead of assert() itself.
 *
 * If running inside a debugger, MOS_ASSERT will allow you to step past the assertion.
 */

/** \def MOS_ASSERT_MSG(cond, ...)
 * \brief Asserts that the provided condition evaluates to true.
 *
 * If it is false, program execution will abort, with an informative
 * statement about which assertion failed, in what file, and it will print out
 * a printf-style message you define.  Example usage:
 @verbatim
   MOS_ASSERT_MSG(x > 0, "Uh oh, x went negative.  Value = %d", x);
 @endverbatim
 *
 * If running inside a debugger, MOS_ASSERT will allow you to step past the assertion.
 */

/**
 * \def MOS_ASSERT_CMD()
 * \brief Runs a command if the provided condition is false
 *
 * For example:
\verbatim
  MOS_ASSERT_CMD(x > 0, handleError(...));
\endverbatim
 */

/** \def MOS_BREAK()
 * \brief Aborts program execution.
 *
 * Aborts program execution with an informative message stating what file and
 * line it was called from. Use MOS_BREAK instead of calling assert(0) or
 * MOS_ASSERT(0).
 *
 * If running inside a debugger, MOS_BREAK will allow you to step past the breakpoint.
 */

/** \def MOS_ISSUE_BREAK()
 * \brief Always issues a breakpoint instruction.
 *
 * This define is mostly for internal use, but is useful if you want to simply issue a break
 * instruction in a cross-platform way.
 *
 * Currently implemented for Windows (any platform), powerpc64, and x86
 */

#include "mos_platform.h"

#ifdef WIN32
# if defined (__MINGW32__)
#  define MOS_ISSUE_BREAK() DebugBreak();
# else // MSVC
#  define MOS_ISSUE_BREAK() __debugbreak();
# endif
#elif defined(__powerpc64__)
# define MOS_ISSUE_BREAK() asm volatile ("tw 31,1,1");
#elif defined(__i386__) || defined(__ia64__) || defined(__x86_64__)
# define MOS_ISSUE_BREAK() asm("int $3");
#else
# include <stdlib.h>
# define MOS_ISSUE_BREAK() abort();
#endif

#ifndef NDEBUG
#ifndef MOS_ASSERT_ENABLED
#define MOS_ASSERT_ENABLED
#endif
#endif

#ifdef MOS_ASSERT_ENABLED
#define MOS_BREAK() \
  do { \
    MOS_FATAL("BREAKPOINT HIT\n\tfile = %s\n\tline=%d\n", __FILE__, __LINE__); \
    MOS_ISSUE_BREAK() \
  } while (false)

#define MOS_ASSERT(cond) \
  do { \
    if (!(cond)) { \
      MOS_FATAL("ASSERTION FAILED\n\tfile = %s\n\tline = %d\n\tcond = %s\n", __FILE__, __LINE__, #cond); \
      MOS_ISSUE_BREAK() \
    } \
  } while (false)

#define MOS_ASSERT_MSG(cond, ...) \
  do { \
    if (!(cond)) { \
      MOS_FATAL("ASSERTION FAILED\n\tfile = %s\n\tline = %d\n\tcond = %s\n\tmessage = ", __FILE__, __LINE__, #cond); \
      MOS_FATAL(__VA_ARGS__); \
      MOS_FATAL("\n"); \
      MOS_ISSUE_BREAK(); \
    } \
  } while (false)

#define MOS_ASSERT_CMD(cond, cmd) \
  do { \
    if (!(cond)) { \
      cmd; \
    } \
  } while (false)


#else
#define MOS_BREAK()
#define MOS_ASSERT(cond)
#define MOS_ASSERT_MSG(cond, ...)
#define MOS_ASSERT_CMD(cond, cmd)
#endif

#endif // MOSCONSOLE_MOSASSERT_H
