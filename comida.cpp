#include "comida.h"

Comida::Comida( QOpenGLWidget * _glWidget ):Model(_glWidget)
{
    this->readOFFFile("off_models/sphere.off");
    this->loadTexture(":/textures/maca.png");
}

void Comida::posiciona(){
}
