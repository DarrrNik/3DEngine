#include "Triangle.hpp"

Scene::Triangle::Triangle(QString name) : Object(name)
{
    vertices = {
        {{ 1,  1,  1}, 0}, {{-1, -1,  1}, 0}, {{-1,  1, -1}, 0},
        {{ 1,  1,  1}, 1}, {{ 1, -1, -1}, 1}, {{-1, -1,  1}, 1},
        {{ 1,  1,  1}, 2}, {{-1,  1, -1}, 2}, {{ 1, -1, -1}, 2},
        {{-1, -1,  1}, 3}, {{ 1, -1, -1}, 3}, {{-1,  1, -1}, 3}
    };
}

Scene::Triangle::~Triangle()
{
}

void Scene::Triangle::draw(const QMatrix4x4 &viewProj)
{
    QMutexLocker locker(&mutex);
    shaderProgram.bind();
    shaderProgram.setUniformValue("uMVP", viewProj);
    shaderProgram.setUniformValue("modelMatrix", modelMatrix);

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 12);
    vao.release();

    shaderProgram.release();
}
