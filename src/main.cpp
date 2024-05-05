#include "raylib.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

std::string ASSET_PATH("/Users/marlonkasemann/Desktop/Coding/Projects/MoleculeBuilder/assets/");
constexpr int WINDOW_WIDTH  = 1500;
constexpr int WINDOW_HEIGHT = 900;
constexpr auto WINDOW_TITLE  = "Molecule Builder";
constexpr float SPRITE_SIZE   = 200;
constexpr Color BACKGROUND_COLOR({23, 23, 23, 255});
Font SYMBOL_FONT;

// ARRAY vs. HASHMAP
std::unordered_map<int, std::string>        SYM          =  {  {1,"H"},         {6,"C"},        {8,"O"}   };
std::unordered_map<int, float>              SCALE_FACTOR =  {  {1,0.25},         {6, 0.5},       {8,0.35}  };
std::unordered_map<int, float>              OUTER_RADIUS =  {  {1,25.0},        {6,55.0},       {8,45.0}  };
std::unordered_map<int, Color>              COLOR        =  {  {1,RAYWHITE},    {6,DARKGRAY},   {8,RED}   };
std::unordered_map<int, std::vector<int> >  REPR         =  {  {1, {1}},          {6, {4}},         {8, {4}}    };
/*
? Currently supported atoms: C, H, O
*/
class Atom {
    private:
    int anum;          // atomic number
    Vector2 pos;       // position on screen in terms of x and y
    bool is_active;    //
    bool is_dragged;   // while this is on, the atom follows the cursor
    Texture2D sprite;  

    public:
    Atom(Vector2 _pos, int _anum){
        pos = _pos;
        anum = _anum;
        is_active = false;
        is_dragged = false;
        sprite = LoadTexture((ASSET_PATH + SYM[anum] + ".png").c_str());
    }

    bool is_hovered() {
        auto [x,y] = pos;
        auto [mx,my] = GetMousePosition();
        //TODO rework
    }

    void _handle_drag(){
        bool left_mouse_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        if(is_hovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) is_active = true;
        if(is_hovered() && left_mouse_down) is_dragged = true;
        if(is_dragged && !left_mouse_down) is_dragged = false;
        if(is_dragged){
            //TODO rework
        }
    }

    void refresh_state() {
        _handle_drag();
    }      

    void render() {
        DrawTextureEx(sprite, {pos.x, pos.y}, 0.0, SCALE_FACTOR[anum], WHITE);
    }
};


int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SYMBOL_FONT = LoadFont((ASSET_PATH + "symbols.ttf").c_str());
    SetTargetFPS(60);

    std::vector<Atom*> atoms;
    Atom* a = new Atom({100.0, 100.0}, 1);
    atoms.push_back(a);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

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
