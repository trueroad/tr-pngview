//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// window.hh: Base window class
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

class window_class
{
public:
  window_class () = default;
  ~window_class () = default;
  window_class (window_class&&) = default;
  window_class& operator= (window_class&&) = default;

  bool init (HINSTANCE, int);
  int message_loop (void);

protected:
  virtual LRESULT wndproc (HWND, UINT, WPARAM, LPARAM);

  bool register_class (PCTSTR);
  bool create_window (PCTSTR, PCTSTR);
  void show_and_update_window (int);

  HINSTANCE hInst_ = NULL;
  HWND hwnd_ = NULL;

private:
  static LRESULT CALLBACK wndproc_static (HWND, UINT, WPARAM, LPARAM);

  const PCTSTR classname_ {TEXT ("TRWINDOWCLASS")};
  const PCTSTR title_ {TEXT ("tr-window")};

  window_class (const window_class&) = delete;
  window_class& operator= (const window_class&) = delete;
};

#endif // INCLUDE_WINDOW_HH
