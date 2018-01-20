//
// tr-pngview 2018-01-20.13
// https://github.com/trueroad/tr-pngview
//
// Periodically read a PNG file and continue to show on a window
// without tearing and flicker
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

#include <windows.h>
#include <tchar.h>
#include <gdiplus.h>
#include <sys/stat.h>

#include "pngview_res.h"

const TCHAR g_package[] =
  TEXT ("tr-pngview 2018-01-20.13\n"
        "Copyright (C) 2018 Masamichi Hosoda. All rights reserved.\n"
        "License: BSD-2-Clause\n\n"
        "https://github.com/trueroad/tr-pngview");

const TCHAR g_classname[] = TEXT ("TRPNGVIEW");
const TCHAR g_window_title[] = TEXT ("pngview");

const WCHAR g_filename[] = L"output.png";

class gdiplus_init
{
public:
  gdiplus_init ()
  {
    Gdiplus::GdiplusStartupInput gpsi;
    Gdiplus::GdiplusStartup (&token_, &gpsi, NULL);
  }
  ~gdiplus_init ()
  {
    Gdiplus::GdiplusShutdown (token_);
  }

private:
  ULONG_PTR token_;

  gdiplus_init (const gdiplus_init&) = delete;
  gdiplus_init& operator= (const gdiplus_init&) = delete;
  gdiplus_init (gdiplus_init&&) = delete;
  gdiplus_init& operator= (gdiplus_init&&) = delete;
};

class bitmap_loader
{
public:
  bitmap_loader () = default;
  ~bitmap_loader ()
  {
    release ();
  }

  void load (void)
  {
    struct _stat st;
    if (_wstat (g_filename, &st))
      return;
    if (st.st_size == size_ && st.st_mtime == mtime_)
      return;

    Gdiplus::Bitmap tmp_bmp {g_filename};
    release ();
    bmp_ = new Gdiplus::Bitmap (tmp_bmp.GetWidth (), tmp_bmp.GetHeight ());

    Gdiplus::Graphics offscreen {bmp_};
    offscreen.DrawImage (&tmp_bmp, 0, 0);

    size_ = st.st_size;
    mtime_ = st.st_mtime;
  }
  void release (void)
  {
    if (bmp_)
      {
        delete bmp_;
        bmp_ = NULL;
      }
  }
  Gdiplus::Bitmap *get (void)
  {
    return bmp_;
  }

private:
  Gdiplus::Bitmap *bmp_ = NULL;
  off_t size_ = 0;
  time_t mtime_ = 0;

  bitmap_loader (const bitmap_loader&) = delete;
  bitmap_loader& operator= (const bitmap_loader&) = delete;
  bitmap_loader (bitmap_loader&&) = default;
  bitmap_loader& operator= (bitmap_loader&&) = default;
};

class window_class
{
public:
  window_class () = default;
  ~window_class () = default;

  bool init (HINSTANCE, int);
  int message_loop (void);

private:
  static LRESULT CALLBACK wndproc_static (HWND, UINT, WPARAM, LPARAM);
  LRESULT wndproc (HWND, UINT, WPARAM, LPARAM);

  bitmap_loader bl_;
  bool bstrech_ = false;

  window_class (const window_class&) = delete;
  window_class& operator= (const window_class&) = delete;
  window_class (window_class&&) = default;
  window_class& operator= (window_class&&) = default;
};

bool
window_class::init (HINSTANCE hInstance, int nCmdShow)
{
  WNDCLASS wc;
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = wndproc_static;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = static_cast<HBRUSH> (GetStockObject (WHITE_BRUSH));
  wc.lpszMenuName  = MAKEINTRESOURCE (IDM_MENU);
  wc.lpszClassName = g_classname;
  if (!RegisterClass (&wc))
    return false;

  HWND hwnd = CreateWindow (g_classname, g_window_title, WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            NULL, NULL, hInstance, this);
  if (!hwnd)
    return false;

  ShowWindow (hwnd, nCmdShow);
  UpdateWindow (hwnd);

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
  switch (uMsg)
    {
    case WM_PAINT:
      {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint (hwnd, &ps);

        {
          Gdiplus::Graphics g {hdc};
          if (bstrech_)
            {
              RECT r;
              GetClientRect (hwnd, &r);
              g.DrawImage (bl_.get (),
                           static_cast<int> (r.left),
                           static_cast<int> (r.top),
                           static_cast<int> (r.right),
                           static_cast<int> (r.bottom));
            }
          else
            g.DrawImage (bl_.get (), 0, 0);
        }

        EndPaint (hwnd, &ps);
      }
      return 0;

    case WM_TIMER:
      bl_.load ();
      InvalidateRect (hwnd, NULL, FALSE);
      return 0;

    case WM_LBUTTONDOWN:
      bstrech_ = !bstrech_;
      InvalidateRect (hwnd, NULL, TRUE);
      return 0;

    case WM_RBUTTONDOWN:
      MessageBox (hwnd, g_package, L"About", MB_OK);
      return 0;

    case WM_COMMAND:
      switch (LOWORD (wParam))
        {
        case IDM_EXIT:
          SendMessage (hwnd, WM_CLOSE, 0, 0);
          break;
        }
      return 0;

    case WM_CREATE:
      bl_.load ();
      SetTimer (hwnd , 1 , 100 , NULL); // 100 ms
      return 0;

    case WM_DESTROY :
      bl_.release ();
      PostQuitMessage (0);
      return 0;
    }

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

int WINAPI
_tWinMain (HINSTANCE hInstance, HINSTANCE, PTSTR, int nCmdShow)
{
  gdiplus_init gi;
  window_class wincls;

  if (!wincls.init (hInstance, nCmdShow))
    return 0;

  return wincls.message_loop ();
}
