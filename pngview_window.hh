//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// pngview_window.hh: pngview window class
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

#ifndef INCLUDE_PNGVIEW_WINDOW_HH
#define INCLUDE_PNGVIEW_WINDOW_HH

#include <windows.h>

#include "window.hh"
#include "hideable_menu.hh"
#include "mouseactivate.hh"
#include "wm_command.hh"
#include "cmd_about.hh"
#include "cmd_exit.hh"
#include "stretch.hh"

class pngview_window: public window_class<pngview_window>,
                      public hideable_menu<pngview_window>,
                      public mouseactivate<pngview_window>,
                      public wm_command<pngview_window>,
                      public cmd_about<pngview_window>,
                      public cmd_exit<pngview_window>
{
public:
  pngview_window ()
  {
    classname_ = pngview_classname_;
    title_ = pngview_title_;

    flush_temp_procmap ();
    add_procedure (WM_PAINT, WmPaint);
    add_procedure (WM_TIMER, WmTimer);
    add_procedure (WM_LBUTTONDOWN, WmLbuttondown);
    add_procedure (WM_SIZE, WmSize);
    add_procedure (WM_DROPFILES, WmDropfiles);
    add_procedure (WM_CREATE, WmCreate);
    add_procedure (WM_DESTROY, WmDestroy);

    flush_temp_cmdprocmap ();
    add_cmdprocedure (IDM_DOT_BY_DOT, Cmd_idm_dot_by_dot);
    add_cmdprocedure (IDM_FILL, Cmd_idm_fill);
    add_cmdprocedure (IDM_CONTAIN, Cmd_idm_contain);
    add_cmdprocedure (IDM_COVER, Cmd_idm_cover);
  }
  ~pngview_window () = default;

private:
  LRESULT WmPaint (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmTimer (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmLbuttondown (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmSize (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmDropfiles (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmCreate (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmDestroy (HWND, UINT, WPARAM, LPARAM);

  LRESULT Cmd_idm_dot_by_dot (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_fill (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_contain (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_cover (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_about (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_exit (HWND, WORD, WORD, LPARAM);

  const PCTSTR pngview_classname_ {TEXT ("TRPNGVIEW")};
  const PCTSTR pngview_title_ {TEXT ("pngview")};
  const UINT_PTR timerid_ = 1;

  stretch_bitmap sb_;
};

#endif // INCLUDE_PNGVIEW_WINDOW_HH
