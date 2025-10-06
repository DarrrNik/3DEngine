#pragma once

#include <QOpenGLWidget>
#include <glm/glm.hpp>

class Scene : public QOpenGLWidget
{
public:
    Scene() = delete;
    Scene(glm::fvec2 viewport, QWidget* parent = nullptr);
    ~Scene();

    
private:

};
