// #define GLFW_INCLUDE_NONE
// #include <GLFW/glfw3.h>
// #include <glimac/Program.hpp>
// #include <glimac/FilePath.hpp>
// #include <glimac/Image.hpp>
// #include <glimac/glm.hpp>
#include "p6/p6.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>


struct Vertex2DColor
{
    glm::vec2 m_position;
    glm::vec3 m_color;

    Vertex2DColor(){
        m_position = glm::vec2(0.);
        m_color = glm::vec3(1.);
    };
    Vertex2DColor(glm::vec2 position, glm::vec3 color){
        m_position = position;
        m_color = color;
    }
    Vertex2DColor(glm::vec2 position){
        m_position = position;
    }
};

struct Vertex2DUV
{
    
    glm::vec2 m_position;
    glm::vec2 m_texture;
    
    
    Vertex2DUV(glm::vec2 position, glm::vec2 texture){
        m_position = position;
        m_texture = texture;
    }
};
glm::mat3 translate(float tx, float ty){
  return glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(tx, ty, 1));
}

glm::mat3 scale(float sx, float sy){
  return glm::mat3(glm::vec3(sx, 0, 0), glm::vec3(0, sy, 0), glm::vec3(0, 0, 1));
}

glm::mat3 rotate(float a){
  return glm::mat3(glm::vec3(cos(glm::radians(a)), sin(glm::radians(a)), 0), glm::vec3(-sin(glm::radians(a)),cos(glm::radians(a)) , 0), glm::vec3(0, 0, 1));
}


int main([[maybe_unused]]int argc, [[maybe_unused]] char* argv[])
{


    auto ctx = p6::Context{{1280, 720, "TP3 EX1 shader triforce"}};
    ctx.maximize_window();



    //template jules
    img::Image img_load = p6::load_image_buffer("assets/textures/triforce.png");

  



    
 
    //template jules
    const p6::Shader shader = p6::load_shader(
        "shaders/tex2D.vs.glsl",
        "shaders/tex2D.fs.glsl"
    );

    shader.use();

    //recuperation de la variable uniforme
    // auto position = glGetUniformLocation(program.getGLId(), "uTime");
    auto position_mat = glGetUniformLocation(shader.id(), "uModelMatrix");

    // auto position_col = glGetUniformLocation(program.getGLId(), "uColor");
    auto position_text = glGetUniformLocation(shader.id(), "uTexture");

    

    

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_load.width(), img_load.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_load.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
    glBindTexture(GL_TEXTURE_2D, 0);




    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::vector<Vertex2DUV> vertices;
    vertices.push_back(Vertex2DUV(glm::vec2(-1., -1.), glm::vec2(0., 0.)));
    vertices.push_back(Vertex2DUV(glm::vec2(1., -1.), glm::vec2(1., 0.)));
    vertices.push_back(Vertex2DUV(glm::vec2(0., 1.), glm::vec2(0.5, 1.)));

    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(Vertex2DUV), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    const GLuint VERTEX_ATTR_UV = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_UV);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);    
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, m_position)); 

    glVertexAttribPointer(VERTEX_ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, m_texture)); //position dans le vbo, la taille d'un attribut (nb coord), type, stride, taille d'asso de chaque coord (ici 5 * taille float), position du premier elem
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //debind de la vao
    glBindVertexArray(0);


    

    auto start = std::chrono::steady_clock::now();

    







    /* Loop until the user closes the window */
    // while (!glfwWindowShouldClose(window)) {
    ctx.update = [&]() {
        shader.use();
        glClearColor(0.f, 0.0f, 0.0f, 1.f);

        

        glClear(GL_COLOR_BUFFER_BIT);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start; 
        glm::mat3 mat_rot = rotate(10*elapsed_seconds.count());
        glm::mat3 mat_rot1 = rotate(-45*elapsed_seconds.count());
        glm::mat3 mat_rot2 = rotate(45*elapsed_seconds.count());


       

        // glUniform1f(position, rotation);
        // rotation+=5;
        glBindVertexArray(vao); 
        glBindTexture(GL_TEXTURE_2D, texture);

        glm::mat3 mat_scale1 = scale(0.2, 0.2);
        glm::mat3 mat_translate1 = translate(0.5, 0.5);
        // glUniform3f(position_col, 1., 1., 0.); //pour changer de couleur dans le shader
        glUniform1i(position_text,0);
        glUniformMatrix3fv(position_mat,1,GL_FALSE, glm::value_ptr(mat_rot*mat_translate1*mat_scale1*mat_rot1)); //pour changer la position grace au shader
        glDrawArrays(GL_TRIANGLES,0,3);

        glm::mat3 mat_scale2 = scale(0.2, 0.2);
        glm::mat3 mat_translate2 = translate(-0.5, -0.5);
        // glUniform3f(position_col, 1., 0., 0.);
        glUniform1i(position_text,0);
        glUniformMatrix3fv(position_mat,1,GL_FALSE, glm::value_ptr(mat_rot*mat_translate2*mat_scale2*mat_rot2));
        glDrawArrays(GL_TRIANGLES,0,3);

        glm::mat3 mat_scale3 = scale(0.2, 0.2);
        glm::mat3 mat_translate3 = translate(0.5, -0.5);
        // glUniform3f(position_col, 0., 1., 0.);
        glUniform1i(position_text,0);
        glUniformMatrix3fv(position_mat,1,GL_FALSE, glm::value_ptr(mat_rot*mat_translate3*mat_scale3*mat_rot1));
        glDrawArrays(GL_TRIANGLES,0,3);

        glm::mat3 mat_scale4 = scale(0.2, 0.2);
        glm::mat3 mat_translate4 = translate(-0.5, 0.5);
        // glUniform3f(position_col, 0., 0., 1.); 
        glUniform1i(position_text,0);
        glUniformMatrix3fv(position_mat,1,GL_FALSE, glm::value_ptr(mat_rot*mat_translate4*mat_scale4*mat_rot2));
        glDrawArrays(GL_TRIANGLES,0,3);




        glBindVertexArray(0);


        
    };
    
    ctx.start();

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &texture);


    

}