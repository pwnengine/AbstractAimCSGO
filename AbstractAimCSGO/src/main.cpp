#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "sdk/interfaces/interfaces.h"
#include "sdk/interfaces/client.h"
#include "hooks/hooks.h"

#include "minhook/MinHook.h"

DWORD WINAPI hack(HINSTANCE hmod) {
  AllocConsole();
  FILE* fp = std::freopen("CONOUT$", "w+", stdout);

  interfaces::client = interfaces::get_interface<void>("VClient018", "client.dll");
  interfaces::client_mode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(interfaces::client))[10] + 5);
  interfaces::entity_list = interfaces::get_interface<iclient_ent_list>("VClientEntityList003", "client.dll");

  if(hooks::init() != MH_OK) {
    std::cout << "Failed to init() hooks\n";
    getchar();
    FreeConsole();
    FreeLibraryAndExitThread(hmod, 0);
  }

  do {
    //std::cout << "tick\n";
    for(int q { 0 }; q <= 64; ++q) {
      const auto player { interfaces::entity_list->get_client_entity(q) };
      if(!player) {
        continue;
      }

      std::cout << "ent " << q << " " << player->get_health() << "\n";
    }
    Sleep(100);
  } while(!(GetAsyncKeyState(VK_END) & 0x8000));

  if(fp != nullptr)
    std::fclose(fp);

  if(hooks::unhook() != MH_OK) {
    std::cout << "Failed to init() hooks\n";
    getchar();
  }
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