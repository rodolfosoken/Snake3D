#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <limits>
#include <iostream>
#include <memory>
#include "material.h"
#include "model.h"

class SnakeHead : public Model
{
public:
    SnakeHead( QOpenGLWidget * _glWidget );
    ~SnakeHead();

};

#endif // SNAKEHEAD_H
