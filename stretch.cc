//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// stretch.cc: Stretch bitmap class
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

#include "stretch.hh"

#include <windows.h>
#include <gdiplus.h>

#include "bitmap_loader.hh"
#include "pngview_res.h"

void
stretch_bitmap::init (HWND hwnd, HMENU hmenu)
{
  hwnd_ = hwnd;
  hmenu_ = hmenu;

  set_mode (mode_);
  bl_.load ();
  calc_coordinate ();
}

void
stretch_bitmap::paint (HDC hdc)
{
  Gdiplus::Graphics g {hdc};
  switch (mode_)
    {
    case mode::dot_by_dot:
      g.DrawImage (bl_.get (), 0, 0, bl_.width (), bl_.height ());
      break;
    case mode::fill:
      g.DrawImage (bl_.get (), 0, 0, width_, height_);
      break;
    case mode::contain:
      g.DrawImage (bl_.get (),
                   stretch_contain_x_, stretch_contain_y_,
                   stretch_contain_width_, stretch_contain_height_);
      break;
    case mode::cover:
      g.DrawImage (bl_.get (),
                   stretch_cover_x_, stretch_cover_y_,
                   stretch_cover_width_, stretch_cover_height_);
      break;
    }
}

void
stretch_bitmap::timer (void)
{
  switch (bl_.load ())
    {
    case bitmap_loader::load_status::size_changed:
      calc_coordinate ();
      // no break
    case bitmap_loader::load_status::same_size:
      InvalidateRect (hwnd_, nullptr, FALSE);
    }
}

void
stretch_bitmap::window_size (WORD w, WORD h)
{
  width_ = w;
  height_ = h;

  if (width_ == 0 || height_ == 0)
    aspect_ratio_ = 0;
  else
    aspect_ratio_ = static_cast<double> (width_) / height_;

  calc_coordinate ();
}

void
stretch_bitmap::load_file (const std::wstring &s)
{
  bl_.set_filename (s);
  bl_.load ();
  calc_coordinate ();
  InvalidateRect (hwnd_, nullptr, TRUE);
}

void
stretch_bitmap::set_mode (mode m)
{
  if (mode_ != m)
    {
      mode_ = m;
      if (hwnd_)
        InvalidateRect (hwnd_, nullptr, TRUE);
    }

  MENUITEMINFO mii {0};
  mii.cbSize = sizeof (mii);
  mii.fMask = MIIM_STATE;

  mii.fState =
    (mode_ == mode::dot_by_dot ? MFS_CHECKED : MFS_UNCHECKED);
  SetMenuItemInfo (hmenu_, IDM_DOT_BY_DOT, FALSE, &mii);

  mii.fState =
    (mode_ == mode::fill ? MFS_CHECKED : MFS_UNCHECKED);
  SetMenuItemInfo (hmenu_, IDM_FILL, FALSE, &mii);

  mii.fState =
    (mode_ == mode::contain ? MFS_CHECKED : MFS_UNCHECKED);
  SetMenuItemInfo (hmenu_, IDM_CONTAIN, FALSE, &mii);

  mii.fState =
    (mode_ == mode::cover ? MFS_CHECKED : MFS_UNCHECKED);
  SetMenuItemInfo (hmenu_, IDM_COVER, FALSE, &mii);

  if (hwnd_)
    DrawMenuBar (hwnd_);
}

void
stretch_bitmap::increment_mode (void)
{
  mode m;

  switch (mode_)
    {
    case mode::dot_by_dot:
      m = mode::fill;
      break;
    case mode::fill:
      m = mode::contain;
      break;
    case mode::contain:
      m = mode::cover;
      break;
    case mode::cover:
      m = mode::dot_by_dot;
      break;
    default:
      m = mode_;
    }

  set_mode (m);
}

void
stretch_bitmap::calc_coordinate (void)
{
  auto zoom_ratio_height {static_cast<double> (height_) / bl_.height ()};
  auto bmp_zoomed_width {zoom_ratio_height * bl_.width ()};

  auto zoom_ratio_width {static_cast<double> (width_) / bl_.width ()};
  auto bmp_zoomed_height {zoom_ratio_width * bl_.height ()};

  if (aspect_ratio_ > bl_.aspect_ratio ())
    {
      stretch_contain_x_ = (width_ - bmp_zoomed_width) / 2;
      stretch_contain_width_ = bmp_zoomed_width;

      stretch_contain_y_ = 0;
      stretch_contain_height_ = height_;

      stretch_cover_y_ = (height_ - bmp_zoomed_height) / 2;
      stretch_cover_height_ = bmp_zoomed_height;

      stretch_cover_x_ = 0;
      stretch_cover_width_ = width_;
    }
  else
    {
      stretch_contain_y_ = (height_ - bmp_zoomed_height) / 2;
      stretch_contain_height_ = bmp_zoomed_height;

      stretch_contain_x_ = 0;
      stretch_contain_width_ = width_;

      stretch_cover_x_ = (width_ - bmp_zoomed_width) / 2;
      stretch_cover_width_ = bmp_zoomed_width;

      stretch_cover_y_ = 0;
      stretch_cover_height_ = height_;
    }
}
