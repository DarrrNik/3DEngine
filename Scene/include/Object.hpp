#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QMutex>
#include <QString>
#include <vector>

namespace Scene
{

class Object : protected QOpenGLFunctions_4_5_Core
{
public:
    enum class Axis { Default, OX, OY, OZ };
    
    Object(QString n = "");
    virtual ~Object();

    virtual bool initShaders(const QString& vertexPath, const QString& fragmentPath);
    virtual void initGeometry();
    virtual void draw(const QMatrix4x4& viewProj);

    virtual void setRotating(bool set);
    virtual bool isRotating();
    virtual void rotate(const QPoint& delta);

    virtual void setMoving(bool set);
    virtual void setMoveAxis(Axis axis);
    virtual bool isMoving();
    virtual void move(const QPoint& delta);
    
    virtual void setScaling(bool set);
    virtual bool isScaling();
    virtual void scale(const QPoint& delta);
protected:
    void updateModelMatrix();

    struct Vertex {
        QVector3D pos;
        float faceID;
    };
    
    QVector3D position { 0, 0, 0 };
    QMatrix4x4 modelMatrix;
    std::vector<Vertex> vertices;

    bool m_isRotating = false;
    QVector2D rotAngles { 0, 0 };
    bool m_isMoving = false;
    Axis m_moveAxis;
    bool m_isScaling = false;
    float m_scale = 1;

    QOpenGLShaderProgram shaderProgram;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo{ QOpenGLBuffer::VertexBuffer };

    QString name;

    QMutex mutex;
};

}

#endif
