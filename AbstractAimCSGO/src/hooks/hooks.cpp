#include "../sdk/interfaces/interfaces.h"
#include "../sdk/interfaces/user_cmd.h"
#include "hooks.h"

using create_move_fn = bool(__thiscall*)(void*, float, user_cmd*);
static create_move_fn o_create_move = nullptr;

constexpr DWORD dw_local_player { 0xDEA964 };
constexpr DWORD m_flags { 0x104 };

bool __stdcall hk_create_move(float frame_time, user_cmd* cmd) {
  if(cmd == nullptr || cmd->command_number == 0)
    return false;

  o_create_move(interfaces::client_mode, frame_time, cmd);

  static unsigned int client { reinterpret_cast<unsigned int>(GetModuleHandle("client.dll")) };
  const unsigned int local_player { *reinterpret_cast<unsigned int*>(client + dw_local_player) };
  if(!local_player)
    return false;

  if(!(*reinterpret_cast<int*>(local_player + m_flags) & 1)) {
    cmd->buttons &= ~IN_JUMP;
  }

  return false;
}

MH_STATUS hooks::init() {
  MH_STATUS status { MH_OK };
  
  status = MH_Initialize();
  if(status != MH_OK)
    return status;


  status = MH_CreateHook(
    (*static_cast<void***>(interfaces::client_mode))[24], 
    &hk_create_move, 
    reinterpret_cast<void**>(&o_create_move)    
  );
  if(status != MH_OK)
    return status;

  status = MH_EnableHook(MH_ALL_HOOKS);
  if(status != MH_OK)
    return status;

  return status;
}

MH_STATUS hooks::unhook() {
  MH_STATUS status { MH_OK };
  
  status = MH_DisableHook(MH_ALL_HOOKS);
  if(status != MH_OK)
    return status;

  status = MH_RemoveHook(MH_ALL_HOOKS);
  if(status != MH_OK)
    return status;

  status = MH_Uninitialize();
  if(status != MH_OK)
    return status;

  return status;
}


