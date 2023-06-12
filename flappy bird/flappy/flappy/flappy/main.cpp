//
//  main.cpp
//  flappy bird
//
//  Created by Tsenguun Otgonbaatar on 2022.12.01.
//

#include <GLUT/glut.h>
#include <GLUT/GLUT.h>  
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
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

Mix_Music *mscMusic = NULL;
Mix_Chunk *sndScratch = NULL;
Mix_Chunk *dieScratch = NULL;

int winHeight, winWidth;
unsigned int basewall, brick, pipe, pipetop;
unsigned int bird, bird2;
unsigned int castle;
int pipeReverse = 0;
bool started = false;
string inst = "Space дарж эхэлнэ";

string level;
int rightKeyPressed = 0;
int leftKeyPressed = 0;
int rightKey = 1;
int leftKey = 0;

//testing
int levelWidth, levelHeight;
float cameraX = 0.0f, cameraY = 0.0f;
float playerPosX = 0.0f, playerPosY = 5.0f;
float playerVelX = 2.0f, playerVelY = 0.0f;
float enemyVelx = 0.0f, enemyVelY = 0.0f;
float enemyPosx = 0.0f, enemyPosY = 0.0f;
int upKeyPressed = 0, bottomKeyPressed = 0;
bool playerOnGround = false;
int birdmod = 0;

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

char getTile(int x, int y) {
    if (x >= 0 && x < levelWidth && y >= 0 && y < levelWidth) {
        return level[y*levelWidth+x];
    } else
        return ' ';
}
void setTile(int x, int y, int c) {
    if (x >= 0 && x < levelWidth && y >= 0 && y < levelWidth) {
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

void drawPipeBody(float a, float b, float c, float d) {
    glBindTexture(GL_TEXTURE_2D, pipe);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.1f);
        glVertex3f(a, b, 0);
    glTexCoord2f(0.0f, 0.9f);
        glVertex3f(a, d, 0);
    glTexCoord2f(1.0f, 0.9f);
        glVertex3f(c, d, 0);
    glTexCoord2f(1.0f, 0.1f);
        glVertex3f(c, b, 0);
    glEnd();

}

void drawPipe(float a, float b, float c, float d) {
    glBindTexture(GL_TEXTURE_2D, pipetop);
    if (pipeReverse) {
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
    } else {
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
            glVertex3f(a, b, 0);
        glTexCoord2f(0.0f, 0.0f);
            glVertex3f(a, d, 0);
        glTexCoord2f(1.0f, 0.0f);
            glVertex3f(c, d, 0);
        glTexCoord2f(1.0f, 1.0f);
            glVertex3f(c, b, 0);
        glEnd();
    }
}

void drawBird(float a, float b, float c, float d) {
    if (birdmod == 1) {
        glBindTexture(GL_TEXTURE_2D, bird2);
    } else {
        glBindTexture(GL_TEXTURE_2D, bird);
    }
    if (leftKey) {
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
        case 32:
            birdmod = 1;
            if (birdmod)
                Mix_PlayChannel(-1, sndScratch, 0);
            started = true;
            playerVelY = -1.5f;
            break;
        case 27:
            Mix_FreeMusic(mscMusic);
            mscMusic = NULL;
            Mix_FreeChunk(sndScratch);
            sndScratch = NULL;
            Mix_FreeChunk(dieScratch);
            dieScratch = NULL;
            Mix_Quit();
            SDL_Quit();
            exit(1);
            
            break;
    }
}
void processSpecialUpKeys2(int key, int xx, int yy) {
    switch (key) {
        case 32:
            birdmod = 0;
            break;
    }
}
void print(int x, int y, char *string) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2i(100, 100);
    glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    int i;
    for (i = 0; i < strlen(string); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);
    }
    glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
}
void init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL mixer error: "<< SDL_GetError() << endl;
    }
    mscMusic = Mix_LoadMUS("../images/backgroundMusic.wav");
    if (mscMusic == NULL) {
        cout << "couldn't load beat.wav: "<< Mix_GetError() << endl;
    }
    sndScratch = Mix_LoadWAV("../images/flySound copy.wav");
    if (sndScratch == NULL) {
        cout << "couldn't load flySound.wav: "<< Mix_GetError() << endl;
    }
    dieScratch = Mix_LoadWAV("../images/dieSound copy.wav");
    if (dieScratch == NULL) {
        cout << "couldn't load dieSound.wav: "<< Mix_GetError() << endl;
    }

    Mix_PlayMusic(mscMusic, -1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE);
    levelWidth = 100;
    levelHeight = 15;
    loadLevel1();
 
    basewall = loadTexture("../images/base.bmp");
    pipe = loadTexture("../images/pipe-green.bmp");
    pipetop = loadTexture("../images/pipe-green.bmp");
    bird = loadTexture("../images/yellowbird-upflap.bmp");
    bird2 = loadTexture("../images/yellowbird-midflap.bmp");
}

int vel = 1;
void updateEnemy(int x, int y) {
    if (getTile(x+vel, y) == '#')
        vel = -vel;
    setTile(x, y, '.');
    setTile(x+vel, y, '*');
}
void newRenderScene(void) {
    // Clear Color and Depth Buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
    
    if (started) {
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
            if (getTile(newPlayerPosX + 0.0f, playerPosY + 0.0f) == '^' || getTile(newPlayerPosX + 0.0f, playerPosY + 0.9f) == '^' ||
                getTile(newPlayerPosX + 0.0f, playerPosY + 0.0f) == '&' || getTile(newPlayerPosX + 0.0f, playerPosY + 0.9f) == '&' ||
                getTile(newPlayerPosX + 0.0f, playerPosY + 0.0f) == '|' || getTile(newPlayerPosX + 0.0f, playerPosY + 0.9f) == '|' ||
                getTile(newPlayerPosX + 0.0f, playerPosY + 0.0f) == '@' || getTile(newPlayerPosX + 0.0f, playerPosY + 0.9f) == '@') {
                Mix_PlayChannel(-1, dieScratch, 0);
                playerPosX = playerPosY = cameraX = cameraY = newPlayerPosX = newPlayerPosY = playerVelY = 0;
                started = false;
                newPlayerPosY = 5.0f;
            }
        }else {
            if (getTile(newPlayerPosX + 1.0f, playerPosY + 0.0f) == '^' || getTile(newPlayerPosX + 1.0f, playerPosY + 0.9f) == '^' ||
                getTile(newPlayerPosX + 1.0f, playerPosY + 0.0f) == '&' || getTile(newPlayerPosX + 1.0f, playerPosY + 0.9f) == '&' ||
                getTile(newPlayerPosX + 1.0f, playerPosY + 0.0f) == '|' || getTile(newPlayerPosX + 1.0f, playerPosY + 0.9f) == '|' ||
                getTile(newPlayerPosX + 1.0f, playerPosY + 0.0f) == '@' || getTile(newPlayerPosX + 1.0f, playerPosY + 0.9f) == '@') {
                Mix_PlayChannel(-1, dieScratch, 0);
                playerPosX = playerPosY = cameraX = cameraY = newPlayerPosX = newPlayerPosY = playerVelY = 0;
                started = false;
                newPlayerPosY = 5.0f;
            }
        }
        playerOnGround = false; 
        if (playerVelY <= 0) {
            if (getTile(newPlayerPosX + 0.0f, newPlayerPosY) == '^' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 0.0f) == '^' ||
                getTile(newPlayerPosX + 0.0f, newPlayerPosY) == '&' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 0.0f) == '&' ||
                getTile(newPlayerPosX + 0.0f, newPlayerPosY) == '|' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 0.0f) == '|' ||
                getTile(newPlayerPosX + 0.0f, newPlayerPosY) == '@' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 0.0f) == '@') {
                Mix_PlayChannel(-1, dieScratch, 0);
                playerPosX = playerPosY = cameraX = cameraY = newPlayerPosX = newPlayerPosY = playerVelY = 0;
                started = false;
                newPlayerPosY = 5.0f;
            }
        } else {
            if (getTile(newPlayerPosX + 0.0f, newPlayerPosY + 1.0f) == '^' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 1.0f) == '^' ||
                getTile(newPlayerPosX + 0.0f, newPlayerPosY + 1.0f) == '&' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 1.0f) == '&' ||
                getTile(newPlayerPosX + 0.0f, newPlayerPosY + 1.0f) == '|' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 1.0f) == '|' ||
                getTile(newPlayerPosX + 0.0f, newPlayerPosY + 1.0f) == '@' || getTile(newPlayerPosX + 0.9f, newPlayerPosY + 1.0f) == '@') {
                Mix_PlayChannel(-1, dieScratch, 0);
                playerPosX = playerPosY = cameraX = cameraY = newPlayerPosX = newPlayerPosY = playerVelY = 0;
                started = false;
                newPlayerPosY = 5.0f;
            }
        }
         
        playerPosX = newPlayerPosX;
        playerPosY = newPlayerPosY;
         
        //Completed level
        if (getTile(playerPosX + 0.0f, playerPosY + 1.0f) == '$' || getTile(playerPosX + 1.0f, playerPosY + 1.0f) == '$' || getTile(playerPosX + 1.0f, playerPosY + 0.0f) == '$' || getTile(playerPosX + 0.0f, playerPosY + 0.0f) == '$'){
//            loadLevel2();
            playerPosX = playerPosY = cameraX = cameraY = newPlayerPosX = newPlayerPosY = 0;
            playerPosX = playerPosY = cameraX = cameraY = newPlayerPosX = newPlayerPosY = playerVelY = 0;
            started = false;
            newPlayerPosY = 5.0f;
        }
    } else {
        print(visibleTileX, visibleTileY, "Press Space");
    }
    
    //glTranslatef(0, -10.0f, 0);
    
    for (int x = -1; x < visibleTileX+1+1; x++) {
        for (int y = -1; y < visibleTileY+1+1; y++) {
            char tileId = getTile(x+offsetX, y+offsetY);
            switch(tileId) {
            case '.':
                break;
            case '@':
                    fill(basewall, x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+1)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY, 0.8f, 0.0f, 0.0f);
                break;
            case '|':
                    drawPipeBody(x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+1)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY);
                    break;
            case '$':
//                    fill(castle, x * tileWidth - tileOffsetX, (y-3) * tileHeight - tileOffsetY, (x+2)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY, 0.8f, 0.0f, 0.0f);
                    break;
            case '&':
                    pipeReverse = 0;
                    drawPipe(x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+1)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY);
                    break;
            case '^':
                    pipeReverse = 1;
                    drawPipe(x * tileWidth - tileOffsetX, y * tileHeight - tileOffsetY, (x+1)*tileWidth - tileOffsetX, (y+1)*tileHeight - tileOffsetY);
                    break;
            default:
                break;
            }
        }
    }
    //draw player
    drawBird((playerPosX- offsetX)*tileWidth, (playerPosY - offsetY)*tileHeight, (playerPosX - offsetX+1)*tileWidth, (playerPosY-offsetY+1)*tileHeight);
    
    cameraX = playerPosX;
    cameraY = playerPosY;
    glutSwapBuffers();
}
//endtest
void loadLevel1() {
    level = "";
    level += "...................||.....||.....||.....||.....||.....||.....&&.....||........||...................$";
    level += "...................||.....||.....||.....||.....||.....||............||........||...................$";
    level += "...................||.....||.....||.....&&.....||.....&&............||........||...................$";
    level += "...................||.....||.....||............||...................||........&&...................$";
    level += "...................&&.....||.....&&............||............^^.....||.............................$";
    level += "..........................||...................&&............||.....||.............................$";
    level += "..........................&&............^^............^^.....||.....||.............................$";
    level += "........................................||............||.....||.....&&........^^...................$";
    level += "...................^^............^^.....||............||.....||...............||...................$";
    level += "...................||............||.....||.....^^.....||.....||...............||...................$";
    level += "...................||.....^^.....||.....||.....||.....||.....||...............||...................$";
    level += "...................||.....||.....||.....||.....||.....||.....||.....^^........||...................$";
    level += "...................||.....||.....||.....||.....||.....||.....||.....||........||...................$";
    level += "...................||.....||.....||.....||.....||.....||.....||.....||........||...................$";
    level += "...................||.....||.....||.....||.....||.....||.....||.....||........||...................$";
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
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,200);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Суга Flappy");
    glutDisplayFunc(newRenderScene);
    glutTimerFunc(1000/60, timerFunc, 0);
    glutSpecialFunc(processSpecialKeys2);
    glutSpecialUpFunc(processSpecialUpKeys2);
    glutReshapeFunc(reshape);
    glutIgnoreKeyRepeat(1);
    init();
    glutMainLoop();
}
