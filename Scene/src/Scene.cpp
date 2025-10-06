#include "Scene.hpp"

#include <GL/gl.h>

Scene::Scene(glm::fvec2 viewport, QWidget* parent)
    : QOpenGLWidget(parent)
{
    glViewport(0, 0, viewport.x, viewport.y);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

Scene::~Scene()
{

}
