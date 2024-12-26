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
    Sprite("sprite/static/0.png"),
    state(fall)
{
    falling_speed=10.f;
    jumpt=0;
    std::string anim_folder[4] = {"static","run","jump","fall"};
    int anim_frame_n[4] = {10,10,10};
    for (int i = 0; i < 3; i++)
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
    setTexture(animation[0][0]);
    setSize(Vector2f(50,50));
    setPosition(Vector2f(100,100));
    info.speed=0.1;
    info.acceleration=0.1;
    info.deceleration=0.05f;
    jump_p=true;
    right=left=false;
    anim_fr=0;
}
void KNIGHT::upadate(float m,float j,GLFWwindow *window){
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
        }
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
    if (mv_final.x==0)
    {
        right=false;
        left=false;
    }
    if (mv_final.y <= 0 && mv_final.y >= -0.25) {
        state = run; 
    } else if (mv_final.y < 0) {
        state = jump_s;   
    } else {
        state = fall;
    }

    if (state==run)
    {
         if (right) {
            setTexture(animation[1][anim_fr]);
        } else if (left) {
            setTexture(animation[1][anim_fr]); 
        } else {
            setTexture(animation[0][0]);
        }
    }else if (state==jump_s)
    {
        if (anim_fr>5)
        {
            setTexture(animation[2][6]);
        }else{
            setTexture(animation[2][anim_fr]);
        }
    }else{

    }

    move(mv_final);
}
void KNIGHT::movement(float value){
    if (value > 0.2 )
    {
        if (left)
        {
            left=false;
            anim_fr=0;
            flipVertically();
        }else{
            mv_final.x+=info.speed/info.acceleration;
            mv_final.x-=info.deceleration;
            right=true;
            if (getPosition().y>600 && getPosition().y<700&& state!=jump_s)
            {
                state=run;
            }
            if (frame_count%1==0)
            {
                anim_fr+=1;
            }
            
        }
    }
    if (value < -0.2)
    {
        if (right)
        {
            right=false;
            anim_fr=0;
            flipVertically();
        }else{
            mv_final.x-=info.speed/info.acceleration;
            mv_final.x+=info.deceleration;
            left=true;
            if (getPosition().y>600 && getPosition().y<700&& state!=jump_s)
            {
                state=run;
            }
            
            if (frame_count%1==0)
            {
                anim_fr+=1;
            }
        }
        
        
       
    }
}
    
    
    

void KNIGHT::jump(float t){
    if(t>0.1)
    {
        mv_final.y-=2.0f;
        jumpt+=0.5;
        state=jump_s;
    }
}