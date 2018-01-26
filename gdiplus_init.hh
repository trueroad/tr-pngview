//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// gdiplus_init.hh: GDI+ initialization class
//
// Copyright (C) 2018 Masamichi Hosoda.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

#ifndef INCLUDE_GUARD_GDIPLUS_INIT_HH
#define INCLUDE_GUARD_GDIPLUS_INIT_HH

#include <gdiplus.h>

class gdiplus_init
{
public:
  gdiplus_init ()
  {
    Gdiplus::GdiplusStartupInput gpsi;
    Gdiplus::GdiplusStartup (&token_, &gpsi, NULL);
  }
  ~gdiplus_init ()
  {
    Gdiplus::GdiplusShutdown (token_);
  }

private:
  ULONG_PTR token_;

  gdiplus_init (const gdiplus_init&) = delete;
  gdiplus_init& operator= (const gdiplus_init&) = delete;
  gdiplus_init (gdiplus_init&&) = delete;
  gdiplus_init& operator= (gdiplus_init&&) = delete;
};

#endif // INCLUDE_GUARD_GDIPLUS_INIT_HH
