#ifndef MODEL_H
#define MODEL_H

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

class Model : public QOpenGLExtraFunctions
{
public :
    Model ( QOpenGLWidget * _glWidget ) ;
    ~Model () ;
    std :: unique_ptr < QVector4D [] > vertices ;
    std :: unique_ptr < unsigned int [] > indices ;
    QOpenGLWidget * glWidget ;
    unsigned int numVertices ;
    unsigned int numFaces ;
    GLuint vao = 0;
    GLuint vboVertices = 0;
    GLuint vboIndices = 0;

    Material material ;
    GLuint vboNormals = 0;
    std :: unique_ptr < QVector3D [] > normals ;
    int shaderIndex ;
    int numShaders ;
    std ::vector<GLuint>shaderProgram;
    void createNormals () ;

    void createVBOs () ;
    void createShaders () ;
    void destroyVBOs () ;
    void destroyShaders () ;
    void drawModel () ;
    void readOFFFile ( const QString & fileName ) ;
    QMatrix4x4 modelMatrix ;
    QVector3D midPoint ;
    double invDiag ;

    std :: unique_ptr < QVector2D [] > texCoords ;
    void createTexCoords () ;
    GLuint vboTexCoords = 0;
    GLuint textureID = 0;
    void loadTexture ( const QImage & image ) ;


};

#endif // MODEL_H
