//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// mouseactivate.hh: Mouse activate class
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

#ifndef INCLUDE_GUARD_MOUSEACTIVATE_HH
#define INCLUDE_GUARD_MOUSEACTIVATE_HH

#include <windows.h>

#include "window.hh"

template <class Derived>
class mouseactivate: virtual public window_class<Derived>
{
public:
  mouseactivate ()
  {
    this->add_procedure (WM_MOUSEACTIVATE, WmMouseactivate);
  }
  ~mouseactivate () = default;

protected:
  LRESULT WmMouseactivate (HWND, UINT, WPARAM, LPARAM);

private:
  mouseactivate (const mouseactivate&) = delete;
  mouseactivate& operator= (const mouseactivate&) = delete;
  mouseactivate (mouseactivate&&) = delete;
  mouseactivate& operator= (mouseactivate&&) = delete;
};

#include "mouseactivate_private.hh"

#endif // INCLUDE_GUARD_MOUSEACTIVATE_HH
