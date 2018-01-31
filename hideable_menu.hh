//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// hideable_menu.hh: Hideable menu class
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

#ifndef INCLUDE_HIDEABLE_MENU_HH
#define INCLUDE_HIDEABLE_MENU_HH

#include <windows.h>

#include "window.hh"

template <class Derived>
class hideable_menu
{
public:
  hideable_menu ()
  {
    auto &derived {static_cast<Derived&> (*this)};

    derived.add_procedure (WM_SYSCOMMAND, WmSyscommand);
    derived.add_procedure (WM_EXITMENULOOP, WmExitmenuloop);
    derived.add_procedure (WM_CREATE, WmCreate);
    derived.add_procedure (WM_DESTROY, WmDestroy);
  }
  ~hideable_menu () = default;

protected:
  LRESULT WmSyscommand (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmExitmenuloop (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmCreate (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmDestroy (HWND, UINT, WPARAM, LPARAM);

  HMENU hmenu_ = NULL;

private:
  hideable_menu (const hideable_menu&) = delete;
  hideable_menu& operator= (const hideable_menu&) = delete;
  hideable_menu (hideable_menu&&) = delete;
  hideable_menu& operator= (hideable_menu&&) = delete;
};

#include "hideable_menu_private.hh"

#endif // INCLUDE_HIDEABLE_MENU_HH
