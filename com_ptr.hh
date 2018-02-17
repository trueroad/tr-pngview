//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// com_ptr.hh: COM smart pointer class
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

#ifndef INCLUDE_GUARD_COM_PTR_HH
#define INCLUDE_GUARD_COM_PTR_HH

#include <objbase.h>

template <class T>
class com_ptr
{
  class disable_AddRef_Release: public T
  {
  private:
    STDMETHODIMP_(ULONG) AddRef ();
    STDMETHODIMP_(ULONG) Release ();
  };

public:
  com_ptr () = default;
  ~com_ptr ()
  {
    if (ptr_)
      ptr_->Release ();
  }

  HRESULT CoCreateInstance (REFCLSID rclsid,
                            LPUNKNOWN pUnkOuter = nullptr,
                            DWORD dwClsContext = CLSCTX_ALL)
  {
    return ::CoCreateInstance (rclsid, pUnkOuter, dwClsContext,
                               IID_PPV_ARGS (&ptr_));
  }
  disable_AddRef_Release * operator-> () const noexcept
  {
    return static_cast<disable_AddRef_Release *> (ptr_);
  }

  operator T* () const noexcept
  {
    return ptr_;
  }
  T& operator* () const noexcept
  {
    return *ptr_;
  }
  T** operator& () noexcept
  {
    return &ptr_;
  }

private:
  T *ptr_ = nullptr;

  com_ptr (const com_ptr&) = delete;
  com_ptr& operator= (const com_ptr&) = delete;
  com_ptr (com_ptr&&) = delete;
  com_ptr& operator= (com_ptr&&) = delete;
};

#endif // INCLUDE_GUARD_COM_PTR_HH
