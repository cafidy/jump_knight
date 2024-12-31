#include"tile.h"

tile::tile(Vector2f pos){
    setTexture("sprite/plateforme/pl.png");
    setPosition(pos);
    setSize(Vector2f(400,40));
}