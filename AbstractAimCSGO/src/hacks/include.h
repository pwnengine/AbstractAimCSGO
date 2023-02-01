#ifndef INCLUDE_H
#define INCLUDE_H

#include "../sdk/interfaces/user_cmd.h"
#include "../vars.h"

namespace hacks {
  namespace movement { 
  void move(user_cmd* cmd, const unsigned int lp, const unsigned fl);
  }
}

#endif
