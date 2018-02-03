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
#include <gdiplus.h>

#include "bitmap_loader.hh"
#include "pngview_res.h"
#include "version.h"

LRESULT
pngview_window::WmPaint (HWND hwnd, UINT, WPARAM, LPARAM)
{
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint (hwnd, &ps);

  {
    Gdiplus::Graphics g {hdc};
    switch (sm_)
      {
      case stretch_mode::dot_by_dot:
        g.DrawImage (bl_.get (), 0, 0);
        break;
      case stretch_mode::fill:
        g.DrawImage (bl_.get (), 0, 0, width_, height_);
        break;
      case stretch_mode::contain:
        g.DrawImage (bl_.get (),
                     stretch_contain_x_, stretch_contain_y_,
                     stretch_contain_width_, stretch_contain_height_);
        break;
      case stretch_mode::cover:
        g.DrawImage (bl_.get (),
                     stretch_cover_x_, stretch_cover_y_,
                     stretch_cover_width_, stretch_cover_height_);
        break;
      }
  }

  EndPaint (hwnd, &ps);

  return 0;
}

LRESULT
pngview_window::WmTimer (HWND hwnd, UINT, WPARAM wParam, LPARAM)
{
  if (static_cast<UINT_PTR> (wParam) == timerid_)
    {
      switch (bl_.load ())
        {
        case bitmap_loader::load_status::size_changed:
          calc_coordinate ();
          // no break
        case bitmap_loader::load_status::same_size:
          InvalidateRect (hwnd, NULL, FALSE);
        }
    }
  return 0;
}

LRESULT
pngview_window::WmLbuttondown (HWND hwnd, UINT, WPARAM, LPARAM)
{
  increment_stretch_mode ();
  return 0;
}

LRESULT
pngview_window::WmSize (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  width_ = LOWORD (lParam);
  height_ = HIWORD (lParam);
  if (width_ == 0 || height_ == 0)
    aspect_ratio_ = 0;
  else
    aspect_ratio_ = static_cast<double> (width_) / height_;
  calc_coordinate ();

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

    bl_.set_filename (buff);
  }

  bl_.load ();
  calc_coordinate ();
  InvalidateRect (hwnd, NULL, TRUE);

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

LRESULT
pngview_window::WmCreate (HWND hwnd, UINT uMsg,
                          WPARAM wParam, LPARAM lParam)
{
  hideable_menu<pngview_window>::WmCreate (hwnd, uMsg, wParam, lParam);
  set_stretch_mode (sm_);

  DragAcceptFiles (hwnd, TRUE);

  bl_.load ();
  calc_coordinate ();

  SetTimer (hwnd , timerid_ , 100 , NULL); // 100 ms

  return 0;
}

LRESULT
pngview_window::WmDestroy (HWND hwnd, UINT uMsg,
                           WPARAM wParam, LPARAM lParam)
{
  KillTimer (hwnd, timerid_);

  bl_.release ();

  hideable_menu<pngview_window>::WmDestroy (hwnd, uMsg, wParam, lParam);

  PostQuitMessage (0);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_dot_by_dot (HWND, WORD, WORD, LPARAM)
{
  set_stretch_mode (stretch_mode::dot_by_dot);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_fill (HWND, WORD, WORD, LPARAM)
{
  set_stretch_mode (stretch_mode::fill);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_contain (HWND, WORD, WORD, LPARAM)
{
  set_stretch_mode (stretch_mode::contain);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_cover (HWND, WORD, WORD, LPARAM)
{
  set_stretch_mode (stretch_mode::cover);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_about (HWND hwnd, WORD, WORD, LPARAM)
{
  MessageBox (hwnd,
              TEXT (PACKAGE_NAME) TEXT (" ")
              TEXT (PACKAGE_VERSION) TEXT ("\n")
              TEXT (PACKAGE_COPYRIGHT) TEXT ("\n")
              TEXT (PACKAGE_LICENSE) TEXT ("\n\n")
              TEXT (PACKAGE_URL),
              TEXT ("About") TEXT (" ") TEXT(PACKAGE_NAME),
              MB_OK);

  return 0;
}

LRESULT
pngview_window::Cmd_idm_exit (HWND hwnd, WORD, WORD, LPARAM)
{
  SendMessage (hwnd, WM_CLOSE, 0, 0);

  return 0;
}
