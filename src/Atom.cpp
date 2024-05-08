//
// Created by Marlon Käsemann on 06.05.24.
//

#include "Atom.h"

Atom::Atom(Vector2 _pos, int _anum){
    pos = _pos;
    anum = _anum;
    is_active = false;
    is_dragged = false;
    sprite = LoadTexture((ASSET_PATH + SYM[anum] + ".png").c_str());
    sprite_diameter = SPRITE_SIZE * SCALE_FACTOR[anum];
    sprite_radius = sprite_diameter / 2;
    middle_point = {pos.x + sprite_radius, pos.y + sprite_radius};
}

Atom::is_hovered() {
    auto [x, y] = middle_point;
    auto [mx, my] = GetMousePosition();
    return mx >= x - sprite_radius && mx <= x + sprite_radius && my >= y - sprite_radius && my <= y + sprite_radius;
}

Atom::_handle_drag(){
    bool left_mouse_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    if(is_hovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) is_active = true;
    if(is_hovered() && left_mouse_down) is_dragged = true;
    if(is_dragged && !left_mouse_down) is_dragged = false;
    if(is_dragged){
        pos = {GetMousePosition().x - sprite_radius, GetMousePosition().y - sprite_radius };
        middle_point = {pos.x + sprite_radius, pos.y + sprite_radius};
    }
}

Atom::refresh_state() {
    _handle_drag();
}

Atom::render() {
    DrawTextureEx(sprite, pos, 0.0, SCALE_FACTOR[anum], WHITE);
}