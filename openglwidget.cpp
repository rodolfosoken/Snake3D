#include "openglwidget.h"


OpenGLWidget :: OpenGLWidget ( QWidget * parent ) : QOpenGLWidget (parent )
{
    camera.projectionMatrix.setToIdentity () ;
    camera.projectionMatrix.ortho ( -1 ,1 , -1 ,1 ,0 ,2) ;
    camera.viewMatrix.setToIdentity () ;
    camera.viewMatrix.translate (0 ,0 , -3) ;
    camera.viewMatrix.scale(0.5);

}

void OpenGLWidget :: initializeGL ()
{
    initializeOpenGLFunctions () ;

    qDebug (" OpenGL version : %s", glGetString ( GL_VERSION ) ) ;
    qDebug (" GLSL %s", glGetString ( GL_SHADING_LANGUAGE_VERSION ) ) ;

    glEnable ( GL_DEPTH_TEST ) ;

    connect (& timer , SIGNAL ( timeout () ) , this , SLOT ( animate () ) ) ;
    timer . start (0) ;

    speed = 0;

    if(!models.size()){
        head = std::make_shared <SnakeHead>(this);
        models.push_back(head);
//        std::shared_ptr <SnakeHead> head2 = std::make_shared <SnakeHead>(this);
//        head2->escala(2);
//        models.push_back(head2);

        plano = std::make_shared <Plano>(this);
        plano->escala(15);
        models.push_back(plano);
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
            head->transladarModel(-speed,0);
            break;
        case right:
            head->transladarModel(speed,0);
            break;
        case up:
            head->transladarModel(0,speed);
            break;
        case down:
           head->transladarModel(0,-speed);
            break;
        }

}

void OpenGLWidget::keyPressEvent( QKeyEvent * event){
    speed = 0.1;
    switch (event->key()) {
        case Qt::Key_Left :
            direcao=left;
            break;
        case Qt::Key_Right:
            direcao=right;
            break;
        case Qt::Key_Up:
           direcao=up;
            break;
        case Qt::Key_Down:
            direcao=down;
            break;
        }
}




void OpenGLWidget :: animate ()
{

    update () ;
}


