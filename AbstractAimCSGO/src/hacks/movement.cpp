#include "include.h"

void hacks::movement::move(user_cmd* cmd, const unsigned int lp, const unsigned fl) {
  if(!vars::bhop) return;

  if(!(*reinterpret_cast<int*>(lp + fl) & 1)) {
    cmd->buttons &= ~IN_JUMP;
  }
}