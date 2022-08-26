/*
 * Copyright (c) 2013, Open Source Robotics Foundation
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

#ifndef MOSCONSOLE_CONSOLE_BACKEND_H
#define MOSCONSOLE_CONSOLE_BACKEND_H

#include "mos_macros.h"

// Import/export for windows dll's and visibility for gcc shared libraries.
#ifdef MOS_BUILD_SHARED_LIBS // mos is being built around shared libraries
  #ifdef mosconsole_backend_interface_EXPORTS // we are building a shared lib/dll
    #define MOSCONSOLE_BACKEND_DECL MOS_HELPER_EXPORT
  #else // we are using shared lib/dll
    #define MOSCONSOLE_BACKEND_DECL MOS_HELPER_IMPORT
  #endif
#else // mos is being built around static libraries
  #define MOSCONSOLE_BACKEND_DECL
#endif

namespace mos
{
namespace console
{

namespace levels
{
enum Level
{
  Debug,
  Info,
  Warn,
  Error,
  Fatal,

  Count
};
}
typedef levels::Level Level;

namespace backend
{

MOSCONSOLE_BACKEND_DECL void notifyLoggerLevelsChanged();

MOSCONSOLE_BACKEND_DECL extern void (*function_notifyLoggerLevelsChanged)();

MOSCONSOLE_BACKEND_DECL void print(void* logger_handle, ::mos::console::Level level, const char* str, const char* file, const char* function, int line);

MOSCONSOLE_BACKEND_DECL extern void (*function_print)(void*, ::mos::console::Level, const char*, const char*, const char*, int);

} // namespace backend
} // namespace console
} // namespace mos

#endif // MOSCONSOLE_CONSOLE_BACKEND_H
