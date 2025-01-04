#include"BBOP/Graphics.h"
#include"iostream"
#include"vector"
#include <GLFW/glfw3.h>
#include"tile.h"


class Map{
    private:
        std::vector<tile> platforme;
        Sprite backg;
        tile ground;
    public:
        Map();
        Map(const char *filmap);
        void Drawmap(Scene &scene);
        CollisionBox* get_pl();
        size_t getPlatsize();
};