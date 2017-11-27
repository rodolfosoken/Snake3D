#include "bloco.h"

Bloco::Bloco( QOpenGLWidget * _glWidget ):Model(_glWidget)
{
    this->readOFFFile("off_models/cube.off");
    this->loadTexture(":/textures/snake-texture.jpg");
}
