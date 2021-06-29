//
//  shaders.hpp
//  opengl_practice
//
//  Created by hyoukim on 2021/06/23.
//

#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <GL/glew.h>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif

