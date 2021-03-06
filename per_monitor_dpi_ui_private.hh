//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// per_monitor_dpi_ui_private.hh: Per monitor DPI UI class
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

template <class Derived>
LRESULT
per_monitor_dpi_ui<Derived>::WmDpiChanged (HWND hwnd, UINT,
                                           WPARAM wParam, LPARAM lParam)
{
  LPRECT lprc {reinterpret_cast <LPRECT> (lParam)};

  auto &p {static_cast<Derived&> (*this)};
  p.get_stretch_bitmap ().set_dpi (LOWORD (wParam), HIWORD (wParam));

  SetWindowPos(hwnd, nullptr, lprc->left, lprc->top,
               lprc->right - lprc->left, lprc->bottom - lprc->top,
               SWP_NOZORDER);

  return 0;
}

template <class Derived>
LRESULT
per_monitor_dpi_ui<Derived>::WmNcCreate (HWND hwnd, UINT uMsg,
                                         WPARAM wParam, LPARAM lParam)
{
  pmd.EnableNonClientDpiScaling (hwnd);

  UINT dpi = pmd.GetDpiForWindow (hwnd);
  auto &p {static_cast<Derived&> (*this)};
  p.get_stretch_bitmap ().set_dpi (dpi, dpi);

  return DefWindowProc (hwnd, uMsg, wParam, lParam);
}
