#ifndef COMIDA_H
#define COMIDA_H

#include "model.h"

class Comida : public Model
{
public:
    Comida(QOpenGLWidget * _glWidget);
    void posiciona();
};

#endif // COMIDA_H