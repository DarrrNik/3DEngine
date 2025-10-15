#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <QString>

#include "Object.hpp"

namespace Scene
{

class Triangle : public Object
{
public:
    Triangle(QString name);
    ~Triangle();
    
    void draw(const QMatrix4x4& viewProj) override;
};

}

#endif