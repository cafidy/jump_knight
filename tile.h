#include"BBOP/Graphics.h"
#include"iostream"
#include"vector"
#include <GLFW/glfw3.h>
class Map;
class tile : public Sprite
{

    public:
        tile();
        tile(Vector2f pos);
};