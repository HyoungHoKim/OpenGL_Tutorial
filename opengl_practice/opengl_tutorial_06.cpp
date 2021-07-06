//
//  opengl_tutorial_06.cpp
//  opengl_practice
//
//  Created by hyoukim on 2021/07/06.
//

#include "opengl_practice.hpp"

int practice_06(void)
{
    GLFWwindow *window;
    
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        return (-1);
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(1024, 768, "Tutorial 06", NULL, NULL);
    if (window == NULL)
    {
        cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials." << endl;
        glfwTerminate();
        return (-1);
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        cerr << "Failed to initialize GLEW" << endl;
        return (-1);
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the moust and enable unlimited mouvment
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);
    
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders(
        "/Users/hyoukim/Desktop/opengl_practice/opengl_practice/tutorial_05_shader_texture/TransformVertexShader.vertexshader",
        "/Users/hyoukim/Desktop/opengl_practice/opengl_practice/tutorial_05_shader_texture/TextureFragmentShader.fragmentshader");
    
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    // Load the texture using any two methods
    GLuint Texture = loadDDS("/Users/hyoukim/Downloads/ogl-master/tutorial05_textured_cube/uvtemplate.DDS");
    // GLuint Texture = loadDDS("uvtemplate.DDS");
    
    GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
    
    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f
    };

    // Two UV coordinatesfor each vertex. They were created with Blender.
    static const GLfloat g_uv_buffer_data[] = {
        0.000059f, 0.000004f,
        0.000103f, 0.336048f,
        0.335973f, 0.335903f,
        1.000023f, 0.000013f,
        0.667979f, 0.335851f,
        0.999958f, 0.336064f,
        0.667979f, 0.335851f,
        0.336024f, 0.671877f,
        0.667969f, 0.671889f,
        1.000023f, 0.000013f,
        0.668104f, 0.000013f,
        0.667979f, 0.335851f,
        0.000059f, 0.000004f,
        0.335973f, 0.335903f,
        0.336098f, 0.000071f,
        0.667979f, 0.335851f,
        0.335973f, 0.335903f,
        0.336024f, 0.671877f,
        1.000004f, 0.671847f,
        0.999958f, 0.336064f,
        0.667979f, 0.335851f,
        0.668104f, 0.000013f,
        0.335973f, 0.335903f,
        0.667979f, 0.335851f,
        0.335973f, 0.335903f,
        0.668104f, 0.000013f,
        0.336098f, 0.000071f,
        0.000103f, 0.336048f,
        0.000004f, 0.671870f,
        0.336024f, 0.671877f,
        0.000103f, 0.336048f,
        0.336024f, 0.671877f,
        0.335973f, 0.335903f,
        0.667969f, 0.671889f,
        1.000004f, 0.671847f,
        0.667979f, 0.335851f
    };
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
    
    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Use our shader
        glUseProgram(programID);
        
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs(window);
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID, 0);
        
        // first attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,          // attribute
            3,          // size
            GL_FLOAT,   // type
            GL_FALSE,   // normalized
            0,          // stride
            (void*)0    // array buffer offset
        );
        
        // second attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,          // attribute
            2,          // size
            GL_FLOAT,   // type
            GL_FALSE,   // normalized
            0,          // stride
            (void*)0    // array buffer offset
        );
        
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        //Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && glfwWindowShouldClose(window) == 0);
    
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &Texture);
    glDeleteVertexArrays(1, &VertexArrayID);
    
    glfwTerminate();
    
    return (0);
}
