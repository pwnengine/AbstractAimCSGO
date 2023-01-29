#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "sdk/interfaces/interfaces.h"

#include "minhook/MinHook.h"

DWORD WINAPI hack(HINSTANCE hmod) {
  AllocConsole();
  FILE* fp = std::freopen("CONOUT$", "w+", stdout);

  

  do {
    std::cout << "tick\n";

    Sleep(100);
  } while(!(GetAsyncKeyState(VK_END) & 0x8000));

  if(fp != nullptr)
    std::fclose(fp);

  FreeConsole();
  FreeLibraryAndExitThread(hmod, 0);
}

BOOL WINAPI DllMain(HINSTANCE hmod, DWORD reason, LPVOID reserved) {
  if(reason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hmod);
    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hack, hmod, 0, nullptr);
  }

  return TRUE;
}