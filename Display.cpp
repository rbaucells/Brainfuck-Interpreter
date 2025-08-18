#include <string>
#include "common.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

int main() {
    Display display("");
}

void error_callback(int error, const char* description)
{
    std::printf("Error with code'%d': %s\n", error, description);
}

Display::Display(const std::string& bfProgram) {
    this -> bfProgram = bfProgram;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::printf("glfw initialization failed");
        exit(0);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        std::printf("window creation failed");
        exit(0);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
}

void Display::update() {

}

Display::~Display() {
    glfwTerminate();
}






