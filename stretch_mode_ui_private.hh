//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// stretch_mode_ui_private.hh: Stretch mode UI class
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

#include "stretch.hh"

template <class Derived>
LRESULT
stretch_mode_ui<Derived>::WmLbuttondown (HWND hwnd, UINT, WPARAM, LPARAM)
{
  auto &p {static_cast<Derived&> (*this)};

  p.get_stretch_bitmap ().increment_mode ();

  return 0;
}

template <class Derived>
LRESULT
stretch_mode_ui<Derived>::Cmd_idm_dot_by_dot (HWND, WORD, WORD, LPARAM)
{
  auto &p {static_cast<Derived&> (*this)};

  p.get_stretch_bitmap ().set_mode (stretch_bitmap::mode::dot_by_dot);

  return 0;
}

template <class Derived>
LRESULT
stretch_mode_ui<Derived>::Cmd_idm_fill (HWND, WORD, WORD, LPARAM)
{
  auto &p {static_cast<Derived&> (*this)};

  p.get_stretch_bitmap ().set_mode (stretch_bitmap::mode::fill);

  return 0;
}

template <class Derived>
LRESULT
stretch_mode_ui<Derived>::Cmd_idm_contain (HWND, WORD, WORD, LPARAM)
{
  auto &p {static_cast<Derived&> (*this)};

  p.get_stretch_bitmap ().set_mode (stretch_bitmap::mode::contain);

  return 0;
}

template <class Derived>
LRESULT
stretch_mode_ui<Derived>::Cmd_idm_cover (HWND, WORD, WORD, LPARAM)
{
  auto &p {static_cast<Derived&> (*this)};

  p.get_stretch_bitmap ().set_mode (stretch_bitmap::mode::cover);

  return 0;
}
