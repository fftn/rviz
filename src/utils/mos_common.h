/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
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

#ifndef MOSCPP_COMMON_H
#define MOSCPP_COMMON_H

#include <stdint.h>
#include <assert.h>
#include <stddef.h>
#include <string>

#include "mos_assert.h"
#include "mos_forwards.h"
#include "mos_serialized_message.h"

#include <boost/shared_array.hpp>

#define MOS_VERSION_MAJOR 1
#define MOS_VERSION_MINOR 14
#define MOS_VERSION_PATCH 3
#define MOS_VERSION_COMBINED(major, minor, patch) (((major) << 20) | ((minor) << 10) | (patch))
#define MOS_VERSION MOS_VERSION_COMBINED(MOS_VERSION_MAJOR, MOS_VERSION_MINOR, MOS_VERSION_PATCH)

#define MOS_VERSION_GE(major1, minor1, patch1, major2, minor2, patch2) (MOS_VERSION_COMBINED(major1, minor1, patch1) >= MOS_VERSION_COMBINED(major2, minor2, patch2))
#define MOS_VERSION_MINIMUM(major, minor, patch) MOS_VERSION_GE(MOS_VERSION_MAJOR, MOS_VERSION_MINOR, MOS_VERSION_PATCH, major, minor, patch)

#include <mos_macros.h>

// Import/export for windows dll's and visibility for gcc shared libraries.

#ifdef MOS_BUILD_SHARED_LIBS // mos is being built around shared libraries
  #ifdef moscpp_EXPORTS // we are building a shared lib/dll
    #define MOSCPP_DECL MOS_HELPER_EXPORT
  #else // we are using shared lib/dll
    #define MOSCPP_DECL MOS_HELPER_IMPORT
  #endif
#else // mos is being built around static libraries
  #define MOSCPP_DECL
#endif

namespace mos
{

void disableAllSignalsInThisThread();

}

#endif

