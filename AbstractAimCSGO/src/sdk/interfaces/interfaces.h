#ifndef INTERFACES_H
#define INTERFACES_H

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

  inline void* g_Client = nullptr;
  inline void* g_ClientMode = nullptr;

  class i_client_ent {
  public:
    const int& get_health() const noexcept {
      return *reinterpret_cast<int*>((uintptr_t)this + 0x100);
    }
  };

  class i_client_ent_list
  {
  public:
    // Get IClientNetworkable interface for specified entity
    virtual void* GetClientNetworkable(int entnum) = 0;
    virtual void* GetClientNetworkableFromHandle(DWORD hEnt) = 0;
    virtual void* GetClientUnknownFromHandle(DWORD hEnt) = 0;

    // NOTE: This function is only a convenience wrapper.
    // It returns GetClientNetworkable( entnum )->GetIClientEntity().
    virtual i_client_ent* GetClientEntity(int entnum) = 0;
    virtual i_client_ent* GetClientEntityFromHandle(DWORD hEnt) = 0;

    // Returns number of entities currently in use
    virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

    // Returns highest index actually used
    virtual int					GetHighestEntityIndex(void) = 0;

    // Sizes entity list to specified size
    virtual void				SetMaxEntities(int maxents) = 0;
    virtual int					GetMaxEntities() = 0;
  };


}

#endif