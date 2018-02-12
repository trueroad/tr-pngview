//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// stretch.hh: Stretch bitmap class
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

#ifndef INCLUDE_GUARD_STRETCH_HH
#define INCLUDE_GUARD_STRETCH_HH

#include <string>

#include <windows.h>

#include "bitmap_loader.hh"

class stretch_bitmap
{
public:
  enum class mode {dot_by_dot, fill, contain, cover};

  stretch_bitmap () = default;
  ~stretch_bitmap ()
  {
    release ();
  }

  void init (HWND, HMENU);
  void release (void)
  {
    bl_.release ();
  }

  void paint (HDC);
  void timer (void);
  void window_size (WORD, WORD);
  void load_file (const std::wstring &s);

  mode get_mode (void) const noexcept
  {
    return mode_;
  }
  void set_mode (mode);
  void increment_mode (void);

private:
  HWND hwnd_ = nullptr;
  HMENU hmenu_ = nullptr;

  int width_ = 0;
  int height_ = 0;
  double aspect_ratio_ = 0;
  int stretch_contain_x_ = 0;
  int stretch_contain_y_ = 0;
  int stretch_contain_width_ = 0;
  int stretch_contain_height_ = 0;
  int stretch_cover_x_ = 0;
  int stretch_cover_y_ = 0;
  int stretch_cover_width_ = 0;
  int stretch_cover_height_ = 0;

  void calc_coordinate (void);

  bitmap_loader bl_;
  mode mode_ = mode::dot_by_dot;
};

#endif // INCLUDE_GUARD_STRETCH_HH
