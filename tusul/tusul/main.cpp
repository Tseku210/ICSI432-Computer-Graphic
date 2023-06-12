//
//  main.cpp
//  tusul
//
//  Created by Tsenguun Otgonbaatar on 2022.12.01.
//

//#include <GLUT/glut.h>
#include <GLUT/GLUT.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;
void loadLevel1();
void loadLevel2();
void loadLevel3();
string level1, level2, level3;


int winHeight, winWidth;
unsigned int basewall, brick, pipe;
unsigned int mario, question, enemy;
unsigned int cloud, bush, hill, castle;

unsigned int loadTexture(const char *filename)
{
    SDL_Surface *img = SDL_LoadBMP(filename);
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
//    cout << img->w << " " << img->h << img->pixels << endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(img);
    return id;
}

void reshape(int w, int h)
{
//    if (h == 0)
//        h = 1;
////    float ratio = w * 1.0 / h;
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glViewport(0, 0, w, h);
////    gluPerspective(45, ratio, 1, 100);
////    glOrtho(0, 64, 0, 16, -10, 10);
////    glOrtho(0, 1000, 0 , 1000, -10, 10);
////    gluOrtho2D(0, 64*10, -16*10, 0);
////    gluOrtho2D(-1000, 1000, 1000, -1000);
//        gluOrtho2D(0, w, h, 0);
//    glMatrixMode(GL_MODELVIEW);
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
    glOrtho(0,winWidth,winHeight,0,1,-1);



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
string level;
int rightKeyPressed = 0;
int leftKeyPressed = 0;
int rightKey = 1;
int leftKey = 0;

//testing
int levelWidth, levelHeight;
float cameraX = 0.0f, cameraY = 0.0f;
float playerPosX = 0.0f, playerPosY = 0.0f;
float playerVelX = 0.0f, playerVelY = 0.0f;
float enemyVelx = 0.0f, enemyVelY = 0.0f;
float enemyPosx = 0.0f, enemyPosY = 0.0f;
int upKeyPressed = 0, bottomKeyPressed = 0;
bool playerOnGround = false;

char getTile(int x, int y) {
    if (x >= 0 && x < levelWidth && y >= 0 && y < levelWidth) {
        return level[y*levelWidth+x];
    } else
        return ' ';
}
void setTile(int x, int y, int c) {
    if (x >= 0 && levelWidth && y >= 0 && y < levelWidth) {
        level[y*levelWidth+x] = c;
    }
}
void fill(unsigned int texture, float a, float b, float c, float d, float red, float green, float blue) {
    if (texture)
        glBindTexture(GL_TEXTURE_2D, texture);
//    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
        glVertex3f(a, b, 0);
    glTexCoord2f(0.0f, 1.0f);
        glVertex3f(a, d, 0);
    glTexCoord2f(1.0f, 1.0f);
        glVertex3f(c, d, 0);
    glTexCoord2f(1.0f, 0.0f);
        glVertex3f(c, b, 0);
    glEnd();
}

void drawWall(float a, float b, float c, float d) {
    glBindTexture(GL_TEXTURE_2D, basewall);
//    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
        glVertex3f(a, b, 0);
    glTexCoord2f(0.0f, 1.0f);
        glVertex3f(a, d, 0);
    glTexCoord2f(1.0f, 1.0f);
        glVertex3f(c, d, 0);
    glTexCoord2f(1.0f, 0.0f);
        glVertex3f(c, b, 0);
    glEnd();
}

void drawSky(float a, float b, float c, float d) {
//    glColor3f(0.48235, 0.47451, 1.00000);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(a, b, 0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(a, d, 0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(c, d, 0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(c, b, 0);
    glEnd();
}

void drawMario(float a, float b, float c, float d) {
    if (leftKey) {
        glBindTexture(GL_TEXTURE_2D, mario);
    //    glColor3f(0.48235, 0.47451, 1.00000);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0, 0.0);
            glVertex3f(a, b, 0);
        glTexCoord2f(1.0, 1.0);
            glVertex3f(a, d, 0);
        glTexCoord2f(0.0, 1.0);
            glVertex3f(c, d, 0);
        glTexCoord2f(0.0, 0.0);
            glVertex3f(c, b, 0);
        glEnd();
        return;
    }
    glBindTexture(GL_TEXTURE_2D, mario);
//    glColor3f(0.48235, 0.47451, 1.00000);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
        glVertex3f(a, b, 0);
    glTexCoord2f(0.0, 1.0);
        glVertex3f(a, d, 0);
    glTexCoord2f(1.0, 1.0);
        glVertex3f(c, d, 0);
    glTexCoord2f(1.0, 0.0);
        glVertex3f(c, b, 0);
    glEnd();
}
void processSpecialKeys2(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT :
            leftKeyPressed = 1;
            leftKey = 1;
            rightKey = 0;
            break;
        case GLUT_KEY_RIGHT :
            rightKeyPressed = 1;
            leftKey = 0;
            rightKey = 1;
            break;
        case GLUT_KEY_UP :
            upKeyPressed = 1;
//            playerPosY += 1;
//            if (y == 0)
//                jump = 1;
            break;
        case GLUT_KEY_DOWN :
            bottomKeyPressed = 1;
//            playerPosY -= 1;
            break;
        case 32:
            if (playerVelY == 0)
                playerVelY = -3.0f;
            break;
    }
}
void processSpecialUpKeys2(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT :
            leftKeyPressed = 0;
            break;
        case GLUT_KEY_RIGHT :
            rightKeyPressed = 0;
            break;
        case GLUT_KEY_UP :
            upKeyPressed = 0;
            break;
        case GLUT_KEY_DOWN :
            bottomKeyPressed = 0;
            break;
    }
}
void init() {
    levelWidth = 100;
    levelHeight = 30;
    loadLevel1();
//    glClearColor(0.48,0.47,1.0,1.0);    //background color and alpha
//    glOrtho(0.0,1360.0,0.0,760.0,-10.0,10.0);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    // glMatrixMode(GL_PROJECTION);
//    // glLoadIdentity();
//    // gluPerspective(45,640.0/480.0,1.0,600.0);
//    // glMatrixMode(GL_MODELVIEW);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_TEXTURE_2D);

    basewall = loadTexture("../images/newbase.bmp");
    brick = loadTexture("../images/brick.bmp");
    mario = loadTexture("../images/mario.bmp");
    castle = loadTexture("../images/castle.bmp");
//    question = loadTexture("../media/bmps/question.bmp");
    cloud = loadTexture("../images/cloud.bmp");
//    bush = loadTexture("../media/bmps/bush.bmp");
//    hill = loadTexture("../media/bmps/hill.bmp");
//    pipe = loadTexture("../media/bmps/pipe.bmp");
    enemy = loadTexture("../images/enemy.bmp");
}
//int vel = 1;
//void updateEnemy(int x, int y) {
//    if (getTile(x+vel, y) == '#')
//        check = -vel;
//    setTile(x, y) = '.';
//    setTile(x+vel, y) = '*';
//}
void newRenderScene(void) {
    // Clear Color and Depth Buffers
    glClearColor(0.48235, 0.47451, 1.00000, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    
    //on user update;
    int tileWidth = 16, tileHeight = 16;
    int visibleTileX = winWidth / tileWidth;
    int visibleTileY = winHeight / tileHeight;
    
    float offsetX = cameraX - visibleTileX / 2.0f;
    float offsetY = cameraY - visibleTileY / 2.0f;
    
    if (offsetX < 0) offsetX = 0;
    if (offsetY < 0) offsetY = 0;
    if (offsetX > levelWidth - visibleTileX) offsetX = levelWidth - visibleTileX;
    if (offsetY > levelHeight - visibleTileY) offsetY = levelHeight - visibleTileY;
    
    float tileOffsetX = (offsetX - (int)offsetX)*tileWidth;
    float tileOffsetY = (offsetY - (int)offsetY)*tileHeight;
    
//    playerVelX = 0.0f;
//    playerVelY = 0.0f;
    
    if (rightKeyPressed) {
//        playerPosX += 1 * 0.6;
        playerVelX += (playerOnGround ? 1.3f : 0.5f) * 0.1;
    }
    if (leftKeyPressed) {
//        playerPosX -= 1 * 0.6;
        playerVelX += (playerOnGround ? -1.3f : -0.5f) * 0.1;
    }
    if (upKeyPressed) {
//        playerPosY -= 1 * 0.6f;
        playerVelY = -1;
    }
    if (bottomKeyPressed) {
//        playerPosY += 1 * 0.6f;
        playerVelY = 1;
    }
    
    playerVelY += 1.0f * 0.1;
    
    if (playerOnGround) {
        playerVelX += -1.0f * playerVelX * 0.1;
        if (abs(playerVelX) < 0.01f) {
            playerVelX = 0.0f;
        }
    }
    
    float newPlayerPosX = playerPosX + playerVelX * 0.1;
    float newPlayerPosY = playerPosY + playerVelY * 0.1;
    
    if (playerVelX > 1.0f) {
        playerVelX = 1.0f;
    }
    if (playerVelX < -1.0f) {
        playerVelX = -1.0f;
    }
    if (playerVelY > 100.0f) {
        playerVelY = 100.0f;
    }
    if (playerVelY < -3.0f) {
        playerVelY = -3.0f;
    }
    
    if (playerVelX <= 0) {
        if (getTile(newPlayerPosX + 0.0f, playerPosY + 0.0f) != '.' || getTile(newPlayerPosX + 0.0f, playerPosY + 0.9f) != '.') {
            newPlayerPosX = (int)newPlayerPosX + 1;
            playerVelX = 0;
        }
    }else {
        if (getTile(newPlayerPosX + 1.0f, playerPosY + 0.0f) != '.' || getTile(newPlayerPosX + 1.0f, playerPosY + 0.9f) != '.') {
            newPlayerPosX = (int)newPlayerPosX;
            playerVelX = 0;
        }
    }
    playerOnGround = false;
    if (playerVelY <= 0) {
        if (getTile(newPlayerPosX + 0.0f, newPlayerPosY) != '.' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 0.0f) != '.') {
            newPlayerPosY = (int)newPlayerPosY + 1;
            playerVelY = 0;
        }
    } else {
        if (getTile(newPlayerPosX + 0.0f, newPlayerPosY + 1.0f) != '.' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 1.0f) != '.') {
            if (getTile(newPlayerPosX + 0.0f, newPlayerPosY + 1.0f) == '@' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 1.0f) == '@') {
                playerPosX = 0;
                playerPosY = 0;
                cameraX = 0;
                cameraY = 0;
                newPlayerPosX = newPlayerPosY = 0;
            } else {
                newPlayerPosY = (int)newPlayerPosY;
                playerVelY = 0;
                playerOnGround = true;
            }
        }
    }
    
    playerPosX = newPlayerPosX;
    playerPosY = newPlayerPosY;
    
    //Completed level
    if (getTile(playerPosX + 0.0f, playerPosY + 1.0f) == '$' || getTile(playerPosX + 1.0f, playerPosY + 1.0f) == '$' || getTile(playerPosX + 1.0f, playerPosY + 0.0f) == '$' || getTile(playerPosX + 0.0f, playerPosY + 0.0f) == '$'){
        loadLevel2();
        playerPosX = playerPosY = cameraX = cameraY = newPlayerPosX = newPlayerPosY = 0;
    }
    
    //glTranslatef(0, -10.0f, 0);
    
    for (int x = -1; x < visibleTileX+1+1; x++) {
        for (int y = -1; y < visibleTileY+1+1; y++) {
            char tileId = getTile(x+offsetX, y+offsetY);
            switch(tileId) {
            case '.':
//                    fill(NULL, x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+1)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY, 0.48235f, 0.47451f, 1.00000f);
                break;
            case '#':
                    fill(basewall, x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+1)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY, 0.8f, 0.0f, 0.0f);
                break;
            case '%':
                    fill(cloud, x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+2)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY, 0.8f, 0.0f, 0.0f);
                    break;
            case '$':
                    fill(castle, x * tileWidth - tileOffsetX, (y-3) * tileHeight - tileOffsetY, (x+2)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY, 0.8f, 0.0f, 0.0f);
                    break;
            case '*':
                    fill(enemy, x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+1)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY, 0.8f, 0.0f, 0.0f);
//                    updateEnemy(enemy, x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+1)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY);
                    break;
            default:
                break;
            }
        }
    }
    //draw player
//    fill("mario", (playerPosX- offsetX)*tileWidth, (playerPosY - offsetY)*tileHeight, (playerPosX - offsetX+1)*tileWidth, (playerPosY-offsetY+1)*tileHeight, 0.3f, 0.8f, 0.3f);
    drawMario((playerPosX- offsetX)*tileWidth, (playerPosY - offsetY)*tileHeight, (playerPosX - offsetX+1)*tileWidth, (playerPosY-offsetY+1)*tileHeight);
    
    cameraX = playerPosX;
    cameraY = playerPosY;
    glutSwapBuffers();
}
//endtest
void loadLevel1() {
    level = "";
    level += "....................................................................................................";
    level += "....................................................................................................";
    level += "......%...........%............%...........##.....#...............%.%............%..................";
    level += "...................................................................................%...%..%.........";
    level += "........................................................###.........................................";
    level += ".........................#####.........##...........................................................";
    level += "........................#######..................................................#..................";
    level += ".......................#########.....................###########....................................";
    level += "############..######...#########################.....###########......#......#........#.............";
    level += "############..######..##########################.....###########......#............#...............$";
    level += "############..######...##################............###########..........................#########.";
    level += "############..#######..##################..............#########...............##...................";
    level += "############..######...##################..######.......########....................................";
    level += "############.....................................................#....#..###........................";
    level += "####################...######........................############.....#.............................";
    level += "####################....###....#################.....############.....#.............................";
    level += "####################.....#....##################.....############.....#.............................";
    level += "####################........####################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
}

void loadLevel2() {
    level = "";
    level += "....................................................................................................";
    level += "....................................................................................................";
    level += "......%...........%............%...........##.....#...............%.%............%..................";
    level += "...................................................................................%...%..%.........";
    level += "........................................................###.........................................";
    level += "..........................##...........##...........................................................";
    level += "..........................##...........##........................................#..................";
    level += "..........................##..........*##............###########....................................";
    level += "##########################################################################################..........";
    level += "############..######..##########################.....###########......#............#...............$";
    level += "############..######...##################............###########..........................#########.";
    level += "############..#######..##################..............#########...............##...................";
    level += "############..######...##################..######.......########....................................";
    level += "############.....................................................#....#..###........................";
    level += "####################...######........................############.....#.............................";
    level += "####################....###....#################.....############.....#.............................";
    level += "####################.....#....##################.....############.....#.............................";
    level += "####################........####################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "####################...#########################.....############.....#.............................";
    level += "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
}

void loadLevel3() {
    
}

void timerFunc(int state) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timerFunc, 0);
}
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,200);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Mario");
//    glutDisplayFunc(renderScene);
//    glutIdleFunc(renderScene);
    glutDisplayFunc(newRenderScene);
    //glutIdleFunc(newRenderScene);
    glutTimerFunc(1000/60, timerFunc, 0);
//    glutKeyboardFunc(processNormalKeys);
//    glutSpecialFunc(pressKey);
    glutSpecialFunc(processSpecialKeys2);
    glutSpecialUpFunc(processSpecialUpKeys2);
    glutReshapeFunc(reshape);
    glutIgnoreKeyRepeat(1);
    glEnable(GL_TEXTURE_2D);
//    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
//        cout << "Could not initialize sdl_image : " << IMG_GetError() << endl;
//    }
//    glEnable(GL_DEPTH_TEST);
    init();
    glutMainLoop();
}
