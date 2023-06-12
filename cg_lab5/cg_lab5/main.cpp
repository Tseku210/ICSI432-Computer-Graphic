//
//  main.cpp
//  cg_lab5
//
//  Created by Tsenguun Otgonbaatar on 2022.10.16.
//

#include <GLUT/glut.h>

GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei rsize = 50;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat winWidth, winHeight;
int cnt = 0;
float deltat = .01;

float a[12][2] = {
    {50, 200}, {100, 200}, {100, 150}, {150, 150}, {150, 200}, {200, 200},
    {200, 50}, {150, 50}, {150, 120}, {100, 120}, {100, 50}, {50, 50}
};
float enda[12][2] = {
    {100, 200}, {150, 200}, {150, 150}, {150, 100}, {150, 50}, {100, 50},
    {100, 70}, {100, 100}, {100, 130}, {100, 150}, {100, 170}, {100, 200
        
    }
};
float e[12][2] = {
    {70, 200}, {200, 200}, {200, 170}, {100, 170}, {100, 150}, {200, 150},
    {200, 120}, {100, 120}, {100, 100}, {200, 100}, {200, 70}, {70, 70}
};

float interShape[12][2];
static float Tween = 0.0;


void display(void){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    //glRectf(x1, y1, x1+rsize, y1+rsize);

//    glBegin(GL_LINE_STRIP);
//    glLineWidth(4.0);
//    glVertex2f(50.0f, 50.0f);
//    glVertex2f(100.0f, 200.0f);
//    glVertex2f(125.0f, 200.0f);
//    glVertex2f(175.0f, 50.0f);
//    glVertex2f(150.0f, 50.0f);
//    glVertex2f(125.0f, 100.0f);
//    glVertex2f(100.0f, 100.0f);
//    glVertex2f(75.0f, 50.0f);
//    glVertex2f(50.0f, 50.0f);
//    glEnd();
    glLineWidth(4.0);
    int i;
    for (i = 0; i < 12; i++){
        if (cnt == 0) {
            interShape[i][0] = (1.0 - Tween)*a[i][0] + Tween*enda[i][0];
            interShape[i][1] = (1.0 - Tween)*a[i][1] + Tween*enda[i][1];
            if (Tween > 1) {
                cnt++;
                Tween = 0;
            }

        } else if (cnt == 1) {
            interShape[i][0] = (1.0 - Tween)*enda[i][0] + Tween*e[i][0];
            interShape[i][1] = (1.0 - Tween)*enda[i][1] + Tween*e[i][1];
            if (deltat < 0 && Tween <= 0) {
                cnt = 0;
                Tween = 1;
            }
        }
    }
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < 12; i++) {
        if (cnt == 0) {
            glVertex2f((1.0 - Tween)*a[i][0] + Tween*enda[i][0], interShape[i][1] = (1.0 - Tween)*a[i][1] + Tween*enda[i][1]);
        } else if (cnt == 1) {
            glVertex2f((1.0 - Tween)*enda[i][0] + Tween*e[i][0], interShape[i][1] = (1.0 - Tween)*enda[i][1] + Tween*e
                       [i][1]);
        }
    }
    glEnd();
    
//    glVertexPointer(2, GL_FLOAT, 0, a);
    
    //for (i = 0; i < 1000000; i++);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glDrawArrays(GL_LINE_LOOP, 0, 12);

    glutSwapBuffers();
//    glFlush();
}
//
//void a() {
//    glBegin(GL_LINE_LOOP);
//
//    glEnd();
//    glutSwapBuffers();
//}

//void b() {
//
//}

void setup(void) {
    glClearColor(0, 0, 0, 1.0f);
}

void timer(int value) {
//    if (x1>winWidth-rsize || x1<0){
//        xstep = -xstep;
//    }
//    if (y1 > winHeight-rsize || y1<0){
//        ystep = -ystep;
//    }
//    if (x1>winWidth-rsize) {
//        x1 = winWidth-rsize-1;
//    }
//    if (y1>winHeight-rsize) {
//        y1 = winHeight-rsize-1;
//    }
//    x1 += xstep;
//    y1 += ystep;
//    glutPostRedisplay();
//    glutTimerFunc(33, timer, 1);
    if (Tween <= 1 && Tween >= 0) {
        Tween += deltat;
    } else {
        deltat = -deltat;
        Tween += deltat;
    }

//    glutSwapBuffers();
    glutPostRedisplay();
    glutTimerFunc(1, timer, 1);
}

void resize(GLsizei w, GLsizei h) {
    if (h==0) h=1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        winHeight = 250.0f*h/w;
        winWidth = 250.0f;
    } else {
        winWidth = 250.0f*w/h;
        winHeight = 250.0f;
    }
    glOrtho(0.0f, winWidth, 0.0f, winHeight, 1.0f, -1.0f);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, const char * argv[]) {
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Animation");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutTimerFunc(33, timer, 1);
    setup();
    glutMainLoop();
    return 0;
}
