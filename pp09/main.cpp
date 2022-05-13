#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>


#pragma comment(lib, "opengl32")

bool isPressed;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        isPressed = true;
        //glfwSetWindowShouldClose(window, GL_TRUE); 
    }
    else {
        isPressed = false;
    }

}

void Jump_player() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.5f, 0.2f);
    glVertex2f(-0.5f, 0.3f);
    glVertex2f(-0.6f, 0.3f);

    glVertex2f(-0.5f, 0.2f);
    glVertex2f(-0.6f, 0.2f);
    glVertex2f(-0.6f, 0.3f);
    glEnd();
}

void player() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.5f, -0.1f);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.6f, 0.0f);

    glVertex2f(-0.5f, -0.1f);
    glVertex2f(-0.6f, -0.1f);
    glVertex2f(-0.6f, 0.0f);
    glEnd();
}

void Enemy() {
    //삼각형(적)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.05f, -0.1f);
    glVertex2f(0.05f, -0.1f);
    glEnd();
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback); //메세지 핸들러

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;


        glClearColor(0.7f, 0.7f, 0.7f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        Enemy();

        if (isPressed) {
            Jump_player();
        }
        else if (isPressed == false) {
            player();
        }

        glfwSwapBuffers(window); //위도우에 저장된 버퍼를 가지고 오는 것
        glfwPollEvents(); //어떤 메세지가 들어있는지(에러, 키입력)
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
