#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void MyGLWidget::updateRotation(double roll, double pitch, double yaw)
{
    xRot = roll;
    yRot = pitch;
    zRot = yaw;

    updateGL();
}

void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);

//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);

//    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    glTranslatef(0.0, 0.0, -10.0);
//    glRotated(xRot , 1.0, 0.0, 0.0);
//    glRotated(yRot , 0.0, 1.0, 0.0);
//    glRotated(zRot , 0.0, 0.0, 1.0);
//    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
//    int side = qMin(width, height);
//    glViewport((width - side) / 2, (height - side) / 2, side, side);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
//#else
//    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
//#endif
//    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::draw()
{
//    qglColor(Qt::red);
//    glBegin(GL_QUADS);
//        glNormal3f(0,0,-1);
//        glVertex3f(-1,-1,0);
//        glVertex3f(-1,1,0);
//        glVertex3f(1,1,0);
//        glVertex3f(1,-1,0);

//    glEnd();
//    glBegin(GL_TRIANGLES);
//        glNormal3f(0,-1,0.707);
//        glVertex3f(-1,-1,0);
//        glVertex3f(1,-1,0);
//        glVertex3f(0,0,1.2);
//    glEnd();
//    glBegin(GL_TRIANGLES);
//        glNormal3f(1,0, 0.707);
//        glVertex3f(1,-1,0);
//        glVertex3f(1,1,0);
//        glVertex3f(0,0,1.2);
//    glEnd();
//    glBegin(GL_TRIANGLES);
//        glNormal3f(0,1,0.707);
//        glVertex3f(1,1,0);
//        glVertex3f(-1,1,0);
//        glVertex3f(0,0,1.2);
//    glEnd();
//    glBegin(GL_TRIANGLES);
//        glNormal3f(-1,0,0.707);
//        glVertex3f(-1,1,0);
//        glVertex3f(-1,-1,0);
//        glVertex3f(0,0,1.2);
//    glEnd();
}
