#include "Object.hpp"
#include <QFile>
#include <QMutexLocker>
#include <algorithm>

using namespace Scene;

Object::Object(QString n)
    : vbo(QOpenGLBuffer::VertexBuffer), name(n)
{
    vertices = {
        // Front face (0)
        {{-0.5f,-0.5f, 0.5f}, 0}, {{0.5f,-0.5f, 0.5f}, 0}, {{0.5f,0.5f,0.5f}, 0},
        {{-0.5f,-0.5f, 0.5f}, 0}, {{0.5f,0.5f,0.5f}, 0}, {{-0.5f,0.5f,0.5f},0},

        // Back face (1)
        {{-0.5f,-0.5f,-0.5f},1}, {{0.5f,0.5f,-0.5f},1}, {{0.5f,-0.5f,-0.5f},1},
        {{-0.5f,-0.5f,-0.5f},1}, {{-0.5f,0.5f,-0.5f},1}, {{0.5f,0.5f,-0.5f},1},

        // Left face (2)
        {{-0.5f,-0.5f,-0.5f},2}, {{-0.5f,-0.5f,0.5f},2}, {{-0.5f,0.5f,0.5f},2},
        {{-0.5f,-0.5f,-0.5f},2}, {{-0.5f,0.5f,0.5f},2}, {{-0.5f,0.5f,-0.5f},2},

        // Right face (3)
        {{0.5f,-0.5f,-0.5f},3}, {{0.5f,0.5f,0.5f},3}, {{0.5f,-0.5f,0.5f},3},
        {{0.5f,-0.5f,-0.5f},3}, {{0.5f,0.5f,-0.5f},3}, {{0.5f,0.5f,0.5f},3},

        // Top face (4)
        {{-0.5f,0.5f,-0.5f},4}, {{-0.5f,0.5f,0.5f},4}, {{0.5f,0.5f,0.5f},4},
        {{-0.5f,0.5f,-0.5f},4}, {{0.5f,0.5f,0.5f},4}, {{0.5f,0.5f,-0.5f},4},

        // Bottom face (5)
        {{-0.5f,-0.5f,-0.5f},5}, {{0.5f,-0.5f,-0.5f},5}, {{0.5f,-0.5f,0.5f},5},
        {{-0.5f,-0.5f,-0.5f},5}, {{0.5f,-0.5f,0.5f},5}, {{-0.5f,-0.5f,0.5f},5},

    };
    m_moveAxis = Axis::Default;
}

Object::~Object()
{
    vao.destroy();
    vbo.destroy();
}

bool Object::initShaders(const QString& vertexPath, const QString& fragmentPath)
{
    QMutexLocker locker(&mutex);
    if (!isInitialized())
    {
        initializeOpenGLFunctions();
    }
    if (shaderProgram.isLinked())
    {
        shaderProgram.removeAllShaders();
    }
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexPath)) {
        qWarning() << "Vertex shader error:" << shaderProgram.log();
        return false;
    }
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentPath)) {
        qWarning() << "Fragment shader error:" << shaderProgram.log();
        return false;
    }
    if (!shaderProgram.link()) {
        qWarning() << "Shader link error:" << shaderProgram.log();
        return false;
    }
    return true;
}

void Object::initGeometry()
{
    QMutexLocker locker(&mutex);
    if (!isInitialized())
    {
        initializeOpenGLFunctions();
    }

    if (vao.isCreated())
    {
        vao.destroy();
    }
    if (vbo.isCreated())
    {
        vbo.destroy();
    }

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices.data(), vertices.size() * sizeof(Vertex));
    vbo.setUsagePattern(QOpenGLBuffer::StreamDraw);

    shaderProgram.bind();

    shaderProgram.enableAttributeArray(0); // aPos
    shaderProgram.setAttributeBuffer(0, GL_FLOAT, offsetof(Vertex, pos), 3, sizeof(Vertex));

    shaderProgram.enableAttributeArray(1); // aFaceID
    shaderProgram.setAttributeBuffer(1, GL_FLOAT, offsetof(Vertex, faceID), 1, sizeof(Vertex));

    vao.release();
}

void Object::draw(const QMatrix4x4& viewProj)
{
    QMutexLocker locker(&mutex);
    shaderProgram.bind();
    shaderProgram.setUniformValue("uMVP", viewProj);
    shaderProgram.setUniformValue("modelMatrix", modelMatrix);

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    vao.release();

    shaderProgram.release();
}

void Scene::Object::setRotating(bool set)
{
    m_isRotating = set;
}

bool Scene::Object::isRotating()
{
    return m_isRotating;
}

void Scene::Object::setMoving(bool set)
{
    m_isMoving = set;
}

void Scene::Object::setMoveAxis(Axis axis)
{
    m_moveAxis = axis;
}

bool Scene::Object::isMoving()
{
    return m_isMoving;
}

void Scene::Object::move(const QPoint &delta)
{
    QMutexLocker locker(&mutex);
    constexpr float sensitivity = 0.01f; 
    float movementX = delta.x() * sensitivity; 
    float movementY = -delta.y() * sensitivity;
    switch (m_moveAxis)
    {
    case Axis::OX:
    {
        position.setX(position.x() + movementX);
        break;
    }
    case Axis::OY:
    {
        position.setY(position.y() + movementY);
        break;
    }
    case Axis::OZ:
    {
        position.setZ(position.z() + movementX);
        break;
    }
    }
    updateModelMatrix();
}

void Scene::Object::setScaling(bool set)
{
    m_isScaling = set;
}

bool Scene::Object::isScaling()
{
    return m_isScaling;
}

void Scene::Object::scale(const QPoint &delta)
{
    float sensitivity = 0.075f;
    m_scale += delta.x() * sensitivity;
    updateModelMatrix();
}

void Scene::Object::updateModelMatrix()
{
    modelMatrix.setToIdentity();
    modelMatrix.translate(position);
    modelMatrix.rotate(rotAngles.y(), 0.0f, 1.0f, 0.0f);
    modelMatrix.rotate(rotAngles.x(), 1.0f, 0.0f, 0.0f);
    modelMatrix.scale(m_scale);
}

void Scene::Object::rotate(const QPoint &delta)
{
    QMutexLocker locker(&mutex);
    float sensitivity = 0.05f;
    float newX = rotAngles.x() + delta.y() * sensitivity;
    float newY = rotAngles.y() + delta.x() * sensitivity;

    if (abs(newX) >= 360.0f)
    {
        newX = 0;
    }
    if (abs(newY) >= 360.0f)
    {
        newY = 0;
    }

    rotAngles.setX(newX);
    rotAngles.setY(newY);

    updateModelMatrix();
}
