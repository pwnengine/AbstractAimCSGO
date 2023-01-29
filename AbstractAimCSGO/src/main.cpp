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

  const auto list { interfaces::get_interface<interfaces::i_client_ent_list>("VClientEntityList003", "client.dll") };

  do {
    std::cout << "tick\n";
    for(int q { 0 }; q <= 64; ++q) {
      const auto player { list->GetClientEntity(q) };
      if(!player) {
        continue;
      }

      std::cout << "ent " << q << " " << player->get_health() << "\n";
    }
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