#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "model.h"
#include "light.h"
#include "camera.h"
#include "snakehead.h"
#include "plano.h"
#include "bloco.h"
#include "comida.h"

class OpenGLWidget : public QOpenGLWidget , protected
QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    Light light ;
    Camera camera;
    QTimer timer ;
    int pontos;
    bool isOver=false;

    std :: list <std::shared_ptr < Model >> models;
    std :: list <std::shared_ptr < Bloco >> paredes;
    std :: shared_ptr<Comida> comida = nullptr;
    std :: shared_ptr<SnakeHead> head = nullptr;
    std :: shared_ptr<Plano> plano = nullptr;

    void criaCenario();
    void geraComida();
    void clear();

protected:
    void initializeGL () ;
    void resizeGL ( int width , int height ) ;
    void paintGL () ;

signals:
    void aumentaPontos(int pontos);

public slots:
    void animate () ;
    void keyPressEvent( QKeyEvent * event);



};

#endif // OPENGLWIDGET_H
