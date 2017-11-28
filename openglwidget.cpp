#include "openglwidget.h"


OpenGLWidget :: OpenGLWidget ( QWidget * parent ) : QOpenGLWidget (parent )
{
    camera.projectionMatrix.setToIdentity () ;
    camera.projectionMatrix.ortho ( -1 ,1 , -1 ,1 ,0 ,2) ;
    camera.viewMatrix.setToIdentity () ;
    camera.viewMatrix.translate (0.7 ,0 , -10) ;
    camera.viewMatrix.rotate(-50,1,0.3,1);
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
    //head->escala(0.5);
    models.push_back(head);

    //cria corpo
    std::shared_ptr<SnakeBody> body = std::make_shared<SnakeBody>(this);
    body->posX-=2;
    head->cresce(body);
    models.push_back(body);

    //cria o terreno
    plano = std::make_shared <Plano>(this);
    plano->transladarModel(-0.05,-0.05,0);
    plano->posZ = -0.09;
    plano->escala(25);
    models.push_back(plano);

    //cria paredes
    criaCenario();

    comida = std::make_shared<Comida>(this);
    comida->posX=10;
    models.push_back(comida);



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

//    qDebug("X:%f ",head->posX);
//    qDebug("Y:%f ",head->posY);

    foreach (std::shared_ptr<Bloco> bloco, paredes) {
        if(std::abs((bloco->posX)-(head->posX/4))<= 1 && std::abs((bloco->posY)-head->posY/4)<= 1){
            head->speed=0;


        }
    }


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


void OpenGLWidget::criaCenario(){
    int size = 10;
    int maze[size][size]={
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };

    for (int i = 0; i < size ; ++i) {
        for (int j = 0; j < size; ++j) {
            if(maze[i][j]){
                 std::shared_ptr<Bloco> bloco = std::make_shared<Bloco>(this);
                 bloco->escala(2);
                 bloco->posX = i*1.5-7;
                 bloco->posY = j*1.5-7;
                 bloco->posZ = 0;
                 models.push_back(bloco);
                 paredes.push_back(bloco);
            }
        }

    }
}

