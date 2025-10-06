#include "SceneObject.hpp"

Scene::Object::Object()
    : pos(0.0), color(0.0, 0.0, 1.0), scale(0)
{
}

Scene::Object::~Object()
{
}

void Scene::Object::rotate(glm::mat3 rotMat)
{
}

void Scene::Object::move(glm::fvec3 moveVec)
{
}
