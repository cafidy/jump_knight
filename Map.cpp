#include"Map.h"

Map::Map(){
    backg.setTexture(Texture("sprite/default.png"));
    tile ti(Vector2f(100.0f,200.0f));
    tile tground(Vector2f(0.0f,750.0f));
    ground=tground;
    platforme.push_back(ti);
    platforme.push_back(ground);
}

Map::Map(const char *filmp){
    backg.setTexture(Texture(filmp));
    backg.setSize(1028,768);
    tile ti(Vector2f(300.0f,600.0f));
    tile tground(Vector2f(0.0f,750.0f));
    ground=tground;
    platforme.push_back(ti);
    platforme.push_back(tground);
}
void Map::Drawmap(Scene &scene){
    scene.Draw(backg);
    scene.Draw(platforme[0]);
    scene.Draw(platforme[1]); 
}

CollisionBox* Map::get_pl(){
    CollisionBox *col=new CollisionBox[platforme.size()];
    for (size_t i = 0; i < platforme.size(); i++)
    {
        col[i]=platforme[i].getCollisionBox();
    }
    return col;
}
size_t Map::getPlatsize(){
    return platforme.size();
}