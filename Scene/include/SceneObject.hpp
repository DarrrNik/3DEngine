#pragma once

#include <glm/glm.hpp>

namespace Scene
{

class Object
{
public:
    Object();
    virtual ~Object();

    void rotate(glm::mat3 rotMat);
    void move(glm::fvec3 moveVec);
private:
    glm::fvec3 pos;
    glm::fvec3 color;
    float scale;
};

}