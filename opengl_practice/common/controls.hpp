//
//  controls.hpp
//  opengl_practice
//
//  Created by hyoukim on 2021/07/06.
//

#ifndef controls_hpp
#define controls_hpp

#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

void computeMatricesFromInputs(GLFWwindow *window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif /* controls_hpp */
