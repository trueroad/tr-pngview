//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// pngview_window.cc: pngview window class
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

#include "pngview_window.hh"

#include <string>

#include <windows.h>

#include "stretch.hh"

LRESULT
pngview_window::WmPaint (HWND hwnd, UINT, WPARAM, LPARAM)
{
  PAINTSTRUCT ps;
  HDC hdc {BeginPaint (hwnd, &ps)};

  sb_.paint (hdc);

  EndPaint (hwnd, &ps);

  return 0;
}

LRESULT
pngview_window::WmSize (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  sb_.window_size (LOWORD (lParam), HIWORD (lParam));

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

LRESULT
pngview_window::WmCreate (HWND hwnd, UINT uMsg,
                          WPARAM wParam, LPARAM lParam)
{
  hideable_menu<pngview_window>::WmCreate (hwnd, uMsg, wParam, lParam);
  sb_.init (hwnd, hmenu_);

  drag_and_drop<pngview_window>::WmCreate (hwnd, uMsg, wParam, lParam);
  timer_handler<pngview_window>::WmCreate (hwnd, uMsg, wParam, lParam);

  return 0;
}

LRESULT
pngview_window::WmDestroy (HWND hwnd, UINT uMsg,
                           WPARAM wParam, LPARAM lParam)
{
  timer_handler<pngview_window>::WmDestroy (hwnd, uMsg, wParam, lParam);
  drag_and_drop<pngview_window>::WmDestroy (hwnd, uMsg, wParam, lParam);

  sb_.release ();
  hideable_menu<pngview_window>::WmDestroy (hwnd, uMsg, wParam, lParam);

  PostQuitMessage (0);

  return 0;
}
