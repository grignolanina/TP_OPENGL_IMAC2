#include <iostream>
#include <vector>
#include "glimac/FreeflyCamera.hpp"
#include "glimac/TrackballCamera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"
#include "glm/gtc/random.hpp"

int const window_width  = 1280;
int const window_height = 720;

struct EarthProgram {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    //texture comment
    // GLint uEarthTexture;
    // GLint uCloudTexture;

    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    EarthProgram()
        : m_Program{p6::load_shader("shaders/3D.vs.glsl", "shaders/directionalLight.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uKd = glGetUniformLocation(m_Program.id(), "uKd");
        uKs = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess = glGetUniformLocation(m_Program.id(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");

        //texture comment
        // uEarthTexture = glGetUniformLocation(m_Program.id(), "uEarthTexture");
        // uCloudTexture = glGetUniformLocation(m_Program.id(), "uCloudTexture");
    }
};

struct MoonProgram {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    //texture comment
    // GLint uTexture;

    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    MoonProgram()
        : m_Program{p6::load_shader("shaders/3D.vs.glsl", "shaders/directionalLight.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        //texture comment
        // uTexture      = glGetUniformLocation(m_Program.id(), "uTexture");
        uKd = glGetUniformLocation(m_Program.id(), "uKd");
        uKs = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess = glGetUniformLocation(m_Program.id(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");
    }
};

int main()
{
    auto ctx = p6::Context{{window_width, window_height, "TP5 EX3"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    
    //declaration des deux structures a la place du load shaders
    EarthProgram earthProgram{};
    MoonProgram moonProgram{};

    //load texture texture comment
    // img::Image img_terre = p6::load_image_buffer("assets/textures/EarthMap.jpg");
    // img::Image img_lune = p6::load_image_buffer("assets/textures/MoonMap.jpg");
    // img::Image img_nuage = p6::load_image_buffer("assets/textures/CloudMap.jpg");


    //creation du vbo
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //creation de la shape
    const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16);

    // fill those coords in the vbo / Static is for constant variables
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    //oprion pour voir les tests en profondeur?
    glEnable(GL_DEPTH_TEST);

    //texture comment
    //initialisation de textures -> multitexturing
    // GLuint textureTerre;
    // glGenTextures(1, &textureTerre);
    // glActiveTexture(GL_TEXTURE0); // la texture textureTerre est bindée sur l'unité GL_TEXTURE0
    // glBindTexture(GL_TEXTURE_2D, textureTerre);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_terre.width(), img_terre.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_terre.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // //debind text
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, 0);
    
    // GLuint textureMoon;
    // glGenTextures(1, &textureMoon);
    // glActiveTexture(GL_TEXTURE1); // la texture textureCloud est bindée sur l'unité GL_TEXTURE1
    // glBindTexture(GL_TEXTURE_2D, textureMoon);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_lune.width(), img_lune.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_lune.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // GLuint textureCloud;
    // glGenTextures(1, &textureCloud);
    // glBindTexture(GL_TEXTURE_2D, textureCloud);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_nuage.width(), img_nuage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_nuage.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);


    // creation du vao
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORM     = 1;
    const GLuint VERTEX_ATTR_UV       = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORM);
    glEnableVertexAttribArray(VERTEX_ATTR_UV);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, position)));
    glVertexAttribPointer(VERTEX_ATTR_NORM, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, normal)));
    glVertexAttribPointer(VERTEX_ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, texCoords)));

    // debind du vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // debind du vao
    glBindVertexArray(0);

    //calcul matrice de projection pour le shader
    glm::mat4 ProjMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);


    //axe de rotation aléatoire lune
    std::vector<glm::vec3> angleRotation;
    std::vector<glm::vec3> axeTranslation;

    for(int i = 0; i<32; i++){
        angleRotation.push_back(glm::sphericalRand(2.f));
        axeTranslation.push_back(glm::sphericalRand(2.f));
    }

    //creation cam & initialisation des mouvements
    // TrackballCamera camera(5, 0, 0);
    Freefly camera;
    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;

    
    ctx.update = [&]() {
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        //CAMERA
        if(right){
            camera.moveLeft(-0.1f);
        }
        if(left){
            camera.moveLeft(0.1f);
        }
        if(up){
            camera.moveFront(0.1f);
        }
        if(down){
            camera.moveFront(-0.1f);
        }

        ctx.key_pressed = [&right, &up, &left, &down](p6::Key key){
            if(key.logical == "d"){
                right = true;
            }
            if(key.logical == "q"){
                left = true;
            }
            if(key.logical == "z"){
                up = true;
            }
            if(key.logical == "s"){
                down = true;
            }
        };

        ctx.key_released = [&right, &up, &left, &down](p6::Key key){
            if(key.logical == "d"){
                right = false;
            }
            if(key.logical == "q"){
                left = false;
            }
            if(key.logical == "z"){
                up = false;
            }
            if(key.logical == "s"){
                down = false;
            }
        };

        ctx.mouse_dragged = [&camera](const p6::MouseDrag& button) {
            camera.rotateLeft(button.delta.x * 5);
            camera.rotateUp(-button.delta.y * 5);
        };

        ctx.mouse_scrolled = [&](p6::MouseScroll scroll){
            camera.moveFront(-scroll.dy);
        };

        const glm::mat4 viewMatrix = camera.getViewMatrix();






        // Shader.use();
        earthProgram.m_Program.use();

        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //bind vao
        glBindVertexArray(vao);


        //TERRE texture comment
        // glUniform1i(earthProgram.uEarthTexture, 0);
        // glUniform1i(earthProgram.uCloudTexture, 1);

        



        const glm::mat4 globalMVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, -5.f});
        const glm::mat4 earthMMatrix = glm::rotate(globalMVMatrix, ctx.time(), {0.f, 1.f, 0.f});
        const glm::mat4 earthMVMatrix = viewMatrix*earthMMatrix; //variation de la MV (simuler une cam)
        const glm::mat4 earthMVPMatrix = ProjMatrix * earthMVMatrix;
        
        // const glm::mat4 earthMVMatrix = glm::rotate(viewMatrix, ctx.time(), {0.f, 1.f, 0.f});
        //app matrice dans le shader
        glUniform3fv(earthProgram.uKd, 1, glm::value_ptr(glm::vec3(0.5, 0.3, 0.3))); //coefficient glossy
        glUniform3fv(earthProgram.uKs, 1, glm::value_ptr(glm::vec3(0.8, 0.2, 0.3))); //coef de reflexion
        glUniform1f(earthProgram.uShininess, 0.6f); //brillance
        glm::vec3 lightdir(1., 1., 1.);
        lightdir = (earthMVMatrix * glm::vec4(lightdir,0.));
        const glm::mat4 normalMatrix = glm::transpose(glm::inverse(earthMVMatrix));

    
        glUniform3fv(earthProgram.uLightDir_vs, 1, glm::value_ptr(lightdir));
        glUniform3fv(earthProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(2.0, 2.0, 2.0)));
       
        glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
        glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(earthMVPMatrix));

        //texture comment
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, textureTerre);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, textureCloud);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());        

        //LUNE
        moonProgram.m_Program.use();
        //texture comment
        // glUniform1i(moonProgram.uTexture, 0);
        // glActiveTexture(GL_TEXTURE0);
       
        

        for(int i = 0; i<32; i++){
            glm::mat4 moonMMatrix = glm::rotate(globalMVMatrix, ctx.time(), angleRotation[i]);
            moonMMatrix = glm::rotate(moonMMatrix, ctx.time(), angleRotation[i]); // Translation * Rotation
            moonMMatrix = glm::translate(moonMMatrix, axeTranslation[i]); // Translation * Rotation * Translation
            moonMMatrix = glm::scale(moonMMatrix, glm::vec3{0.2f}); // Translation * Rotation * Translation * Scale


            const glm::mat4 moonMVMatrix = viewMatrix*moonMMatrix; //variation de la MV (simuler une cam)
            const glm::mat4 moonMVPMatrix = ProjMatrix * moonMVMatrix;

            glm::vec3 Kd(0.1, 0.1, 0.3); //coef glossy
            glm::vec3 Ks(0.2, 0.4, 0.8); //coef de reflexion
            glm::vec3 intensity(2., 2., 2.);

            glUniform3fv(moonProgram.uKd, 1, glm::value_ptr(Kd)); 
            glUniform3fv(moonProgram.uKs, 1, glm::value_ptr(Ks)); 

            glUniform1f(moonProgram.uShininess, 0.01); //brillance
            lightdir = (moonMVMatrix * glm::vec4(lightdir,0.));
            glUniform3fv(moonProgram.uLightDir_vs, 1, glm::value_ptr(lightdir));
            glUniform3fv(moonProgram.uLightIntensity, 1, glm::value_ptr(intensity));
            const glm::mat4 normalMoonMatrix = glm::transpose(glm::inverse(moonMVMatrix));


            glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(moonMVMatrix));
            glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMoonMatrix));
            glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(moonMVPMatrix));

            //texture comment
            // glBindTexture(GL_TEXTURE_2D, textureMoon);

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);

        //debind vao
        glBindVertexArray(0);

    };

    

    ctx.start();

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    //texture comment
    // glDeleteTextures(1, &textureTerre);
    // glDeleteTextures(1, &textureMoon);
    // glDeleteTextures(1, &textureCloud);

    return 0;
}

