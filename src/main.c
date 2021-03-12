#include "main.h"

int main(void)
{
    /*
        Initialize GLFW
    */
    glfwInit();

    /*
        Set GLFW OpenGL version to version 3.3
        Set GLFW OpenGL profile to Core profile
    */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /*
        For Mac OS X
    */
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /*
        Create our window
    */
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "QTest", NULL, NULL);
    if (window == NULL)
    {
        puts("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /*
        Initialize GLAD library
    */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        puts("Failed to initialize GLAD");
        return -1;
    }

    /*
       Set our OpenGL viewport callback function
   */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /*
        Enter our render loop!
    */
    render(window);

    return 0;
}