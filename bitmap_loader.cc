//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// bitmap_loader.cc: Bitmap loader class
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

#include "bitmap_loader.hh"

#include <string>

#include <windows.h>
#include <gdiplus.h>
#include <sys/stat.h>

bitmap_loader::load_status
bitmap_loader::load (void)
{
  struct _stat st;
  if (_wstat (filename_.c_str (), &st))
    return load_status::no_change;
  if (st.st_size == size_ && st.st_mtime == mtime_)
    return load_status::no_change;

  Gdiplus::Bitmap tmp_bmp {filename_.c_str ()};

  load_status retval = load_status::same_size;
  auto w = tmp_bmp.GetWidth ();
  if (w != width_)
    {
      width_ = w;
      retval = load_status::size_changed;
    }
  auto h = tmp_bmp.GetHeight ();
  if (h != height_)
    {
      height_ = h;
      retval = load_status::size_changed;
    }

  release ();
  bmp_ = new Gdiplus::Bitmap (width_, height_);

  Gdiplus::Graphics offscreen {bmp_};
  offscreen.DrawImage (&tmp_bmp, 0, 0);

  size_ = st.st_size;
  mtime_ = st.st_mtime;

  if (retval != load_status::same_size)
    {
      if (width_ == 0 || height_ == 0)
        aspect_ratio_ = 0;
      else
        aspect_ratio_ = static_cast<double> (width_) / height_;
    }

  return retval;
}

void
bitmap_loader::release (void)
{
  if (bmp_)
    {
      delete bmp_;
      bmp_ = NULL;
    }
}
