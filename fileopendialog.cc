//
// tr-pngview
// https://github.com/trueroad/tr-pngview
//
// fileopendialog.cc: File open dialog
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

#define _WIN32_WINNT 0x0600

#include "fileopendialog.hh"

#include <string>

#include <windows.h>
#include <shobjidl.h>

#include "com_init.hh"
#include "com_ptr.hh"
#include "com_heap_ptr.hh"

namespace
{
  COMDLG_FILTERSPEC rgSpec [] =
    {
      { L"PNG file", L"*.png" },
      { L"All", L"*.*" }
    };
}

std::wstring file_open_dialog (const std::wstring &prev_name)
{
  std::wstring retval;
  com_init ci;

  if (SUCCEEDED (ci))
  {
    com_ptr<IFileOpenDialog> pFileOpen;

    HRESULT hr = pFileOpen.CoCreateInstance (__uuidof (FileOpenDialog));
    if (SUCCEEDED (hr))
      {
        pFileOpen->SetFileTypes (sizeof (rgSpec) / sizeof (rgSpec[0]),
                                 rgSpec);
        if (!prev_name.empty ())
          pFileOpen->SetFileName (prev_name.c_str ());
        hr = pFileOpen->Show (nullptr);

        if (SUCCEEDED (hr))
          {
            com_ptr<IShellItem> pItem;
            hr = pFileOpen->GetResult (&pItem);

            if (SUCCEEDED (hr))
              {
                com_heap_ptr<WCHAR> pszFilePath;
                hr = pItem->GetDisplayName (SIGDN_FILESYSPATH, &pszFilePath);

                if (SUCCEEDED (hr))
                  retval = pszFilePath;
              }
          }
      }
  }

  return retval;
}
