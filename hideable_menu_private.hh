//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// hideable_menu_private.cc: hideable menu class
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
hideable_menu<Derived>::WmSyscommand (HWND hwnd, UINT uMsg,
                                      WPARAM wParam, LPARAM lParam)
{
  if (wParam == SC_KEYMENU)
    {
      SetMenu (hwnd, hmenu_);
      InvalidateRect (hwnd, nullptr, TRUE);
    }

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

template <class Derived>
LRESULT
hideable_menu<Derived>::WmExitmenuloop (HWND hwnd, UINT uMsg,
                                        WPARAM wParam, LPARAM lParam)
{
  SetMenu (hwnd, nullptr);
  InvalidateRect (hwnd, nullptr, TRUE);

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

template <class Derived>
LRESULT
hideable_menu<Derived>::WmCreate (HWND hwnd, UINT, WPARAM, LPARAM)
{
  auto &derived {static_cast<Derived&> (*this)};

  hmenu_ = LoadMenu (derived.get_hInst (), MAKEINTRESOURCE (IDM_MENU));

  return 0;
}

template <class Derived>
LRESULT
hideable_menu<Derived>::WmDestroy (HWND hwnd, UINT, WPARAM, LPARAM)
{
  DestroyMenu (hmenu_);
  hmenu_ = nullptr;

  return 0;
}
