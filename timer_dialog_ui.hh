//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// timer_dialog_ui.hh: timer dialog box UI class
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

#ifndef INCLUDE_TIMER_DIALOG_UI_HH
#define INCLUDE_TIMER_DIALOG_UI_HH

#include <windows.h>

#include "dialogbox.hh"

class timer_dialog_ui: public dialogbox_class<timer_dialog_ui>
{
public:
  timer_dialog_ui (UINT i): interval_ (i)
  {
    flush_temp_procmap ();
    add_procedure (WM_INITDIALOG, WmInitdialog);

    flush_temp_cmdprocmap ();
    add_cmdprocedure (IDOK, Idok);
    add_cmdprocedure (IDCANCEL, Idcancel);
  }
  ~timer_dialog_ui () = default;

  UINT get_interval (void)
  {
    return interval_;
  }

private:
  INT_PTR WmInitdialog (HWND, UINT, WPARAM, LPARAM);

  INT_PTR Idok (HWND, WORD, WORD, LPARAM);
  INT_PTR Idcancel (HWND, WORD, WORD, LPARAM);

  UINT interval_;
};

#include "timer_dialog_ui_private.hh"

#endif // INCLUDE_TIMER_DIALOG_UI_HH
