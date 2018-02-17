//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// dlgprocmap_init_base.hh: Dialog box procedure map initialization base class
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

#ifndef INCLUDE_GUARD_DLGPROCMAP_INIT_BASE_HH
#define INCLUDE_GUARD_DLGPROCMAP_INIT_BASE_HH

#include <unordered_map>
#include <utility>
#include <vector>

#include <windows.h>

template <class Derived>
class dlgprocmap_init_base
{
  using procedure = INT_PTR (Derived::*) (HWND, UINT, WPARAM, LPARAM);

public:
  dlgprocmap_init_base () = default;
  virtual ~dlgprocmap_init_base () = default;

protected:
  void add_temp_procmap (UINT uMsg, procedure proc)
  {
    procedures_temp_.push_back (std::make_pair (uMsg, proc));
  }
  void flush_temp_procmap (std::unordered_map<UINT, procedure> *m)
  {
    for (const auto &p: procedures_temp_)
      {
        (*m)[p.first] = p.second;
      }
    procedures_temp_.clear ();
  }

private:
  std::vector<std::pair<UINT, procedure>> procedures_temp_;

  dlgprocmap_init_base (const dlgprocmap_init_base&) = delete;
  dlgprocmap_init_base& operator= (const dlgprocmap_init_base&) = delete;
  dlgprocmap_init_base (dlgprocmap_init_base&&) = delete;
  dlgprocmap_init_base& operator= (dlgprocmap_init_base&&) = delete;
};

#endif // INCLUDE_GUARD_DLGPROCMAP_INIT_BASE_HH
