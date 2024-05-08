//
// Created by Marlon Käsemann on 06.05.24.
//

#ifndef MOLECULEBUILDER_ATOM_H
#define MOLECULEBUILDER_ATOM_H

#include "config.h"

class Atom {
private:
    int anum;          // atomic number
    Vector2 pos;       // position on screen in terms of x and y
    bool is_active;    //
    bool is_dragged;   // while this is on, the atom follows the cursor
    Texture2D sprite;
    float sprite_diameter;
    float sprite_radius;
    Vector2 middle_point;
public:
    Atom(Vector2 _pos, int _anum);
    bool is_hovered();
    void _handle_drag();
    void refresh_state();
    void render();
};


#endif //MOLECULEBUILDER_ATOM_H
