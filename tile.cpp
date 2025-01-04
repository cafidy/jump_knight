#include"tile.h"
tile::tile(){

}
tile::tile(Vector2f pos){
    setTexture("sprite/map/pl.png");
    setPosition(pos);
    setSize(Vector2f(400,40));
}