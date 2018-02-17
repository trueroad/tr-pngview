//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// dialogbox_private.hh: Base dialog box class
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
INT_PTR
dialogbox_class<Derived>::dialogbox (HINSTANCE hInstance, LPCTSTR lpTemplate,
                                     HWND hWndParent)
{
  return DialogBoxParam (hInstance, lpTemplate, hWndParent, dlgproc_static,
                         reinterpret_cast <LPARAM>
                         (dynamic_cast<Derived*> (this)));
}

template <class Derived>
INT_PTR CALLBACK
dialogbox_class<Derived>::dlgproc_static (HWND hwnd, UINT uMsg,
                                          WPARAM wParam, LPARAM lParam)
{
  Derived *dc;
  if (uMsg == WM_INITDIALOG)
    {
      dc = reinterpret_cast<Derived*> (lParam);
      SetWindowLongPtr (hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR> (dc));
    }
  else
    {
      dc = reinterpret_cast<Derived*>
        (GetWindowLongPtr (hwnd, GWLP_USERDATA));
    }

  if (dc)
    {
      auto val {dc->procedures_.find (uMsg)};
      if (val != dc->procedures_.end ())
        return (dc->*(val->second)) (hwnd, uMsg, wParam, lParam);
    }

  return FALSE;
}

template <class Derived>
INT_PTR
dialogbox_class<Derived>::WmCommand (HWND hwnd, UINT,
                                     WPARAM wParam, LPARAM lParam)
{
  auto &p {static_cast<Derived&> (*this)};

  auto wCode {HIWORD (wParam)};
  auto wId {LOWORD (wParam)};

  auto val {cmdprocs_.find (wId)};
  if (val != cmdprocs_.end ())
    return (p.*(val->second)) (hwnd, wCode, wId, lParam);
  return FALSE;
}
