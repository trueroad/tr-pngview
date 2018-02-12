//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// per_monitor_dpi.hh: Per monitor DPI class
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

#ifndef INCLUDE_GUARD_PER_MONITOR_DPI_HH
#define INCLUDE_GUARD_PER_MONITOR_DPI_HH

#include <windows.h>

// DPI_AWARENESS_CONTEXT handle
#if !defined (DPI_AWARENESS_CONTEXT_UNAWARE) && \
  !defined (DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) && \
  !defined (DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE) && \
  !defined (DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)
DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);
#endif

// DPI_AWARENESS_CONTEXT_SYSTEM_AWARE:
//   Windows 10 Anniversary Update (1607) +
#ifndef DPI_AWARENESS_CONTEXT_SYSTEM_AWARE
#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE \
  (reinterpret_cast<DPI_AWARENESS_CONTEXT> (-2))
#endif

// DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE:
//   Windows 10 Anniversary Update (1607) +
#ifndef DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE \
  (reinterpret_cast<DPI_AWARENESS_CONTEXT> (-3))
#endif

// DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2:
//   Windows 10 Creators Update (1703) +
#ifndef DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 \
  (reinterpret_cast<DPI_AWARENESS_CONTEXT> (-4))
#endif

class per_monitor_dpi
{
public:
  per_monitor_dpi ();
  ~per_monitor_dpi () = default;

  static bool get_switch_aware (void) noexcept
  {
    return bswitchaware_;
  }

  static void EnableNonClientDpiScaling (HWND);
  static DPI_AWARENESS_CONTEXT
  SetThreadDpiAwarenessContext (DPI_AWARENESS_CONTEXT);

private:
  using LPENABLENONCLIENTDPISCALING = BOOL (WINAPI *) (HWND);
  using LPSETTHREADDPIAWARENESSCONTEXT = DPI_AWARENESS_CONTEXT
    (WINAPI *) (DPI_AWARENESS_CONTEXT);

  class module_user32dll
  {
  public:
    module_user32dll ()
    {
      hMod_ = LoadLibrary (TEXT ("user32.dll"));
    }
    ~module_user32dll ()
    {
      FreeLibrary (hMod_);
    }

    FARPROC get_proc_address (LPCSTR s)
    {
      if (hMod_)
        return GetProcAddress (hMod_, s);
      else
        return nullptr;
    }

  private:
    HMODULE hMod_;
  };

  static module_user32dll mu_;
  static LPENABLENONCLIENTDPISCALING lpfnEnableNonClientDpiScaling_;
  static LPSETTHREADDPIAWARENESSCONTEXT lpfnSetThreadDpiAwarenessContext_;
  static bool bswitchaware_;

  per_monitor_dpi (const per_monitor_dpi&) = delete;
  per_monitor_dpi& operator= (const per_monitor_dpi&) = delete;
  per_monitor_dpi (per_monitor_dpi&&) = delete;
  per_monitor_dpi& operator= (per_monitor_dpi&&) = delete;
};

class dpi_system_aware
{
public:
  dpi_system_aware ()
  {
    if (per_monitor_dpi::get_switch_aware ())
      per_monitor_dpi::SetThreadDpiAwarenessContext
        (DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
  }
  ~dpi_system_aware ()
  {
    if (per_monitor_dpi::get_switch_aware ())
      per_monitor_dpi::SetThreadDpiAwarenessContext
        (DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
  }
};

#endif // INCLUDE_GUARD_PER_MONITOR_DPI_HH
