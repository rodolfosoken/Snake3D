#include "snakebody.h"

SnakeBody::SnakeBody( QOpenGLWidget * _glWidget):Model(_glWidget)
{
    this->readOFFFile("off_models/sphere.off");
    this->loadTexture(":/textures/snake-texture.jpg");
}
