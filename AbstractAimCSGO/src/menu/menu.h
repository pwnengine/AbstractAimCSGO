#ifndef MENU_H
#define MENU_H

#include <directx9/d3d9.h>
#include <directx9/d3dx9.h>

#include <string>

struct pos2d_t {
  int x { };
  int y { };
};

class fonts {
public:
  void setup_fonts(IDirect3DDevice9* pdevice);
  ID3DXFont* arial_big { nullptr };
  ID3DXFont* arial_small { nullptr };
  ID3DXFont* tahoma_big { nullptr };
  ID3DXFont* tahoma_small { nullptr };
};

class hack_menu {
public:
  void draw(IDirect3DDevice9* pdevice);
private:
  void begin_menu(IDirect3DDevice9* pdevice, D3DRECT* rect);
  void add_item(IDirect3DDevice9* pdevice, const char* text, int& val, int min, int max, int index, pos2d_t& pos);
  void handle_input();
  fonts font { };
  pos2d_t base_pos { };
  int selection { 3 };
};
inline hack_menu menu { };

#endif
