# 3DEngine

Простейший 3D движок на C++ с использованием Qt6 и OpenGL.

## Описание

Проект реализует базовую 3D-сцену с поддержкой:

- Отрисовки кубов, сфер и треугольников.
- Камеры с управлением WASD + мышь.
- Стилезации объектов через фрагментные шейдеры.
- Перемещение, поворот и масштабирование объектов через горячие клавиши.

## Сборка

Используется **CMake** с генератором MinGW Makefiles.

### Требования

- Qt6 (динамическая сборка)
- CMake ≥ 3.25

### Пример сборки
Рекомендуется использовать расширения Qt C++ Extension Pack, так как оно самостоятельно настраивает переменные окружения нужные для сборки. Для запуска потребуются динамические библиотеки Qt QtCore, QtGui, QtOpenGL, QtOpenGLWidgets, QtWidgets
```bash
# Создать папку для сборки
mkdir build

# Запуск CMake
cmake ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE ^
  -DCMAKE_C_COMPILER:FILEPATH=${path/to/C_COMPILER} ^
  -DCMAKE_CXX_COMPILER:FILEPATH=${path/to/CXX_COMPILER} ^
  -G "MinGW Makefiles" ^
  -S C:/Users/dasha/source/3DEngine ^
  -B C:/Users/dasha/source/3DEngine/build

# Сборка
cmake --build .\build\
