#include "openglwidget.h"


OpenGLWidget :: OpenGLWidget ( QWidget * parent ) : QOpenGLWidget (parent )
{
    camera.projectionMatrix.setToIdentity () ;
    camera.projectionMatrix.ortho ( -1 ,1 , -1 ,1 ,0 ,2) ;
    camera.viewMatrix.setToIdentity () ;
    camera.viewMatrix.translate (0.7 ,1 , -10) ;
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
    head->posX=-4;
    //head->escala(0.5);
    models.push_back(head);

    //cria corpo
    std::shared_ptr<SnakeBody> body = std::make_shared<SnakeBody>(this);
    body->posX-=6;
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

    geraComida();

    //colisao com o corpo
    foreach (std::shared_ptr<SnakeBody> corpo, head->corpos) {
        if(std::abs((corpo->posX)-(head->posX))< 1 && std::abs((corpo->posY)-head->posY)< 1){
            head->speed=0;
            //game over
        }
    }


    //colisao com a parede
    foreach (std::shared_ptr<Bloco> bloco, paredes) {
        if(std::abs((bloco->posX)-(head->posX/4.2))<= 1 && std::abs((bloco->posY)-head->posY/4.2)<= 1){
            head->speed=0;
            //game over
        }
    }

    //colisao com a comida
    if(comida){
        comida->drawModel(light,camera);

        if(std::abs((comida->posX)-(head->posX))<= 1 && std::abs((comida->posY)-head->posY)<= 1){
            //cria corpo
            std::shared_ptr<SnakeBody> body = std::make_shared<SnakeBody>(this);
            head->cresce(body);
            models.push_back(body);

            //destroi comida
            comida->~Model();
            comida=nullptr;
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

void OpenGLWidget::geraComida(){
        if (!comida){
            comida = std::make_shared<Comida>(this);
            comida->posX=std::rand()%30-20;
            comida->posY=std::rand()%30-20;

     }
}

