#ifndef CLIENT_H
#define CLIENT_H

#include <windows.h>

class iclient_ent {
public:
  const int& get_health() const noexcept {
    return *reinterpret_cast<int*>((uintptr_t)this + 0x100);
  }
};

class iclient_ent_list {
public:
  virtual void* get_client_networkable(int ent_num) = 0;
  virtual void* get_client_networkable_from_handle(DWORD hent) = 0;
  virtual void* get_client_unknown_from_handle(DWORD hent) = 0;

  virtual iclient_ent* get_client_entity(int ent_num) = 0;
  virtual iclient_ent* get_client_entity_from_handle(DWORD hent) = 0;

  // Returns number of entities currently in use
  virtual int					number_of_entities(bool binclude_nonnetworkable) = 0;

  // Returns highest index actually used
  virtual int					get_highest_entity_index(void) = 0;

  // Sizes entity list to specified size
  virtual void				set_max_entities(int maxents) = 0;
  virtual int					set_max_entities() = 0;
};

#endif