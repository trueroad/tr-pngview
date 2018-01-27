//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// bitmap_loader.hh: Bitmap loader class
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

#ifndef INCLUDE_GUARD_BITMAP_LOADER_HH
#define INCLUDE_GUARD_BITMAP_LOADER_HH

#include <string>

#include <sys/stat.h>

const wchar_t g_default_filename[] = L"output.png";

namespace Gdiplus
{
  class Bitmap;
}

class bitmap_loader
{
public:
  enum class load_status {no_change, same_size, size_changed};

  bitmap_loader () = default;
  ~bitmap_loader ()
  {
    release ();
  }

  load_status load (void);
  void release (void);

  void set_filename (const std::wstring &s)
  {
    filename_ = s;
  }
  Gdiplus::Bitmap *get (void)
  {
    return bmp_;
  }
  int width (void)
  {
    return width_;
  }
  int height (void)
  {
    return height_;
  }
  double aspect_ratio (void)
  {
    return aspect_ratio_;
  }

private:
  std::wstring filename_ {g_default_filename};
  Gdiplus::Bitmap *bmp_ = NULL;
  int width_ = 0;
  int height_ = 0;
  double aspect_ratio_ = 0;
  off_t size_ = 0;
  time_t mtime_ = 0;

  bitmap_loader (const bitmap_loader&) = delete;
  bitmap_loader& operator= (const bitmap_loader&) = delete;
  bitmap_loader (bitmap_loader&&) = default;
  bitmap_loader& operator= (bitmap_loader&&) = default;
};

#endif // INCLUDE_GUARD_BITMAP_LOADER_HH
