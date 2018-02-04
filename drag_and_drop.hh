//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// drag_and_drop.hh: Drag and drop class
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

#ifndef INCLUDE_GUARD_DRAG_AND_DROP_HH
#define INCLUDE_GUARD_DRAG_AND_DROP_HH

#include <windows.h>

#include "procmap_init_base.hh"

template <class Derived>
class drag_and_drop:  virtual public procmap_init_base<Derived>
{
public:
  drag_and_drop ()
  {
    this->add_temp_procmap (WM_DROPFILES, WmDropfiles);
    this->add_temp_procmap (WM_CREATE, WmCreate);
    this->add_temp_procmap (WM_DESTROY, WmDestroy);
  }
  ~drag_and_drop () = default;

protected:
  LRESULT WmDropfiles (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmCreate (HWND, UINT, WPARAM, LPARAM);
  LRESULT WmDestroy (HWND, UINT, WPARAM, LPARAM);
};

#include "drag_and_drop_private.hh"
  
#endif // INCLUDE_GUARD_DRAG_AND_DROP_HH
