#include "KNIGHT.h"
#include"Map.h"

int main()
{
    
    GLFWwindow * window;
    bbopInit(1024,768,"window name",window);
    Scene default_scene;
    KNIGHT perso1(window,"sprite");
    std::cout<<"pp"<<std::endl;
    Map map("sprite/background/forest.png");
    const double fpsLimit = 1.0/60.0;
    double lastUpdateTime = 0;  
    double lastFrameTime = 0;
    while (!glfwWindowShouldClose(window))
    {
        bbopCleanWindow(window,Vector3i(0,0,0),1.0f);
        default_scene.Use();
        double now = glfwGetTime();
        map.Drawmap(default_scene);
        
        if ((now - lastFrameTime) >= fpsLimit)
        {
            int axescount;
            const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axescount);
            perso1.upadate(axes[0],axes[2],window);
            default_scene.Draw(perso1);    
            showfps(window);
            glfwSwapBuffers(window);                
            lastFrameTime = now;
        }
        
        bbopErrorCheck();
        glfwPollEvents();
        lastUpdateTime=now;
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}