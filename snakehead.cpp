#include "snakehead.h"

#include "SnakeHead.h"

SnakeHead :: SnakeHead ( QOpenGLWidget * _glWidget ):Model(_glWidget)
{
    this->readOFFFile("off_models/sphere.off");
    this->loadTexture(":/textures/snake-texture.jpg");
}
SnakeHead :: ~SnakeHead ()
{
}

