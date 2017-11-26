#include "openglwidget.h"

OpenGLWidget :: OpenGLWidget ( QWidget * parent ) : QOpenGLWidget (parent )
{
    camera.projectionMatrix.setToIdentity () ;
    camera.projectionMatrix.ortho ( -1 ,1 , -1 ,1 ,0 ,2) ;
    camera.viewMatrix.setToIdentity () ;
    camera.viewMatrix.translate (0 ,0 , -1) ;

}

void OpenGLWidget :: initializeGL ()
{
    initializeOpenGLFunctions () ;

    qDebug (" OpenGL version : %s", glGetString ( GL_VERSION ) ) ;
    qDebug (" GLSL %s", glGetString ( GL_SHADING_LANGUAGE_VERSION ) ) ;

    glEnable ( GL_DEPTH_TEST ) ;

    connect (& timer , SIGNAL ( timeout () ) , this , SLOT ( animate () ) ) ;
    timer . start (0) ;

    if(!model){
        model = std::make_shared <SnakeHead>(this);
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
    if (! model )
    return ;
    int shaderProgramID = model -> shaderProgram ;
    QVector4D ambientProduct = light.ambient * model -> material.ambient ;
    QVector4D diffuseProduct = light.diffuse * model -> material.diffuse ;
    QVector4D specularProduct = light.specular * model -> material.specular ;
    GLuint locProjection = glGetUniformLocation ( shaderProgramID , "projection") ;
    GLuint locView = glGetUniformLocation ( shaderProgramID , "view") ;
    GLuint locLightPosition = glGetUniformLocation ( shaderProgramID , "lightPosition") ;
    GLuint locAmbientProduct = glGetUniformLocation ( shaderProgramID ,"ambientProduct") ;
    GLuint locDiffuseProduct = glGetUniformLocation ( shaderProgramID , "diffuseProduct") ;
    GLuint locSpecularProduct = glGetUniformLocation ( shaderProgramID , "specularProduct" ) ;
    GLuint locShininess = glGetUniformLocation ( shaderProgramID , "shininess") ;
    glUseProgram ( shaderProgramID ) ;

    glUniformMatrix4fv ( locProjection , 1 , GL_FALSE , camera.projectionMatrix . data () ) ;
    glUniformMatrix4fv ( locView , 1 , GL_FALSE , camera.viewMatrix . data () ) ;
    glUniform4fv ( locLightPosition , 1 , &( light . position [0]) ) ;
    glUniform4fv ( locAmbientProduct , 1 , &( ambientProduct [0]) ) ;
    glUniform4fv ( locDiffuseProduct , 1 , &( diffuseProduct [0]) ) ;
    glUniform4fv ( locSpecularProduct , 1 , &( specularProduct [0]) ) ;
    glUniform1f ( locShininess , model -> material.shininess ) ;
    model ->drawModel();


}



void OpenGLWidget :: animate ()
{
    update () ;
}


