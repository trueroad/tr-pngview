//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// drag_and_drop_private.hh: Drag and drop class
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

#include <string>

#include <windows.h>

#include "stretch.hh"

template <class Derived>
LRESULT
drag_and_drop<Derived>::WmDropfiles (HWND hwnd, UINT uMsg,
                                     WPARAM wParam, LPARAM lParam)
{
  {
    std::wstring buff;
    HDROP hd = reinterpret_cast<HDROP> (wParam);

    buff.resize (DragQueryFileW (hd, 0, nullptr, 0) + 1);
    DragQueryFileW (hd, 0, &buff.at (0), buff.size ());
    DragFinish (hd);

    {
      auto &p {static_cast<Derived&> (*this)};

      p.get_stretch_bitmap ().load_file (buff);
    }
  }

  return 0;
}

template <class Derived>
LRESULT
drag_and_drop<Derived>::WmCreate (HWND hwnd, UINT uMsg,
                                  WPARAM wParam, LPARAM lParam)
{
  DragAcceptFiles (hwnd, TRUE);

  return 0;
}

template <class Derived>
LRESULT
drag_and_drop<Derived>::WmDestroy (HWND hwnd, UINT uMsg,
                                   WPARAM wParam, LPARAM lParam)
{
  DragAcceptFiles (hwnd, FALSE);

  return 0;
}
