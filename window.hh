//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// window.hh: Window class
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

#ifndef INCLUDE_WINDOW_HH
#define INCLUDE_WINDOW_HH

#include <windows.h>

#include "bitmap_loader.hh"

class window_class
{
  enum class stretch_mode {dot_by_dot, fill, contain, cover};

public:
  window_class () = default;
  ~window_class () = default;
  window_class (window_class&&) = default;
  window_class& operator= (window_class&&) = default;

  bool init (HINSTANCE, int);
  int message_loop (void);

  stretch_mode get_stretch_mode (void)
  {
    return sm_;
  }
  void set_stretch_mode (stretch_mode);
  void increment_stretch_mode (void);

private:
  static LRESULT CALLBACK wndproc_static (HWND, UINT, WPARAM, LPARAM);
  LRESULT wndproc (HWND, UINT, WPARAM, LPARAM);

  bool register_class (void);
  bool create_window (void);
  void show_and_update_window (int);

  void calc_coordinate (void);

  const TCHAR *classname_ {TEXT ("TRPNGVIEW")};
  const TCHAR *window_title_ {TEXT ("pngview")};

  HINSTANCE hInst_ = NULL;
  HWND hwnd_ = NULL;
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

  window_class (const window_class&) = delete;
  window_class& operator= (const window_class&) = delete;
};

#endif // INCLUDE_WINDOW_HH
