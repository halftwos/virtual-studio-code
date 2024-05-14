#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}
void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{   //打印数据
		//printf("%c | %c | %c\n", board[i][0], board[i][1], board[i][2]);
		int j = 0;
		for (j = 0; j < col; j++) {
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|");
		}
		printf("\n");
		//打印分割
		if (i < row - 1)
		{
			int j = 0;
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
					printf("|");
			}
			printf("\n");
		}

	}
}
void playerMove(char board[ROW][COL], int row, int col) {
	int x = 0, y = 0;
	printf("玩家下棋:>\n");
	while (1) {
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col) //判断坐标是否非法
		{
			if (board[x - 1][y - 1] == ' ') //判断坐标是否已经被占用
			{
				board[x - 1][y - 1] = '*'; //玩家棋子为‘*’
				break;
			}
			else
				printf("坐标被占用，请重新输入\n");
		}
		else {
			printf("坐标非法，请重新输入\n");
		}
	}
}
//在game.c文件中
void ComputerMove(char board[ROW][COL], int row, int col) 
{
	printf("电脑下棋 :>\n");
	int x = 0;
	int y = 0;
	while (1) 
	{

		x = rand() % row;
		y = rand() % col;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
	
	}
int full(char board[ROW][COL], int row, int col) {
	int i = 0;
	for (i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == ' ') {
				return 0;
			}
		}
	}
}
char Iswin(char board[ROW][COL], int row, int col) {
	//行
	int i = 0;
	for (i= 0; i < row; i++) {
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ') {
			return board[i][1];
		}
	}
	//列
	int j = 0;
	for (j = 0; j < col; j++) {
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ') {
			return board[1][j];
		}
	}
	//对角线
	if (board[0][0] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') {
		return board[1][1];
	}
	//没人赢
	if (full(board,row,col)) {
		return 'Q';
	}
	//游戏继续
	return'C';
}