#ifndef ARROWS_HPP
#define ARROWS_HPP

#include <QObject>
#include <QOpenGLFunctions_4_5_Core>

#include <Object.hpp>

namespace Scene
{

class Arrows : public Object
{
public:
    Arrows();
    ~Arrows() = default;

    void init();
    void initGeometry() override;    
    void draw(const QMatrix4x4& viewProj) override;
};

}
#endif
