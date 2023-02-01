#include "menu.h"
#include "../vars.h"
#include <iostream>

void hack_menu::draw(IDirect3DDevice9* pdevice) {
  if(GetAsyncKeyState(VK_MBUTTON) & 1) vars::open = !vars::open;

  if(!vars::open)
    return;

  font.setup_fonts(pdevice);
  
  RECT rect { };
  pos2d_t pos { 0,0 };
  D3DRECT test_rect { 100, 100, 300, 500 };

  begin_menu(pdevice, &test_rect);
  {
    add_item(pdevice, "BHOP", vars::bhop, 0, 1, 1, pos);
    add_item(pdevice, "ESP", vars::esp, 0, 5, 2, pos);
    add_item(pdevice, "bro man2", vars::test_3, 0, 5, 3, pos);
    add_item(pdevice, "bro man2", vars::test_4, 0, 5, 4, pos);
  }
}

void hack_menu::begin_menu(IDirect3DDevice9* pdevice, D3DRECT* rect) {
  D3DRECT backup { *rect };
  rect->x1 = rect->x1 - 2;
  rect->y1 = rect->y1 - 2;
  rect->x2 = rect->x2 + 2;
  rect->y2 = rect->y2 + 2;
  pdevice->Clear(1, rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(149, 57, 110), 0.0f, 0);
  pdevice->Clear(1, &backup, D3DCLEAR_TARGET, D3DCOLOR_ARGB(1, 60, 82, 117), 0.0f, 0);
  base_pos = { rect->x1, rect->y1 };

  if(GetAsyncKeyState(VK_LSHIFT) & 1) {
    ++selection;
    if(selection > 4) selection = 1;
  }
}

void hack_menu::add_item(IDirect3DDevice9* pdevice, const char* text, int& val, int min, int max, int index, pos2d_t& pos) {
  int base_padding_x { 5 };
  int base_padding_y { 17 };
  int padding { 5 };
  int height { 35 };
  int width { 295 };
  
  D3DRECT rect {  };
  if(index == 1)
    rect = { base_pos.x + base_padding_x, base_pos.y + base_padding_y, width, base_pos.y + height };  
  else
    rect = { pos.x, pos.y, width, pos.y + (height / 2) };

  pos.x = rect.x1;
  pos.y = rect.y2 + padding;

  if(index == selection) {
    pdevice->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(173, 42, 152), 0.0f, 0);

    if((GetAsyncKeyState(VK_RBUTTON) & 1) && val < max) {
      val += 1;
    } else if((GetAsyncKeyState(VK_LBUTTON) & 1) && val > min) {
      val -= 1;
    }
  }
  else
    pdevice->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(56, 81, 117), 0.0f, 0);

  RECT text_rect { };
  SetRect(&text_rect, rect.x1 + 5, rect.y1 + 1, rect.x2 + 60, rect.y2);
  if(font.arial_small) {
    char buf[256] { };
    std::sprintf(buf, "                                           <     %d     >", val);
    font.arial_small->DrawTextA(NULL, text, -1, &text_rect, DT_LEFT, D3DCOLOR_XRGB(87, 200, 138));
    font.arial_small->DrawTextA(NULL, buf, -1, &text_rect, DT_LEFT, D3DCOLOR_XRGB(87, 200, 138));
  }
}

void fonts::setup_fonts(IDirect3DDevice9* pdevice) {
  if(tahoma_big == nullptr) {
    HRESULT hr { D3DXCreateFontA(pdevice,
      25,
      0,
      FW_NORMAL,
      1,
      false,
      DEFAULT_CHARSET,
      OUT_DEFAULT_PRECIS,
      ANTIALIASED_QUALITY,
      FF_DONTCARE,
      "Tahoma",
      &tahoma_big
      )
    };
  }

  if(tahoma_small == nullptr) {
    HRESULT hr { D3DXCreateFontA(pdevice,
      12,
      6,
      FW_NORMAL,
      1,
      false,
      DEFAULT_CHARSET,
      OUT_DEFAULT_PRECIS,
      ANTIALIASED_QUALITY,
      FF_DONTCARE,
      "Tahoma",
      &tahoma_small
      )
    };
  }

  if(arial_big == nullptr) {
    HRESULT hr { D3DXCreateFontA(pdevice,
      25,
      0,
      FW_NORMAL,
      1,
      false,
      DEFAULT_CHARSET,
      OUT_DEFAULT_PRECIS,
      ANTIALIASED_QUALITY,
      FF_DONTCARE,
      "Arial",
      &arial_big
      )
    };
  }

  if(arial_small == nullptr) {
    HRESULT hr { D3DXCreateFontA(pdevice,
      12,
      4,
      FW_NORMAL,
      1,
      false,
      DEFAULT_CHARSET,
      OUT_DEFAULT_PRECIS,
      ANTIALIASED_QUALITY,
      FF_DONTCARE,
      "Arial",
      &arial_small
      )
    };
  }
}
