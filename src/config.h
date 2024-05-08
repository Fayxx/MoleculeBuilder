//
// Created by Marlon Käsemann on 06.05.24.
//

#ifndef MOLECULEBUILDER_CONFIG_H
#define MOLECULEBUILDER_CONFIG_H


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


#endif //MOLECULEBUILDER_CONFIG_H
