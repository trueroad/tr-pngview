//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// window.cc: Base window class
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

#include "window.hh"

#include <string>

#include <windows.h>
#include <tchar.h>

#include "pngview_res.h"

bool
window_class::init (HINSTANCE hInstance, int nCmdShow)
{
  hInst_ = hInstance;

  if (!register_class ())
    return false;

  if (!create_window ())
    return false;

  show_and_update_window (nCmdShow);

  return true;
}

int
window_class::message_loop (void)
{
  MSG msg;
  while (GetMessage (&msg, NULL, 0, 0))
    {
      TranslateMessage (&msg);
      DispatchMessage (&msg);
    }

  return msg.wParam;
}

LRESULT CALLBACK
window_class::wndproc_static (HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  window_class *wc;
  if (uMsg == WM_NCCREATE)
    {
      wc = reinterpret_cast<window_class*>
        ((reinterpret_cast<LPCREATESTRUCT> (lParam))->lpCreateParams);
      SetWindowLongPtr (hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR> (wc));
    }
  else
    {
      wc = reinterpret_cast<window_class*>
        (GetWindowLongPtr (hwnd, GWLP_USERDATA));
    }

  if (wc)
    {
      return wc->wndproc (hwnd, uMsg, wParam, lParam);
    }

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

LRESULT
window_class::wndproc (HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

bool
window_class::register_class (void)
{
  WNDCLASS wc;

  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = wndproc_static;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInst_;
  wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = static_cast<HBRUSH> (GetStockObject (WHITE_BRUSH));
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = classname_;

  if (!RegisterClass (&wc))
    return false;

  return true;
}

bool
window_class::create_window (void)
{
  hwnd_ = CreateWindow (classname_, title_, WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, NULL, hInst_, this);

  if (!hwnd_)
    return false;

  return true;
}

void
window_class::show_and_update_window (int nCmdShow)
{
  ShowWindow (hwnd_, nCmdShow);
  UpdateWindow (hwnd_);
}
