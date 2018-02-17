//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// dialogbox.hh: Base dialog box class
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

#ifndef INCLUDE_DIALOGBOX_HH
#define INCLUDE_DIALOGBOX_HH

#include <unordered_map>

#include <windows.h>

#include "dlgprocmap_init_base.hh"
#include "dlgcmdmap_init_base.hh"

template <class Derived>
class dialogbox_class: virtual public dlgprocmap_init_base<Derived>,
                       virtual public dlgcmdmap_init_base<Derived>
{
  using procedure = INT_PTR (Derived::*) (HWND, UINT, WPARAM, LPARAM);
  using cmdproc = INT_PTR (Derived::*) (HWND, WORD, WORD, LPARAM);

public:
  dialogbox_class ()
  {
    add_procedure (WM_INITDIALOG, WmInitdialog);
    add_procedure (WM_COMMAND, WmCommand);
  }
  virtual ~dialogbox_class () = default;

  INT_PTR dialogbox (HINSTANCE, LPCTSTR, HWND);

protected:
  void add_procedure (UINT uMsg, procedure proc)
  {
    procedures_[uMsg] = proc;
  }
  void flush_temp_procmap (void)
  {
    dlgprocmap_init_base<Derived>::flush_temp_procmap (&procedures_);
  }
  void add_cmdprocedure (WORD wId, cmdproc proc)
  {
    cmdprocs_[wId] = proc;
  }
  void flush_temp_cmdprocmap (void)
  {
    dlgcmdmap_init_base<Derived>::flush_temp_cmdprocmap (&cmdprocs_);
  }

  INT_PTR WmInitdialog (HWND, UINT, WPARAM, LPARAM)
  {
    return TRUE; // Set default keyboard focus
  }

  INT_PTR enddialog (HWND hwnd, WORD, WORD wId, LPARAM)
  {
    EndDialog (hwnd, wId);
    return TRUE;
  }

private:
  static INT_PTR CALLBACK dlgproc_static (HWND, UINT, WPARAM, LPARAM);

  INT_PTR WmCommand (HWND, UINT, WPARAM, LPARAM);

  std::unordered_map<UINT, procedure> procedures_;
  std::unordered_map<WORD, cmdproc> cmdprocs_;
};

#include "dialogbox_private.hh"

#endif // INCLUDE_DIALOGBOX_HH
