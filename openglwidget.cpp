#include "openglwidget.h"


OpenGLWidget :: OpenGLWidget ( QWidget * parent ) : QOpenGLWidget (parent )
{
//    camera.projectionMatrix.setToIdentity () ;
//    camera.projectionMatrix.ortho ( -1 ,1 , -1 ,1 ,0 ,2) ;
//    camera.viewMatrix.setToIdentity () ;
//    camera.viewMatrix.translate (0 ,0 , -1) ;

}

void OpenGLWidget :: initializeGL ()
{
    initializeOpenGLFunctions () ;

    qDebug (" OpenGL version : %s", glGetString ( GL_VERSION ) ) ;
    qDebug (" GLSL %s", glGetString ( GL_SHADING_LANGUAGE_VERSION ) ) ;

    glEnable ( GL_DEPTH_TEST ) ;

    connect (& timer , SIGNAL ( timeout () ) , this , SLOT ( animate () ) ) ;
    timer . start (0) ;



    if(!models.size()){
        head = std::make_shared <SnakeHead>(this);

        head -> trackBall . resizeViewport ( width () , height () ) ;

        models.push_back(head);
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
        model ->transladarModel(0.01,0.01);
        model -> drawModel(light,camera) ;

    }

}

void OpenGLWidget :: mouseMoveEvent ( QMouseEvent * event )
{
    mouseEventHandler(event,1);
}
void OpenGLWidget :: mousePressEvent ( QMouseEvent * event )
{
    mouseEventHandler(event,2);
}
void OpenGLWidget :: mouseReleaseEvent ( QMouseEvent * event )
{
    mouseEventHandler(event,3);
}


void OpenGLWidget::mouseEventHandler(QMouseEvent * event, int num){

    foreach (std::shared_ptr <Model> model, models) {
        if (!model ) return ;
        else{
            model -> trackBall . mouseMove ( event -> localPos () ) ;
            if ( event -> button () & Qt :: LeftButton  && num==2)
                model -> trackBall . mousePress ( event -> localPos () ) ;
            else if ( event -> button () & Qt :: LeftButton && num ==3)
                model -> trackBall . mouseRelease ( event -> localPos () ) ;
        }
    }
}


void OpenGLWidget :: animate ()
{
    update () ;
}


