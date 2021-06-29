//
//  opengl_practice.cpp
//  opengl_practice
//
//  Created by hyoukim on 2021/06/22.
//

#include "opengl_practice.hpp"

// make window
int practice_01 (void)
{
    // GLFW 초기화
    if (!glfwInit())
    {
        cerr << "GLFW 초기화 실패" << endl;
        return (-1);
    }
    
    //GLFW_SAMPLES : 멀티 샘플링을 사용하기 위한 설정, 4x anti-aliasing, 계단 현상 방지
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3을 쓸 겁니다.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS에서 설정 해주면 좋다. 안해도 상관없음
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // 새창을 열고, OpenGL 컨텍스트를 생성
    GLFWwindow *window; // 후술되는 코드를 보면, 이 변수는 전역(Global)입니다.
    window = glfwCreateWindow(640, 480, "Tutorial 01", NULL, NULL);
    if (window == NULL) {
        cerr << "GLFW 윈도우를 여는데 실패했습니다." << endl;
        glfwTerminate();
        return (-1);
    }
    
    // GLEW 초기화
    glfwMakeContextCurrent(window);
    glewExperimental = true; // 코어 프로파일을 위해 필요함
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        return (-1);
    }
    
    // 밑에서 Escape키가 눌러지는 것을 감지할 수 있도록 할 것
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    do {
        // 아무것도 그리지 않습니다. 두번째 튜토리얼에서 진행
        
        // 버퍼들을 교체
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);
    return (0);
}
