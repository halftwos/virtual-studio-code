#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

IMAGE img; // 定义背景图片
IMAGE player1, player2; // 定义玩家图片
IMAGE bullet[2]; // 定义子弹图片
IMAGE enemyIMG[2]; // 定义敌机图片
bool game_over = false; // 定义游戏结束标志
enum MyEnum
{
    WIDTH = 480, // 定义窗口宽度
    HEIGHT = 700, // 定义窗口高度
    BULLET_NUM = 15, // 定义子弹数量
    ENEMY_NUM = 10, // 定义敌机数量
    BIG='B',
    SMALL='S'
};

struct plane
{
    int x; // 飞机的x坐标
    int y; // 飞机的y坐标
    bool live; // 飞机是否存活
    int width; // 飞机宽度
    int height; // 飞机高度
    int hp; // 飞机血量
    char type; // 飞机类型
} player, bull[BULLET_NUM], enemy[ENEMY_NUM];

void enemyHP(int i)
{
    int flag = rand() % 10;
    if (flag >= 0 && flag <= 2)
    {
        enemy[i].type = SMALL;
        enemy[i].hp = 1;
        enemy[i].width = 57;
        enemy[i].height = 43;
    }
    else
    {
        enemy[i].type = BIG;
        enemy[i].hp = 3;
        enemy[i].width = 69;
        enemy[i].height = 99;
    }
}

void gameinit()
{
    player.x = WIDTH / 2;
    player.y = HEIGHT - 120;
    player.live = true;

    for (int i = 0; i < BULLET_NUM; i++)
    {
        bull[i].x = 0;
        bull[i].y = 0;
        bull[i].live = false;
    }

    for (int i = 0; i < ENEMY_NUM; i++)
    {

        enemy[i].live = false;
        enemyHP(i);
    }
}

void loadImg()
{
    loadimage(&img, "background.png");
    loadimage(&player1, "images\\me1.png");
    loadimage(&bullet[0], "images\\bullet1.png");
    loadimage(&bullet[1], "images\\bullet2.png");
    loadimage(&enemyIMG[0], "images\\enemy1.png");
    loadimage(&enemyIMG[1], "images\\enemy2.png");
}

void gameDraw()
{
    loadImg();
    putimage(0, 0, &img);
    putimage(player.x, player.y, &player1);

    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (bull[i].live)
        {
            putimage(bull[i].x, bull[i].y, &bullet[0], NOTSRCERASE);
            putimage(bull[i].x, bull[i].y, &bullet[1], SRCINVERT);
        }
    }

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (enemy[i].live)
        {
            if (enemy[i].type == BIG)
            {
                putimage(enemy[i].x, enemy[i].y, &enemyIMG[1]);
            }
            else
            {
                putimage(enemy[i].x, enemy[i].y, &enemyIMG[0]);
            }
        }
    }
}

bool timer(int ms, int id)
{
    static DWORD t[20];
    if (clock() - t[id] > ms)
    {
        t[id] = clock();
        return true;
    }
    return false;
}

void createbullet()
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (!bull[i].live)
        {
            bull[i].x = player.x + 60;
            bull[i].y = player.y;
            bull[i].live = true;
            break;
        }
    }
}

void createnemy()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (!enemy[i].live)
        {
            enemy[i].x = rand() % (WIDTH - 60);
            enemy[i].y = 0;
            enemy[i].live = true;
            enemyHP(i);
            printf("(type:%c) (x:%d) (y:%d) (state:%d) (HP:%d)\n", enemy[i].type, enemy[i].x, enemy[i].y, enemy[i].live, enemy[i].hp);
            break;
        }
    }
}

void enemymove(int speed)
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (enemy[i].live)
        {
            enemy[i].y += speed;
            if (enemy[i].y > HEIGHT)
            {
                enemy[i].live = false;
            }
        }
    }
}

void BulletMove(int speed)
{
    if (GetAsyncKeyState(VK_SPACE) && timer(100, 1))
    {
        createbullet();
    }

    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (bull[i].live)
        {
            bull[i].y -= speed;
            if (bull[i].y < 0)
            {
                bull[i].live = false;
            }
        }
    }
}

void playermove(int speed)
{
    if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
    {
        if (player.y > 0) player.y -= speed;
    }
    if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
    {
        if (player.y < HEIGHT - 100) player.y += speed;
    }
    if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
    {
        if (player.x > -50) player.x -= speed;
    }
    if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
    {
        if (player.x < WIDTH - 50) player.x += speed;
    }
}

void hit()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (!enemy[i].live)
            continue;

        for (int j = 0; j < BULLET_NUM; j++)
        {
            if (!bull[j].live)
                continue;

            if (bull[j].x > enemy[i].x &&
                bull[j].x < enemy[i].x + enemy[i].width &&
                bull[j].y > enemy[i].y &&
                bull[j].y < enemy[i].y + enemy[i].height)
            {
                bull[j].live = false;
                enemy[i].hp--;
            }
        }

        if (enemy[i].hp <= 0)
        {
            enemy[i].live = false;
        }
        // 检测玩家飞机和敌机的碰撞
        for (int i = 0; i < ENEMY_NUM; i++)
        {
            if (player.x + player.width > enemy[i].x &&
                player.x < enemy[i].x + enemy[i].width &&
                player.y + player.height > enemy[i].y &&
                player.y < enemy[i].y + enemy[i].height)
            {
                game_over = true;
            }
        }
    }
}

int main()
{
    initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
    srand(time(NULL));
    gameinit();
    loadImg();
    BeginBatchDraw();

    while (1)
    {
        gameDraw();
        FlushBatchDraw();
        playermove(3);
        BulletMove(1);
        if (timer(500, 0)) createnemy();
        if (timer(5, 2)) enemymove(1);
        hit();
        if (game_over)
        {
            printf("Game Over!\n");
            break;
        }
    }
    
    EndBatchDraw();
    return 0;
}
