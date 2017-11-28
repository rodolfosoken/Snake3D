#include "openglwidget.h"


OpenGLWidget :: OpenGLWidget ( QWidget * parent ) : QOpenGLWidget (parent )
{
    camera.projectionMatrix.setToIdentity () ;
    camera.projectionMatrix.ortho ( -1 ,1 , -1 ,1 ,0 ,2) ;
    camera.viewMatrix.setToIdentity () ;
    camera.viewMatrix.translate (0 ,0 , -5) ;
    //camera.viewMatrix.rotate(-90,1,0,0);
    camera.viewMatrix.scale(0.5);

}

void OpenGLWidget :: initializeGL ()
{
    initializeOpenGLFunctions () ;

    qDebug (" OpenGL version : %s", glGetString ( GL_VERSION ) ) ;
    qDebug (" GLSL %s", glGetString ( GL_SHADING_LANGUAGE_VERSION ) ) ;

    glEnable ( GL_DEPTH_TEST ) ;

    connect (& timer , SIGNAL ( timeout () ) , this , SLOT ( animate () ) ) ;
    timer . start (60) ;

    //inicia parado
    speed = 0;

    //cria a cabeca da cobra
    head = std::make_shared <SnakeHead>(this);
    models.push_back(head);
    head->escala(0.5);

    //posicao anterior da cabeca
    posAntX= head->posX + speed;
    posAntY= head->posY;

    //cria o terreno
    plano = std::make_shared <Plano>(this);
    plano->posZ = -0.03;
    plano->escala(15);
    models.push_back(plano);


    for (int var = 0; var < 10; ++var) {
        std::shared_ptr<SnakeBody> body = std::make_shared<SnakeBody>(this);
        cresce(body);
        models.push_back(body);
    }





}

void OpenGLWidget :: resizeGL (int width , int height )
{
    glViewport (0 , 0 , width , height ) ;
    camera . resizeViewport ( width , height ) ;
    update () ;

}
void OpenGLWidget :: paintGL ()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;
    foreach (std::shared_ptr <Model> model, models) {
        if (! model )
            return ;
        model -> drawModel(light,camera) ;

    }

    switch (direcao) {
        case left :
            head->transladarModel(-speed,0,0);
            moveCorpo();
            break;
        case right:
            head->transladarModel(speed,0,0);
            moveCorpo();
            break;
        case up:
            head->transladarModel(0,speed,0);
            moveCorpo();
            break;
        case down:
           head->transladarModel(0,-speed,0);
           moveCorpo();
            break;
        }

}

void OpenGLWidget::keyPressEvent( QKeyEvent * event){
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

void OpenGLWidget::moveCorpo(){

    for (size_t i = 0, n = corpos.size()-1; i < n; ++i){
        corpos[i]->posX= corpos[i+1]->posX;
        corpos[i]->posY= corpos[i+1]->posY;
    }

    corpos.last()->posX = posAntX;
    corpos.last()->posY = posAntY;

    posAntX= head->posX;
    posAntY= head->posY;

}

void OpenGLWidget::cresce(std::shared_ptr<SnakeBody> body){
    body->escala(0.5);
    corpos.prepend(body);
}


void OpenGLWidget :: animate ()
{

    update () ;
}


