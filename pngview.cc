//
// tr-pngview 2018-01-21.00
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
  TEXT ("tr-pngview 2018-01-21.00\n"
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
  enum class load_status {no_change, same_size, size_changed};

  bitmap_loader () = default;
  ~bitmap_loader ()
  {
    release ();
  }

  load_status load (void)
  {
    struct _stat st;
    if (_wstat (g_filename, &st))
      return load_status::no_change;
    if (st.st_size == size_ && st.st_mtime == mtime_)
      return load_status::no_change;

    Gdiplus::Bitmap tmp_bmp {g_filename};

    load_status retval = load_status::same_size;
    auto w = tmp_bmp.GetWidth ();
    if (w != width_)
      {
        width_ = w;
        retval = load_status::size_changed;
      }
    auto h = tmp_bmp.GetHeight ();
    if (h != height_)
      {
        height_ = h;
        retval = load_status::size_changed;
      }

    release ();
    bmp_ = new Gdiplus::Bitmap (width_, height_);

    Gdiplus::Graphics offscreen {bmp_};
    offscreen.DrawImage (&tmp_bmp, 0, 0);

    size_ = st.st_size;
    mtime_ = st.st_mtime;

    if (retval != load_status::same_size)
      {
        if (width_ == 0 || height_ == 0)
          aspect_ratio_ = 0;
        else
          aspect_ratio_ = static_cast<double> (width_) / height_;
      }

    return retval;
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
  int width (void)
  {
    return width_;
  }
  int height (void)
  {
    return height_;
  }
  int aspect_ratio (void)
  {
    return aspect_ratio_;
  }

private:
  Gdiplus::Bitmap *bmp_ = NULL;
  int width_ = 0;
  int height_ = 0;
  double aspect_ratio_ = 0;
  off_t size_ = 0;
  time_t mtime_ = 0;

  bitmap_loader (const bitmap_loader&) = delete;
  bitmap_loader& operator= (const bitmap_loader&) = delete;
  bitmap_loader (bitmap_loader&&) = default;
  bitmap_loader& operator= (bitmap_loader&&) = default;
};

class window_class
{
  enum class stretch_mode {dot_by_dot, fill};

public:
  window_class () = default;
  ~window_class () = default;

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

  HWND hwnd_ = NULL;
  HMENU hmenu_ = NULL;
  int width_ = 0;
  int height_ = 0;
  double aspect_ratio_ = 0;

  bitmap_loader bl_;
  stretch_mode sm_ = stretch_mode::dot_by_dot;

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

  hwnd_ = CreateWindow (g_classname, g_window_title, WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, NULL, hInstance, this);
  if (!hwnd_)
    return false;

  hmenu_ = GetMenu (hwnd_);
  SetMenu (hwnd_, NULL);
  set_stretch_mode (sm_);

  ShowWindow (hwnd_, nCmdShow);
  UpdateWindow (hwnd_);

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

void
window_class::set_stretch_mode (stretch_mode s)
{
  if (sm_ != s)
    {
      sm_ = s;
      InvalidateRect (hwnd_, NULL, TRUE);
    }

  MENUITEMINFO mii {0};
  mii.cbSize = sizeof (mii);
  mii.fMask = MIIM_STATE;

  mii.fState = sm_ == stretch_mode::dot_by_dot ? MFS_CHECKED : MFS_UNCHECKED;
  SetMenuItemInfo (hmenu_, IDM_DOT_BY_DOT, FALSE, &mii);

  mii.fState = sm_ == stretch_mode::fill ? MFS_CHECKED : MFS_UNCHECKED;
  SetMenuItemInfo (hmenu_, IDM_FILL, FALSE, &mii);

  DrawMenuBar (hwnd_);
}

void
window_class::increment_stretch_mode (void)
{
  stretch_mode s;

  switch (sm_)
    {
    case stretch_mode::dot_by_dot:
      s = stretch_mode::fill;
      break;
    case stretch_mode::fill:
      s = stretch_mode::dot_by_dot;
      break;
    default:
      s = sm_;
    }

  set_stretch_mode (s);
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
          switch (sm_)
            {
            case stretch_mode::dot_by_dot:
              g.DrawImage (bl_.get (), 0, 0);
              break;
            case stretch_mode::fill:
              g.DrawImage (bl_.get (), 0, 0, width_, height_);
              break;
            }
        }

        EndPaint (hwnd, &ps);
      }
      return 0;

    case WM_TIMER:
      if (bl_.load () != bitmap_loader::load_status::no_change)
        InvalidateRect (hwnd, NULL, FALSE);
      return 0;

    case WM_LBUTTONDOWN:
      increment_stretch_mode ();
      return 0;

    case WM_COMMAND:
      switch (LOWORD (wParam))
        {
        case IDM_DOT_BY_DOT:
          set_stretch_mode (stretch_mode::dot_by_dot);
          break;
        case IDM_FILL:
          set_stretch_mode (stretch_mode::fill);
          break;
        case IDM_ABOUT:
          MessageBox (hwnd, g_package, L"About tr-pngview", MB_OK);
          break;
        case IDM_EXIT:
          SendMessage (hwnd, WM_CLOSE, 0, 0);
          break;
        }
      return 0;

    case WM_SIZE:
      width_ = LOWORD (lParam);
      height_ = HIWORD (lParam);
      if (width_ == 0 || height_ == 0)
        aspect_ratio_ = 0;
      else
        aspect_ratio_ = static_cast<double> (width_) / height_;
      break;

    case WM_MOUSEACTIVATE:
      if (HIWORD (lParam) == WM_LBUTTONDOWN)
        return MA_ACTIVATEANDEAT;
      break;

    case WM_SYSCOMMAND:
      if (wParam == SC_KEYMENU)
        {
          SetMenu (hwnd, hmenu_);
          InvalidateRect (hwnd, NULL, TRUE);
        }
      break;

    case WM_EXITMENULOOP:
      SetMenu (hwnd, NULL);
      InvalidateRect (hwnd, NULL, TRUE);
      break;

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
