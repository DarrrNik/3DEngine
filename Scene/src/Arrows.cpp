#include "Arrows.hpp"

Scene::Arrows::Arrows()
{
}

void Scene::Arrows::init()
{
    initShaders("./shaders/arrows.vert", "./shaders/arrows.frag");
    initGeometry();
}

void Scene::Arrows::initGeometry()
{
    if (!isInitialized())
    {
        initializeOpenGLFunctions();
    }
    
    Vertex vertices[] = {        
        {{0.0f, 0.0f, 0.0f}, 0}, {{2.0f, 0.0f, 0.0f}, 0},
        {{0.0f, 0.0f, 0.0f}, 1}, {{0.0f, 2.0f, 0.0f }, 1},
        {{0.0f, 0.0f, 0.0f}, 2}, {{0.0f, 0.0f, 2.0f}, 2}
    };

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    shaderProgram.bind();

    shaderProgram.enableAttributeArray(0); // aPos
    shaderProgram.setAttributeBuffer(0, GL_FLOAT, offsetof(Vertex, pos), 3, sizeof(Vertex));

    shaderProgram.enableAttributeArray(1); // aFaceID
    shaderProgram.setAttributeBuffer(1, GL_FLOAT, offsetof(Vertex, faceID), 1, sizeof(Vertex));

    vao.release();
}

void Scene::Arrows::draw(const QMatrix4x4 &viewProj)
{
    shaderProgram.bind();
    shaderProgram.setUniformValue("uMVP", viewProj);

    vao.bind();
    glDrawArrays(GL_LINES, 0, 6);
    vao.release();

    shaderProgram.release();
}
