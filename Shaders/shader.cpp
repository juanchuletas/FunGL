#include "shader.hpp"


Shader::Shader(std::string pathVert, std::string pathFrag, std::string pathgeom){

    std::string vPath; 
    GLuint vShader = 0; 
    GLuint geomShader = 0; 
    GLuint fShader = 0; 
    vShader = loadShader(GL_VERTEX_SHADER, pathVert); 
    geomShader = loadShader(GL_GEOMETRY_SHADER, pathgeom); 
    fShader = loadShader(GL_FRAGMENT_SHADER, pathFrag);  


    glDeleteShader(vShader);
    glDeleteShader(geomShader);
    glDeleteShader(fShader);

}
Shader::Shader(std::string pathVert, std::string pathFrag){
    std::cout<<"Shader Constructor"<<std::endl;

    std::string vPath; 
    GLuint vShader = 0; 
    GLuint geomShader = 0; 
    GLuint fShader = 0; 

    vShader = loadShader(GL_VERTEX_SHADER, pathVert); 
    fShader = loadShader(GL_FRAGMENT_SHADER, pathFrag); 

    this->linkProgram(vShader,geomShader,fShader);
}
Shader::~Shader(){
    std::cout<<"Shader destructor"<<std::endl;

    glDeleteProgram(idP);
}
// ********* METHODS *************

std::string Shader::loadShaderFromSource(std::string& source){
    
    std::string temp = "";
    std::string src = "";

    std::ifstream src_file;

    src_file.open(source);
    if(src_file.is_open()){
        while(std::getline(src_file,temp)){
            src+= temp + "\n";
        }
    }
    else{
        std::cout<<"Error: "<<source<<"  could not be open\n";
    }
    src_file.close();

    return src;

}
 GLuint Shader::loadShader(GLenum type, std::string& source){
   
    char infoLog[512];
    GLint success;  
    GLuint shader = glCreateShader(type);//Creates a type Shader: VERTEX or  FRAGMENT
    std::string src = loadShaderFromSource(source);
    const GLchar* srcShader = src.c_str();
    glShaderSource(shader,1,&srcShader,NULL);
    glCompileShader(shader);

    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cout<<"ERROR::LOADSHADERS::COULD_NOT_COMPLILE_VERTEX_SHADER\n";
        std::cout<<infoLog<<std::endl;
        //loadSuccess = false;
    }
    
    return shader;
 }
void Shader::linkProgram(GLuint vShader, GLuint geomShader, GLuint fShader){
    char infoLog[512];
    GLint success;
    std::cout<<"LINKING"<<std::endl;
    this->idP  = glCreateProgram();
    glAttachShader(idP,vShader);

    if(geomShader){
        glAttachShader(idP,geomShader);
    }
    glAttachShader(idP,fShader);

    glLinkProgram(idP);
    
    glGetProgramiv(idP,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(idP,512,NULL,infoLog);
        std::cout<<"ERROR::SHADERS::COULD_NOT_LINK_PROGRAM\n";
        std::cout<<infoLog<<std::endl;
    }

      //END
     glUseProgram(0);
}
void Shader::Bind(){
    glUseProgram(this->idP);
}
void Shader::unBind(){

    glUseProgram(0);
}
 void Shader::setUniformVec3f(glm::fvec3 value, std::string name){
      
     this->Bind();


    glUniform3fv(glGetUniformLocation(this->idP, name.c_str()),1, glm::value_ptr(value));




     this->unBind();
 }
void Shader::setUniformVec2f(glm::fvec2 value, std::string name){
      
     this->Bind();


    glUniform2fv(glGetUniformLocation(this->idP, name.c_str()),1, glm::value_ptr(value));




     this->unBind();
 }
void Shader::setUniformVec1f(GLfloat value, std::string name){
      
     this->Bind();


    glUniform1f(glGetUniformLocation(this->idP, name.c_str()),value);




     this->unBind();
 }
void Shader::setMat4fv(glm::mat4 value, std::string name, GLboolean transpose = GL_FALSE){
 
    this->Bind();

        glUniformMatrix4fv(glGetUniformLocation(this->idP, name.c_str()), 1,transpose, glm::value_ptr(value));

    this->unBind();
}