//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// window.hh: Base window class
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

#ifndef INCLUDE_WINDOW_HH
#define INCLUDE_WINDOW_HH

#include <unordered_map>

#include <windows.h>

#include "procmap_init_base.hh"

template <class Derived>
class window_class: virtual public procmap_init_base<Derived>
{
  using procedure = LRESULT (Derived::*) (HWND, UINT, WPARAM, LPARAM);

public:
  window_class () = default;
  virtual ~window_class () = default;

  HINSTANCE get_hInst (void) const noexcept
  {
    return hInst_;
  }
  HWND get_hwnd (void) const noexcept
  {
    return hwnd_;
  }

  bool init (HINSTANCE, int);
  int message_loop (void);

protected:
  PCTSTR classname_ {TEXT ("TRWINDOWCLASS")};
  PCTSTR title_ {TEXT ("tr-window")};

  void add_procedure (UINT uMsg, procedure proc)
  {
    procedures_[uMsg] = proc;
  }
  void flush_temp_procmap (void)
  {
    procmap_init_base<Derived>::flush_temp_procmap (&procedures_);
  }

  bool register_class (void);
  bool create_window (void);
  void show_and_update_window (int);

  HINSTANCE hInst_ {nullptr};
  HWND hwnd_ {nullptr};

private:
  static LRESULT CALLBACK wndproc_static (HWND, UINT, WPARAM, LPARAM);

  std::unordered_map<UINT, procedure> procedures_;
};

#include "window_private.hh"

#endif // INCLUDE_WINDOW_HH
