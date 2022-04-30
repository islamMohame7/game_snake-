#include <graphics.h>
#include<climits>
#include<queue>
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<chrono>
#include<time.h>
#include <unistd.h>
using namespace std :: chrono;
using namespace std;
bool again=FALSE;
const int CELL_SIZE = 18;
const int EMPTY = 0;
const int BODY1 = 1;
const int BODY2 = 6;
const int APPLE = 2;
const int WALL = 3;
const int SNOWFLAKE = 4;
const int BOMB=5;
const int HEART=7;
int snakelife=5;
bool isgameover=false;
bool isFireStarted;
int movescore1=0, movescore2=0, eatAppleScore1=0, eatAppleScore2=0;
long long speed1=4000000, speed2=4000000;
int mcolor, color=YELLOW, freezecolor, color2=LIGHTMAGENTA;
enum Directions1 {UP,DOWN,LEFT,RIGHT};
enum Directions2 {W,S,A,D};
Directions1 snakeDirection1=DOWN, snakeDirectionprev1=  DOWN;
Directions2 snakeDirection2= S, snakeDirectionprev2=  S;
void Game();
void checkkeyinput();
void startFire();
struct location1
{int r;
int c;};
struct location2
{
  int r;
 int c;
};
Directions1 fireDirection;
location1 fireLocation;
queue<location1> snakebodyl;    //Queue for snake body
queue<location2> snakebody2;
int board1[35][45]=
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,3,0,0,3,0,0,0,3,3,3,3,3,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,3,0,3,0,0,0,3,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,3,3,3,0,3,0,0,0,3,0,3,0,3,0,3,3,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,3,0,0,0,3,0,0,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,3,0,3,0,3,3,3,0,3,0,0,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,3,0,0,3,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,0,3,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,3,0,3,0,0,0,0,3,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,3,0,0,0,3,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,3,0,3,0,0,0,3,3,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,3,0,0,0,3,0,3,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,3,0,3,3,3,0,3,0,3,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,3,3,3,3,0,3,3,3,0,3,0,0,0,3,0,0,3,0,0,3,3,3,0,0,3,0,0,3,0,3,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,3,0,3,0,3,0,3,0,3,0,0,0,3,0,3,0,3,0,3,0,0,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,0,3,3,3,0,3,3,3,0,3,3,3,0,3,3,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,0,0,3,0,3,0,3,0,3,3,0,3,3,0,3,0,3,0,3,0,0,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,3,0,0,0,3,0,3,3,3,0,3,0,0,0,3,0,3,0,3,0,3,0,0,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}};
int board[35][45]=
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}};


 //   ----The Functios Of Draw&Erase Every Element----//

void drawWall(int row, int col){

int left = col*CELL_SIZE;
int top = row*CELL_SIZE;
int right = left + CELL_SIZE;
int bottom = top + CELL_SIZE;
setfillstyle(SOLID_FILL,LIGHTRED);
bar(left,top,right,bottom);
setcolor(BLACK);
setlinestyle(SOLID_LINE,1, NORM_WIDTH);
line(left+0, top+9 , left+18, top+9);
line(left+12, top+0, left+12, top+9);
line(left+4, top+9, left+4 , bottom);
line(left, bottom, right , bottom);
line(left, top , right , top);}


void drawFire(int row, int col){
int left = col*CELL_SIZE;
int top = row*CELL_SIZE;
setfillstyle(SOLID_FILL, LIGHTCYAN);
bar (left+2, top+2, left+15, top+15);
}
void eraseFire (int row, int col){
 int left = col*CELL_SIZE;
int top = row*CELL_SIZE;
setfillstyle(SOLID_FILL, BLACK);
bar (left, top, left+18, top+18);
}



void drawheart (int row, int col)
{int left = col*CELL_SIZE;
int top = row*CELL_SIZE;
readimagefile("heart.ico", left, top, left+16, top + 16);}

void eraseheart (int row, int col)
{int left = col*CELL_SIZE;
 int top = row*CELL_SIZE;
 setfillstyle(SOLID_FILL, BLACK);
 bar(left, top, left+18, top+18);
}
void drawbomb(int row, int col)
{
    int left=col*CELL_SIZE;
    int top = row*CELL_SIZE;
    readimagefile("bomb.ico", left, top, left + 16, top + 16);
}

void drawSnow(int row, int col)
{int left = col*CELL_SIZE;
int top = row*CELL_SIZE;
readimagefile("snowflake.ico", left, top, left+16, top+16);
}
void drawApple(int row,int col){
int left=col*CELL_SIZE;
int top=row*CELL_SIZE;
readimagefile("green_apple.ico",left,top,left+16,top+16);
}
void drawempty(int row, int col)
{
    int left=col*CELL_SIZE;
    int top = row*CELL_SIZE;
    int right = left+CELL_SIZE;
    int bottom = top+CELL_SIZE;
setfillstyle(SOLID_FILL, BLACK);
bar (left, top, right, bottom);}

void drawSnakeBody1 (int row, int col)
{int left = col*CELL_SIZE;
 int top =row*CELL_SIZE;
 setfillstyle(SOLID_FILL,color);  //   ***************   //
 bar(left+1, top+1, left+17, top+17);
}
void eraseSnakeBody1 (int row, int col)
{int left = col*CELL_SIZE;
int top = row*CELL_SIZE;
setfillstyle(SOLID_FILL, BLACK);
bar(left, top, left+18, top+18);}

void drawSnakeBody2(int row, int col)
{int left = col*CELL_SIZE;
int top =row*CELL_SIZE;
setfillstyle(SOLID_FILL, color2 );
bar (left+1, top+1, left+17, top+17);
}
void eraseSnakeBody2(int row, int col)
{int left = col*CELL_SIZE;
int top = row*CELL_SIZE;
setfillstyle(SOLID_FILL, BLACK);
bar (left,top, left+18, top+18);}

void generatewall()
{for (int i=0;i<=4;i++) {
int r,c;
do
{
    r=rand()%35;
    c=rand()%45;
}
while(board[r][c]!=EMPTY);              //*****************//
board[r][c]= WALL;                 //*******************//
drawWall(r,c);}}

//---Functions Of Drawing Screens----//
void drawBoard()
{
  for (int row=0; row<35; row++)
    {  for (int col=0; col<45; col++)
         {  switch(board1[row][col])
              {  case WALL:
                 drawWall(row, col);
                 break;
                  case EMPTY:
                  drawempty(row, col);
                 break;
            }
setcolor(LIGHTGRAY);
settextjustify(CENTER_TEXT, CENTER_TEXT);
settextstyle(BOLD_FONT,HORIZ_DIR,2);
outtextxy(getmaxx()/2, getmaxy()/6, "Press Enter");}}}
void drawMenuBoard()
{for (int row=0; row<40; row++) //number of row and number of coloumns :: time complexity
   for(int col=0; col<50; col++)
    drawWall(row,col);}

void drawBoard1(){
  for(int row=0; row<35; row++)
  {for (int col=0; col<45; col++)

   {switch(board[row][col])
{
case EMPTY:
     drawempty(row,col);
      break;
case BODY1:
     drawempty(row,col);
     drawSnakeBody1 (row,col);
      break;
case BODY2:
    drawempty(row, col);
    drawSnakeBody2(row, col);
    break;
case APPLE:
    drawempty(row, col);
    drawApple(row, col);
    break;
case WALL:
    drawempty(row, col);
    drawWall(row,col);
     break;
case SNOWFLAKE:
     drawempty(row, col);
     drawSnow(row, col);
     break;
case BOMB:
     drawempty(row, col);
     drawbomb(row, col);
     break;
case HEART:
     drawempty(row, col);
     drawheart(row, col);
     break;}}}}

void MenuBoardSingleorMulti()
{
system("cls");
drawMenuBoard();
setcolor(WHITE);
setbkcolor(LIGHTRED);
settextstyle(BOLD_FONT, HORIZ_DIR, 5);
outtextxy(300, 50,"The Snake Game");
settextstyle(BOLD_FONT, HORIZ_DIR, 5);
outtextxy(300, 220," single player Press 1");
outtextxy(300, 320," Multiplayer Press 2");}

 void choosesnakecolor()
{
system("cls");
drawMenuBoard();
setcolor(WHITE);
setbkcolor(LIGHTRED);
settextstyle(BOLD_FONT, HORIZ_DIR, 5);
outtextxy(350,50, "Choose Snake color");
setcolor(YELLOW);
outtextxy(350,220, "Yellow Press 3");
setcolor(BLUE);
outtextxy(350,320,"Bluel Press 4");
setcolor(GREEN);
outtextxy(350,420, "Green Press 5");
int colornum;
colornum=getch();
while( (colornum !=51)&&(colornum !=52)&&(colornum !=53))
colornum=getch();
switch(colornum)
{case 51:
    mcolor=YELLOW; color=mcolor;  break;
case 52:
     mcolor=BLUE;color=mcolor;   break;
case 53:
     mcolor=GREEN;color=mcolor;  break;}}
 //--the Functions Of Generating The Things That The Snake--//
void generatebomb()
{
int r,c;
do
{
r=rand()%35;
c=rand()%45;}
while(board [r][c] != EMPTY);
board[r][c]= BOMB;
drawbomb(r,c);
}
void generatesnow()
{
  int r,c;
    do
{

r=rand()%35;
c=rand()%45;
}
while(board[r][c]!=EMPTY);
board[r][c]= SNOWFLAKE;
drawSnow(r,c);}

 void generatenextapple()
{
  int r,c;
  do
{r=rand()%33;
c=rand()%43;}
while(board [r][c] != EMPTY);
board[r][c]= APPLE;
drawApple(r,c);}

//----Function Of Respawn Snake----//

void initsnake1()
{
                                 // queue//
location1 loc;
loc.r=15;
loc.c=15;
for(int i=0 ; i<=1;i++){
snakebodyl.push(loc);
board[loc.r][loc.c] =1;
loc.r+=1;}}

 void initsnake2()
{
location2 loc;
loc.r=15;
loc.c=35;
for (int i=0; i<=1; i++)
{
snakebody2.push(loc);
board[loc.r][loc.c] =1;
loc.r+=1;}}
// function Of Snake Moving //
location1 getnextFireLocation()
{
location1 nextFireLoc=fireLocation;
switch(fireDirection)
{
case UP:
nextFireLoc.r -=1;
break;
case DOWN:
nextFireLoc.r +=1;
break;
case LEFT:
nextFireLoc.c -=1;
break;
case RIGHT:
nextFireLoc.c +=1;
break;}
return nextFireLoc;}

location1 getnexthead1()
{
location1 head1=snakebodyl.back();

if (snakeDirection1 == UP && snakeDirectionprev1 != DOWN ||(snakeDirection1 == DOWN && snakeDirectionprev1 == UP))
{
    head1.r -= 1;
    snakeDirectionprev1 = UP;
}
else if (snakeDirection1 == DOWN && snakeDirectionprev1 != UP||(snakeDirection1 == UP && snakeDirectionprev1 == DOWN))
{
    head1.r += 1;
    snakeDirectionprev1 = DOWN;
}
else if (snakeDirection1 == LEFT && snakeDirectionprev1 != RIGHT||(snakeDirection1 == RIGHT && snakeDirectionprev1 == LEFT))
{
    head1.c -= 1;
    snakeDirectionprev1 = LEFT;
}
else if (snakeDirection1 == RIGHT && snakeDirectionprev1 != LEFT||(snakeDirection1 == LEFT && snakeDirectionprev1 == RIGHT))
{
    head1.c += 1;
    snakeDirectionprev1 = RIGHT;
}
return head1;}

location2 getnexthead2()
{
location2 head2=snakebody2.back();
if (snakeDirection2 == W && snakeDirectionprev2 != S ||(snakeDirection2 == S && snakeDirectionprev2 == W))
{
    head2.r -= 1;
    snakeDirectionprev2 = W;
}
else if (snakeDirection2 == S && snakeDirectionprev2 != W||(snakeDirection2 == W && snakeDirectionprev2 == S))
{
    head2.r += 1;
    snakeDirectionprev2 = S;
}
else if (snakeDirection2 == A && snakeDirectionprev2 != D||(snakeDirection2 == D && snakeDirectionprev2 == A))
{
    head2.c -= 1;
    snakeDirectionprev2 = A;
}
else if (snakeDirection2 == D && snakeDirectionprev2 != A||(snakeDirection2 == A && snakeDirectionprev2 == D))
{
    head2.c += 1;
    snakeDirectionprev2 = D;
}
return head2;}

   void moveandgrowsnake1(location1 nexthead1)
{
    snakebodyl.push(nexthead1);
    drawSnakeBody1(nexthead1.r,nexthead1.c);
    board[nexthead1.r][nexthead1.c] =1;
}
void movesnake1tonextlocation(location1 nexthead1)
{
snakebodyl.push(nexthead1);
drawSnakeBody1(nexthead1.r,nexthead1.c);
board[nexthead1.r][nexthead1.c] =1;
location1 tail1=snakebodyl.front();
snakebodyl.pop();
eraseSnakeBody1(tail1.r,tail1.c);
board[tail1.r][tail1.c] =0;
}
void moveandgrowsnake2(location2 nexthead2)
{
snakebody2.push(nexthead2);
drawSnakeBody2(nexthead2.r,nexthead2.c);
board[nexthead2.r][nexthead2.c] =1;}

 void movesnake2tonextlocation(location2 nexthead2)
{snakebody2.push(nexthead2);
drawSnakeBody2(nexthead2.r, nexthead2.c);
board[nexthead2.r][nexthead2.c] =1;
location2 tai12=snakebody2.front();
snakebody2.pop();
eraseSnakeBody2(tai12.r,tai12.c);
board[tai12.r][tai12.c] =0; }

  //----The Function of Freezing The Snake----//

void freezesnake1()
{speed1=1000000;
freezecolor=LIGHTCYAN;
color=freezecolor;}

void freezesnake2()
{
speed2=1000000;
color2=LIGHTCYAN;}

void gameover()
{
 isgameover=true;
 setcolor(WHITE);
 setbkcolor(BLACK);
 settextjustify(CENTER_TEXT, CENTER_TEXT);
 settextstyle(BOLD_FONT, HORIZ_DIR,8);
 outtextxy(getmaxx()/2, getmaxy()/2, "Game Over");
 char arr [50];
 settextstyle(BOLD_FONT,HORIZ_DIR,5);
 sprintf(arr, "Scorel: %d", eatAppleScore1);
 outtextxy(130,50,arr);}

void gameover1()
{
    isgameover=true;
    setcolor(WHITE);
    setbkcolor(BLACK);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,8);
    outtextxy(getmaxx()/2,getmaxy()/3, "Snake2 won");
    char as [50];
    settextstyle(BOLD_FONT, HORIZ_DIR,5);
    sprintf(as, "Score2: %d",eatAppleScore2);
    outtextxy(130,100,as);}

void gameover2()
{
   isgameover=true;
   setcolor(WHITE);
   setbkcolor(BLACK);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(BOLD_FONT, HORIZ_DIR, 8);
   outtextxy(getmaxx()/2,getmaxy()/3,"Snakel won");
   char as[50];
   settextstyle(BOLD_FONT, HORIZ_DIR,5);
   sprintf(as, "Score2: %d",eatAppleScore2);
   outtextxy(130,100,as);}

//----More Move Snake Functions----//
void movesnake1()
{location1 nexthead1 = getnexthead1();
    switch (board[nexthead1.r][nexthead1.c])
    {
    case EMPTY:
        movesnake1tonextlocation(nexthead1);
        break;
    case APPLE:
        moveandgrowsnake1(nexthead1);
        generatenextapple();
        speed1 = 4000000;
        color = mcolor;
        movescore1++;
        eatAppleScore1++;
        if (movescore1 % 4 == 0)
        {
            generatesnow();
            movescore1++;
        }
        else if (movescore1 % 5 == 0)
            generatebomb();
        break;
    case WALL:
    case BODY1:
    case BODY2:
    case BOMB:
    {color = RED;
    snakelife--;
    if (movescore2 != 0)
    {
        gameover();
        gameover1();
    }
    break; }

    case SNOWFLAKE:
        movesnake1tonextlocation(nexthead1);
        freezesnake1();
        break;
    }}

void movesnake2()
{
location2 nexthead2 = getnexthead2();
switch (board[nexthead2. r ][nexthead2. c])
{case EMPTY:
movesnake2tonextlocation(nexthead2);
break;
case APPLE:
moveandgrowsnake2(nexthead2);
generatenextapple();
speed2=400000;
color2=LIGHTMAGENTA;
eatAppleScore2++;
movescore2++;
if (movescore2%5==0)
{generatesnow();
movescore2++;}
else if (movescore2%6==0)
generatebomb();
break;
case WALL:
 case BODY1:
case BODY2:
case BOMB:
color2=RED;
gameover();
gameover2();
break;
case SNOWFLAKE:
movesnake2tonextlocation(nexthead2);
freezesnake2();
break;}}

 void snakehearts()
{
switch (snakelife)
{case 5:
isgameover=false;
break;
case 4:
isgameover=false;
drawMenuBoard();
drawBoard1();
initsnake1();
eraseheart(1,3);
board[1][3]=EMPTY;
snakelife--;
break;
case 2:
isgameover=false;
drawMenuBoard();
drawBoard1();

initsnake1();
eraseheart(1,2);
board[1][2]=EMPTY;
snakelife--;
break;
   case 0:
eraseheart(1,1);
board[1][1]=EMPTY;
gameover();
break;
}}
void checkkeyinput()
{
    char ch;
    if(kbhit()){
        ch=getch();
        if(ch==32){
         startFire();
        }}
}
 //----The Fire Functions----//

void startFire()
{


isFireStarted =true;



fireLocation = getnexthead1 ();

fireDirection = snakeDirection1;

drawFire(fireLocation.r,fireLocation.c);
}
void stopFire()
{


isFireStarted=false;

eraseFire(fireLocation.r,fireLocation.c);

board[fireLocation.r][fireLocation.c]=EMPTY;
}
  void moveFire(){

if(isFireStarted)
{


location1 nextFireLoc = getnextFireLocation();
if(nextFireLoc.r>35 || nextFireLoc.r<0 || nextFireLoc.c>45 || nextFireLoc.c<0)
{
    stopFire();
    return;
}
if(board[fireLocation.r][fireLocation.c]==APPLE || board[fireLocation.r][fireLocation.c]==BODY1 || board[fireLocation.r][fireLocation.c]==BODY2)
    return ;
drawFire(nextFireLoc.r,nextFireLoc.c);

eraseFire(fireLocation.r,fireLocation.c);
fireLocation=nextFireLoc;
if(board[fireLocation.r][fireLocation.c]==WALL ||(board[fireLocation.r][fireLocation.c]==BOMB)||
   (board[fireLocation.r][fireLocation.c]==SNOWFLAKE))
board[fireLocation.r][fireLocation.c]=EMPTY;
}
  }
/*switch(board[fireLocation.r][fireLocation.c])
{


case SNOWFLAKE:

case BOMB:

eraseFire(fireLocation.r,fireLocation.c);

board1[fireLocation.r][fireLocation.c]=EMPTY;

break;
}
//fireLocation = nextFireLoc;
  }*/
///-=-Game control functions----.*/

  void changesnakedirection1 (char ch)
{
switch(ch)
{
case KEY_UP:
snakeDirection1=UP;
break;
case KEY_DOWN:
snakeDirection1=DOWN;
break;
case KEY_LEFT:
snakeDirection1=LEFT;
break;
case KEY_RIGHT:
snakeDirection1=RIGHT;
break;}}
void changesnakedirection2(int con)
{
switch (con)
{case 119:
snakeDirection2=W;
break;
case 115:
snakeDirection2=S;
break;
case 97:
snakeDirection2=A;
break;
case 100:
snakeDirection2=D;
break;}}
//--Input----//
   void KEYINPUTTEST()
{
int key;
char ch;
if (kbhit())
{   ch=key=getch();
    if (ch==0)
   {ch=getch();
 changesnakedirection1(ch);
}else if( (key==97)|| (key==100)|| (key==115)|| (key==119))
{changesnakedirection2(key);}else if (key==32)//SpaceBar

if(!isFireStarted)
startFire();

}}

//---Enter&Retry BUTTON----//
void checkEnterButton()
{int button;
button=getch();
while(button!=13) //ASCII code for ENTER key is 13
{button=getch();}
}
//--------EXIT BUTTON -----------//
void checkEntersButton()
{int button;
button=getch();
if(button==13) //ASCII code for ENTER key is 13
{button=getch();
     Game();}
}
void checkExitButton()
{int Exit;
Exit=getch();
if(Exit==27)//ASCII code for EXIT key is 27
{
closegraph(ALL_WINDOWS);}
else{
    checkEntersButton();
}
}

void Game()
{
closegraph(ALL_WINDOWS);
snakelife=5;
board[1][3]=HEART;
board[1][2]=HEART;
board[1][1]=HEART;
eatAppleScore1=0;
eatAppleScore2=0;
initwindow(45 * CELL_SIZE, 35 * CELL_SIZE, " Snake Game ");
int levelnum;
int gametimer=0;
isgameover=false;
drawBoard();
checkEnterButton();
//drawahmed();//
checkEnterButton();
MenuBoardSingleorMulti();
levelnum = getch();
while( (levelnum!=49)&&(levelnum !=50))
levelnum =getch();
switch(levelnum)
{case 49:
  choosesnakecolor();
  drawBoard1();
  initsnake1();
  while(!isgameover)
  {if (gametimer==INT_MAX)
    gametimer=0;
if (gametimer % 1000000==0){
moveFire();}
if(gametimer%speed1==0)
   movesnake1();
   gametimer++;
   KEYINPUTTEST();
snakehearts();
if(eatAppleScore1==10)
    {eatAppleScore1++;
    generatewall();
    }}
   break;
   case 50:
   drawBoard1();
   board[1][3]=EMPTY;
   drawempty(1,3);
   board[1][2]=EMPTY;
   drawempty(1,2);
   board[1][1]=EMPTY;
   drawempty(1,1);
   mcolor=YELLOW;
   initsnake1();
   initsnake2();
while(!isgameover)
{if (gametimer==INT_MAX)
gametimer=0;
if(gametimer%1000000==0)
    moveFire();
if (gametimer%speed1==0 && gametimer%speed2==0)
{movesnake2();
movescore2++;
movesnake1();}
gametimer++;
KEYINPUTTEST();
KEYINPUTTEST();}
break;}
 setcolor(WHITE);
setbkcolor(BLACK);
settextstyle(BOLD_FONT, HORIZ_DIR, 3);
outtextxy(400, 370, "EXIT: 'ESC' ");
outtextxy(400, 450, "again: 'ENTER' ");
outtextxy(400, 450, "again: 'ENTER' ");
checkExitButton();
return;
while(!kbhit());
closegraph();
}
int main()
{
    auto start = chrono::steady_clock::now();
Game();
    auto end = chrono::steady_clock::now();

    cout << "Elapsed time in nanoseconds: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;

    cout << "Elapsed time in milliseconds: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;

    cout << "Elapsed time in seconds: "
        << chrono::duration_cast<chrono::seconds>(end - start).count()
        << " sec";
return 0;
}
