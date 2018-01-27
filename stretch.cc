//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// stretch.cc: stretch functions
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

#include <windows.h>

#include "pngview_res.h"

void
pngview_window::set_stretch_mode (stretch_mode s)
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

  mii.fState = sm_ == stretch_mode::contain ? MFS_CHECKED : MFS_UNCHECKED;
  SetMenuItemInfo (hmenu_, IDM_CONTAIN, FALSE, &mii);

  mii.fState = sm_ == stretch_mode::cover ? MFS_CHECKED : MFS_UNCHECKED;
  SetMenuItemInfo (hmenu_, IDM_COVER, FALSE, &mii);

  DrawMenuBar (hwnd_);
}

void
pngview_window::increment_stretch_mode (void)
{
  stretch_mode s;

  switch (sm_)
    {
    case stretch_mode::dot_by_dot:
      s = stretch_mode::fill;
      break;
    case stretch_mode::fill:
      s = stretch_mode::contain;
      break;
    case stretch_mode::contain:
      s = stretch_mode::cover;
      break;
    case stretch_mode::cover:
      s = stretch_mode::dot_by_dot;
      break;
    default:
      s = sm_;
    }

  set_stretch_mode (s);
}

void
pngview_window::calc_coordinate (void)
{
  auto zoom_ratio_height = static_cast<double> (height_) / bl_.height ();
  auto bmp_zoomed_width = zoom_ratio_height * bl_.width ();

  auto zoom_ratio_width = static_cast<double> (width_) / bl_.width ();
  auto bmp_zoomed_height = zoom_ratio_width * bl_.height ();

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
