//
//  texture.cpp
//  opengl_practice
//
//  Created by hyoukim on 2021/07/04.
//
# include "texture.hpp"

GLuint loadBMP_custom(const char *imagepath)
{
    cout << "Reading image " << imagepath << endl;
    
    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    // Actual RGB data
    unsigned char *data;
}
