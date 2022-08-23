/*
 * Copyright (C) 2009, Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Willow Garage, Inc. nor the names of its
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

#ifndef MOSLIB_BUILTIN_MESSAGE_TRAITS_H
#define MOSLIB_BUILTIN_MESSAGE_TRAITS_H

#include "mos_message_traits.h"
#include "mos_time.h"

namespace mos
{
namespace message_traits
{

#define MOSLIB_CREATE_SIMPLE_TRAITS(Type) \
    template<> struct IsSimple<Type> : public TrueType {}; \
    template<> struct IsFixedSize<Type> : public TrueType {};

MOSLIB_CREATE_SIMPLE_TRAITS(uint8_t)
MOSLIB_CREATE_SIMPLE_TRAITS(int8_t)
MOSLIB_CREATE_SIMPLE_TRAITS(uint16_t)
MOSLIB_CREATE_SIMPLE_TRAITS(int16_t)
MOSLIB_CREATE_SIMPLE_TRAITS(uint32_t)
MOSLIB_CREATE_SIMPLE_TRAITS(int32_t)
MOSLIB_CREATE_SIMPLE_TRAITS(uint64_t)
MOSLIB_CREATE_SIMPLE_TRAITS(int64_t)
MOSLIB_CREATE_SIMPLE_TRAITS(float)
MOSLIB_CREATE_SIMPLE_TRAITS(double)
MOSLIB_CREATE_SIMPLE_TRAITS(Time)
MOSLIB_CREATE_SIMPLE_TRAITS(Duration)

// because std::vector<bool> is not a true vector, bool is not a simple type
template<> struct IsFixedSize<bool> : public TrueType {};

} // namespace message_traits
} // namespace mos

#endif // MOSLIB_BUILTIN_MESSAGE_TRAITS_H

