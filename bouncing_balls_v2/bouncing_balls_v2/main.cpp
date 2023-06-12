//
//  main.cpp
//  bouncing_balls
//
//  Created by Tsenguun Otgonbaatar on 2022.10.27.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <string.h>

#define PI 3.14159f
#define LOW -20
#define HIGH 20
#define n 11
// ardaas ni neg chigleld murgulduhiig shiid


#define defaultS 1

GLfloat winWidth, winHeight;
float t = 0.0;
bool shouldUpdate = true;



struct ball {
    GLfloat r;
    GLfloat ballx;
    GLfloat bally;
    GLfloat speedx;
    GLfloat speedy;
    GLfloat mass;
    GLsizei count;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};

typedef ball Ball;

struct event {
    float time = 0;
    Ball *a, *b;
    GLsizei countA, countB;
};

typedef event Event;

typedef struct node {
    Event e;
 
} Node;

typedef struct PQ {
    Node *node;
    int len;
} PQ;

void timer(int);
void drawCircle(Ball*);

 
//Ball *balls = (Ball *) malloc(sizeof(Ball) * n);
Ball balls[n];
Event e = {0, NULL, NULL, 0, 0};
Node pq[100000];
GLdouble dt = 0.01;
int size = 0;

void swap(Node *a, Node *b) {
  Node temp = *b;
  *b = *a;
  *a = temp;
}

// Function to heapify the tree
void heapify(Node array[], int size, int i) {
  if (size == 1) {
      return;
  } else {
    // Find the largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && array[l].e.time < array[largest].e.time)
      largest = l;
    if (r < size && array[r].e.time < array[largest].e.time)
      largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&array[i], &array[largest]);
      heapify(array, size, largest);
    }
  }
}

// Function to insert an element into the tree
void insert(Node array[], Event e) {
  if (size == 0) {
    array[0].e = e;
    size += 1;
  } else {
    array[size].e = e;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(array, size, i);
    }
  }
}

// Function to delete an element from the tree
Event deleteRoot(Node array[]) {
    Event e = array[0].e;
    swap(&array[0], &array[size - 1]);
    size -= 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(array, size, i);
    }
    return e;
}


// Driver code
//int main() {
//  int array[10];
//
//  insert(array, 3);
//  insert(array, 4);
//  insert(array, 9);
//  insert(array, 5);
//  insert(array, 2);
//
//  printf("Max-Heap array: ");
//  printArray(array, size);
//
//  deleteRoot(array, 4);
//
//  printf("After deleting an element: ");
//
//  printArray(array, size);
//}
//
// Return the value at head
//int peek(Node** head)
//{
//    return (*head)->data;
//}



int compareTo(Event *e1, Event *e2) {
    return e1->time - e2->time;
}

//int isValid(Event e1, Event e2) {
//
//}
// asuudal ened baina !!!
float timeToHit(Ball *ball1, Ball *ball2) {
    if (ball1 == ball2) return INFINITY;
    float dx = ball2->ballx - ball1->ballx, dy = ball2->bally - ball1->bally;
    float dvx = ball2->speedx - ball1->speedx, dvy = ball2->speedy - ball1->speedy;
    float dvdr = dx*dvx + dy*dvy;
    if (dvdr > 0) return INFINITY;
    float dvdv = dvx*dvx + dvy*dvy;
    float drdr = dx*dx + dy*dy;
    float sigma = ball1->r + ball2->r;
    float d = (dvdr*dvdr) - dvdv * (drdr - sigma*sigma);
    if (d < 0) return INFINITY;
    return (-(dvdr + sqrt(d)) / dvdv);
}

float timeToHitVerticalWall(Ball *ball) {
    float dt;
    if (ball->speedy < 0) {
//        dt = (ball->bally - 0 + ball->r + ball->r) / -ball->speedy;
//        dt = (ball->r - ball->bally) / ball->speedy;
        dt = (ball->bally) / -ball->speedy;
    } else if (ball->speedy > 0){
        dt = (winHeight - ball->bally - ball->r - ball->r) / ball->speedy;
//        dt = (winHeight - ball->r - ball->bally) / ball->speedy;
    } else {
        return INFINITY;
    }
    return dt;
}


float timeToHitHorizontalWall(Ball *ball) {
    float dt;
    if (ball->speedx < 0) {
//        dt = (ball->ballx - ::dt) / -ball->speedx;
//        dt = (ball->r - ball->ballx) / ball->speedx;
        dt = (ball->ballx) / -ball->speedx;
    } else if (ball->speedx > 0) {
//        dt = (winWidth - ball->ballx - ball->r - ball->r) / ball->speedx;
        dt = (winWidth - ball->r - ball->ballx) / ball->speedx;
    } else {
        return INFINITY;
    }
    return dt;
}

void bounceOffVerticalWall(Ball *ball) {
//    float r = ball->r;
//    ball->ballx += ball->speedx;
//    ball->bally += ball->speedy;
//    float randomx = ball->randomx;
//    float randomy = ball->randomy;
//    if (ball->bally+r > winHeight-r){
//        ball->speedy = -ball->speedy;
//    } else if (ball->bally+r < r) {
//        ball->speedy = -ball->speedy;
//    }
//    if (ball->ballx+r > winWidth-r) {
//        ball->speedx = -ball->speedx;
//    } else if (ball->ballx+r < r) {
//        ball->speedx = -ball->speedx;
//    }
//    ball->speedy = -ball->speedy;
//    ball->bally = winWidth - ball->r;
//    ball->ballx = ball->ballx + ball->speedx * dt;
    printf("\nvertical\n");
    ball->speedy = -ball->speedy;
    if (ball->speedy >= 0) {
        ball->bally = ball->bally + ball->speedy*dt;
    } else {
        ball->bally = ball->bally - ball->speedy*dt;
    }
    ball->ballx = ball->ballx + ball->speedx * dt;
}

void bounceOffHorizontalWall(Ball *ball) {
//    float r = ball->r;
//    ball->ballx += ball->speedx;
//    ball->bally += ball->speedy;
//    float randomx = ball->randomx;
//    float randomy = ball->randomy;
//    if (ball->bally+r > winHeight-r){
//        ball->speedy = -ball->speedy;
//    } else if (ball->bally+r < r) {
//        ball->speedy = -ball->speedy;
//    }
//    if (ball->ballx+r > winWidth-r) {
//        ball->speedx = -ball->speedx;
//    } else if (ball->ballx+r < r) {
//        ball->speedx = -ball->speedx;
//    }
    printf("\nhorizontal\n");
    ball->speedx = -ball->speedx;
    if (ball->speedx >= 0) {
        ball->ballx = ball->ballx + ball->speedx*dt;
    } else {
        ball->ballx = ball->ballx - ball->speedx*dt;
    }
    ball->bally = ball->bally + ball->speedy * dt;
    ball->count++;
}

void bounceOff(Ball *ball1, Ball *ball2) {
    printf("before bounce off");
    if (ball1 == NULL || ball2 == NULL) return;
    printf("bounceoff");
    
    double dx = ball2->ballx - ball1->ballx, dy = ball2->bally - ball1->bally;
    double dvx = ball2->speedx - ball1->speedx, dvy = ball2->speedy - ball1->speedy;
    double dvdr = dx*dvx + dy*dvy;
    double dist = ball1->r + ball2->r;
    double J = 2 * ball1->mass * ball2->mass * dvdr / ((ball1->mass + ball2->mass) * dist);
    double Jx = J * dx / dist;
    double Jy = J * dy / dist;
    
    ball1->speedx += Jx / ball1->mass;
    ball1->speedy += Jy / ball1->mass;
    ball2->speedx -= Jx / ball2->mass;
    ball2->speedy -= Jy / ball2->mass;
    
//    if ((ball1->speedx < 0 && ball2->speedx >= 0) || (ball2->speedx < 0 && ball1->speedx >= 0)) {
//        ball1->speedx = -ball1->speedx;
//        ball2->speedx = -ball2->speedx;
//    } else if ((ball1->speedy < 0 && ball2->speedy >= 0) || (ball2->speedy < 0 && ball1->speedy >= 0)){
//        ball1->speedy = -ball1->speedy;
//        ball2->speedy = -ball2->speedy;
//    }
    ball1->count++;
    ball2->count++;
}

void predict(Ball *ball) {
    int i = 0;
    if (ball == NULL) return;
    for (i = 0; i < n; i++) {
        double dt = timeToHit(ball, &balls[i]);
        //printf("%lf\n", dt);
        Event e;
        e.time = t + dt;
        e.a = ball;
        e.b = &balls[i];
        e.countA = ball->count;
        e.countB = balls[i].count;
        if (t + dt < INFINITY) {
            insert(pq, e);
        }
    }
    if (t + timeToHitVerticalWall(ball) < INFINITY) {
        Event e1 = {t + timeToHitVerticalWall(ball), ball, NULL};
        e1.countA = ball->count;
        insert(pq, e1);
    }
    if (t + timeToHitHorizontalWall(ball) < INFINITY) {
        Event e2 = {t + timeToHitHorizontalWall(ball), NULL, ball};
        e2.countB = ball->count;
        insert(pq, e2);
    }
}

void move(Ball *ball, double dt) {
    ball->ballx = ball->ballx + ball->speedx*dt;
    ball->bally = ball->bally + ball->speedy*dt;
}

int isValid(Event *event) {
//    if ((event->countA > event->countB || event->countB > event->countA) && isinf(event->time) == 1) {
//        return 0;
//    }
    if (isinf(event->time) == 1) {
        return 0;
    }
    if (event->a && !event->b) {
        if (event->countA != event->a->count) {
            return 0;
        } else {
            return 1;
        }
    } else if (event->b && !event->a) {
        if (event->countB != event->b->count) {
            return 0;
        } else {
            return 1;
        }
    } else if (event->a && event->b) {
        if (event->countA != event->a->count || event->countB != event->b->count) {
            return 0;
        } else {
            return 1;
        }
    }
//    if (event->a == NULL && event->b == NULL) {
//        return 0;
//    }
//    if (tmp1 == event->b && tmp2 == event->a) {
//        tmp1 = NULL;
//        tmp2 = NULL;
//        return 0;
//    }
    if (event->time <= t) {
        return 1;
    }
    return 0;
}

void simulate(Node pq[], Ball ball[]) {
//    Node tmpo = {NULL, NULL};
//    *pq = {NULL, NULL};
    int i;
    if (shouldUpdate) {
        for (i = 0; i < n; i++) {
            predict(&balls[i]);
        }
    }
    shouldUpdate = false;
//    Event e = {0, NULL, NULL, 0, 0};
//    pq = newNode(e);
    // pq->e != NULL
//    t = roundf(t * 100) / 100;
//    float ti = roundf(pq->e.time * 100) / 100;
//    if (isgreaterequal(t, ti)) {
//        Event event;
//        event = pop(&pq);
//        Ball *a = event.a;
//        Ball *b = event.b;
//        if (a != NULL && b != NULL) bounceOff(a, b);
//        else if (a != NULL && b == NULL) bounceOffVerticalWall(a);
//        else if (a == NULL && b != NULL) bounceOffHorizontalWall(b);
//        else if (a == NULL && b == NULL) {
////            timer(0);
//            glutPostRedisplay();
////            return;
//
////            glutSwapBuffers();
//        };
//    }
    while (isgreaterequal(t, pq->e.time)) {
//        while (isEmpty(&pq) != 0) {
            Event event;
            event = deleteRoot(pq);
        if (isValid(&event) == 0) {
            for (i = 0; i < n; i++) {
                move(&balls[i], dt);
            }
            glutPostRedisplay();
            return;
        }
            Ball *a = event.a;
            Ball *b = event.b;

            t = event.time;

            if (a != NULL && b != NULL) bounceOff(a, b);
            else if (a != NULL && b == NULL) bounceOffVerticalWall(a);
            else if (a == NULL && b != NULL) bounceOffHorizontalWall(b);
            else if (a == NULL && b == NULL) {
                glutPostRedisplay();
                return;
    //            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //        //    printf("displaying");
    //            int i;
    //
    //            for (i = 0; i < n; i++) {
    //                //move(&balls[i], dt);
    //                drawCircle(&balls[i]);
    //            }
    //            glutSwapBuffers();
    //            simulate(pq, balls);
    //            Event e = {0, NULL, NULL, 0, 0};
    //            pq = newNode(e);
            };
        for (i = 0; i < n; i++) {
            move(&balls[i], dt);
        }

            predict(a);
            predict(b);
        glutPostRedisplay();
        return;
    }
        for (i = 0; i < n; i++) {
            move(&balls[i], dt);
        }
    
//    }
//    while (isEmpty(&pq) != 0) {
//        Event event;
//        event = pop(&pq);
//        if (isValid(&event) == 0) continue;
//        Ball *a = event.a;
//        Ball *b = event.b;
//
////        t = event.time;
//        for (i = 0; i < n; i++) {
//            move(&balls[i], dt);
//        }
//
//        if (a != NULL && b != NULL) bounceOff(a, b);
//        else if (a != NULL && b == NULL) bounceOffVerticalWall(a);
//        else if (a == NULL && b != NULL) bounceOffHorizontalWall(b);
//        else if (a == NULL && b == NULL) {
//            glutPostRedisplay();
//            return;
////            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////        //    printf("displaying");
////            int i;
////
////            for (i = 0; i < n; i++) {
////                //move(&balls[i], dt);
////                drawCircle(&balls[i]);
////            }
////            glutSwapBuffers();
////            simulate(pq, balls);
////            Event e = {0, NULL, NULL, 0, 0};
////            pq = newNode(e);
//        };
//
//        predict(a);
//        predict(b);
//    }
//    for (i = 0; i < n; i++) {
//        move(&balls[i], dt);
//    }
    glutPostRedisplay();
}


void drawCircle(Ball *ball) {
    int i;
    float r = ball->r;
    int xstep = ball->ballx;
    int ystep = ball->bally;
    //glColor3f(0.5f, 0.0f, 1.0f); // (0.5, 0, 1) is half red and full blue, giving dark purple.
    glColor3f(ball->red, ball->green, ball->blue);
    glBegin(GL_POLYGON);
    for (i = 0; i < 50; i++) {
        float theta = (2*PI*i)/50;
        glVertex2f(r*cos(theta)+xstep, r*sin(theta)+ystep);
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    printf("displaying");
    int i;
//    for (i = 0; i < n; i++) {
//        move(&balls[i], 1);
//    }
//    glutPostRedisplay();
    for (i = 0; i < n; i++) {
//        move(&balls[i], dt);
        drawCircle(&balls[i]);
    }
    glutSwapBuffers();
    simulate(pq, balls);
    t += dt;
}

void resize(GLsizei w, GLsizei h) {
    if (h == 0) h=1;
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
    
    printf("width: %.2f\n", winWidth);
    printf("height: %.2f\n", winHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//void timer(int) {
////    int i;
////    for (i = 0; i < n; i++) {
////        Ball *ball = &balls[i];
////        float r = ball->r;
////        ball->ballx += ball->speedx;
////        ball->bally += ball->speedy;
////        float randomx = ball->randomx;
////        float randomy = ball->randomy;
////        if (ball->bally+r > winHeight-r){
////            ball->speedy = -ball->speedy;
////        } else if (ball->bally+r < r) {
////            ball->speedy = -ball->speedy;
////        }
////        if (ball->ballx+r > winWidth-r) {
////            ball->speedx = -ball->speedx;
////        } else if (ball->ballx+r < r) {
////            ball->speedx = -ball->speedx;
////        }
////    }
////
////    glutPostRedisplay();
////    glutTimerFunc(1000/100, timer, 0);
////    simulate(pq, balls);
////    int i;
////    for (i = 0; i < n; i++) {
////        move(&balls[i], dt);
////    }
////    simulate(pq, balls);
////    simulate(pq, balls);
////    Event e = {0, NULL, NULL, 0, 0};
////    pq = newNode(e);
//    glutTimerFunc(dt, timer, 0);
//}

void setup(void) {
//    memset(balls, 0, sizeof balls);
    glClearColor(0, 0, 0, 1.0f);
    int i;
    Ball tmp[n];
    for (i = 0; i < n; i++) {
        //printf("\nwtf\n");
        Ball ball;
        ball.r = (rand() % 4) + 3;
//        ball.r = 2;
        ball.ballx = rand() % 313;
        ball.bally = rand() % 250;
//        ball.speedx = (rand() % (HIGH - LOW + 1)) + LOW;
//        ball.speedy = (rand() % (HIGH - LOW + 1)) + LOW;
        ball.speedx = 20;
        ball.speedy = 20;
//        ball.mass = (rand() % (5 - 3 + 1)) + 3;
        ball.mass = 5;
        ball.count = 0;
        ball.red = rand() / (double)RAND_MAX;
        ball.green = rand() / (double)RAND_MAX;
        ball.blue = rand() / (double)RAND_MAX;
        tmp[i] = ball;
        //printf("%f", balls[i].red);
    }
    for (i = 0; i < n; i++) {
        balls[i] = tmp[i];
    }
    Event e = {0, NULL, NULL, 0, 0};
    Node node;
    node.e = e;
    pq[0] = node;
    size++;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("Balls");
    setup();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    //glutTimerFunc(0, timer, 0);
//    glutMouseFunc(mouse);
//    glutKeyboardFunc(keyboard);
    glutMainLoop();
    printf("balls freed");
    return EXIT_SUCCESS;
}

