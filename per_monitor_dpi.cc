//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// per_monitor_dpi.cc: Per monitor DPI class
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

#include "per_monitor_dpi.hh"

#include <windows.h>

per_monitor_dpi::module_user32dll
per_monitor_dpi::mu_;

per_monitor_dpi::LPENABLENONCLIENTDPISCALING
per_monitor_dpi::lpfnEnableNonClientDpiScaling_ {NULL};

per_monitor_dpi::LPSETTHREADDPIAWARENESSCONTEXT
per_monitor_dpi::lpfnSetThreadDpiAwarenessContext_ {NULL};

bool
per_monitor_dpi::bswitchaware_;

per_monitor_dpi::per_monitor_dpi ()
{
  lpfnEnableNonClientDpiScaling_ =
    reinterpret_cast<LPENABLENONCLIENTDPISCALING>
    (mu_.get_proc_address ("EnableNonClientDpiScaling"));
  lpfnSetThreadDpiAwarenessContext_ =
    reinterpret_cast<LPSETTHREADDPIAWARENESSCONTEXT>
    (mu_.get_proc_address ("SetThreadDpiAwarenessContext"));

  if (SetThreadDpiAwarenessContext
      (DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2))
    {
      // Windows 10 Creators Update (1703) +
      bswitchaware_ = false;
    }
  else
    {
      // Windows 10 Anniversary Update (1607)
      bswitchaware_ = true;
      SetThreadDpiAwarenessContext (DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
    }
}

// EnableNonClientDpiScaling: Windows 10 Anniversary Update (1607) +
void
per_monitor_dpi::EnableNonClientDpiScaling (HWND hwnd)
{
  if (lpfnEnableNonClientDpiScaling_)
    lpfnEnableNonClientDpiScaling_ (hwnd);
}

// SetThreadDpiAwarenessContext: Windows 10 Anniversary Update (1607) +
HANDLE
per_monitor_dpi::SetThreadDpiAwarenessContext (HANDLE haware)
{
  if (lpfnSetThreadDpiAwarenessContext_)
    return lpfnSetThreadDpiAwarenessContext_ (haware);
  return NULL;
}
