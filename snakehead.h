#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "model.h"
#include "snakebody.h"

class SnakeHead : public Model
{
public:
    SnakeHead( QOpenGLWidget * _glWidget);
    ~SnakeHead();

    void mudaDirecao(QKeyEvent * event);
    QList <std::shared_ptr<SnakeBody>> corpos;
    void moveCorpo();
    void cresce(std::shared_ptr<SnakeBody> body);

    void anda();

private:
    float posAntX = 0;
    float posAntY = 0;
    float speed = 0;
    enum direcoes {up=0,down=1,right=2,left=3};
    direcoes direcao;


};

#endif // SNAKEHEAD_H
