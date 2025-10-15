#include "OGLScene.hpp"
#include <algorithm>
#include <QMetaMethod>
#include <QOpenGLTexture>

#include "Cube.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"

using namespace Scene;

OGLScene::OGLScene(QWidget* parent)
    : QOpenGLWidget(parent), m_width(width()), m_height(height()),
      camera(this, QVector3D(0.0f,0.0f,3.0f)), rotating(false),
      objects{ }, activeObj(nullptr)
{
    redrawTimer = new QTimer(this);
    connect(redrawTimer, &QTimer::timeout, this, qOverload<>(&QWidget::update));
    connect(redrawTimer, &QTimer::timeout, &camera, &Camera::move);
    redrawTimer->start(16);

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    setFocus();
}

OGLScene::~OGLScene() 
{
    std::for_each(objects.begin(), objects.end(), 
        [](Object* obj) { delete obj; });
}

void OGLScene::OnAddCube()
{
    QMutexLocker locker(&mutex);
    makeCurrent();
    const QString name = QString("Cube_") + QString::number(objects.size() + 1);
    objects.append(new Cube(name));
    objects.last()->initShaders("shaders/colorful.vert", "shaders/colorful.frag");
    objects.last()->initGeometry();
    doneCurrent();
    emit ObjectAdded(name);
}

void OGLScene::OnAddSphere()
{
    QMutexLocker locker(&mutex);
    makeCurrent();
    const QString name = QString("Sphere_") + QString::number(objects.size() + 1);
    objects.append(new Sphere(name));
    objects.last()->initShaders("shaders/colorful.vert", "shaders/colorful.frag");
    objects.last()->initGeometry();
    doneCurrent();
    emit ObjectAdded(name);
}

void OGLScene::OnAddTriangle()
{
    QMutexLocker locker(&mutex);
    makeCurrent();
    const QString name = QString("Triangle_") + QString::number(objects.size() + 1);
    objects.append(new Triangle(name));
    objects.last()->initShaders("shaders/colorful.vert", "shaders/colorful.frag");
    objects.last()->initGeometry();
    doneCurrent();
    emit ObjectAdded(name);
}

void OGLScene::OnActiveObjectChanged(int index)
{
    activeObj = objects[index];
}

void OGLScene::paintGL()
{
    QMutexLocker locker(&mutex);
    glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    QMatrix4x4 view = camera.getViewMatrix();
    arrows.draw(projection * view);
    for (auto* obj : objects)
    {
        obj->draw(projection * view);
    }
}

void OGLScene::resizeGL(int w, int h)
{
    QMutexLocker locker(&mutex);
    makeCurrent();
    m_width = w;
    m_height = h;
    glViewport(0, 0, w, h);

    projection.setToIdentity();
    projection.perspective(45.0f, float(width()) / float(height()), 0.1f, 100.0f);
}

void OGLScene::initializeGL()
{
    QMutexLocker locker(&mutex);
    initializeOpenGLFunctions();
    qDebug() << "GL version:" << reinterpret_cast<const char*>(glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST);
    arrows.init();
}

void OGLScene::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        rotating = true;
        lastMousePos = event->pos();

        grabMouse();
        setCursor(Qt::BlankCursor);
        setFocus();
    }
    QWidget::mousePressEvent(event);
}

void OGLScene::mouseMoveEvent(QMouseEvent *event)
{
    QPoint delta = event->pos() - lastMousePos;
    if (rotating && activeObj && activeObj->isRotating())
    {
        activeObj->rotate(delta);
        QCursor::setPos(lastMousePos);
    }
    else if (rotating && activeObj && activeObj->isMoving())
    {
        activeObj->move(delta);
        QCursor::setPos(lastMousePos);
    }
    else if (rotating && activeObj && activeObj->isScaling())
    {
        activeObj->scale(delta);
        QCursor::setPos(lastMousePos);
    }
    else if (rotating) 
    {
        camera.rotate(delta);
        QCursor::setPos(lastMousePos);
    }
    QWidget::mouseMoveEvent(event);
}

void OGLScene::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        rotating = false;

        releaseMouse();
        unsetCursor();
    }
    QWidget::mouseReleaseEvent(event);
}

void OGLScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Control:
    {
        camera.setMove(Camera::Direction::Down, true);
        break;
    }
    case Qt::Key_Space:
    {
        camera.setMove(Camera::Direction::Up, true);
        break;
    }
    case Qt::Key_W:
    {
        camera.setMove(Camera::Direction::Forward, true);
        break;
    }
    case Qt::Key_S:
    {
        camera.setMove(Camera::Direction::Back, true);
        break;
    }
    case Qt::Key_A:
    {
        camera.setMove(Camera::Direction::Left, true);
        break;
    }
    case Qt::Key_D:
    {
        camera.setMove(Camera::Direction::Right, true);
        break;
    }
    case Qt::Key_X:
    {
        if (activeObj)
        {
            activeObj->setMoveAxis(Object::Axis::OX);
        }
        break;
    }
    case Qt::Key_Y:
    {
        if (activeObj)
        {
            activeObj->setMoveAxis(Object::Axis::OY);
        }
        break;
    }
    case Qt::Key_Z:
    {
        if (activeObj)
        {
            activeObj->setMoveAxis(Object::Axis::OZ);
        }
        break;
    }
    case Qt::Key_R:
    {
        if (activeObj)
        {
            activeObj->setRotating(true);
        }
        break;
    }
    case Qt::Key_E:
    {
        if (activeObj)
        {
            activeObj->setMoving(true);
        }
        break;
    }
    case Qt::Key_T:
    {
        if (activeObj)
        {
            activeObj->setScaling(true);
        }
        break;
    }
    }
    QWidget::keyPressEvent(event);
}

void OGLScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Control:
    {
        camera.setMove(Camera::Direction::Down, false);
        break;
    }
    case Qt::Key_Space:
    {
        camera.setMove(Camera::Direction::Up, false);
        break;
    }
    case Qt::Key_W:
    {
        camera.setMove(Camera::Direction::Forward, false);
        break;
    }
    case Qt::Key_S:
    {
        camera.setMove(Camera::Direction::Back, false);
        break;
    }
    case Qt::Key_A:
    {
        camera.setMove(Camera::Direction::Left, false);
        break;
    }
    case Qt::Key_D:
    {
        camera.setMove(Camera::Direction::Right, false);
        break;
    }
    case Qt::Key_X:
    case Qt::Key_Y:
    case Qt::Key_Z:
    {
        if (activeObj)
        {
            activeObj->setMoveAxis(Object::Axis::Default);
        }
        break;
    }
    case Qt::Key_R:
    {
        if (activeObj)
        {
            activeObj->setRotating(false);
        }
        break;
    }
    case Qt::Key_E:
    {
        if (activeObj)
        {
            activeObj->setMoving(false);
        }
        break;
    }
    case Qt::Key_T:
    {
        if (activeObj)
        {
            activeObj->setScaling(false);
        }
        break;
    }
    }
    QWidget::keyReleaseEvent(event);
}
