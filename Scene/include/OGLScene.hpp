#ifndef OGLSCENE_HPP
#define OGLSCENE_HPP

#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QString>
#include <QObject>
#include <QMatrix4x4>
#include <QMutex>
#include <QOpenGLFramebufferObject>

#include "Camera.hpp"
#include "Object.hpp"
#include "Arrows.hpp"

class OGLScene : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OGLScene(QWidget* parent = nullptr);
    ~OGLScene();

signals:
    void ObjectAdded(QString name);

public slots:
    void OnAddCube();
    void OnAddSphere();
    void OnAddTriangle();
    void OnActiveObjectChanged(int index);

protected:
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void initializeGL() override;
    
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    int m_height;
    int m_width;

    Camera camera;
    bool rotating;
    QPoint lastMousePos;

    Scene::Arrows arrows;
    QVector<Scene::Object*> objects;
    Scene::Object* activeObj;
    QMatrix4x4 projection;

    bool rotateCurObj = false;

    QTimer* redrawTimer;
    QMutex mutex;
};

#endif // OGLSCENE_HPP
