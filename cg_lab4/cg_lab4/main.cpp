//
//  main.cpp
//  cg_lab4
//
//  Created by Tsenguun Otgonbaatar on 2022.09.26.
//

#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>

int W = 500, H = 500;


static void display(void){
    float r, theta;
    const float pi = 3.14159f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int k = 0; k < 5; k++) {
        for (int l = 0; l < 4; l++) {
            r = 0.1;
//            gluOrtho2D((W/5*k)/500, ((W/5*k)+(W/5))/500, (H/4*l)/500, ((H/4*l)+(H/4))/500);
            glViewport(W/5*k, H/4*l, W/5, H/4);
            //glViewport(<#GLint x#>, <#GLint y#>, <#GLsizei width#>, <#GLsizei height#>)
            //glOrtho(W/500*k, W/500*k+W/500,H/400*l, H/400*l+H/400, -1.0, 1.0);
            //glOrtho(W/5*k, (W/5*k)+(W/5), H/4*l, (H/4*l)+(H/4), 1, -1);
//            gluOrtho2D(-0.25, 0.25, -0.25, 0.25);
//            gluOrtho2D(<#GLdouble left#>, <#GLdouble right#>, <#GLdouble bottom#>, <#GLdouble top#>)
            for (int i = 0; i < 1; i++) {
                glBegin(GL_LINE_LOOP);
//                gluOrtho2D(100+i, 200+i, 200+i, 100+i);
//                glOrtho(W/5*k, (W/5*k)+(W/5), H/4*l, (H/4*l)+(H/4), 1, -1);
                for (int j = 0; j < 3; j++) {
                    theta = (2 * pi * j)/3;
                    if ((k % 2 == 0 && l % 2 == 0) || (k%2!=0 && l%2!=0)) {
                        glVertex2f(r*cos(theta-i), r*sin(theta-i));
                    } else {
                        glVertex2f(r*cos(theta+i), r*sin(theta+i));
                    }
                    
                }
//                gluOrtho2D(W/5*k+i, W/5*k+1+i, H/4*l+10+i, H/4*l+i);
//                gluOrtho2D(0, 2, 2, 0);
                
                glEnd();
                //gluOrtho2D(W/5*k, W/5*k+1, H/4*l+10, H/4*l);
                
                r+=0.00;
                glFlush();
            }
        }
    }
}

static void resize(GLsizei w, GLsizei h) {
    W=w;
    H=h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(0, 0.25, 0, 0.25, 1, -1);
    glOrtho(-0.25, 0.25 ,-0.25, 0.25, -1.0, 1.0);
    //glOrtho(0, w/500 , 0, h/400, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(W, H);
    glutCreateWindow("Pattern");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutMainLoop();
    return EXIT_SUCCESS;
}
