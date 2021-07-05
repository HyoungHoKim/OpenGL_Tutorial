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
    
    //Open the file
    FILE *file = fopen(imagepath, "rb");
    if (!file)
    {
        cout << imagepath << " could not be opened. Are you in the forget to read the FAQ!" << endl;
        getchar();
        return (0);
    }
    
    // Read the header, i.e the 54 first bytes
    // If less than 54 bytes are read, problem
    if (fread(header, 1, 54, file) != 54)
    {
        cout << "Not a correct BMP file" << endl;
        fclose(file);
        return (0);
    }
    
    // A BMP files always begins with "BM"
    if (header[0] != 'B' || header[1] != 'M')
    {
        cout << "Not a correct BMP file" << endl;
        fclose(file);
        return (0);
    }
    
    // Make sure this is a 24bpp file
    if (*(int*) & (header[0x1E]) != 0)
    {
        cout << "Not a correct BMP file" << endl;
        fclose(file);
        return (0);
    }
    if (*(int*) & (header[0x1C]) != 24)
    {
        cout << "Not a correct BMP file" << endl;
        fclose(file);
        return (0);
    }
    
    // Read the information about image
    dataPos = *(int*) & (header[0x0A]);
    imageSize = *(int*) & (header[0x22]);
    width = *(int*) & (header[0x12]);
    height = *(int*) & (header[0x16]);
    
    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
        imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue Component
    if (dataPos == 0)
        dataPos = 54; // The BMP header is done that way
    
    // create a buffer
    data = new unsigned char [imageSize];
    
    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);
    
    // Everything is in memory now, the file can be closed.
    fclose(file);
    
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    // Opengl has now copied the data. Free our own version
    delete[] data;
    
    // Poor filtering, or ...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return (textureID);
}
