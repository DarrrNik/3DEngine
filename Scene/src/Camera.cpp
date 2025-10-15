#include "Camera.hpp"

Camera::Camera(QObject* parent, const QVector3D& position, const QVector3D& up, float yaw, float pitch, float roll)
    : QObject(parent), Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch), Roll(roll), moveDist(0.35f)
{
    updateVectors();
    WASDUpDown.fill(false);
}

QMatrix4x4 Camera::getViewMatrix() const
{
    QMatrix4x4 view;
    view.lookAt(Position, Position + Front, Up);
    return view;
}

QMatrix4x4 Camera::getTranslationMatrix() const
{
    QMatrix4x4 mat;
    mat.translate(-Position);
    return mat;
}

void Camera::moveForward(float distance)
{
    Position += Front * distance;
}

void Camera::moveRight(float distance)
{
    Position += Right * distance;
}

void Camera::moveUp(float distance)
{
    Position += Up * distance;
}

void Camera::rotate(float deltaYaw, float deltaPitch, float deltaRoll)
{
    Yaw += deltaYaw;
    Pitch += deltaPitch;
    Roll += deltaRoll;

    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateVectors();
}

void Camera::rotate(QPoint delta)
{
    float sensitivity = 0.085f;
    Yaw += delta.x() * sensitivity;
    Pitch -= delta.y() * sensitivity;

    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;
    updateVectors();
}

void Camera::setPosition(const QVector3D& pos)
{
    Position = pos;
}

void Camera::setAngles(float yaw, float pitch, float roll)
{
    Yaw = yaw;
    Pitch = pitch;
    Roll = roll;
    updateVectors();
}

void Camera::setMove(Direction dir, bool enable)
{
    WASDUpDown[static_cast<int>(dir)] = enable;
}

void Camera::move()
{
    if (WASDUpDown[static_cast<int>(Direction::Forward)])
    {
        moveForward(moveDist);
    }
    if (WASDUpDown[static_cast<int>(Direction::Back)])
    {
        moveForward(-moveDist);
    }
    if (WASDUpDown[static_cast<int>(Direction::Left)])
    {
        moveRight(-moveDist);
    }
    if (WASDUpDown[static_cast<int>(Direction::Right)])
    {
        moveRight(moveDist);
    }
    if (WASDUpDown[static_cast<int>(Direction::Up)])
    {
        moveUp(moveDist);
    }
    if (WASDUpDown[static_cast<int>(Direction::Down)])
    {
        moveUp(-moveDist);
    }
    updateVectors();
}

void Camera::updateVectors()
{
    // Вычисление нового вектора фронта по углам Эйлера
    QVector3D front;
    front.setX(qCos(qDegreesToRadians(Yaw)) * qCos(qDegreesToRadians(Pitch)));
    front.setY(qSin(qDegreesToRadians(Pitch)));
    front.setZ(qSin(qDegreesToRadians(Yaw)) * qCos(qDegreesToRadians(Pitch)));
    Front = front.normalized();

    // Правый и верхний векторы
    Right = QVector3D::crossProduct(Front, WorldUp).normalized();
    Up = QVector3D::crossProduct(Right, Front).normalized();
}
