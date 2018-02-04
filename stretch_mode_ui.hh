//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// stretch_mode_ui.hh: Stretch mode UI class
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

#ifndef INCLUDE_GUARD_STRETCH_MODE_UI_HH
#define INCLUDE_GUARD_STRETCH_MODE_UI_HH

#include <windows.h>

#include "cmdmap_init_base.hh"
#include "procmap_init_base.hh"
#include "pngview_res.h"

template <class Derived>
class stretch_mode_ui: virtual public procmap_init_base<Derived>,
                       virtual public cmdmap_init_base<Derived>
{
public:
  stretch_mode_ui ()
  {
    this->add_temp_procmap (WM_LBUTTONDOWN, WmLbuttondown);

    this->add_temp_cmdprocmap (IDM_DOT_BY_DOT, Cmd_idm_dot_by_dot);
    this->add_temp_cmdprocmap (IDM_FILL, Cmd_idm_fill);
    this->add_temp_cmdprocmap (IDM_CONTAIN, Cmd_idm_contain);
    this->add_temp_cmdprocmap (IDM_COVER, Cmd_idm_cover);
  }
  ~stretch_mode_ui () = default;

private:
  LRESULT WmLbuttondown (HWND, UINT, WPARAM, LPARAM);

  LRESULT Cmd_idm_dot_by_dot (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_fill (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_contain (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_cover (HWND, WORD, WORD, LPARAM);
};

#include "stretch_mode_ui_private.hh"

#endif // INCLUDE_GUARD_STRETCH_MODE_UI_HH
