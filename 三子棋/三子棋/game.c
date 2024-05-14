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
	{   //��ӡ����
		//printf("%c | %c | %c\n", board[i][0], board[i][1], board[i][2]);
		int j = 0;
		for (j = 0; j < col; j++) {
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|");
		}
		printf("\n");
		//��ӡ�ָ�
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
	printf("�������:>\n");
	while (1) {
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col) //�ж������Ƿ�Ƿ�
		{
			if (board[x - 1][y - 1] == ' ') //�ж������Ƿ��Ѿ���ռ��
			{
				board[x - 1][y - 1] = '*'; //�������Ϊ��*��
				break;
			}
			else
				printf("���걻ռ�ã�����������\n");
		}
		else {
			printf("����Ƿ�������������\n");
		}
	}
}
//��game.c�ļ���
void ComputerMove(char board[ROW][COL], int row, int col) 
{
	printf("�������� :>\n");
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
	//��
	int i = 0;
	for (i= 0; i < row; i++) {
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ') {
			return board[i][1];
		}
	}
	//��
	int j = 0;
	for (j = 0; j < col; j++) {
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ') {
			return board[1][j];
		}
	}
	//�Խ���
	if (board[0][0] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') {
		return board[1][1];
	}
	//û��Ӯ
	if (full(board,row,col)) {
		return 'Q';
	}
	//��Ϸ����
	return'C';
}