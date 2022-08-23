/*
 * Copyright (C) 2008, Willow Garage, Inc.
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


#ifndef MOSPACK_MOSPACK_BACKCOMPAT_H
#define MOSPACK_MOSPACK_BACKCOMPAT_H

#include <string>
#include "macros.h"

namespace mospack
{

/**
 * @brief Backward compatibility API for libmospack (DEPRECATED).
 * @deprecated Used by moslib.  Don't use in new code.
 */
class MOSPACK_DECL MOSPack
{
  private:
    std::string output_;
  public:
    /**
     * @brief Constructor
     * @deprecated Used by moslib.  Don't use in new code.
     */
    MOSPack() {}
    /**
     * @brief Run mospack with the given arguments.  Call getOutput() to
     * get the result.
     * @param argc Number of arguments in argv.
     * @param argv List of arguments.
     * @return Zero if the call succeeded, non-zero otherwise.
     * @deprecated Used by moslib.  Don't use in new code.
     */
    int run(int argc, char** argv);
    /**
     * @brief Run mospack with the given arguments.  Call getOutput() to
     * get the result.
     * @param cmd Space-separated list of arguments.
     * @return Zero if the call succeeded, non-zero otherwise.
     * @deprecated Used by moslib.  Don't use in new code.
     */
    int run(const std::string& cmd);
    /**
     * @brief Get the output from the last successful run() call.
     * @return The result string.
     * @deprecated Used by moslib.  Don't use in new code.
     */
    std::string getOutput() {return output_;}
    /**
     * @brief Are we operating in quiet mode?
     * @return Always true.
     * @deprecated Used by moslib.  Don't use in new code.
     */
    bool is_quiet() {return true;}
};

} // namespace mospack


#endif
