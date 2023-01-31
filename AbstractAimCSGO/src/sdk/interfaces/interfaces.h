#ifndef INTERFACES_H
#define INTERFACES_H

#include "client.h"

#include <directx9/d3d9.h>
#include <windows.h>

using create_interface_fn = void* (*)(const char*, int*);

namespace interfaces {
  template <typename T>
  T* get_interface(const char* i_name, const char* lib) {
    HINSTANCE hmod {}; 
    FARPROC   func {};

    hmod = GetModuleHandleA(lib);
    if(!hmod) { return nullptr; }

    func = GetProcAddress(hmod, "CreateInterface");
    if(!func) { return nullptr; };

    create_interface_fn create_interface = reinterpret_cast<create_interface_fn>(func);

    return (T*)create_interface(i_name, nullptr);
  }

  inline void* client { nullptr };
  inline void* client_mode { nullptr };
  inline iclient_ent_list* entity_list { nullptr };
  inline IDirect3DDevice9* device { nullptr };
}

#endif