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
struct dash_info{
    bool dright;
    bool dleft;
    bool nodash;
};

enum State {
    still = 0 , 
    run = 1, 
    jump_s = 2 , 
    fall = 3,
    attack_s = 4,
    dash_s=5,
    hit=6
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
        bool atr;
        bool atl;
        double dasht;
        speed_info info;
        float jumpt;
        dash_info dinfo;
        State state;
        bool enddash;
        std::vector<Texture> animation[6];
    public:
        KNIGHT(GLFWwindow*& window_, std::string sprite_folder);
        void upadate(float m,float j,char b,GLFWwindow *window,Map map);
        void movement(float value);
        void jump(float t);
        void contact(Map pp);
        void attack(char f , float c);
        void dash(char buttu , float d);
        void direction();
        void verif_state();
        int return_state();
        void get_hit(KNIGHT perso);
        
};


