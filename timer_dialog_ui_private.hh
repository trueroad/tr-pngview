//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// timer_dialog_ui_private.hh: timer dialog box UI class
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

INT_PTR
timer_dialog_ui::WmInitdialog (HWND hwnd, UINT uMsg,
                                        WPARAM wParam, LPARAM lParam)
{
  SetDlgItemInt (hwnd, IDC_TIMER, interval_, FALSE);

  return dialogbox_class<timer_dialog_ui>::WmInitdialog
    (hwnd, uMsg, wParam, lParam);
}

INT_PTR
timer_dialog_ui::Idok (HWND hwnd, WORD, WORD, LPARAM)
{
  UINT i;
  BOOL bsuccess;

  i = GetDlgItemInt (hwnd, IDC_TIMER, &bsuccess, FALSE);

  if (!bsuccess)
    {
      MessageBox (hwnd, TEXT ("Invalid"), TEXT ("Error"),
                  MB_ICONERROR | MB_OK);
      SetDlgItemInt (hwnd, IDC_TIMER, interval_, FALSE);

      return TRUE;
    }

  if ( i < USER_TIMER_MINIMUM )
    {
      MessageBox (hwnd, TEXT ("Too small"), TEXT ("Warning"),
                  MB_ICONWARNING | MB_OK);
      SetDlgItemInt (hwnd, IDC_TIMER, USER_TIMER_MINIMUM, FALSE);

      return TRUE;
    }
  else if ( i > USER_TIMER_MAXIMUM )
    {
      MessageBox (hwnd, TEXT ("Too large"), TEXT ("Warning"),
                  MB_ICONWARNING | MB_OK);
      SetDlgItemInt (hwnd, IDC_TIMER, USER_TIMER_MAXIMUM, FALSE);

      return TRUE;
    }

  EndDialog (hwnd, i);

  return TRUE;
}

INT_PTR
timer_dialog_ui::Idcancel (HWND hwnd, WORD, WORD, LPARAM)
{
  EndDialog (hwnd, interval_);

  return TRUE;
}
