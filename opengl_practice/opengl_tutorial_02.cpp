//
//  opengl_tutorial_02.cpp
//  opengl_practice
//
//  Created by hyoukim on 2021/06/29.
//

#include "opengl_practice.hpp"

// draw triangle
int practice_02(void)
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
    window = glfwCreateWindow(1024, 768, "Tutorial 02", NULL, NULL);
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
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    cout << glGetString(GL_VERSION) << endl;
    
    // tutorial_02 시작
    // Vertex Array Object 생성
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // 쉐이더들에서 우리의 GLSL프로그램을 생성하고 컴파일하기
    GLuint programID = LoadShaders("/Users/hyoukim/Desktop/opengl_practice/opengl_practice/tutorial_02_shader/SimpleVertexShader.vertexshader", "/Users/hyoukim/Desktop/opengl_practice/opengl_practice/tutorial_02_shader/SimpleFragmentShader.fragmentshader");
    
    static const GLfloat g_vertex_buffer_data[] = {
        0.0f,  0.5f, 0.0f, //vertex 1  위 중앙
        0.5f, -0.5f, 0.0f, //vertex 2  오른쪽 아래
        -0.5f, -0.5f, 0.0f //vertex 3  왼쪽 아래
    };
    
    // 이것이 우리의 버텍스 버퍼를 가리킵니다.
    GLuint vertexbuffer;
    // 버퍼를 하나 생성합니다. vertexbuffer에 식별자를 넣습니다.
    glGenBuffers(1, &vertexbuffer);
    // 아래의 명령어들은 우리의 "vertexbuffer" 버퍼에 대해서 다룰겁니다.
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // 우리의 버텍스들을 OpenGL로. 넘겨줍니다.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    do {
        
        // clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        // Use our shader
        glUseProgram(programID);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );
        
        //draw triangle!
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices
        // starting at 0 -> 1 triangle
        glDisableVertexAttribArray(0);
        
        // 버퍼들을 교체
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);
    
    //Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return (0);
}
