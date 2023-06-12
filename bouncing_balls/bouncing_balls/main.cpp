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
#define LOW -10
#define HIGH 10
#define n 2 // ardaas ni neg chigleld murgulduhiig shiid


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
    struct node* next;
 
} Node;

typedef struct PQ {
    Node *node;
    int len;
} PQ;

void timer(int);
void drawCircle(Ball*);

 
// Function to Create A New Node
Node* newNode(Event event)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->e = event;
    temp->next = NULL;
    return temp;
}
//Ball *balls = (Ball *) malloc(sizeof(Ball) * n);
Ball balls[n];
Event e = {0, NULL, NULL, 0, 0};
Node *pq = newNode(e);
GLdouble dt = 0.1;
Ball *tmp1;
Ball *tmp2;
int size = 0;
void swap(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

// Function to heapify the tree
void heapify(int array[], int size, int i) {
  if (size == 1) {
    printf("Single element in the heap");
  } else {
    // Find the largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && array[l] > array[largest])
      largest = l;
    if (r < size && array[r] > array[largest])
      largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&array[i], &array[largest]);
      heapify(array, size, largest);
    }
  }
}

// Function to insert an element into the tree
void insert(int array[], int newNum) {
  if (size == 0) {
    array[0] = newNum;
    size += 1;
  } else {
    array[size] = newNum;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(array, size, i);
    }
  }
}

// Function to delete an element from the tree
void deleteRoot(int array[], int num) {
  int i;
  for (i = 0; i < size; i++) {
    if (num == array[i])
      break;
  }

  swap(&array[i], &array[size - 1]);
  size -= 1;
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(array, size, i);
  }
}

// Print the array
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i)
    printf("%d ", array[i]);
  printf("\n");
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
 
// Removes the element with the
// highest priority from the list
int popN = 0;
Event pop(Node** head)
{
//    printf("popping\n");
//    printf("%d", ++popN);
    Node* temp = *head;
    //Event e = {0, NULL, NULL, 0, 0};
    
    (*head) = (*head)->next;
    Event e = temp->e;
    free(temp);
    return e;
}
 
// Function to push according to priority
void push(Node** head, Event event)
{
    Node* start = (*head);
 
    // Create new Node
    Node* temp = newNode(event);
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->e.time > event.time) {
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL && start->next->e.time &&
            start->next->e.time < event.time) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}
 
int isEmpty(Node** head)
{
    if ((*head) == NULL) {
        return 0;
    }
    return 1;
//    return (*head) == NULL;
}


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
//        dt = (ball->bally - 0 + ball->r - ball->r) / -ball->speedy;
        dt = (int)(ball->bally) / -ball->speedy;
    } else {
        dt = (int)(winHeight - ball->bally - ball->r - ball->r) / ball->speedy;
    }
    return dt;
}
float timeToHitHorizontalWall(Ball *ball) {
    float dt;
    if (ball->speedx < 0) {
//        dt = (ball->ballx - ::dt) / -ball->speedx;
        dt = (ball->ballx) / -ball->speedx;
    } else {
        dt = (winWidth - ball->ballx - ball->r - ball->r) / ball->speedx;
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
}

void bounceOff(Ball *ball1, Ball *ball2) {
    tmp1 = ball1;
    tmp2 = ball2;
    printf("before bounce off");
    if (ball1 == NULL || ball2 == NULL) return;
    printf("bounceoff");
    
    double dx = ball2->ballx - ball1->ballx, dy = ball2->bally - ball1->bally;
    double dvx = ball2->speedx - ball1->speedx, dvy = ball2->speedy - ball1->speedy;
    double dvdr = dx*dvx + dy*dvy;
    double dist = ball1->r + ball2->r;
    double J = 2 * ball1->mass * ball2->mass * dvdr / ((ball1->mass + ball2->mass) * dist);
//    double Jx = J * dx / dist;
//    double Jy = J * dy / dist;
    
//    ball1->speedx += Jx / ball1->mass;
//    ball1->speedy += Jy / ball1->mass;
//    ball2->speedx -= Jx / ball2->mass;
//    ball2->speedy -= Jy / ball2->mass;
    
    if ((ball1->speedx < 0 && ball2->speedx >= 0) || (ball2->speedx < 0 && ball1->speedx >= 0)) {
        ball1->speedx = -ball1->speedx;
        ball2->speedx = -ball2->speedx;
    } else if ((ball1->speedy < 0 && ball2->speedy >= 0) || (ball2->speedy < 0 && ball1->speedy >= 0)){
        ball1->speedy = -ball1->speedy;
        ball2->speedy = -ball2->speedy;
    }
//    ball1->count++;
//    ball2->count++;
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
        push(&pq, e);
    }
    Event e1 = {timeToHitVerticalWall(ball), ball, NULL};
    Event e2 = {timeToHitHorizontalWall(ball), NULL, ball};
    push(&pq, e1);
    push(&pq, e2);
}

void move(Ball *ball, double dt) {
    ball->ballx = ball->ballx + ball->speedx*dt;
    ball->bally = ball->bally + ball->speedy*dt;
//    GLfloat rx = ball->ballx;
//    GLfloat ry = ball->bally;
//    GLfloat vx = ball->speedx;
//    GLfloat vy = ball->speedy;
//    if ((rx + vx*dt < 0) || (rx + vx*dt > winWidth - ball->r - ball->r)) {
//        ball->speedx = -ball->speedx;
//    }
//    if ((ry + vy*dt < 0) || (ry + vy*dt > winHeight - ball->r - ball->r)) {
//        ball->speedy = -ball->speedy;
//    }
    //glutPostRedisplay();
//    float r = ball->r;
//    ball->ballx += ball->speedx;
//    ball->bally += ball->speedy;
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
}

int isValid(Event *event) {
    if ((event->countA > event->countB || event->countB > event->countA) && isinf(event->time) == 1) {
        return 0;
    }
    if (isinf(event->time) == 1) {
        return 0;
    }
//    if (event->a == NULL && event->b == NULL) {
//        return 0;
//    }
//    if (tmp1 == event->b && tmp2 == event->a) {
//        tmp1 = NULL;
//        tmp2 = NULL;
//        return 0;
//    }
    if (event->time <= dt) {
        return 1;
    }
    return 0;
}

bool isEqual(float a, float b)
{
 
    // Correct method to compare
    // floating-point numbers
    if (abs(a - b) < 1e-9) {
        return true;
    }
    else {
        return false;
    }
}
 

void simulate(Node *pq, Ball *ball) {
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
    if (isgreaterequal(t, pq->e.time)) {
//        while (isEmpty(&pq) != 0) {
            Event event;
            event = pop(&pq);
        if (isValid(&event) == 0) {
            glutPostRedisplay();
            return;
        }
            Ball *a = event.a;
            Ball *b = event.b;

    //        t = event.time;
            for (i = 0; i < n; i++) {
                move(&balls[i], dt);
            }

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

            predict(a);
            predict(b);
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
        glVertex2f(r*cos(theta)+r+xstep, r*sin(theta)+r+ystep);
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
    for (i = 0; i < n; i++) {
        //move(&balls[i], dt);
        drawCircle(&balls[i]);
    }
    simulate(pq, balls);
    glutSwapBuffers();
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
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int) {
//    int i;
//    for (i = 0; i < n; i++) {
//        Ball *ball = &balls[i];
//        float r = ball->r;
//        ball->ballx += ball->speedx;
//        ball->bally += ball->speedy;
//        float randomx = ball->randomx;
//        float randomy = ball->randomy;
//        if (ball->bally+r > winHeight-r){
//            ball->speedy = -ball->speedy;
//        } else if (ball->bally+r < r) {
//            ball->speedy = -ball->speedy;
//        }
//        if (ball->ballx+r > winWidth-r) {
//            ball->speedx = -ball->speedx;
//        } else if (ball->ballx+r < r) {
//            ball->speedx = -ball->speedx;
//        }
//    }
//
//    glutPostRedisplay();
//    glutTimerFunc(1000/100, timer, 0);
//    simulate(pq, balls);
//    int i;
//    for (i = 0; i < n; i++) {
//        move(&balls[i], dt);
//    }
//    simulate(pq, balls);
//    simulate(pq, balls);
//    Event e = {0, NULL, NULL, 0, 0};
//    pq = newNode(e);
    t += dt;
    glutTimerFunc(dt, timer, 0);
}

void setup(void) {
//    memset(balls, 0, sizeof balls);
    glClearColor(0, 0, 0, 1.0f);
    int i;
    Ball tmp[n];
    for (i = 0; i < n; i++) {
        //printf("\nwtf\n");
        Ball ball;
        ball.r = (rand() % 4) + 3;
        ball.ballx = rand() % 250;
        ball.bally = rand() % 250;
        ball.speedx = (rand() % (HIGH - LOW + 1)) + LOW;
        ball.speedy = (rand() % (HIGH - LOW + 1)) + LOW;
        ball.mass = (rand() % (200 - 150 + 1)) + 150;
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
    pq = newNode(e);
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
    glutTimerFunc(0, timer, 0);
//    glutMouseFunc(mouse);
//    glutKeyboardFunc(keyboard);
    glutMainLoop();
    printf("balls freed");
    return EXIT_SUCCESS;
}

