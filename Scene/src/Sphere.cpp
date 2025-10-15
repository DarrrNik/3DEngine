#include "Sphere.hpp"

Scene::Sphere::Sphere(QString name) : Object(name)
{
    vertices = {};
    int stacks = 16, slices = 32;
    float radius = 0.75f;
    int id = 0;
    for (int i = 0; i <= stacks; ++i)
    {
        float phi = M_PI * float(i) / stacks; // широта от 0 до π
        float y = cos(phi);
        float r = sin(phi); // радиус горизонтального круга

        for (int j = 0; j <= slices; ++j)
        {
            float theta = 2.0f * M_PI * float(j) / slices; // долгота от 0 до 2π
            float x = r * cos(theta);
            float z = r * sin(theta);

            Vertex v;
            v.pos = QVector3D(x * radius, y * radius, z * radius);
            v.faceID = id; // можно не использовать

            vertices.push_back(v);
            id = (id + 1) % 7;
        }
    }
    vertices.shrink_to_fit();

    indices = {};
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int first  = i * (slices + 1) + j;
            int second = first + slices + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
    indices.shrink_to_fit();
}

Scene::Sphere::~Sphere()
{
}

void Scene::Sphere::initGeometry()
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
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    ibo.create();
    ibo.bind();
    ibo.allocate(indices.data(), indices.size() * sizeof(unsigned int));
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    shaderProgram.bind();

    shaderProgram.enableAttributeArray(0); // aPos
    shaderProgram.setAttributeBuffer(0, GL_FLOAT, offsetof(Vertex, pos), 3, sizeof(Vertex));

    shaderProgram.enableAttributeArray(1); // aFaceID
    shaderProgram.setAttributeBuffer(1, GL_FLOAT, offsetof(Vertex, faceID), 1, sizeof(Vertex));

    vao.release();
}

void Scene::Sphere::draw(const QMatrix4x4 &viewProj)
{
    QMutexLocker locker(&mutex);
    shaderProgram.bind();
    shaderProgram.setUniformValue("uMVP", viewProj);
    shaderProgram.setUniformValue("modelMatrix", modelMatrix);

    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.release();

    shaderProgram.release();
}
