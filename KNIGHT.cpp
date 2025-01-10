#include "KNIGHT.h"
void showfps(GLFWwindow* window)
{
    static double lastTime = glfwGetTime();
    static int frameCount = 0;
    
    // Obtenir le temps actuel
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    
    // Incrémenter le compteur de frames
    frameCount++;
    
    // Afficher les FPS toutes les 2 secondes
    if (deltaTime >= 2.0) {
        // Calculer les FPS
        double fps = (double)frameCount / deltaTime;
        
        // Afficher dans le terminal
        std::cout << "FPS: " << fps << std::endl;
        
        // Réinitialiser le compteur et mettre à jour le temps
        frameCount = 0;
        lastTime = currentTime;
    }
}
KNIGHT::KNIGHT(GLFWwindow*& window_, std::string sprite_folder):
    Sprite("sprite/static/0.png")
{
    
    jumpt=0;
    std::string anim_folder[6] = {"static","run","jump","fall","melee","dash"};
    int anim_frame_n[6] = {10,10,10,10,8,10};
    for (int i = 0; i < 6; i++)
    {
        
        std::string anim_folder_i=sprite_folder+"/"+anim_folder[i];
        for (int k = 0; k < anim_frame_n[i]; k++)
        {
            std::string anim_frame=anim_folder_i+"/"+ std::to_string(k)+".png";
            Texture new_frame(anim_frame.c_str());
            std::cout<<anim_frame<<std::endl;
            animation[i].push_back(new_frame);
            std::cout<<anim_frame<<std::endl;
        }
        
    }
    state=fall;
    setTexture(animation[1][5]);
    setSize(Vector2f(50,50));
    setPosition(Vector2f(100,100));
    info.speed=0.1;
    info.acceleration=0.1;
    info.deceleration=0.05f;
    jump_p=true;
    right=left=false;
    anim_fr=0;
    right=false;
    left=false;
    stati=true;
}
void KNIGHT::upadate(float m,float j,char b,GLFWwindow *window,Map map){
    frame_count++;
    mv_final.x=0;
    dash(b);
    movement(m);
    if (jumpt<0.75 && jump_p==true)
    {
        jump(j);
    }else if (jumpt>=1)
    {
        jump_p=false;
        mv_final.y+=0.5f;
        if (getPosition().y > 600)
        {
            jumpt=0;
            jump_p=true;
            jumpt=0;
        }
    }
    if (glfwGetTime()-dasht>2)
    {
        dash_p=true;
    }
    
        
  
    if (getPosition().x>BBOP_WINDOW_SIZE.x-20)
    {
        mv_final.x=-2;
    }
    if (getPosition().x<20)
    {
        mv_final.x=2;
    }
    if (getPosition().y>650)
    {
        mv_final.y=-0.5;
    }
   
    mv_final.y+=0.25f;
    if (getPosition().y+mv_final.y>BBOP_WINDOW_SIZE.y || getPosition().y+mv_final.y<0)
    {
        mv_final.y=0;
    }

    if (anim_fr==9)
    {
        anim_fr=0;
    }
    if (mv_final.y <= 0 && mv_final.y >= -0.25) {
        state = run; 
    } else if (mv_final.y < 0) {
        state = jump_s;   
    } else if (mv_final.y>0)
    {
        state = fall;
        anim_fr=0;
    }else if (mv_final.x==0 && mv_final.y==0)
    {
        state=still;
    }
    
    

    contact(map);

    if (state==run)
    {
        direction();
        setTexture(animation[1][anim_fr]);
    }
    if (state==dash_s)
    {
        setTexture(animation[5][anim_fr]);
        if (frame_count%3==0 && anim_fr<9)
        {
            anim_fr++;
        }
        if (anim_fr==9)
        {
            dash_p=false;
            state=still;
            dasht=glfwGetTime();
            anim_fr=0;
        }
        direction();
        
        
    }
    
    if (state==jump_s)
    {
        
        if (anim_fr>5)
        {
            setTexture(animation[2][6]);
        }else{
            direction();
            setTexture(animation[2][anim_fr]);
        }
        direction();
    }
    if (state==still)
    {
        setTexture(animation[0][0]);
    }
    
    if (anim_fr>8 && state==run)
    {
        anim_fr=0;
    }
    if (state==fall)
    {
        setTexture(animation[3][anim_fr]);
        if (anim_fr<9)
        {
            anim_fr++;
        }
        
    }
    
    Vector2f mvv;
    mvv.x=mv_final.x;
    mvv.y=mv_final.y;
    
    move(mvv);
}
void KNIGHT::movement(float value){
    if (state!=dash_s)
    {
        if (value > 0.2 )
        {
            mv_final.x+=info.speed/info.acceleration;
            mv_final.x-=info.deceleration;
            right=true;
            if (getPosition().y>600 && getPosition().y<700&& state!=jump_s)
            {
                state=run;
            }
            if (frame_count%3==0)
            {
                anim_fr++;
            }
        }
        if (value < -0.2)
        {
            left=true;
            mv_final.x-=info.speed/info.acceleration;
            mv_final.x+=info.deceleration;
            
            if (getPosition().y>600 && getPosition().y<700&& state!=jump_s)
            {
                state=still;
            }
            
            if (frame_count%3==0)
            {
                anim_fr++;
            }
        }
    }else{
        if (value>0.2)
        {
            mv_final.x+=5;
        }else{
            mv_final.x-=5;
        }
        
    }
}
    
    
    

void KNIGHT::jump(float t){
    if(t>0.1 && state!=dash_s)
    {
        mv_final.y-=2.0f;
        jumpt+=0.25;
        state=jump_s;
        anim_fr++;
    }
}

void KNIGHT::contact(Map pp){
    for (size_t i = 0; i < sizeof(pp.get_pl()); i++)
    {
        if (getCollisionBox().check(pp.get_pl()[i]))
        {
            float overlap_left = pp.get_pl()[i].getRight() - shapeCollisionBox.getLeft();
            float overlap_right = shapeCollisionBox.getRight() - pp.get_pl()[i].getLeft();
            float overlap_top = pp.get_pl()[i].getBottom() - shapeCollisionBox.getTop() - 8.f;
            float overlap_bottom = shapeCollisionBox.getBottom() - pp.get_pl()[i].getTop()-8.f;
            float min_overlap = std::min({overlap_right, overlap_left, overlap_top, overlap_bottom});

            if(min_overlap == overlap_top){
                move(0.f,pp.get_pl()[i].getBottom() - shapeCollisionBox.getTop()+0.1f);
                mv_final.y = 0.f;
            }else if(min_overlap == overlap_bottom) {
                
                move(0.f,-(shapeCollisionBox.getBottom()-pp.get_pl()[i].getTop()));
                if(state == fall){
                    state=run;
                }
                if (mv_final.y>0)
                {
                    mv_final.y=0;
                }
                jump_p=true;
                jumpt=0;
            }else if(min_overlap == overlap_right) {
                move(-(shapeCollisionBox.getRight() - pp.get_pl()[i].getLeft()), 0.f);
            }else if (min_overlap == overlap_left) {
                move(pp.get_pl()[i].getRight() - shapeCollisionBox.getLeft(), 0.f);
            }
        }
        
    }
        
}
void KNIGHT::attack(float a){
    if (a>0.2 && state!=jump_s)
    {
        state=attack_s;
    }
    
}

void KNIGHT::dash(char button){
    if (GLFW_PRESS==button)
    {
        if (state!=dash_s && dash_p==true)
        {
            anim_fr=0;
        }
        state=dash_s;
        mv_final.x=0;
        
    }
    
}

void KNIGHT::direction(){
    if (mv_final.x>0) {
        if (left)
        {
            flipVertically();
            left=false;
            if (state!=jump_s)
            {
                anim_fr=0;
            }
            
        } 
    } else if (mv_final.x<0) {
        if (right)
        {
            flipVertically();
            right=false;
            if (state!=jump_s)
            {
                anim_fr=0;
            }
        } 
    } 
}