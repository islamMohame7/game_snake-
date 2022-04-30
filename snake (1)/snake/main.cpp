#include <graphics.h>
#include<climits>
#include<queue>
#include<iostream>
#include<stdio.h>
#include<windows.h>
using namespace std;
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
Directions2 snakeDirection2= S;
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
/*void drawFire(int row, int col)
int left = col*CELL_SIZE:
int top = row*CELL_SIZE;
readimagefile( "yg. ico", left, top, left +16, top +16 ):
void eraseFire (int row, int col)
= int left = col*CELL_SIZE;
int top = row*CELL_SIZE;
setfillstyle(SOLID_FILL, BLACK);
bar (left, top, left+18, top+18);
}*/

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
{for (int row=0; row<35; row++)
   for(int col=0; col<45; col++)
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
outtextxy(180, 50,"The Snake Game");
settextstyle(BOLD_FONT, HORIZ_DIR, 5);
outtextxy(100, 220," single player Press 1");
outtextxy(100, 320," Multiplayer Press 2");}

 void choosesnakecolor()
{
system("cls");
drawMenuBoard();
setcolor(WHITE);
setbkcolor(LIGHTRED);
settextstyle(BOLD_FONT, HORIZ_DIR, 5);
outtextxy(300,50, "Choose Snake color");
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
{r=rand()%35;
c=rand()%45;}
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
/*switch(snakeDirection1)
{
case UP:
head1.r -=1;
break;
case DOWN:
head1.r +=1;
break;
case LEFT:
head1.c -=1;
break;
case RIGHT:
head1.c +=1;
break;}*/
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
switch( snakeDirection2)
{
case W:
head2.r -=1;
break;
case S:
head2.r +=1;
break;
case A:
head2.c -=1;
break;
case D:
head2.c +=1;
break;}
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
speed2=4000000;
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

 //----The Fire Functions----//

/*avoid startFire()

isFireStarted

true:



fireLocation = getnexthead1 ():

fireDirection = snakeDirection1;

drawFire(firelocation.r,fireLocation.c);

void stopFire()

isFireStarted=false:

eraseFire(fireLocation.r,fireLocation.c);

boardI[fireLocation.r][fireLocation.c]-EMPTY:
    ------------------------------------------------------
  void moveFireO)

if(1sFireStarted)

location| nextFireLoc = getnextFireLocation();

drawFire(nextFireLoc.r,nextFireLoc.c);

eraseFire(fireLocation.r,fireLocation.c);

switch(boardi[fireLocation.r][fireLocation.c])

case SNOWFLAKE:

case BOMB:

eraseFire(fireLocation.r,fireLocation.c);

boardi[fireLocation.r][fireLocation.c]=EMPTY:

break:

fireLocation = nextFireLoc;

-=-Game control functions----.*/

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
{changesnakedirection2(key);}/*else if (key==32)//SpaceBar

if(tisFireStarted)

)

startFire():

)*/}}

//---Enter&Retry BUTTON----//
void checkEnterButton()
{int button;
button=getch();
while(button!=13) //ASCII code for ENTER key is 13
{button=getch();}}
//--------EXIT BUTTON -----------//

void checkExitButton()
{int Exit;
Exit=getch();
while(Exit!=27)//ASCII code for EXIT key is 27
{Exit=getch();}
closegraph(ALL_WINDOWS);}

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
//if (gametimer % 500000==0){
//moveFire();}
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
//outtextxy(400, 350, "Retry: 'Enter' ");
outtextxy(400, 370, "EXIT: 'ALT+ESC' ");
checkEnterButton();
return;
checkExitButton();
while(!kbhit());
closegraph();
}
int main()
{

while(1)
Game();
return 0;
}
