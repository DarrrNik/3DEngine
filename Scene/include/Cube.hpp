#ifndef CUBE_HPP
#define CUBE_HPP

#include <QString>

#include "Object.hpp"

namespace Scene
{

class Cube : public Object
{
public:
    Cube(QString name);
    ~Cube();
};

}

#endif