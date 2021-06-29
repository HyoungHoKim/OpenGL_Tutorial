//
//  loadShader.cpp
//  opengl_practice
//
//  Created by hyoukim on 2021/06/22.
//

#include "shaders.hpp"

GLuint LoadShaders (const char * vertex_file_path, const  char *fragment_file_path)
{
    // 쉐이더들 생성
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // 버텍스 쉐이더 코드를 파일에서 읽기
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        std::cout << "Impassible to open " << vertex_file_path << ". " << "Are you in the right directory ? Don't forget to read the FAQ !" << std::endl;
        getchar();
        return (0);
    }
    
    // 프레그먼트 쉐어더 코드를 파일에서 읽기
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    // 버텍스 쉐이더를 컴파일
    std::cout << "Compiling shader : " << vertex_file_path << std::endl;
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);
    
    // 버텍스 쉐이더를 검사
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        std::cout << &VertexShaderErrorMessage[0] << std::endl;
    }
    
    // 프레그먼트 쉐이더를 컴파일
    std::cout << "Compiling shader : " << fragment_file_path << std::endl;
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1,  &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);
    
    // 프래그먼트 쉐이더를 검사
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        std::cout << &FragmentShaderErrorMessage[0] << std::endl;
    }
    
    // 프로그램에 링크
    std::cout << "Linking program" << std::endl;
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    
    // 프로그램 검사
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        std::cout << &ProgramErrorMessage[0] << std::endl;
    }
    
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    
    return (ProgramID);
}
