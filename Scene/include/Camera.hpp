#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QObject>
#include <QVector3D>
#include <QMatrix4x4>
#include <QtMath>
#include <QShortcut>

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(
        QObject* parent = nullptr,
        const QVector3D& position = QVector3D(0.0f, 0.0f, 3.0f),
        const QVector3D& up = QVector3D(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f,
        float roll = 0.0f
    );

    enum class Direction
    {
        Forward = 0,
        Left,
        Back,
        Right,
        Up,
        Down
    };

    // Возвращает матрицу вида для шейдера
    QMatrix4x4 getViewMatrix() const;

    // Отдельная матрица перевода (только сдвиг)
    QMatrix4x4 getTranslationMatrix() const;

    // Перемещения в локальных осях камеры
    void moveForward(float distance);
    void moveRight(float distance);
    void moveUp(float distance);

    // Поворот камеры: дельты в градусах
    void rotate(float deltaYaw, float deltaPitch, float deltaRoll = 0.0f);
    void rotate(QPoint delta);

    // Быстрая установка позиции и углов
    void setPosition(const QVector3D& pos);
    void setAngles(float yaw, float pitch, float roll = 0.0f);

    void setMove(Direction dir, bool enable);
    void move();

    const QVector3D& getPosition() const { return Position; }
    const QVector3D& getFront() const { return Front; }
    const QVector3D& getUp() const { return Up; }
    const QVector3D& getRight() const { return Right; }

private:
    QVector3D Position;
    QVector3D Front;
    QVector3D Up;
    QVector3D Right;
    QVector3D WorldUp;

    // Углы Эйлера (в градусах)
    float Yaw;
    float Pitch;
    float Roll;

    std::array<bool, 6> WASDUpDown;
    float moveDist;

    void updateVectors();
};

#endif
