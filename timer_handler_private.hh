//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// pngview_window.cc: pngview window class
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

#include <windows.h>

#include "stretch.hh"

template <class Derived>
LRESULT
timer_handler<Derived>::WmTimer (HWND hwnd, UINT uMsg,
                                 WPARAM wParam, LPARAM lParam)
{
  if (static_cast<UINT_PTR> (wParam) == timerid_)
    {
      auto &p {static_cast<Derived&> (*this)};
      
      p.get_stretch_bitmap ().timer ();

      return 0;
    }

  return DefWindowProc (hwnd, uMsg, wParam, lParam);;
}

template <class Derived>
LRESULT
timer_handler<Derived>::WmCreate (HWND hwnd, UINT uMsg,
                                  WPARAM wParam, LPARAM lParam)
{
  SetTimer (hwnd , timerid_ , 100 , nullptr); // 100 ms

  return 0;
}

template <class Derived>
LRESULT
timer_handler<Derived>::WmDestroy (HWND hwnd, UINT uMsg,
                                   WPARAM wParam, LPARAM lParam)
{
  KillTimer (hwnd, timerid_);

  return 0;
}
