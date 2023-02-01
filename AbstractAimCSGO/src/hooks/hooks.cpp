#include "../sdk/interfaces/interfaces.h"
#include "../sdk/interfaces/user_cmd.h"
#include "../hacks/include.h"
#include "hooks.h"

#include "../menu/menu.h"

#include <directx9/d3d9.h>
#include <directx9/d3dx9.h>

using end_scene_fn = HRESULT(__stdcall*)(IDirect3DDevice9*);
static end_scene_fn o_end_scene { nullptr };

using create_move_fn = bool(__thiscall*)(void*, float, user_cmd*);
static create_move_fn o_create_move { nullptr };

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

  hacks::movement::move(cmd, local_player, m_flags);

  return false;
}

HRESULT __stdcall hk_end_scene(IDirect3DDevice9* pdevice) {
  menu.draw(pdevice);

  return o_end_scene(pdevice);
}

MH_STATUS hooks::init() {
  IDirect3D9* pd3d { Direct3DCreate9(D3D_SDK_VERSION) };
  if(pd3d == nullptr)
    return MH_UNKNOWN;

  D3DPRESENT_PARAMETERS present_params { };
  present_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
  present_params.hDeviceWindow = GetForegroundWindow();
  present_params.Windowed = true;

  pd3d->CreateDevice(D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    GetForegroundWindow(),
    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
    &present_params,
    &interfaces::device);

  MH_STATUS status { MH_OK };
  
  status = MH_Initialize();
  if(status != MH_OK)
    return status;

  status = MH_CreateHook(
    (*reinterpret_cast<void***>(interfaces::device))[42],
    &hk_end_scene,
    reinterpret_cast<void**>(&o_end_scene)
  );
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

  interfaces::device->Release();
  pd3d->Release();

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


