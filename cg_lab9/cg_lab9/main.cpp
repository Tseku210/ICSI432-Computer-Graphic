//#include<GLUT/GLUT.h>
//#include <math.h>
//#define GL_PI 3.1415f
//#include<stdio.h>
//static GLfloat xRot = 0.0f;
//static GLfloat yRot = 0.0f;
//GLfloat winWidth, winHeight;
//float ver [100000][3];
//int flat [100000][3];
//
//
//
//
//
//void RenderScene(void)
//    {
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
//    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
//    int i;
//
//
//
//
//    int v = 0;
//    int f = 0;
//    char key;
//    FILE *fin;
//    fin = fopen("/Users/tsenguunotgonbaatar/Documents/computer_graphics/cg_lab9/dragon.obj", "r");
//
//
//
//    if (fin == NULL)
//        printf("\ncan't open input file\n");
//
//
//
//    while(!feof(fin)){
//        fscanf(fin,"%c",&key);
//        if(key == 'v')
//        {
//            fscanf(fin,"%f",&ver[v][0]);
//            fscanf(fin,"%f",&ver[v][1]);
//            fscanf(fin,"%f",&ver[v][2]);
//            v = v+1;
//        }
//        else if(key == 'f')
//        {
//            fscanf(fin,"%d",&flat[f][0]);
//            fscanf(fin,"%d",&flat[f][1]);
//            fscanf(fin,"%d",&flat[f][2]);
//            f = f+1;
//        }
//    }
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//    glBegin(GL_TRIANGLES);
//    for (i = 0; i <100000; ++i)
//    {
//        glColor3f(1,1,1);
//        glVertex3fv(ver[flat[i][0]-1]);
//        glVertex3fv(ver[flat[i][1]-1]);
//        glVertex3fv(ver[flat[i][2]-1]);
//    }
//    glEnd();
//    glutSwapBuffers();
//
//    }
//
//
//
//void SpecialKeys(int key, int x, int y)
//    {
//    if(key == GLUT_KEY_UP)
//        xRot-= 3.0f;
//
//    if(key == GLUT_KEY_DOWN)
//        xRot += 3.0f;
//
//    if(key == GLUT_KEY_LEFT)
//        yRot -= 3.0f;
//
//    if(key == GLUT_KEY_RIGHT)
//        yRot += 3.0f;
//
//    if(key > 356.0f)
//        xRot = -xRot;
//
//    if(key < -1.0f)
//        xRot = 355.0f;
//
//    if(key > 356.0f)
//        yRot = -yRot;
//
//    if(key < -1.0f)
//        yRot = 355.0f;
//
//    // Refresh the Window
//    glutPostRedisplay();
//    }
//
//
//void ChangeSize(int w, int h)
//    {
//    GLfloat nRange = 1.0f;
//    if(h == 0)
//        h = 1;
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    if (w <= h)
//        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);
//    else
//        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    }
//
//int main(int argc, char* argv[])
//    {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutCreateWindow("Dragon");
//    glutReshapeFunc(ChangeSize);
//    glutSpecialFunc(SpecialKeys);
//    glutDisplayFunc(RenderScene);
//
//    glutMainLoop();
//
//    return 0;
//    }
//header



//#include<GLUT/GLUT.h>
//#include<stdio.h>
//#include<iostream>
//using namespace std;
////globals
//int tooloh=0;
//GLuint elephant;
//float elephantrot;
//float elephantroty;
//char ch='1';
//
//
//
////other functions and main
//
//
//
////.obj loader code begins
//
//
//
//void loadObj(char *fname)
//{
//FILE *fp;
//int read;
//GLfloat x, y, z;
//char ch;
//elephant=glGenLists(1);
//fp=fopen(fname,"r");
//if (!fp)
//    {
//        printf("can't open file %s\n", fname);
//      exit(1);
//    }
//glPointSize(1.0);
//glNewList(elephant, GL_COMPILE);
//{
//glPushMatrix();
//glBegin(GL_POINTS);
//while(!(feof(fp)))
//{
//  read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
//  if(read==4&&ch=='v')
//  {
//   glVertex3f(x,y,z);
//  }
//}
//glEnd();
//}
//glPopMatrix();
//glEndList();
//fclose(fp);
//}
//
//
//
////.obj loader code ends here
//
//void SpecialKeys(int key, int x, int y)
//    {
//    if(key == GLUT_KEY_UP)
//        elephantrot-= 3.0f;
//
//    if(key == GLUT_KEY_DOWN)
//        elephantrot += 3.0f;
//
//    if(key == GLUT_KEY_LEFT)
//        elephantroty -= 3.0f;
//
//    if(key == GLUT_KEY_RIGHT)
//        elephantroty += 3.0f;
//
//    if(key > 356.0f)
//        elephantrot = 0;
//
//    if(key < -1.0f)
//        elephantrot = 355.0f;
//
//    if(key > 356.0f)
//        elephantroty = 0;
//
//    if(key < -1.0f)
//        elephantroty = 355.0f;
//
//    // Refresh the Window
//    glutPostRedisplay();
//    }
//
//
//void reshape(int w,int h)
//{
//    glViewport(0,0,w,h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//        gluPerspective (100, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
//    //glOrtho(-25,25,-2,2,0.1,100);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//
//
//void drawCar()
//{
//     glPushMatrix();
//     glTranslatef(0,-100,-100);
//     glColor3f(0.2,0.2,0.2);
//     glScalef(10,10,10);
////     glScalef(3,3,3);
//     glRotatef(elephantrot,elephantrot,0,0);
//     glRotatef(elephantroty,0,0,elephantroty);
//     glCallList(elephant);
//     glPopMatrix();
//     if(elephantrot>360)elephantrot=elephantrot-360;
//}
//
//
//
//void display(void)
//{
//       glClearColor (1.0,1.0,1.0,1.0);
//       glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//       glLoadIdentity();
//       drawCar();
//       glutSwapBuffers(); //swap the buffers
//
//
//
//}
////# This file uses centimeters as units for non-parametric coordinates.
//
////mtllib Character.mtl
////g default
//
//
//int main(int argc,char **argv)
//{
//    glutInit(&argc,argv);
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
//    glutInitWindowSize(800,450);
//    glutInitWindowPosition(20,20);
//    glutCreateWindow("ObjLoader");
//    glutReshapeFunc(reshape);
//    glutDisplayFunc(display);
//    glutIdleFunc(display);
//    glutSpecialFunc(SpecialKeys);
//    loadObj("/Users/tsenguunotgonbaatar/Downloads/Character.obj");//replace porsche.obj with radar.obj or any other .obj to display it
//
//    glutMainLoop();
//    return 0;
//}



#include<GLUT/glut.h>
#include<math.h>
#include<stdio.h>



GLfloat winWidth, winHeight;
float ver [50000][3];
int flat [100000][3];
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;



void normalize(float*v){
    float length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    for(int i = 0; i<3; i++)
    {
        v[i] = v[i]/length;
    }
}



float *cross_product(float*a,float*b)
{
    float result[] = {a[1]*b[2]-a[2]*b[1], - (a[0]*b[2]-a[2]*b[0]), a[0]*b[1]-a[1]*b[0]};
    normalize(result);
    return result;
}



float *calculate_normal(float *a, float *b, float *c)
{
    float x[] = {b[0]-a[0],b[1]-a[1],b[2]-a[2]};
    float y[] = {c[0]-a[0],c[1]-a[1],c[2]-a[2]};



    float *result = cross_product(x,y);
    return result;
}




#define SIL GLU_SILHOUETTE
#define FILL GLU_LINE
void init()
{
    glClearColor(1 , 1 , 1 , 1);
    GLfloat ambient[] = {0,0,0,1};
    GLfloat diffuse[] = {1,1,1,1};
    GLfloat specular[] = {1,1,1,1};
    GLfloat position[] = {0,3,3,0};



    GLfloat lmodel_ambient[] = {0.2,0.2,0.2,1};
    GLfloat local_view[] = {0.0};



    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);



    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);



}




void display()
{
    glClearColor(0, 0, 0, 1);
    int i;
    float normal[3];
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,1,-1);

    glViewport(0,0,1000,1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 0.0f, 1.0f);



    int v = 0;
    int f = 0;
    char key;
    FILE *fin;
    fin = fopen("/Users/tsenguunotgonbaatar/Downloads/Character.obj", "r");



    if (fin == NULL)
        printf("\ncan't open input file\n");



    while(!feof(fin)){
        fscanf(fin,"%c",&key);
        if(key == 'v')
        {
            fscanf(fin,"%f",&ver[v][0]);
            fscanf(fin,"%f",&ver[v][1]);
            fscanf(fin,"%f",&ver[v][2]);
            v = v+1;
        }
        else if(key == 'f')
        {
            fscanf(fin,"%d",&flat[f][0]);
            fscanf(fin,"%d",&flat[f][1]);
            fscanf(fin,"%d",&flat[f][2]);
            f = f+1;
        }
    }
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBegin(GL_TRIANGLES);



    for (i = 0; i <100000; ++i)
    {
        //glColor3f(1,1,1);
        glNormal3fv(calculate_normal(ver[flat[i][0]-1],ver[flat[i][1]-1],ver[flat[i][2]-1]));
        glVertex3fv(ver[flat[i][0]-1]);
        glVertex3fv(ver[flat[i][1]-1]);
        glVertex3fv(ver[flat[i][2]-1]);
    }
    glEnd();



    glutSwapBuffers();
}
void reshape(int w, int h)
{
    if(h==0)
        h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
    {
        winHeight=250*h/w;
        winWidth=250;
    }else
    {
        winWidth=250*w/h;
        winHeight=250;
    }
    glOrtho(0,winWidth,0,winHeight,1,-1);



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}




void SpecialKeys(int key, int x, int y)
    {
    if(key == GLUT_KEY_UP)
        xRot-= 5.0f;



    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;



    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;



    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;



    if(key > 356.0f)
        xRot = 0.0f;



    if(key < -1.0f)
        xRot = 355.0f;



    if(key > 356.0f)
        yRot = 0.0f;



    if(key < -1.0f)
        yRot = 355.0f;



    glutPostRedisplay();
    }
int main(int args, char**argv)
{



    glutInit(&args,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);



    glutInitWindowPosition(400,0);
    glutInitWindowSize(1000,1000);
//    glutInitWindowPosition(100, 100);
    glutCreateWindow("Window");
    glutDisplayFunc(display);
    glutSpecialFunc(SpecialKeys);



    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}
