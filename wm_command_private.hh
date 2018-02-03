//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// wm_command_private.hh: WM_COMMAND processing class
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

#include "pngview_res.h"

template <class Derived>
LRESULT
wm_command<Derived>::WmCommand (HWND hwnd, UINT, WPARAM wParam, LPARAM lParam)
{
  auto &p {static_cast<Derived&> (*this)};

  switch (LOWORD (wParam))
    {
    case IDM_DOT_BY_DOT:
      return p.Cmd_idm_dot_by_dot (hwnd, HIWORD (wParam),
                                   LOWORD (wParam), lParam);
    case IDM_FILL:
      return p.Cmd_idm_fill (hwnd, HIWORD (wParam), LOWORD (wParam), lParam);
    case IDM_CONTAIN:
      return p.Cmd_idm_contain (hwnd, HIWORD (wParam),
                                LOWORD (wParam), lParam);
    case IDM_COVER:
      return p.Cmd_idm_cover (hwnd, HIWORD (wParam), LOWORD (wParam), lParam);
    case IDM_ABOUT:
      return p.Cmd_idm_about (hwnd, HIWORD (wParam), LOWORD (wParam), lParam);
    case IDM_EXIT:
      return p.Cmd_idm_exit (hwnd, HIWORD (wParam), LOWORD (wParam), lParam);
    }
  return 0;
}
