#ifndef USER_CMD_H
#define USER_CMD_H

struct vec3 {
  float x, y, z;
};

enum cmd_buttons : int {
  IN_ATTACK = (1 << 0),
  IN_JUMP = (1 << 1),
  IN_DUCK = (1 << 2),
  IN_FORWARD = (1 << 3),
  IN_BACK = (1 << 4),
  IN_USE = (1 << 5),
  IN_CANCEL = (1 << 6),
  IN_LEFT = (1 << 7),
  IN_RIGHT = (1 << 8),
  IN_MOVELEFT = (1 << 9),
  IN_MOVERIGHT = (1 << 10),
  IN_SECOND_ATTACK = (1 << 11),
  IN_RUN = (1 << 12),
  IN_RELOAD = (1 << 13),
  IN_LEFT_ALT = (1 << 14),
  IN_RIGHT_ALT = (1 << 15),
  IN_SCORE = (1 << 16),
  IN_SPEED = (1 << 17),
  IN_WALK = (1 << 18),
  IN_ZOOM = (1 << 19),
  IN_FIRST_WEAPON = (1 << 20),
  IN_SECOND_WEAPON = (1 << 21),
  IN_BULLRUSH = (1 << 22),
  IN_FIRST_GRENADE = (1 << 23),
  IN_SECOND_GRENADE = (1 << 24),
  IN_MIDDLE_ATTACK = (1 << 25)
};

struct user_cmd {
  void* vmt;
  int command_number;
  int tick_count;
  vec3 view_point;
  vec3 aim_direction;
  float forward_move;
  float side_move;
  float up_move;
  int buttons;
  char impulse;
  int weapon_select;
  int weapon_subType;
  int random_seed;
  short mouse_delta_x;
  short mouse_delta_y;
  bool has_been_predicted;
  vec3 head_angles;
  vec3 head_offset;
};

#endif