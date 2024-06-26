
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

#include "raylib.h"
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
    Atom(Vector2 _pos, int _anum){
        pos = _pos;
        anum = _anum;
        is_active = false;
        is_dragged = false;
        sprite = LoadTexture((ASSET_PATH + SYM[anum] + ".png").c_str());
        sprite_diameter = SPRITE_SIZE * SCALE_FACTOR[anum];
        sprite_radius = sprite_diameter / 2;
        middle_point = {pos.x + sprite_radius, pos.y + sprite_radius};
    }

    bool is_hovered() {
        auto [x, y] = middle_point;
        auto [mx, my] = GetMousePosition();
        return mx >= x - sprite_radius && mx <= x + sprite_radius && my >= y - sprite_radius && my <= y + sprite_radius;
    }
    void _handle_drag(){
        bool left_mouse_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        if(is_hovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) is_active = true;
        if(is_hovered() && left_mouse_down) is_dragged = true;
        if(is_dragged && !left_mouse_down) is_dragged = false;
        if(is_dragged){
            pos = {GetMousePosition().x - sprite_radius, GetMousePosition().y - sprite_radius };
            middle_point = {pos.x + sprite_radius, pos.y + sprite_radius};
        }
    }
    void refresh_state() {
        _handle_drag();
    }

    void render() {
        DrawTextureEx(sprite, pos, 0.0, SCALE_FACTOR[anum], WHITE);
    }
};

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SYMBOL_FONT = LoadFont((ASSET_PATH + "symbols.ttf").c_str());
    SetTargetFPS(60);
    Atom* a = new Atom({100.0, 100.0}, 1);
    std::vector<Atom*> atoms;
    atoms.push_back(a);

    int curr_selected = 0;
    int curr_key;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        while((curr_key = GetKeyPressed())){
            switch(curr_key){
                case KEY_ONE:
                    atoms.push_back(new Atom(GetMousePosition(), 1));
                    break;
                case KEY_SIX:
                    atoms.push_back(new Atom(GetMousePosition(), 6));
                    break;
                case KEY_EIGHT:
                    atoms.push_back(new Atom(GetMousePosition(), 8));
                    break;
            }
        }

        for(Atom* atom : atoms){
            atom->refresh_state();
        } 
        for(Atom* atom : atoms){
            atom->render();
        } 
        EndDrawing();
    }
    CloseWindow();

    for(Atom* atom : atoms)
        delete atom;

    UnloadFont(SYMBOL_FONT);
    return 0;
}
