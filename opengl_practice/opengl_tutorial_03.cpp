//
//  opengl_tutorial_03.cpp
//  opengl_practice
//
//  Created by hyoukim on 2021/06/29.
//

#include "opengl_practice.hpp"

// Matrix
int practice_03(void)
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
    GLuint programID = LoadShaders("/Users/hyoukim/Desktop/opengl_practice/opengl_practice/tutorial_03_shader/SimpleTransform.vertexshader", "/Users/hyoukim/Desktop/opengl_practice/opengl_practice/tutorial_02_shader/SimpleFragmentShader.fragmentshader");
    
    // 우리의 "MVP" 행렬에 대한 참조를 얻는다.
    // 초기화때만 해야한다.
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    // 프로젝션 매트릭스 : 45도 시야각, 4:3 비율, 시야 범위 : 0.1 유닛 <---> 100 유닛
    mat4 Projection = glm::perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    
    // 혹은 ortho(직교) 카메라에선
    // mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);  // 월드 좌표로 표현
    
    // 카메라 매트릭스
    mat4 View = glm::lookAt(
                       vec3(4, 3, 3), // 카메라는 (4, 3, 3)에 있다.
                       vec3(0, 0, 0), // 그리고 카메라는 원점을 본다.
                       vec3(0, 1, 0)  // 머리가 위쪽이다.
                       );
    
    // 모델 매트릭스 : 단위 매트릭스 (모델은 원점에 배치된다.)
    mat4 Model = mat4(1.0f);
    // 모델뷰프로젝션 : 3개의 매트릭스들을 곱한다.
    mat4 MVP = Projection * View * Model; // 행렬곱은 반대순서로 이루어진다.
    
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
        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
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
