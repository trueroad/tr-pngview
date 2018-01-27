//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// pngview_window.hh: pngview window class
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

#ifndef INCLUDE_PNGVIEW_WINDOW_HH
#define INCLUDE_PNGVIEW_WINDOW_HH

#include <windows.h>

#include "window.hh"
#include "bitmap_loader.hh"

class pngview_window: public window_class
{
  enum class stretch_mode {dot_by_dot, fill, contain, cover};

public:
  pngview_window () = default;
  ~pngview_window () = default;
  pngview_window (pngview_window&&) = default;
  pngview_window& operator= (pngview_window&&) = default;

  bool init (HINSTANCE, int);

  stretch_mode get_stretch_mode (void)
  {
    return sm_;
  }
  void set_stretch_mode (stretch_mode);
  void increment_stretch_mode (void);

private:
  LRESULT wndproc (HWND, UINT, WPARAM, LPARAM);

  void calc_coordinate (void);

  HMENU hmenu_ = NULL;

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

  bitmap_loader bl_;
  stretch_mode sm_ = stretch_mode::dot_by_dot;

  pngview_window (const pngview_window&) = delete;
  pngview_window& operator= (const pngview_window&) = delete;
};

#endif // INCLUDE_PNGVIEW_WINDOW_HH
