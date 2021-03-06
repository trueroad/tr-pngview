//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// timer_handler.hh: Timer handler class
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

#ifndef INCLUDE_GUARD_TIMER_HANDLER_HH
#define INCLUDE_GUARD_TIMER_HANDLER_HH

#include <windows.h>

#include "procmap_init_base.hh"
#include "cmdmap_init_base.hh"
#include "pngview_res.h"

template <class Derived>
class timer_handler:  virtual public procmap_init_base<Derived>,
                      virtual public cmdmap_init_base<Derived>
{
public:
  timer_handler ()
  {
    this->add_temp_procmap (WM_TIMER, WmTimer);
    this->add_temp_procmap (WM_CREATE, WmCreate);
    this->add_temp_procmap (WM_DESTROY, WmDestroy);

    this->add_temp_cmdprocmap (IDM_USE_TIMER, Cmd_idm_use_timer);
    this->add_temp_cmdprocmap (IDM_SET_INTERVAL, Cmd_idm_set_interval);
  }
  ~timer_handler () = default;

protected:
  LRESULT WmTimer (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmCreate (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmDestroy (HWND, UINT, WPARAM, LPARAM);

  LRESULT Cmd_idm_use_timer (HWND, WORD, WORD, LPARAM);
  LRESULT Cmd_idm_set_interval (HWND, WORD, WORD, LPARAM);

private:
  const UINT_PTR timerid_ {1};
  bool btimer_ {true};
  UINT interval_ {100}; // 100 ms

  void set_timer (HWND);
};

#include "timer_handler_private.hh"

#endif // GUARD_TIMER_HANDLER_HH
