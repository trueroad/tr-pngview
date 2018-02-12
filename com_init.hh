//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// com_init.hh: COM initialization class
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

#ifndef INCLUDE_GUARD_COM_INIT_HH
#define INCLUDE_GUARD_COM_INIT_HH

#include <objbase.h>

class com_init
{
public:
  com_init (DWORD dwCoInit = COINIT_APARTMENTTHREADED |
            COINIT_DISABLE_OLE1DDE)
  {
    hr_ = CoInitializeEx (nullptr, dwCoInit);
  }
  ~com_init ()
  {
    if (SUCCEEDED (hr_))
      CoUninitialize ();
  }

  operator HRESULT () const noexcept
  {
    return hr_;
  }

private:
  HRESULT hr_;

  com_init (const com_init&) = delete;
  com_init& operator= (const com_init&) = delete;
  com_init (com_init&&) = delete;
  com_init& operator= (com_init&&) = delete;
};

#endif // INCLUDE_GUARD_COM_INIT_HH
