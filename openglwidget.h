#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "model.h"
#include "light.h"
#include "camera.h"
#include "snakehead.h"
#include"plano.h"

class OpenGLWidget : public QOpenGLWidget , protected
QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    Light light ;
    Camera camera;
    QTimer timer ;


    std :: list <std::shared_ptr < Model >> models;
    std :: shared_ptr<SnakeHead> head = nullptr;
    std :: shared_ptr<Plano> plano = nullptr;
    enum direcoes {up=0,down=1,right=2,left=3};
    direcoes direcao;
    float speed;



protected:
    void initializeGL () ;
    void resizeGL ( int width , int height ) ;
    void paintGL () ;

signals:

public slots:
    void animate () ;
    void keyPressEvent( QKeyEvent * event);



};

#endif // OPENGLWIDGET_H
