#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "model.h"
#include "light.h"
#include "camera.h"
#include "snakehead.h"

class OpenGLWidget : public QOpenGLWidget , protected
QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    std :: list <std::shared_ptr < Model >> models;
    std :: shared_ptr<SnakeHead> head = nullptr;
    Light light ;
    Camera camera;
    QTimer timer ;
    void mouseMoveEvent ( QMouseEvent * event ) ;
    void mousePressEvent ( QMouseEvent * event ) ;
    void mouseReleaseEvent ( QMouseEvent * event ) ;
    void mouseEventHandler ( QMouseEvent * event ,int num) ;


protected:
    void initializeGL () ;
    void resizeGL ( int width , int height ) ;
    void paintGL () ;

signals:

public slots:
    void animate () ;



};

#endif // OPENGLWIDGET_H
