#include "plano.h"

Plano::Plano( QOpenGLWidget * _glWidget ):Model(_glWidget)
{
    this->readOFFFile("off_models/plano.off");
    this->loadTexture(":/textures/floor.jpg");
}
