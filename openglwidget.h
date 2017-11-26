#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "snakehead.h"
#include "light.h"
#include "camera.h"

class OpenGLWidget : public QOpenGLWidget , protected
QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    std :: shared_ptr < SnakeHead > model = nullptr ;
    Light light ;
    Camera camera;
    QTimer timer ;


protected:
    void initializeGL () ;
    void resizeGL ( int width , int height ) ;
    void paintGL () ;

signals:

public slots:
    void animate () ;



};

#endif // OPENGLWIDGET_H
