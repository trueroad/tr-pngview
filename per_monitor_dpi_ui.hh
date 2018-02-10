//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// per_monitor_dpi_ui.hh: Per monitor DPI UI class
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

#ifndef INCLUDE_GUARD_PER_MONITOR_DPI_UI_HH
#define INCLUDE_GUARD_PER_MONITOR_DPI_UI_HH

#include <windows.h>

#include "procmap_init_base.hh"
#include "per_monitor_dpi.hh"

// WM_DPICHANGED: Windows 8.1+
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02e0
#endif

template <class Derived>
class per_monitor_dpi_ui: virtual public procmap_init_base<Derived>
{
public:
  per_monitor_dpi_ui ()
  {
    this->add_temp_procmap (WM_DPICHANGED, WmDpiChanged);
    this->add_temp_procmap (WM_NCCREATE, WmNcCreate);
  }
  ~per_monitor_dpi_ui () = default;

protected:
  LRESULT WmDpiChanged (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmNcCreate (HWND, UINT, WPARAM, LPARAM);

private:
  per_monitor_dpi pmd;
};

#include "per_monitor_dpi_ui_private.hh"

#endif // INCLUDE_GUARD_PER_MONITOR_DPI_UI_HH
