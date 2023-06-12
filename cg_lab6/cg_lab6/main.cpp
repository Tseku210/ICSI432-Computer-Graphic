//// Snowman.cpp
//// Demonstrates using Quadric Objects
//// OpenGL SuperBible
//// Richard S. Wright Jr.
//
//#include "GLUT/glut.h"    // OpenGL toolkit
//#include <stdio.h>
//
//// Rotation amounts
//static GLfloat xRot = 0.0f;
//static GLfloat yRot = 0.0f;
//
//
//////////////////////////////////////////////////////////////////////////////
//// Change viewing volume and viewport.  Called when window is resized
//
//
//void ChangeSize(int w, int h)
//    {
//    GLfloat fAspect;
//
//    // Prevent a divide by zero
//    if(h == 0)
//        h = 1;
//
//    // Set Viewport to window dimensions
//    glViewport(0, 0, w, h);
//
//    fAspect = (GLfloat)w/(GLfloat)h;
//
//    // Reset coordinate system
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    // Produce the perspective projection
//    gluPerspective(35.0f, fAspect, 1.0, 40.0);
//    //glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    }
//
//
//// This function does any needed initialization on the rendering
//// context.  Here it sets up and initializes the lighting for
//// the scene.
//void SetupRC()
//    {
//
//    // Light values and coordinates
//    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
//    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
//    GLfloat     lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };
//
//    glEnable(GL_DEPTH_TEST);    // Hidden surface removal
//    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
//    glEnable(GL_CULL_FACE);        // Do not calculate inside
//
//    // Enable lighting
//    glEnable(GL_LIGHTING);
//
//    // Setup and enable light 0
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
//    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
//    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
//    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
//    glEnable(GL_LIGHT0);
//
//    // Enable color tracking
//    glEnable(GL_COLOR_MATERIAL);
//
//    // Set Material properties to follow glColor values
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//
//    // Black blue background
//    glClearColor(0.25f, 0.25f, 0.50f, 1.0f );
//    }
//
//// Respond to arrow keys
//void SpecialKeys(int key, int x, int y)
//    {
//    if(key == GLUT_KEY_UP)
//        xRot-= 5.0f;
//
//    if(key == GLUT_KEY_DOWN)
//        xRot += 5.0f;
//
//    if(key == GLUT_KEY_LEFT)
//        yRot -= 5.0f;
//
//    if(key == GLUT_KEY_RIGHT)
//        yRot += 5.0f;
//
//    xRot = (GLfloat)((const int)xRot % 360);
//    yRot = (GLfloat)((const int)yRot % 360);
//
//    // Refresh the Window
//    glutPostRedisplay();
//    }
//
//int initialX;
//int initialY;
//
//void mouse(int button, int state, int x, int y) {
//    initialX = x;
//    initialY = y;
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        printf("Working");
//        if (x > initialX) {
//            yRot = 5.0f;
//        } else if (x < initialX) {
//            yRot -= 5.0f;
//        }
//        if (y > initialY) {
//            xRot -= 5.0f;
//        } else if (y < initialY) {
//            xRot += 5.0f;
//        }
//        xRot = (GLfloat)((const int)xRot % 360);
//        yRot = (GLfloat)((const int)yRot % 360);
//    }
//    glutPostRedisplay();
//}
//
//// Called to draw scene
//void RenderScene(void)
//    {
//    GLUquadricObj *pObj;    // Quadric Object
//
//    // Clear the window with current clearing color
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // Save the matrix state and do the rotations
//    glPushMatrix();
//        // Move object back and do in place rotation
//        glTranslatef(0.0f, -1.0f, -5.0f);
//        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
//        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
//
//        // Draw something
//        pObj = gluNewQuadric();
//        gluQuadricNormals(pObj, GLU_SMOOTH);
//
//        // Main Body
//        glPushMatrix();
//            glColor3f(1.0f, 1.0f, 1.0f);
//            gluSphere(pObj, .40f, 26, 13);  // Bottom
//
//            glTranslatef(0.0f, .550f, 0.0f); // Mid section
//            gluSphere(pObj, .3f, 26, 13);
//
//            glTranslatef(0.0f, 0.45f, 0.0f); // Head
//            gluSphere(pObj, 0.24f, 26, 13);
//
//            // Eyes
//            glColor3f(0.0f, 0.0f, 0.0f);
//            glTranslatef(0.1f, 0.1f, 0.21f);
//            gluSphere(pObj, 0.02f, 26, 13);
//
//            glTranslatef(-0.2f, 0.0f, 0.0f);
//            gluSphere(pObj, 0.02f, 26, 13);
//
//            // Nose
//            glColor3f(1.0f, 0.3f, 0.3f);
//            glTranslatef(0.1f, -0.12f, 0.0f);
//            gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);
//        glPopMatrix();
//
//        // Hat
//        glPushMatrix();
//            glColor3f(0.0f, 0.0f, 0.0f);
//            glTranslatef(0.0f, 1.17f, 0.0f);
//            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
//            gluCylinder(pObj, 0.17f, 0.17f, 0.4f, 26, 13);
//
//            // Hat brim
//            glDisable(GL_CULL_FACE);
//            gluDisk(pObj, 0.17f, 0.28f, 26, 13);
//            glEnable(GL_CULL_FACE);
//
//            glTranslatef(0.0f, 0.0f, 0.40f);
//            gluDisk(pObj, 0.0f, 0.17f, 26, 13);
//        glPopMatrix();
//
//    // Restore the matrix state
//    glPopMatrix();
//
//    // Buffer swap
//    glutSwapBuffers();
//    }
//
//
//
//int main(int argc, char *argv[])
//    {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Modeling with Quadrics");
//    glutReshapeFunc(ChangeSize);
//    glutSpecialFunc(SpecialKeys);
//    glutDisplayFunc(RenderScene);
//    //glutMouseFunc(mouse);
//
//    SetupRC();
//    glutMainLoop();
//
//    return 0;
//    }
//
//
//
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <cstring>
#include <cmath>

bool fullscreen = false;
bool mouseDown = false;
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;

void drawCube()
{
    glutWireCube(1.0);
}
void bell()
{
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_SMOOTH);
    gluQuadricNormals(qobj, GLU_FLAT);
    gluCylinder(qobj, 0.6, 0.3, 0.6, 15, 5);
}
void disk1()
{
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_FLAT);
    gluDisk(qobj, 0.3, 0.3, 20, 10);
}
void bellHandle()
{
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_FLAT);
    gluCylinder(qobj, 0.1, 0.1, 1.0, 15, 5);
    glScalef(0.0f, 1.0f, 0.0f);
}

bool init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(0.0);
    return true;
}

void drawSnowman() {
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    gluQuadricDrawStyle(pObj, GLU_FILL);
//    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
//    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    // Main Body
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-1.0f, 0.4f, 0.0f);
        gluSphere(pObj, .40f, 26, 13);  // Bottom

        glTranslatef(0.0f, .550f, 0.0f); // Mid section
        gluSphere(pObj, .3f, 26, 13);

        glTranslatef(0.0f, .45f, 0.0f); // Head
        gluSphere(pObj, 0.24f, 26, 13);

        // Eyes
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.1f, 0.1f, 0.21f);
        gluSphere(pObj, 0.02f, 26, 13);

        glTranslatef(-0.2f, 0.0f, 0.0f);
        gluSphere(pObj, 0.02f, 26, 13);

        // Nose
        glColor3f(1.0f, 0.3f, 0.3f);
        glTranslatef(0.1f, -0.12f, 0.0f);
        gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);
        // Hat
        glColor3f(0.5f, .3f, 0.0f);
        glTranslatef(.0f, 0.2f, -0.21f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.17f, 0.17f, 0.4f, 26, 13);

        // Hat brim
        //glDisable(GL_CULL_FACE);
        gluDisk(pObj, 0.17f, 0.28f, 26, 13);
        //glEnable(GL_CULL_FACE);

        glTranslatef(0.0f, 0.0f, 0.40f);
        gluDisk(pObj, 0.0f, 0.17f, 26, 13);
        //mod
        glColor4f(0.5,0.3,0,5);
        glTranslated(-1.0f, 0.0f,-2.0f);
        glRotated(0,1,0,0);
        gluCylinder(pObj, 0.2, .2, 0.5, 50, 4);
        glColor4d(0,0.5,0,1);
        glTranslated(0, 0, 1);
        glRotated(180,1,0,0);
        gluCylinder(pObj, 0, .5, 0.6, 50, 4);
        glTranslated(0, 0, -.2);
        gluCylinder(pObj, 0, 0.4, 0.5, 50, 4);
        glTranslated(0, 0, -.2);
        gluCylinder(pObj, 0, 0.3, 0.4, 50, 4);
//    glPopMatrix();
//    glColor3f(1, 0., 0.);
//   glPushMatrix();
//     glTranslated(-2,-2,-6);
//    gluSphere(pObj, .8,  50, 50);
//    glPopMatrix();
//    glColor3ub(244, 224, 190);
//    glPushMatrix();
//     glTranslated(-2,-0.9,-6);
//    gluSphere(pObj, .4,  50, 50);
//    glPopMatrix();
//    glColor3f(1., 1.,1.);
//    glPushMatrix();
//    glTranslated(-1.34,0.1,-4);
//     gluSphere(pObj, .08,  50, 50);
//    glPopMatrix();
//     glPushMatrix();
//    glTranslated(-1.3,-1.,-4);
//     gluSphere(pObj, .06,  50, 50);
//    glPopMatrix();
//    glPushMatrix();
//    glTranslated(-1.2,-1.3,-4);
//     gluSphere(pObj, .06,  50, 50);
//    glPopMatrix();
//    glPushMatrix();
//    glTranslated(-1.25,-1.6,-4);
//     gluSphere(pObj, .06,  50, 50);
//    glPopMatrix();
//    glColor3f(1., 0.,0.);
//     glPushMatrix();
//    glTranslated(-2.,0.2,-6);
//    glRotated(90,1,0,0);
//     gluCylinder(pObj, 0, 0.3, .8, 50, 4);
//    glPopMatrix();
//
//    glColor3f(0, 0., 0.);
//    glPushMatrix();
//    glTranslated(-.9,-.4,-3);
//     gluSphere(pObj, .03,  50, 50);
//    glPopMatrix();
//     glPushMatrix();
//    glTranslated(-1.1,-.4,-3);
//     gluSphere(pObj, .03,  50, 50);
//    glPopMatrix();
//   glColor3ub(244, 224, 190);
//    glPushMatrix();
//     glTranslated(-2.2,-1.4,-5);
//    gluSphere(pObj, .15,  50, 50);
//    glPopMatrix();
//    glPushMatrix();
//     glTranslated(-1.1,-1.3,-5);
//    gluSphere(pObj, .15,  50, 50);
//    glPopMatrix();
//   gluDeleteQuadric(pObj);

    glPopMatrix();

    //mod
//    glColor4f(0.5,0.3,0,5);
//       glPushMatrix();
//         glTranslated(0,0,0);
//         glRotated(90,1,0,0);
//          gluCylinder(pObj, 0.4, .4, 1, 50, 4);
//         glPopMatrix();
//     glPushMatrix();
//       glColor4d(0,0.5,0,1);
//     glPushMatrix();
//         glTranslated(0,-.6,-6);
//         glRotated(90,1,0,0);
//          gluCylinder(pObj, 0, 1, 1.3, 50, 4);
//         glPopMatrix();
//     glPushMatrix();
//         glTranslated(0,-.1,-6);
//         glRotated(90,1,0,0);
//          gluCylinder(pObj, 0, .9, 1.2, 50, 4);
//         glPopMatrix();
//          glPushMatrix();
//         glTranslated(0,0.4,-6);
//         glRotated(90,1,0,0);
//          gluCylinder(pObj, 0, .7, 1.1, 50, 4);
//         glPopMatrix();
//          glPushMatrix();
//         glTranslated(0,0.9,-6);
//         glRotated(90,1,0,0);
//          gluCylinder(pObj, 0, .5, 1, 50, 4);
//         glPopMatrix();
//    //chimeglel
//    glColor3f(0.8,0,0);
//     glPushMatrix();
//         glTranslated(0.4,-.8,-4);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();
//
//     glPushMatrix();
//         glTranslated(0,-1.2,-4);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();
//          glPushMatrix();
//         glTranslated(-.2,-0.2,-4);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();
//        glColor3f(0.8,0.8,0);
//           glPushMatrix();
//         glTranslated(.2,-0.3,-4);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();
//            glPushMatrix();
//         glTranslated(-.3,-0.8,-4);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();
//         glColor3f(1.f, 0.5f, 0.f);
//          glPushMatrix();
//         glTranslated(-.5,-1.2,-4);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();
//    glColor3f(0.0f, 0.5f, 0.5f);
//     glPushMatrix();
//         glTranslated(0,-0.7,-4);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();
//
//    glColor3f(1., 0.,1.);
//     glPushMatrix();
//         glTranslated(.4,-1.2,-4);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();
//          glPushMatrix();
//         glTranslated(.1,0.2,-4.5);
//          gluSphere(pObj, .07,  50, 50);
//         glPopMatrix();

}

void drawTree() {
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    gluQuadricDrawStyle(pObj, GLU_FILL);
    glColor4f(0.5,0.3,0,5);
       glPushMatrix();
         glTranslated(0,-1.8,-6);
         glRotated(90,1,0,0);
          gluCylinder(pObj, 0.4, .4, 1, 50, 4);
         glPopMatrix();
     glPushMatrix();
       glColor4d(0,0.5,0,1);
     glPushMatrix();
         glTranslated(0,-.6,-6);
         glRotated(90,1,0,0);
          gluCylinder(pObj, 0, 1, 1.3, 50, 4);
         glPopMatrix();
     glPushMatrix();
         glTranslated(0,-.1,-6);
         glRotated(90,1,0,0);
          gluCylinder(pObj, 0, .9, 1.2, 50, 4);
         glPopMatrix();
          glPushMatrix();
         glTranslated(0,0.4,-6);
         glRotated(90,1,0,0);
          gluCylinder(pObj, 0, .7, 1.1, 50, 4);
         glPopMatrix();
          glPushMatrix();
         glTranslated(0,0.9,-6);
         glRotated(90,1,0,0);
          gluCylinder(pObj, 0, .5, 1, 50, 4);
         glPopMatrix();
    //chimeglel
    glColor3f(0.8,0,0);
     glPushMatrix();
         glTranslated(0.4,-.8,-4);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();

     glPushMatrix();
         glTranslated(0,-1.2,-4);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();
          glPushMatrix();
         glTranslated(-.2,-0.2,-4);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();
        glColor3f(0.8,0.8,0);
           glPushMatrix();
         glTranslated(.2,-0.3,-4);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();
            glPushMatrix();
         glTranslated(-.3,-0.8,-4);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();
         glColor3f(1.f, 0.5f, 0.f);
          glPushMatrix();
         glTranslated(-.5,-1.2,-4);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();
    glColor3f(0.0f, 0.5f, 0.5f);
     glPushMatrix();
         glTranslated(0,-0.7,-4);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();

    glColor3f(1., 0.,1.);
     glPushMatrix();
         glTranslated(.4,-1.2,-4);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();
          glPushMatrix();
         glTranslated(.1,0.2,-4.5);
          gluSphere(pObj, .07,  50, 50);
         glPopMatrix();

}

void drawTable()
{
    glBegin(GL_QUADS);
    // Front
    //
    glColor3f(.4, .6, .6);
    glVertex3f(-4.0f, -0.2f, 2.0f);
    glVertex3f(2.0f, -0.2f, 2.0f);
    glVertex3f(2.0f, 0.2f, 2.0f);
    glVertex3f(-4.0f, 0.2f, 2.0f);

    // Back
    //;
    glVertex3f(-4.0f, -0.2f, -2.0f);
    glVertex3f(-4.0f, 0.2f, -2.0f);
    glVertex3f(2.0f, 0.2f, -2.0f);
    glVertex3f(2.0f, -0.2f, -2.0f);

    // Right
    //
    glVertex3f(2.0f, -0.2f, -2.0f);
    glVertex3f(2.0f, 0.2f, -2.0f);
    glVertex3f(2.0f, 0.2f, 2.0f);
    glVertex3f(2.0f, -0.2f, 2.0f);

    // Left
    ;
    glVertex3f(-4.0f, -0.2f, -2.0f);
    glVertex3f(-4.0f, -0.2f, 2.0f);
    glVertex3f(-4.0f, 0.2f, 2.0f);
    glVertex3f(-4.0f, 0.2f, -2.0f);

    // top
    //

    glVertex3f(2.0f, 0.2f, 2.0f);
    glVertex3f(-4.0f, 0.2f, 2.0f);
    glVertex3f(-4.0f, 0.2f, -2.0f);
    glVertex3f(2.0f, 0.2f, -2.0f);

    // bottom
    ;

    glVertex3f(2.0f, -0.2f, 2.0f);
    glVertex3f(-4.0f, -0.2f, 2.0f);
    glVertex3f(-4.0f, -0.2f, -2.0f);
    glVertex3f(2.0f, -0.2f, -2.0f);

    // table front leg
    // front
    //
    glColor3f(.4f, .6f, 0.0f);
    glVertex3f(1.8f, -0.2f, 1.6f);
    glVertex3f(1.4f, -0.2f, 1.6f);
    glVertex3f(1.4f, -3.0f, 1.6f);
    glVertex3f(1.8f, -3.0f, 1.6f);

    // back
    //;

    glVertex3f(1.8f, -0.2f, 1.2f);
    glVertex3f(1.4f, -0.2f, 1.2f);
    glVertex3f(1.4f, -3.0f, 1.2f);
    glVertex3f(1.8f, -3.0f, 1.2f);

    // right
    //

    glVertex3f(1.8f, -0.2f, 1.6f);
    glVertex3f(1.8f, -0.2f, 1.2f);
    glVertex3f(1.8f, -3.0f, 1.2f);
    glVertex3f(1.8f, -3.0f, 1.6f);

    // left
    //;

    glVertex3f(1.4f, -0.2f, 1.6f);
    glVertex3f(1.4f, -0.2f, 1.2f);
    glVertex3f(1.4f, -3.0f, 1.2f);
    glVertex3f(1.4f, -3.0f, 1.6f);

    // back leg back
    // front
    //;
    glVertex3f(1.8f, -0.2f, -1.2f);
    glVertex3f(1.4f, -0.2f, -1.2f);
    glVertex3f(1.4f, -3.0f, -1.2f);
    glVertex3f(1.8f, -3.0f, -1.2f);

    // back
    //;

    glVertex3f(1.8f, -0.2f, -1.6f);
    glVertex3f(1.4f, -0.2f, -1.6f);
    glVertex3f(1.4f, -3.0f, -1.6f);
    glVertex3f(1.8f, -3.0f, -1.6f);

    // right
    //

    glVertex3f(1.8f, -0.2f, -1.6f);
    glVertex3f(1.8f, -0.2f, -1.2f);
    glVertex3f(1.8f, -3.0f, -1.2f);
    glVertex3f(1.8f, -3.0f, -1.6f);

    // left
    //

    glVertex3f(1.4f, -0.2f, -1.6f);
    glVertex3f(1.4f, -0.2f, -1.2f);
    glVertex3f(1.4f, -3.0f, -1.2f);
    glVertex3f(1.4f, -3.0f, -1.6f);

    // leg left front
    //

    glVertex3f(-3.8f, -0.2f, 1.6f);
    glVertex3f(-3.4f, -0.2f, 1.6f);
    glVertex3f(-3.4f, -3.0f, 1.6f);
    glVertex3f(-3.8f, -3.0f, 1.6f);

    // back
    //;

    glVertex3f(-3.8f, -0.2f, 1.2f);
    glVertex3f(-3.4f, -0.2f, 1.2f);
    glVertex3f(-3.4f, -3.0f, 1.2f);
    glVertex3f(-3.8f, -3.0f, 1.2f);

    // right

    glVertex3f(-3.8f, -0.2f, 1.6f);
    glVertex3f(-3.8f, -0.2f, 1.2f);
    glVertex3f(-3.8f, -3.0f, 1.2f);
    glVertex3f(-3.8f, -3.0f, 1.6f);

    // left
    ;

    glVertex3f(-3.4f, -0.2f, 1.6f);
    glVertex3f(-3.4f, -0.2f, 1.2f);
    glVertex3f(-3.4f, -3.0f, 1.2f);
    glVertex3f(-3.4f, -3.0f, 1.6f);

    // left leg back front

    // front
    ;
    // glColor3f(1,1,1);
    glVertex3f(-3.8f, -0.2f, -1.2f);
    glVertex3f(-3.4f, -0.2f, -1.2f);
    glVertex3f(-3.4f, -3.0f, -1.2f);
    glVertex3f(-3.8f, -3.0f, -1.2f);

    // back
    ;

    glVertex3f(-3.8f, -0.2f, -1.6f);
    glVertex3f(-3.4f, -0.2f, -1.6f);
    glVertex3f(-3.4f, -3.0f, -1.6f);
    glVertex3f(-3.8f, -3.0f, -1.6f);

    // right

    glVertex3f(-3.8f, -0.2f, -1.6f);
    glVertex3f(-3.8f, -0.2f, -1.2f);
    glVertex3f(-3.8f, -3.0f, -1.2f);
    glVertex3f(-3.8f, -3.0f, -1.6f);

    // left

    glVertex3f(-3.4f, -0.2f, -1.6f);
    glVertex3f(-3.4f, -0.2f, -1.2f);
    glVertex3f(-3.4f, -3.0f, -1.2f);
    glVertex3f(-3.4f, -3.0f, -1.6f);
    
    

    glPopMatrix();

    glEnd();
}
void display()
{
    glClearColor(0.3, 0.3, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
        0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    /*
        glPushMatrix();
        GLUquadricObj *qobj;
        qobj = gluNewQuadric();
        gluQuadricDrawStyle(qobj, GLU_FILL);
        gluQuadricNormals(qobj, GLU_FLAT);
        gluCylinder(qobj, 0.6, 0.3, 0.6, 30, 5);
        glPopMatrix();


        glPushMatrix();
        GLUquadricObj *qobj1;
        qobj1 = gluNewQuadric();
        gluQuadricDrawStyle(qobj1, GLU_FILL);
        gluQuadricNormals(qobj1, GLU_FLAT);
        gluDisk(qobj1, 0.3, 0.3, 30, 5);
        glPopMatrix();

    gluDisk(gluNewQuadric(), 2-1, 2-1, 32, 32);

        glPushMatrix();
        GLUquadricObj *qobj2;
        qobj2 = gluNewQuadric();
        gluQuadricDrawStyle(qobj2, GLU_FILL);
        gluQuadricNormals(qobj2, GLU_FLAT);
        gluCylinder(qobj2, 0.1, 0.1, 1.0, 30, 5);
        glPopMatrix();


    */
    glPushMatrix();
    glScalef(0.25f, 0.25f, 0.25f);
    drawTable();
    drawSnowman();
    //drawTree();
    glFlush();
    glutSwapBuffers();
}

void resize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle()
{
    if (!mouseDown)
    {
        xrot += 0.3f;
        yrot += 0.4f;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(1);
        break;
    }
}

void specialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_F1)
    {
        fullscreen = !fullscreen;

        if (fullscreen)
            glutFullScreen();
        else
        {
            glutReshapeWindow(500, 500);
            glutPositionWindow(50, 50);
        }
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

void mouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = x - xdiff;
        xrot = y + ydiff;
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Shiree");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(resize);
    if (!init())
        return 1;
    glutMainLoop();
    return 0;
}
