#include "snakehead.h"

#include "SnakeHead.h"

SnakeHead :: SnakeHead ( QOpenGLWidget * _glWidget):Model(_glWidget)
{
    this->readOFFFile("off_models/sphere.off");
    this->loadTexture(":/textures/smiley.jpg");
    //posicao anterior da cabeca
    posAntX= this->posX + speed;
    posAntY= this->posY;
}
SnakeHead :: ~SnakeHead ()
{
}

void SnakeHead::anda(){
    switch (direcao) {
        case left :
            this->transladarModel(-speed,0,0);
            moveCorpo();
            break;
        case right:
            this->transladarModel(speed,0,0);
            moveCorpo();
            break;
        case up:
            this->transladarModel(0,speed,0);
            moveCorpo();
            break;
        case down:
           this->transladarModel(0,-speed,0);
           moveCorpo();
            break;
        }
}

void SnakeHead::mudaDirecao(QKeyEvent *event){
    //velocidade da cobra
    speed = 2;
    switch (event->key()) {
    case Qt::Key_Left :
        if(direcao != right)
            direcao=left;
        break;
    case Qt::Key_Right:
        if(direcao != left)
            direcao=right;
        break;
    case Qt::Key_Up:
        if(direcao != down)
            direcao=up;
        break;
    case Qt::Key_Down:
        if(direcao!=up)
            direcao=down;
        break;
    }
}

void SnakeHead::cresce(std::shared_ptr<SnakeBody> body){
    body->escala(this->scaleFactor);
    corpos.prepend(body);
    moveCorpo();
}

void SnakeHead::moveCorpo(){

    for (size_t i = 0, n = corpos.size()-1; i < n; ++i){
        corpos[i]->posX= corpos[i+1]->posX;
        corpos[i]->posY= corpos[i+1]->posY;
    }

    corpos.last()->posX = posAntX;
    corpos.last()->posY = posAntY;

    posAntX= this->posX;
    posAntY= this->posY;

}




