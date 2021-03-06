#include "model.h"

 Model :: Model( QOpenGLWidget * _glWidget )
{
    glWidget = _glWidget ;
    glWidget -> makeCurrent () ;
    initializeOpenGLFunctions () ;

}
 Model :: ~ Model ()
{
    destroyVBOs () ;
    destroyShaders () ;
}

void Model:: destroyVBOs ()
{
    glDeleteBuffers (1 , & vboVertices ) ;
    glDeleteBuffers (1 , & vboIndices ) ;
    glDeleteBuffers (1 , & vboNormals ) ;
    glDeleteBuffers (1 , & vboTexCoords ) ;
    glDeleteVertexArrays (1 , & vao ) ;
    vboTexCoords = 0;
    vboVertices = 0;
    vboIndices = 0;
    vboNormals = 0;
    vao = 0;

}

void Model:: destroyShaders ()
{

    glDeleteProgram ( shaderProgram ) ;

    shaderProgram=0 ;
}

void Model:: createVBOs ()
{
    glWidget -> makeCurrent () ;

    destroyVBOs () ;

    glGenVertexArrays (1 , & vao ) ;
    glBindVertexArray ( vao ) ;

    glGenBuffers (1 , & vboVertices ) ;
    glBindBuffer ( GL_ARRAY_BUFFER , vboVertices ) ;
    glBufferData ( GL_ARRAY_BUFFER , numVertices * sizeof ( QVector4D ), vertices . get () , GL_STATIC_DRAW ) ;
    glVertexAttribPointer (0 , 4 , GL_FLOAT , GL_FALSE , 0 , nullptr ) ;
    glEnableVertexAttribArray (0) ;
    vertices.reset();

    glGenBuffers (1 , & vboNormals ) ;
    glBindBuffer ( GL_ARRAY_BUFFER , vboNormals ) ;
    glBufferData ( GL_ARRAY_BUFFER , numVertices * sizeof ( QVector3D )
    , normals . get () , GL_STATIC_DRAW ) ;
    glVertexAttribPointer (1 , 3 , GL_FLOAT , GL_FALSE , 0 , nullptr ) ;
    glEnableVertexAttribArray (1) ;
    normals.reset();

    glGenBuffers (1 , & vboTexCoords ) ;
    glBindBuffer ( GL_ARRAY_BUFFER , vboTexCoords ) ;
    glBufferData ( GL_ARRAY_BUFFER , numVertices*sizeof(QVector2D),texCoords.get(),GL_STATIC_DRAW ) ;
    glBindBuffer ( GL_ARRAY_BUFFER , vboTexCoords ) ;
    glVertexAttribPointer (2 , 2 , GL_FLOAT , GL_FALSE , 0 , nullptr ) ;
    glEnableVertexAttribArray (2) ;
    texCoords.reset();

    glGenBuffers (1 , & vboIndices ) ;
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , vboIndices ) ;
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER , numFaces * 3 * sizeof (unsigned int ) , indices . get () , GL_STATIC_DRAW ) ;
    indices.reset();


}

void Model:: drawModel (Light &light, Camera &camera)
{

    int shaderProgramID = this->shaderProgram ;
    QVector4D ambientProduct = light.ambient *this-> material.ambient ;
    QVector4D diffuseProduct = light.diffuse *this-> material.diffuse ;
    QVector4D specularProduct = light.specular *this-> material.specular ;
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
    glUniform1f ( locShininess ,this-> material.shininess ) ;

    //================Draw Model =================
    modelMatrix . setToIdentity () ;
//    modelMatrix . rotate ( trackBall . getRotation () ) ;
    modelMatrix . scale ( invDiag *scaleFactor , invDiag*scaleFactor , invDiag*scaleFactor ) ;
    modelMatrix . translate ( this->posX,this->posY,this->posZ ) ;
    GLuint locModel = 0;
    GLuint locNormalMatrix = 0;
    //GLuint locShininess = 0;
    locModel = glGetUniformLocation ( shaderProgram , "model") ;
    locNormalMatrix = glGetUniformLocation ( shaderProgram , "normalMatrix") ;
    locShininess = glGetUniformLocation ( shaderProgram, "shininess") ;

    glBindVertexArray ( vao ) ;
    glUseProgram ( shaderProgram) ;
    glUniformMatrix4fv ( locModel , 1 , GL_FALSE , modelMatrix.data());
    glUniformMatrix3fv ( locNormalMatrix , 1 , GL_FALSE ,modelMatrix .
                         normalMatrix () . data () ) ;
    glUniform1f ( locShininess , static_cast < GLfloat >( material.shininess ) ) ;

    if ( textureID )
    {
        GLuint locColorTexture = 0;
        locColorTexture = glGetUniformLocation ( shaderProgram , "colorTexture") ;
        glUniform1i ( locColorTexture , 0) ;
        glActiveTexture ( GL_TEXTURE0 ) ;
        glBindTexture ( GL_TEXTURE_2D , textureID ) ;
    }

    glDrawElements ( GL_TRIANGLES , numFaces * 3 , GL_UNSIGNED_INT ,  0) ;

}

void Model:: readOFFFile ( QString const & fileName )
{

    std::ifstream stream;
    stream.open(fileName.toUtf8(),std::ifstream::in);
    if (!stream.is_open())
    {
        qWarning("Cannot open file.");
        return;
    }

    std::string line;
    stream >> line;
    stream >> numVertices >> numFaces >> line;

    // http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
    vertices = std::make_unique<QVector4D[]>(numVertices);
    indices = std::make_unique<unsigned int[]>(numFaces * 3);

    if (numVertices > 0)
    {
        float minLim = std::numeric_limits<float>::lowest();
        float maxLim = std::numeric_limits<float>::max();
        QVector4D max(minLim, minLim, minLim, 1.0);
        QVector4D min(maxLim, maxLim, maxLim, 1.0);
        for (unsigned int i = 0; i < numVertices; ++i)
        {
            float x, y, z;
            stream >> x >> y >> z;
            max.setX(std::max(max.x(), x));
            max.setY(std::max(max.y(), y));
            max.setZ(std::max(max.z(), z));
            min.setX(std::min(min.x(), x));
            min.setY(std::min(min.y(), y));
            min.setZ(std::min(min.z(), z));
            vertices[i] = QVector4D(x, y, z, 1.0);
        }

        midPoint = QVector3D((min + max) * 0.5);
        invDiag = 1 / (max - min).length();
    }

    for (unsigned int i = 0; i < numFaces; ++i)
    {
        unsigned int a, b, c;
        stream >> line >> a >> b >> c;
        indices[i * 3 + 0] = a;
        indices[i * 3 + 1] = b;
        indices[i * 3 + 2] = c;
    }
    stream.close();

    createNormals();
    createTexCoords();
    createShaders();
    createVBOs();
}

void Model:: createNormals ()
{
    normals = std :: make_unique < QVector3D [] >( numVertices ) ;
    for ( unsigned int i = 0; i < numFaces ; ++ i )
    {
        QVector3D a = QVector3D ( vertices [ indices [ i * 3 + 0]]) ;
        QVector3D b = QVector3D ( vertices [ indices [ i * 3 + 1]]) ;
        QVector3D c = QVector3D ( vertices [ indices [ i * 3 + 2]]) ;
        QVector3D faceNormal = QVector3D :: crossProduct (( b - a ) , (c - b ) ) ;//I am not normalizing ( weighted average )
        // Accumulates face normals on the vertices
        normals [ indices [ i * 3 + 0]] += faceNormal ;
        normals [ indices [ i * 3 + 1]] += faceNormal ;
        normals [ indices [ i * 3 + 2]] += faceNormal ;
    }
    for ( unsigned int i = 0; i < numVertices ; ++ i )
    {
        normals [ i ]. normalize () ;
    }
}

void Model::createTexCoords()
{
    texCoords = std::make_unique<QVector2D[]>(numVertices);

    // Compute minimum and maximum values
    auto minz = std::numeric_limits<float>::max();
    auto maxz = std::numeric_limits<float>::lowest();

    for (unsigned int i = 0; i < numVertices; ++i)
    {
        minz = std::min(vertices[i].z(), minz);
        maxz = std::max(vertices[i].z(), maxz);
    }

    for (unsigned int i = 0; i < numVertices; ++i)
    {
        auto s = (std::atan2(vertices[i].y(), vertices[i].x()) + M_PI) / (2 * M_PI);
        auto t = 1.0f - (vertices[i].z() - minz) / (maxz - minz);
        texCoords[i] = QVector2D(s, t);
    }
}

void Model::loadTexture(const  QString &fileName)
{
    if (textureID)
    {
        (glDeleteTextures(1, &textureID));
    }
    QImage image ;
    image . load ( fileName ) ;
    image = image . convertToFormat ( QImage :: Format_RGBA8888 ) ;

    (glGenTextures(1, &textureID));
    (glBindTexture(GL_TEXTURE_2D, textureID));
    (glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits()));

    (glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    (glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    (glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    (glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    (glGenerateMipmap(GL_TEXTURE_2D));
}

void Model:: createShaders ()
{
    QString vertexShaderFile = ":/shaders/vtexture.glsl";
    QString fragmentShaderFile = ":/shaders/ftexture.glsl";

    destroyShaders () ;
    shaderProgram = 0;

    QFile vs ( vertexShaderFile) ;
    QFile fs ( fragmentShaderFile) ;
    vs . open ( QFile :: ReadOnly | QFile :: Text ) ;
    fs . open ( QFile :: ReadOnly | QFile :: Text ) ;
    QTextStream streamVs (& vs ) , streamFs (& fs ) ;
    QString qtStringVs = streamVs . readAll () ;
    QString qtStringFs = streamFs . readAll () ;
    std :: string stdStringVs = qtStringVs . toStdString () ;
    std :: string stdStringFs = qtStringFs . toStdString () ;
    GLuint vertexShader = 0;
    vertexShader = glCreateShader ( GL_VERTEX_SHADER ) ;
    // Send the vertex shader source code to GL
    const GLchar * source = stdStringVs . c_str () ;
    glShaderSource ( vertexShader , 1 , & source , 0) ;
    // Compile the vertex shader
    glCompileShader ( vertexShader ) ;
    GLint isCompiled = 0;
    glGetShaderiv ( vertexShader , GL_COMPILE_STATUS , & isCompiled ) ;
    if ( isCompiled == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetShaderiv ( vertexShader , GL_INFO_LOG_LENGTH , &
                        maxLength ) ;
        // The maxLength includes the NULL character
        std :: vector < GLchar > infoLog ( maxLength ) ;
        glGetShaderInfoLog ( vertexShader , maxLength , & maxLength , &
                             infoLog [0]) ;
        qDebug ("%s", & infoLog [0]) ;
        glDeleteShader ( vertexShader ) ;
        return ;
    }
    GLuint fragmentShader = 0;
    fragmentShader = glCreateShader ( GL_FRAGMENT_SHADER ) ;
    // Send the fragment shader source code to GL
    // Note that std :: string ’s . c_str is NULL character terminated .
    source = stdStringFs . c_str () ;//( const GLchar *) stringFs .toStdString (). c_str ();
    glShaderSource ( fragmentShader , 1 , & source , 0) ;
    // Compile the fragment shader
    glCompileShader ( fragmentShader ) ;
    glGetShaderiv ( fragmentShader , GL_COMPILE_STATUS , & isCompiled ) ;
    if ( isCompiled == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetShaderiv ( fragmentShader , GL_INFO_LOG_LENGTH , &
                        maxLength ) ;
        std :: vector < GLchar > infoLog ( maxLength ) ;
        glGetShaderInfoLog ( fragmentShader , maxLength , & maxLength ,
                             & infoLog [0]) ;
        qDebug ("%s", & infoLog [0]) ;
        glDeleteShader ( fragmentShader ) ;
        glDeleteShader ( vertexShader ) ;
        return ;
    }

    GLuint shaderProgramID = 0;
    shaderProgramID = glCreateProgram () ;
    shaderProgram = shaderProgramID;
    // Attach our shaders to our program
    glAttachShader ( shaderProgramID , vertexShader ) ;
    glAttachShader ( shaderProgramID , fragmentShader ) ;
    // Link our program
    glLinkProgram ( shaderProgramID ) ;
    // Note the different functions here : glGetProgram * instead of glGetShader *.
    GLint isLinked = 0;
    glGetProgramiv ( shaderProgramID , GL_LINK_STATUS , ( int *) & isLinked )   ;
    if ( isLinked == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetProgramiv ( shaderProgramID , GL_INFO_LOG_LENGTH , &
                         maxLength ) ;
        // The maxLength includes the NULL character
        std :: vector < GLchar > infoLog ( maxLength ) ;
        glGetProgramInfoLog ( shaderProgramID , maxLength , & maxLength , &
                              infoLog [0]) ;
        qDebug ("%s", & infoLog [0]) ;
        glDeleteProgram ( shaderProgramID ) ;
        glDeleteShader ( vertexShader ) ;
        glDeleteShader ( fragmentShader ) ;
        return ;
    }

    glDetachShader ( shaderProgramID , vertexShader ) ;
    glDetachShader ( shaderProgramID , fragmentShader ) ;
    glDeleteShader ( vertexShader ) ;
    glDeleteShader ( fragmentShader ) ;
    vs . close () ;
    fs . close () ;

}

void Model::escala(float factor){
    this->scaleFactor = factor;
}

void Model::transladarModel(float dx,float dy,float dz){

    //qDebug("posX: %f",this->posX);
    modelMatrix . setToIdentity () ;
    if(isFlipedY)
        modelMatrix.translate(-dx,dy,dz);
    else
        modelMatrix.translate(dx,dy,dz);
    posX += dx;
    posY += dy;
}

