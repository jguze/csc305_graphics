#include "openglwidget.h"
#include <QDebug>

static const double DegPerPixel = - 1;
static const double ScalePerPixel = - 0.1;

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    cameraManager.cameraPos.setX(-180);
    cameraManager.cameraPos.setY(75);
    cameraManager.cameraPos.setZ(0);

    cameraManager.viewTo.setX(0);
    cameraManager.viewTo.setY(0);
    cameraManager.viewTo.setZ(0);

    cameraManager.focalLength = 1500;
    cameraManager.depthPasses = 1;

    backgroundColour = QVector3D(0.0, 0.0, 0.0);

    isScaling = isRotating = false;
    isDepthOfField = false;

    imageViewer = NULL;
    shadeModel = new LambertianShadeModel();

    sampleSize = 1;
    sampleSize2 = 1;
    std::srand(time(NULL));
    randomNumbers.push_back((double)std::rand() / RAND_MAX);
    initializeScene();
    initializeLights();
}

void OpenGLWidget::printMatrix(QMatrix4x4 m)
{
    for (int i = 0; i < 4; i++)
    {
       qDebug() << m.row(i).x() << m.row(i).y() << m.row(i).z() << m.row(i).w();
    }
}

void OpenGLWidget::initializeScene()
{
    root = new SceneGraphNode();
    SceneGraphNode * sphereNode = new SceneGraphNode();
    sphereNode->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::SPHERE), materialFactory.getMaterialProperties(MaterialFactory::GREEN));
    sphereNode->localTransform.scale(5);
    sphereNode->localTransform.translate(0,0.5,0);
    root->addChild(sphereNode);

    SceneGraphNode * floor = new SceneGraphNode();
    floor->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::CUBE), materialFactory.getMaterialProperties(MaterialFactory::CHROME));
    floor->localTransform.scale(200, 1, 200);
    floor->localTransform.translate(0, -5, 0);
    root->addChild(floor);

    SceneGraphNode * leftWall = new SceneGraphNode();
    leftWall->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::CUBE), materialFactory.getMaterialProperties(MaterialFactory::RUBY));
    leftWall->localTransform.scale(200, 70, 1);
    leftWall->localTransform.translate(0, 0.871, -40);
    root->addChild(leftWall);

    SceneGraphNode * rightWall = new SceneGraphNode();
    rightWall->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::CUBE), materialFactory.getMaterialProperties(MaterialFactory::JADE));
    rightWall->localTransform.scale(200,70,1);
    rightWall->localTransform.translate(0, 0.871,40);
    root->addChild(rightWall);

    SceneGraphNode * backWall = new SceneGraphNode();
    backWall->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::CUBE), materialFactory.getMaterialProperties(MaterialFactory::BRONZE));
    backWall->localTransform.scale(1, 70, 260);
    backWall->localTransform.translate(40, 0.873, 0);
    root->addChild(backWall);

//    SceneGraphNode * frontWall = new SceneGraphNode();
//    frontWall->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::CUBE), materialFactory.getMaterialProperties(MaterialFactory::RUBY));
//    frontWall->localTransform.scale(1, 70, 260);
//    frontWall->localTransform.translate(-40, 0.873, 0);
//    root->addChild(frontWall);

    sphereNode = new SceneGraphNode();
    sphereNode->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::SPHERE), new SceneObjectProperties(QVector3D(0.5, 0, 0.5), 150, QVector3D(0.1, 0.1, 0.1), QVector3D(0.4, 0.4, 0.4), 0));
    sphereNode->localTransform.scale(10);
    sphereNode->localTransform.translate(2,1,-2);
    root->addChild(sphereNode);

    sphereNode = new SceneGraphNode();
    sphereNode->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::SPHERE), materialFactory.getMaterialProperties(MaterialFactory::MIRROR));
    sphereNode->localTransform.scale(6);
    sphereNode->localTransform.translate(-3, 0.5, 3);
    root->addChild(sphereNode);

//    SceneGraphNode * cube = new SceneGraphNode;
//    cube->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::CUBE), materialFactory.getMaterialProperties(MaterialFactory::EMERALD));
//    cube->localTransform.scale(4);
//    cube->localTransform.translate(5, 0.5, 5);
//    root->addChild(cube);

//    printMatrix(sphereNode->localTransform);
//    printMatrix(sphereNode->localTransform.inverted());
//    printMatrix(sphereNode->localTransform.transposed());

//    sphereNode = new SceneGraphNode();
//    sphereNode->setSceneObject(primitiveFactory.getSceneObject(PrimitiveFactory::SPHERE), materialFactory.getMaterialProperties(MaterialFactory::MIRROR));
//    sphereNode->localTransform.scale(6);
//    sphereNode->localTransform.translate(-3,2,2);
//    root->addChild(sphereNode);
}

void OpenGLWidget::initializeLights()
{
    lightManager.addLight(LightSource(QVector3D(15,25,15), 0.7, 0.2, &primitiveFactory));
    lightManager.addLight(LightSource(QVector3D(-30, 15, -11), 0.6, 0.1, &primitiveFactory));
    lightManager.addAreaLight(AreaLightSource(QVector3D(0, 30, -5), QVector3D(0, 30, 5), QVector3D(5, 30, -5), 0.8, 0.2, 3, &primitiveFactory));
    lightManager.updateLights();
}

void OpenGLWidget::initializeGL()
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0, (GLint)w, (GLint)h );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 1500);
    glMatrixMode( GL_MODELVIEW );

    renderWidth = w;
    renderHeight = h;
}

void OpenGLWidget::paintGL()
{
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraManager.cameraPos.x(), cameraManager.cameraPos.y(), cameraManager.cameraPos.z(),
              cameraManager.viewTo.x(), cameraManager.viewTo.y(), cameraManager.viewTo.z(), 0,1,0);
    drawAxis();
    drawLight();

    root->draw();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        isRotating = true;
    } else if (e->button() == Qt::RightButton)
    {
        isScaling = true;
    } else if (e->button() == Qt::MiddleButton)
    {
    }
    lastPoint = e->pos();
    update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && isRotating)
    {
        rotate(e->pos(), lastPoint);
        isRotating = false;
    } else if (e->button() == Qt::RightButton && isScaling)
    {
        scale(e->pos(), lastPoint);
        isScaling = false;
    } else if (e->button() == Qt::MiddleButton)
    {
    }
    update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent * e)
{
    if ((e->buttons() & Qt::LeftButton) && isRotating)
    {
        rotate(e->pos(), lastPoint);
    } else if ((e->buttons() & Qt::RightButton) && isScaling)
    {
        scale(e->pos(), lastPoint);
    }
    lastPoint = e->pos();

    update();
}

void OpenGLWidget::drawAxis()
{
    glColor3f(1.0, 0, 0);
    QVector3D zero = QVector3D(0,0,0);
    zero.setX(-AXIS_LENGTH);
    draw3DLine(zero, QVector3D(AXIS_LENGTH, 0, 0));
    zero.setX(0);
    zero.setY(-AXIS_LENGTH);
    glColor3f(0, 1.0, 0);
    draw3DLine(zero, QVector3D(0, AXIS_LENGTH, 0));
    zero.setY(0);
    zero.setZ(-AXIS_LENGTH);
    glColor3f(0, 0, 1.0);
    draw3DLine(zero, QVector3D(0,0, AXIS_LENGTH));
}


void OpenGLWidget::draw3DLine(QVector3D v0, QVector3D v1)
{
    glBegin(GL_LINE_STRIP);
    glVertex3f(v0.x(), v0.y(), v0.z());
    glVertex3f(v1.x(), v1.y(), v1.z());
    glEnd();
}

void OpenGLWidget::rayTrace()
{
/*
 * for each pixel in the new image
 *     fire ray at pixel
 *     return nearest object, or null
 *     compute angle to light source
 *     if object in the way, shadows
 *     color correctly
 *
 */
    progressBar->setValue(0);
    int progressValue = 0;
    int renderSize = renderWidth * renderHeight;
    QImage myImage(renderWidth, renderHeight, QImage::Format_RGB32);
    Ray ray;
    HitRecord hitRecord;
    QVector3D surfacePoint;
    double max_t = 1000.0;
    double min_t = 0;
    QVector3D pixelColour;
    QVector3D depthColour;
    double pixel_i;
    double pixel_j;
    initializeBackgroundTexture();
    lightManager.updateLights();
    ray.calculateUVW(cameraManager.viewTo - cameraManager.cameraPos, QVector3D(0,1,0));
    cameraManager.setUVW(ray.u, ray.v, ray.w);
    for (int i = 0; i < renderWidth; i++)
    {
        for (int j = 0; j < renderHeight; j++)
        {
            pixelColour = QVector3D(0,0,0);
            for (int p = 0; p < sampleSize; p++)
            {
                for (int q = 0; q < sampleSize; q++)
                {
                        pixel_i = i + ((p + jitterValue(p + q)) / sampleSize);
                        pixel_j = j + ((q + jitterValue(p + q)) / sampleSize);
                        ray.calculateRay(renderWidth, renderHeight, pixel_i, pixel_j, cameraManager.getCameraPos(), cameraManager.focalLength);
                        hitRecord = root->queryScene(ray, &min_t, &max_t);

                        if (hitRecord.hit)
                        {
                            surfacePoint = ray.getPoint((hitRecord.t));
                            pixelColour += shadeModel->getPixelColour(root, cameraManager.getCameraPos(), hitRecord.sceneObjectProperties, hitRecord.t,
                                                               hitRecord.sceneObject->getNormal(surfacePoint, hitRecord.transform, hitRecord),
                                                                surfacePoint, lightManager.allLights, 1, getBackgroundColour(pixel_i, pixel_j));
                        } else {
                            pixelColour += getBackgroundColour(pixel_i, pixel_j);
                        }
                }
            }
            pixelColour /= sampleSize2;
            myImage.setPixel(i, renderHeight - j - 1, qRgb(pixelColour.x() * 255, pixelColour.y() * 255, pixelColour.z() * 255));
            progressValue += 1;
        }
        progressBar->setValue(((double)progressValue / renderSize) * 100);
        qDebug() << ((double)progressValue / renderSize) * 100;
    }

    prepareImageDisplay(&myImage);
    qtImage = myImage.copy(0,0, myImage.width(), myImage.height());
}

double OpenGLWidget::jitterValue(int i)
{
    return randomNumbers[i];
}

void OpenGLWidget::prepareImageDisplay(QImage * image)
{
    imageViewer->displayImage(QGLWidget::convertToGLFormat( *image ));
}

void OpenGLWidget::saveImage()
{
    if (qtImage.width() == 0)
        return;
    QString fileBuffer = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "D:\\School",
                               tr("Images (*.png *.xpm *.jpg *.bmp)"));

    bool result = qtImage.save(fileBuffer);
    if (!result)
    {
        qDebug() << "Failure";
    } else {
        qDebug() << "Success";
    }
}

void OpenGLWidget::loadBackgroundTexture()
{
    QString fileBuffer = QFileDialog::getOpenFileName(this, tr("Load Background Texture"), "D:\\School",  tr("Images (*.png *.xpm *.jpg *.bmp)"));
    bool result = backgroundTexture.load(fileBuffer);

    if (!result)
    {
        qDebug() << "Failed to load background texture";
    }
}

void OpenGLWidget::initializeBackgroundTexture()
{
    if (backgroundTexture.width() != 0)
    {
//        scaledBackgroundTexture = backgroundTexture.scaled(renderWidth, renderHeight);
        scaledBackgroundTexture = backgroundTexture;
    }
}

QVector3D OpenGLWidget::getBackgroundColour(int i, int j)
{
    if (backgroundTexture.width() != 0)
    {
       QRgb r = scaledBackgroundTexture.pixel(i, renderHeight - j - 1);
       return QVector3D( ((double)qRed(r)) / 255,  ((double)qGreen(r)) / 255, ((double)qBlue(r)) / 255);
    } else {
        return backgroundColour;
    }
}

void OpenGLWidget::raytraceImage()
{
    rayTrace();
    update();
}

void OpenGLWidget::setImageViewer(ImageViewer *_imageViewer)
{
    imageViewer = _imageViewer;
}

void OpenGLWidget::rotate(QPoint change, QPoint original)
{
    double yRot = (change.x() - original.x()) * DegPerPixel;
    double zRot = (change.y() - original.y()) * DegPerPixel;

    QMatrix4x4 rotation;
    rotation.setToIdentity();;
    rotation.rotate(yRot, 0, 1, 0);
    rotation.rotate(zRot, 0, 0, 1);
    cameraManager.cameraPos = rotation * cameraManager.cameraPos;
}

void OpenGLWidget::scale(QPoint desc, QPoint original)
{
    qreal newLength = (desc.y() - original.y()) * ScalePerPixel + cameraManager.cameraPos.length();
    if ( newLength > 0.5 )
    {
        cameraManager.cameraPos = cameraManager.cameraPos.normalized() * newLength;
    }
}

void OpenGLWidget::drawLight()
{
    QMatrix4x4 transform;
    SceneObjectProperties sp;
    for (std::vector<LightSource>::iterator it = lightManager.allLights.begin(); it != lightManager.allLights.end(); it++)
    {
        transform.setToIdentity();
        transform.translate(it->position);
        it->sphere->drawGeometry(transform, &sp);
    }
//    if (isDepthOfField)
//    {
//        TriangleMesh * mesh = (TriangleMesh *) root->children[0]->getSceneObject();
//        mesh->boundingBox->drawGeometry(mesh->boundingBoxTransform, new SceneObjectProperties());
//    }
}

void OpenGLWidget::changeShadeModelBlinnPhong(bool on)
{
    if (on)
    {
        delete shadeModel;
        shadeModel = new BlinnPhongShadeModel();
    }
}

void OpenGLWidget::changeShadeModelLambertian(bool on)
{
    if (on)
    {
        delete shadeModel;
        shadeModel = new LambertianShadeModel();
    }
}

void OpenGLWidget::changeMaterial(int material)
{
    if (root->children.size() == 0)
        return;
    root->children.front()->sceneObjectProperties = materialFactory.getMaterialProperties((MaterialFactory::Material)material);
    update();
}

void OpenGLWidget::loadObjFile()
{
    bool ok;
    QString fileBuffer = QFileDialog::getOpenFileName(this, tr("Load Obj File"), "D:\\School", tr("Obj Files (*.obj)"));
    TriangleMesh * newMesh = objFileReader.readObjFile(fileBuffer, &ok);
    if (!ok)
    {
        qDebug() << ":(";
        return;
    }
    newMesh->boundingBox = primitiveFactory.getSceneObject(PrimitiveFactory::SPHERE);
    SceneGraphNode * sceneGraphNode = new SceneGraphNode();
    sceneGraphNode->setSceneObject(newMesh, materialFactory.getMaterialProperties(MaterialFactory::BRASS));
    root->addChild(sceneGraphNode);
    update();
}

void OpenGLWidget::changeAntiAlias(int _sampleSize)
{
    sampleSize = _sampleSize;
    sampleSize2 = pow(sampleSize, 2);
    randomNumbers.clear();
    for (int i = 0; i < sampleSize2; i++)
    {
        randomNumbers.push_back((double)std::rand() / RAND_MAX);
    }
}

void OpenGLWidget::setProgressBar(QProgressBar  * _pBar)
{
    progressBar = _pBar;
}

void OpenGLWidget::clearScreen()
{
    root->destroyAll();
    update();
}

void OpenGLWidget::handleKeyPress(QKeyEvent *e)
{
    if (e->key() == Qt::Key_W)
    {
        cameraManager.viewTo.setZ(cameraManager.viewTo.z() - STRAFE_AMOUNT);
    } else if (e->key() == Qt::Key_A)
    {
        cameraManager.viewTo.setX(cameraManager.viewTo.x() - STRAFE_AMOUNT);
    } else if (e->key() == Qt::Key_S)
    {
        cameraManager.viewTo.setZ(cameraManager.viewTo.z() + STRAFE_AMOUNT);
    } else if (e->key() == Qt::Key_D)
    {
        cameraManager.viewTo.setX(cameraManager.viewTo.x() + STRAFE_AMOUNT);
    } else if (e->key() == Qt::Key_Q)
    {
        cameraManager.viewTo.setY(cameraManager.viewTo.y() - STRAFE_AMOUNT);
    } else if (e->key() == Qt::Key_E)
    {
        cameraManager.viewTo.setY(cameraManager.viewTo.y() + STRAFE_AMOUNT);
    }
    update();
}

void OpenGLWidget::changeDepthOfField(int e)
{
    cameraManager.depthPasses = e;
}
