#include "KNIGHT.h"


int main()
{
    
    GLFWwindow * window;
    bbopInit(1024,768,"window name",window);
    Scene default_scene;
    
    KNIGHT perso1(window,"sprite");
    KNIGHT perso2(window,"sprite");
    std::cout<<"pp"<<std::endl;
    Map map("sprite/background/forest.png");
    glfwSwapInterval(2);
    while (!glfwWindowShouldClose(window))
    {
        bbopCleanWindow(window,Vector3i(0,0,0),1.0f);
        default_scene.Use();
        double now = glfwGetTime();
        map.Drawmap(default_scene);
        int axescount;
        const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axescount);
        int buttoncount;
        const unsigned char *button = glfwGetJoystickButtons(GLFW_JOYSTICK_1 , &buttoncount);
        perso1.upadate(axes[0],axes[2],button[1],window,map);
        perso1.attack(button[2],axes[0]);
        perso2.upadate(0.0f,0.0f,button[0],window,map);
        perso2.get_hit(perso1);
        default_scene.Draw(perso1);   
        default_scene.Draw(perso2);
        showfps(window);
        glfwSwapBuffers(window);                
        bbopErrorCheck();
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}