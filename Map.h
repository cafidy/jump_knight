#include"BBOP/Graphics.h"
#include"iostream"
#include"vector"
#include <GLFW/glfw3.h>



class Map{
    private:
        std::vector<Sprite> platforme;
        Sprite backg;
    public:
        Map();
        Map(const char *filmap);
        void Drawmap(Scene &scene);
        CollisionBox* get_pl();
};