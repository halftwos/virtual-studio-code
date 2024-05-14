#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 3 //定义行
#define COL 3 //定义列
//初始化棋盘
void InitBoard(char board[ROW][COL], int row, int col);

//打印棋盘
void DisplayBoard(char board[ROW][COL], int row, int col);

//玩家下棋
void playerMove(char board[ROW][COL], int row,int col);

//电脑下棋
void ComputerMove(char board[ROW][COL], int row, int col);

//判断谁赢
char Iswin(char board[ROW][COL],int row,int col);

