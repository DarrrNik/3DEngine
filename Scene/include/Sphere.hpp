#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <QString>

#include "Object.hpp"

namespace Scene
{

class Sphere : public Object
{
public:
    Sphere(QString name);
    ~Sphere();
    
    void initGeometry() override;
    void draw(const QMatrix4x4& viewProj) override;
protected:
    QOpenGLBuffer ibo { QOpenGLBuffer::IndexBuffer };
    std::vector<unsigned int> indices;
};

}

#endif