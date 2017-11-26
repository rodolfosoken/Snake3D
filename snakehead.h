#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <limits>
#include <iostream>
#include <memory>
#include "material.h"

class SnakeHead : public QOpenGLExtraFunctions
{
public:
    SnakeHead( QOpenGLWidget * _glWidget );
    ~SnakeHead();

    std :: unique_ptr < QVector4D [] > vertices ;
    std :: unique_ptr < QVector3D [] > normals ;
    std :: unique_ptr < unsigned int [] > indices ;
    std :: unique_ptr < QVector2D [] > texCoords ;

    QOpenGLWidget * glWidget ;

    unsigned int numVertices ;
    unsigned int numFaces ;

    void createVBOs () ;
    void createShaders () ;
    void createTexCoords () ;
    void createNormals () ;

    GLuint vao = 0;

    GLuint vboVertices = 0;
    GLuint vboIndices = 0;
    GLuint vboNormals = 0;
    GLuint vboTexCoords = 0;
    GLuint textureID = 0;

    Material material ;

    void destroyVBOs () ;
    void destroyShaders () ;
    void readOFFFile ( const QString & fileName ) ;
    void loadTexture ( const  QString &fileName ) ;

    void drawModel () ;

    QMatrix4x4 modelMatrix ;
    QVector3D midPoint ;
    double invDiag ;

    GLuint shaderProgram;



};

#endif // SNAKEHEAD_H
