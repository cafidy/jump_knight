#include"Map.h"

Map::Map(){
    backg.setTexture(Texture("sprite/default.png"));
    tile ti(Vector2f(100.0f,200.0f));
    platforme.push_back(ti);
}

Map::Map(const char *filmp){
    backg.setTexture(Texture(filmp));
    backg.setSize(1028,768);
    tile ti(Vector2f(300.0f,600.0f));
    platforme.push_back(ti);
}
void Map::Drawmap(Scene &scene){
    scene.Draw(backg);
    scene.Draw(platforme[0]);
}

CollisionBox* Map::get_pl(){
    CollisionBox *col=new CollisionBox[sizeof(platforme)];
    for (size_t i = 0; i < sizeof(platforme); i++)
    {
        col[i]=platforme[i].getCollisionBox();
    }
    return col;
}