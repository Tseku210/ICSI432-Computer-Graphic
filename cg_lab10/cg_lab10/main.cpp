#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLUT/glut.h>
//
//#define far
//#define near
//#define FAR                 far
//#define NEAR                near
//
//typedef unsigned char BYTE;
//typedef unsigned char byte;
//
//double axisY = 0;
//double axisX = 0;
//int num_texture = -1;
//
//GLuint obj;
//GLuint image;
//
//typedef struct tagRGBTRIPLE {
//       BYTE    rgbtBlue;
//       BYTE    rgbtGreen;
//       BYTE    rgbtRed;
//} RGBTRIPLE, *PRGBTRIPLE, NEAR *NPRGBTRIPLE, FAR *LPRGBTRIPLE;
//
//typedef struct vertex
//{
//   GLfloat x;
//   GLfloat y;
//   GLfloat z;
//} Vertex;
//
//typedef struct normal
//{
//   GLfloat x;
//   GLfloat y;
//   GLfloat z;
//} Normal;
//
//typedef struct texture
//{
//   GLfloat x;
//   GLfloat y;
//} Texture;
//
//typedef struct face
//{
//   GLint v1, v2, v3, v4;
//   GLint n1, n2, n3, n4;
//   GLint t1, t2, t3, t4;
//} Face;
//
//GLuint loadBMP_custom(const char *imagepath) {
//  unsigned char header[54];
//  unsigned int dataPos;
//  unsigned int width, height;
//  unsigned int imageSize;
//  unsigned char *l_texture;
//  unsigned char *data;
//
//  printf("filename: %s\n", imagepath);
//  FILE *file = fopen(imagepath, "rb");
//  if (!file) {
//    printf("Image could not be opened\n");
//    return 0;
//  } else {
//    printf("Image opened\n");
//  }
//
//  if (fread(header, 1, 54, file) != 54) {
//    printf("Not correct\n");
//    return false;
//  }
//
//  if (header[0] != 'B' || header[1] != 'M') {
//    printf("Not correct\n");
//    return 0;
//  }
//  RGBTRIPLE rgb;
//  int j = 0;
//    dataPos = *(int *)&(header[0x0A]);
//    imageSize = *(int *)&(header[0x22]);
//    width = *(int *)&(header[0x12]);
//    height = *(int *)&(header[0x16]);
//
//  l_texture = (byte *)malloc(width * height * 4);
//
//  // And fill it with zeros
//  memset(l_texture, 0, width * height * 4);
//  // At this point we can read every pixel of the image
//    j=0;
//  for (int i = 0; i < width * height; i++) {
//    // We load an RGB value from the file
//    fread(&rgb, sizeof(rgb), 1, file);
//
//    // And store it
//    l_texture[j + 0] = rgb.rgbtRed;   // Red component
//    l_texture[j + 1] = rgb.rgbtGreen; // Green component
//    l_texture[j + 2] = rgb.rgbtBlue;  // Blue component
//    l_texture[j + 3] = 255;           // Alpha value
//    j += 4;                           // Go to the next position
//  }
//
//
//  data = new unsigned char[imageSize];
//
//  fread(data, 1, imageSize, file);
//
//  fclose(file);
//
//  GLuint textureID;
//  glGenTextures(1, &textureID);
//
//  glBindTexture(GL_TEXTURE_2D, textureID);
//
//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
//               GL_UNSIGNED_BYTE, data);
//
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
//                  GL_REPEAT); // If the u,v coordinates overflow the range 0,1
//                              // the image is repeated
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//                  GL_LINEAR); // The magnification function ("linear" produces
//                              // better results)
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//                  GL_LINEAR_MIPMAP_NEAREST); // The minifying function
//
//  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//               l_texture);
//
//  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE,
//                    l_texture);
//
//  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//  return textureID;
//}
//
//
//void DrawObj(FILE *fp)
//{
//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity(); // Initialize the model matrix as identity
//
//
//   obj = glGenLists(1);
//
//   char ch;
//   int i;
//   int res;
//   int id_texture;
//
//   Vertex *vertex = (Vertex *)malloc(1 * sizeof(Vertex));
//   int Ivertex = 0;
//
//   Normal *normal = (Normal *)malloc(1 * sizeof(Normal));
//   int Inormal = 0;
//
//   Texture *texture = (Texture *)malloc(1 * sizeof(Texture));
//   int Itexture = 0;
//
//   Face *face = (Face *)malloc(1 * sizeof(Face));
//   int temp = 0;
//
//   glColor3f(0.8, 0.2, 0.4);
//   glNewList(obj, GL_COMPILE);
//   while (1)
//   {
//       char lineHeader[128];
//       res = fscanf(fp, "%s", lineHeader);
//       if (res == EOF)
//           break;
//
//       if (strcmp(lineHeader, "v") == 0)
//       {
//           fscanf(fp, " %f %f %f", &vertex[Ivertex].x, &vertex[Ivertex].y, &vertex[Ivertex].z);
//
//           Ivertex++;
//           vertex = (Vertex *)realloc(vertex, (Ivertex + 1) * sizeof(Vertex));
//       }
//       else if (strcmp(lineHeader, "vn") == 0)
//       {
//           fscanf(fp, " %f %f %f", &normal[Inormal].x, &normal[Inormal].y, &normal[Inormal].z);
//
//           Inormal++;
//           normal = (Normal *)realloc(normal, (Inormal + 1) * sizeof(Normal));
//       }
//       else if (strcmp(lineHeader, "vt") == 0)
//       {
//           fscanf(fp, " %f %f", &texture[Itexture].x, &texture[Itexture].y);
//
//           Itexture++;
//           texture = (Texture *)realloc(texture, (Itexture + 1) * sizeof(Texture));
//       }
//       else if (strcmp(lineHeader, "f") == 0)
//       {
//           fscanf(fp, " %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &face[temp].v1, &face[temp].t1, &face[temp].n1, &face[temp].v2, &face[temp].t2, &face[temp].n2, &face[temp].v3, &face[temp].t3, &face[temp].n3, &face[temp].v4, &face[temp].t4, &face[temp].n4);
//
//           temp++;
//           face = (Face *)realloc(face, (temp + 1) * sizeof(Face));
//       }
//   }
//
//   printf("%d" , image);
//   glBindTexture(GL_TEXTURE_2D, image); // We set the active texture
//
//   glBegin(GL_QUADS);
//   for (i = 0; i < temp - 1; i++)
//   {
//       glTexCoord2f(texture[face[i].t1 - 1].x, texture[face[i].t1 - 1].y);
//       glNormal3f(normal[face[i].n1 - 1].x, normal[face[i].n1 - 1].y, normal[face[i].n1 - 1].z);
//       glVertex3f(vertex[face[i].v1 - 1].x, vertex[face[i].v1 - 1].y, vertex[face[i].v1 - 1].z);
//
//       glTexCoord2f(texture[face[i].t2 - 1].x, texture[face[i].t2 - 1].y);
//       glNormal3f(normal[face[i].n2 - 1].x, normal[face[i].n2 - 1].y, normal[face[i].n2 - 1].z);
//       glVertex3f(vertex[face[i].v2 - 1].x, vertex[face[i].v2 - 1].y, vertex[face[i].v2 - 1].z);
//
//       glTexCoord2f(texture[face[i].t3 - 1].x, texture[face[i].t3 - 1].y);
//       glNormal3f(normal[face[i].n3 - 1].x, normal[face[i].n3 - 1].y, normal[face[i].n3 - 1].z);
//       glVertex3f(vertex[face[i].v3 - 1].x, vertex[face[i].v3 - 1].y, vertex[face[i].v3 - 1].z);
//
//       glTexCoord2f(texture[face[i].t4 - 1].x, texture[face[i].t4 - 1].y);
//       glNormal3f(normal[face[i].n4 - 1].x, normal[face[i].n4 - 1].y, normal[face[i].n4 - 1].z);
//       glVertex3f(vertex[face[i].v4 - 1].x, vertex[face[i].v4 - 1].y, vertex[face[i].v4 - 1].z);
//   }
//   glEnd();
//
//   // glBegin(GL_POINTS);
//   // for (i = 0; i < Ivertex; i++){
//   //     glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
//   // }
//   // glEnd();
//
//   glEndList();
//   // glFlush(); // This force the execution of OpenGL commands
//   // glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
//
//
//   free(vertex);
//   free(normal);
//   free(texture);
//   free(face);
//}
//
//void Draw()
//{
//   glPushMatrix();
//   glTranslatef(0, -2, 0);
//   glScalef(0.4, 0.4, 0.4);
//   glRotatef(axisX, 1.0, 0.0, 0.0);
//   glRotatef(axisY, 0.0, 1.0, 0.0);
//   glCallList(obj);
//   glPopMatrix();
//}
//
//void display(void)
//{
//   glClearColor(0.0, 0.0, 0.0, 1.0);
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   Draw();
//   glutSwapBuffers();
//}
//
//void WindowSize(GLsizei w, GLsizei h)
//{
//   if (h == 0)
//       h = 1;
//   glViewport(0, 0, w, h);
//
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
//}
//
//void Keyboard(unsigned char key, int x, int y)
//{
//   if (key == 27)
//       exit(0);
//
//   else if (key == 'd')
//   {
//       axisY += 5;
//   }
//
//   else if (key == 'a')
//   {
//       axisY -= 5;
//   }
//
//   else if (key == 'w')
//   {
//       axisX += 5;
//   }
//
//   else if (key == 's')
//   {
//       axisX -= 5;
//   }
//   else if (key == 'z') {
//       glScalef(0.6, 0.6, 0.6);
//   }
//   glutPostRedisplay();
//}
//
//void mouse(int button, int state, int x, int y)
//{
//   if (state == 1)
//       return;
//   if (button == 3)
//       glScalef(1.1, 1.1, 1.1);
//   else if (button == 4)
//       glScalef(0.9, 0.9, 0.9);
//   glutPostRedisplay();
//}
//
//void init()
//{
//    glScalef(0.1, 0.1, 0.1);
//   glShadeModel(GL_SMOOTH);
//   glLoadIdentity();
//   glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
//   glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping
//   // Light values and coordinates
//   GLfloat whiteLight[] = {0.05f, 0.05f, 0.05f, 1.0f};
//   GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
//   GLfloat lightPos[] = {-10.f, 5.0f, 5.0f, 1.0f};
//
//   glEnable(GL_DEPTH_TEST); // Hidden surface removal
//   glFrontFace(GL_CW);      // Counter clock-wise polyrgons face out
//   glEnable(GL_CULL_FACE);  // Do not calculate inside
//
//   // Enable lighting
//   glEnable(GL_LIGHTING);
//
//   image = loadBMP_custom("Texture.bmp");
//
//   // Setup and enable light 0
//   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
//   glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
//   glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
//   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//   glEnable(GL_LIGHT0);
//
//   // Enable color tracking
//   glEnable(GL_COLOR_MATERIAL);
//
//   // Set Material properties to follow glColor values
//   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//   // Black blue background
//   glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
//}
//
//
//int main(int argc, char **argv)
//{
//
//   char *path = (char *)malloc(128 * sizeof(char));
////   puts("NAME!!!: ");
////   scanf(" %s", path);
//   FILE *fp = fopen("character.obj", "r");
//
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//
//   glutInitWindowSize(600, 800);
//   glutInitWindowPosition(0, 0);
//   glutCreateWindow(".obj file");
//   init();
//   glEnable(GL_CULL_FACE);
//
//   glutDisplayFunc(display);
//   glutKeyboardFunc(Keyboard);
//   glutMouseFunc(mouse);
//
//   DrawObj(fp);
//   fclose(fp);
//
//   glutMainLoop();
//
//   return 0;
//}


void display() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the viewport to be the top left corner of the window with a width and height of 300
    gluOrtho2D(-10, 10, 10, 10);
    glViewport(0, 0, 1000/2, 500/2);

//
//    // Draw the square using a line strip
//    glBegin(GL_POLYGON);
//    glColor3f(1, 1, 1);
//    glVertex2f(-1, 1);
//    glVertex2f(-1, -1);
//    glVertex2f(1, -1);
//    glVertex2f(1, 1);
//    glEnd();
//    glBegin(GL_POINTS);
//    glPointSize(50.0f);
//    glColor3f(1, 1, 1);
//    glVertex2f(0, 0);
//
//    glEnd();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glVertex2f(-1, 1);
        glVertex2f(-1, -1);
        glVertex2f(1, -1);
        glVertex2f(1, 1);
        glEnd();
    glPointSize(50.0f);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POINTS);
    glVertex3f(1, 0, 0);
    glEnd();
    glTranslatef(1, 0, 0);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POINTS);
    glVertex3f(1, 0, 0);
    glEnd();
    glRotatef(90, 1, 0, 0);
//    glColor3f(0.7, 0.7, 0.7);
//    glBegin(GL_POINTS);
//    glVertex3f(1, 0, 0);
//    glEnd();
    glRotatef(90, 0, 1, 0);
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POINTS);
    glVertex3f(1, 0, 0);
    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("hello");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
