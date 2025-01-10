#include"Map.h"

Map::Map(){
    backg.setTexture(Texture("sprite/default.png"));
    Sprite ti(Texture("sprite/plateforme/pl.png"),Vector2f(200.0f,200.0f));
    ti.setSize(Vector2f(300.0f,100.0f));
    Sprite tgro(Texture("sprite/plateforme/pl.png"),Vector2f(0.0f,600.0f));
    ti.setSize(Vector2f(1028.0f,200.0f));
    platforme.push_back(ti);
    platforme.push_back(tgro);
}

Map::Map(const char *filmp){
    backg.setTexture(Texture(filmp));
    backg.setSize(1028,768);
    Sprite ti(Texture("sprite/plateforme/pl.png"),Vector2f(200.0f,200.0f));
    ti.setSize(Vector2f(100.0f,100.0f));
    Sprite tgro(Texture("sprite/plateforme/pl.png"),Vector2f(0.0f,600.0f));
    tgro.setSize(Vector2f(1028.0f,200.0f));
    platforme.push_back(ti);
    platforme.push_back(tgro);
}
void Map::Drawmap(Scene &scene){
    scene.Draw(backg);
    scene.Draw(platforme[0]);
    scene.Draw(platforme[1]);
}

CollisionBox* Map::get_pl(){
    CollisionBox *col=new CollisionBox[sizeof(platforme)];
    for (size_t i = 0; i < sizeof(platforme); i++)
    {
        col[i]=platforme[i].getCollisionBox();
    }
    return col;
}