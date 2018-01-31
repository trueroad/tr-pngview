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

#include "hideable_menu.hh"
#include "mouseactivate.hh"
#include "bitmap_loader.hh"

class pngview_window: public window_class<pngview_window>,
                      public hideable_menu<pngview_window>,
                      public mouseactivate<pngview_window>
{
  enum class stretch_mode {dot_by_dot, fill, contain, cover};

public:
  pngview_window ()
  {
    classname_ = pngview_classname_;
    title_ = pngview_title_;

    add_procedure (WM_PAINT, WmPaint);
    add_procedure (WM_TIMER, WmTimer);
    add_procedure (WM_LBUTTONDOWN, WmLbuttondown);
    add_procedure (WM_COMMAND, WmCommand);
    add_procedure (WM_SIZE, WmSize);
    add_procedure (WM_DROPFILES, WmDropfiles);
    add_procedure (WM_CREATE, WmCreate);
    add_procedure (WM_DESTROY, WmDestroy);
  }
  ~pngview_window () = default;

  stretch_mode get_stretch_mode (void)
  {
    return sm_;
  }
  void set_stretch_mode (stretch_mode);
  void increment_stretch_mode (void);

private:
  LRESULT WmPaint (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmTimer (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmLbuttondown (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmCommand (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmSize (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmDropfiles (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmCreate (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmDestroy (HWND, UINT, WPARAM, LPARAM);

  void calc_coordinate (void);

  const PCTSTR pngview_classname_ {TEXT ("TRPNGVIEW")};
  const PCTSTR pngview_title_ {TEXT ("pngview")};
  const UINT_PTR timerid_ = 1;

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
  pngview_window (pngview_window&&) = delete;
  pngview_window& operator= (pngview_window&&) = delete;
};

#endif // INCLUDE_PNGVIEW_WINDOW_HH
