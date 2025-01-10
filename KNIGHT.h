#include"BBOP/Graphics.h"
#include"iostream"
#include"vector"
#include <GLFW/glfw3.h>
#include"Map.h"

void showfps(GLFWwindow *pWindow);
struct speed_info{
    float speed;
    float acceleration;
    float deceleration;
};
enum State {
    still = 0 , 
    run = 1, 
    jump_s = 2 , 
    fall = 3,
    attack_s = 4,
    dash_s=5
    };
struct speed_info;
class KNIGHT : public Sprite
{
    private:
        int anim_fr;
        Vector2f mv_final;
        bool jump_p;
        unsigned int frame_count;
        bool right,left,stati;
        bool dash_p;
        double dasht;
        speed_info info;
        float jumpt;
        float falling_speed;
        State state;
        std::vector<Texture> animation[6];
    public:
        KNIGHT(GLFWwindow*& window_, std::string sprite_folder);
        void upadate(float m,float j,char b,GLFWwindow *window,Map map);
        void movement(float value);
        void jump(float t);
        void contact(Map pp);
        void attack(float f);
        void dash(char buttu);
        void direction();
};


