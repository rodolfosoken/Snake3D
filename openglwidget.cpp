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

    //cria a cabeca da cobra
    head = std::make_shared <SnakeHead>(this);
    models.push_back(head);
    head->escala(0.5);


    //cria o terreno
    plano = std::make_shared <Plano>(this);
    plano->posZ = -0.03;
    plano->escala(15);
    models.push_back(plano);



    std::shared_ptr<SnakeBody> body = std::make_shared<SnakeBody>(this);
    body->posX-=2;
    head->cresce(body);
    models.push_back(body);






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

    head->anda();

    //desenha todos os objetos
    foreach (std::shared_ptr <Model> model, models) {
        if (! model )
            return ;
        model -> drawModel(light,camera) ;

    }
}

void OpenGLWidget::keyPressEvent( QKeyEvent * event){
    head->mudaDirecao(event);
}


void OpenGLWidget :: animate ()
{

    update () ;
}


