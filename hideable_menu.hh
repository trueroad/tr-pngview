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

#include "procmap_init_base.hh"

template <class Derived>
class hideable_menu: virtual public procmap_init_base<Derived>
{
public:
  hideable_menu ()
  {
    this->add_temp_procmap (WM_SYSCOMMAND, WmSyscommand);
    this->add_temp_procmap (WM_EXITMENULOOP, WmExitmenuloop);
    this->add_temp_procmap (WM_CREATE, WmCreate);
    this->add_temp_procmap (WM_DESTROY, WmDestroy);
  }
  ~hideable_menu () = default;

protected:
  LRESULT WmSyscommand (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmExitmenuloop (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmCreate (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmDestroy (HWND, UINT, WPARAM, LPARAM);

  HMENU hmenu_ = nullptr;
};

#include "hideable_menu_private.hh"

#endif // INCLUDE_HIDEABLE_MENU_HH
