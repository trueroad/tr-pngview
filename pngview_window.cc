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
  HDC hdc = BeginPaint (hwnd, &ps);

  sb_.paint (hdc);

  EndPaint (hwnd, &ps);

  return 0;
}

LRESULT
pngview_window::WmTimer (HWND hwnd, UINT, WPARAM wParam, LPARAM)
{
  if (static_cast<UINT_PTR> (wParam) == timerid_)
    sb_.timer ();
  return 0;
}

LRESULT
pngview_window::WmLbuttondown (HWND hwnd, UINT, WPARAM, LPARAM)
{
  sb_.increment_mode ();
  return 0;
}

LRESULT
pngview_window::WmSize (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  sb_.window_size (LOWORD (lParam), HIWORD (lParam));

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

LRESULT
pngview_window::WmDropfiles (HWND hwnd, UINT uMsg,
                             WPARAM wParam, LPARAM lParam)
{
  {
    std::wstring buff;
    HDROP hd = reinterpret_cast<HDROP> (wParam);

    buff.resize (DragQueryFileW (hd, 0, NULL, 0) + 1);
    DragQueryFileW (hd, 0, &buff.at (0), buff.size ());
    DragFinish (hd);

    sb_.load_file (buff);
  }

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

LRESULT
pngview_window::WmCreate (HWND hwnd, UINT uMsg,
                          WPARAM wParam, LPARAM lParam)
{
  hideable_menu<pngview_window>::WmCreate (hwnd, uMsg, wParam, lParam);

  DragAcceptFiles (hwnd, TRUE);

  sb_.init (hwnd, hmenu_);

  SetTimer (hwnd , timerid_ , 100 , NULL); // 100 ms

  return 0;
}

LRESULT
pngview_window::WmDestroy (HWND hwnd, UINT uMsg,
                           WPARAM wParam, LPARAM lParam)
{
  KillTimer (hwnd, timerid_);

  sb_.release ();

  hideable_menu<pngview_window>::WmDestroy (hwnd, uMsg, wParam, lParam);

  PostQuitMessage (0);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_dot_by_dot (HWND, WORD, WORD, LPARAM)
{
  sb_.set_mode (stretch_bitmap::mode::dot_by_dot);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_fill (HWND, WORD, WORD, LPARAM)
{
  sb_.set_mode (stretch_bitmap::mode::fill);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_contain (HWND, WORD, WORD, LPARAM)
{
  sb_.set_mode (stretch_bitmap::mode::contain);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_cover (HWND, WORD, WORD, LPARAM)
{
  sb_.set_mode (stretch_bitmap::mode::cover);

  return 0;
}
