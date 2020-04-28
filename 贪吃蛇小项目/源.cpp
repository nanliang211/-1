#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<graphics.h>

using namespace std;
const int N = 100;
const int size1 = 10;
enum Ch
{
	up=72,down=80,left=75,right=77
};
class Coor
{
public:
	int x;
	int y;
};
class Snake
{
public:
	int n;//当前有几节蛇
	Coor szb[N];
	Ch ch;//方向
};
class Food
{
public:
	Coor fzb;
	bool iseat;
};
Food food;
Snake snake;
void GameInit()
{
	srand((unsigned int)time(NULL));
	initgraph(640, 480,SHOWCONSOLE);
	snake.n = 3;
	snake.ch = Ch::right;
	snake.szb[0].x = 100;
	snake.szb[0].y = 100;
	snake.szb[1].x = 90;
	snake.szb[1].y = 100;
	snake.szb[2].x = 80;
	snake.szb[2].y = 100;
	food.iseat = 1;
}
//绘制蛇
void DrawSnake()
{
	system("cls");
	cleardevice();
	cout << "蛇的当前节数" << snake.n << endl;
	cout << "蛇的当前方向" << snake.ch << endl;
	for (int i = 0; i < snake.n; i++)
	{
		cout << "第" << i + 1 << "节蛇的坐标" << snake.szb[i].x <<" "<< snake.szb[i].y << endl;
		setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		fillrectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x+size1,snake.szb[i].y+size1);	
	}
	fillrectangle(food.fzb.x, food.fzb.y, food.fzb.x + size1, food.fzb.y + size1);
}
void Snakemove()
{
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.szb[i].x = snake.szb[i - 1].x;
		snake.szb[i].y = snake.szb[i - 1].y;
	}
	switch (snake.ch)
	{
	case Ch::up:
		snake.szb[0].y -= size1;
		break;
	case Ch::down:
		snake.szb[0].y += size1;
		break;
	case Ch::left:
		snake.szb[0].x -= size1;
		break;
	case Ch::right:
		snake.szb[0].x += size1;
		break;
	default:
		break;
	}
}
//改变方向
void ChangeCh()
{
	char key;//int_cdecl
	key =  _getch();//接收键盘的输入
	switch(key)
	{
	case Ch::up:
		if(snake.ch!=Ch::down)
		snake.ch = up;
		break;
	case Ch::down:
		if (snake.ch != Ch::up)
		snake.ch = down;
		break;
	case Ch::left:
		if (snake.ch != Ch::right)
		snake.ch = Ch::left;
		break;
	case Ch::right:
		if (snake.ch != Ch::left)
		snake.ch = Ch::right;
		break;
	}
}
void CreateFood()
{
	int flag;
	while (true)
	{
		flag = 0;
		food.fzb.x = rand() % 64 * 10;
		food.fzb.y = rand() % 48 * 10;
		for (int i = 0; i < snake.n; i++)
		{
			if (snake.szb[i].x == food.fzb.x && snake.szb[i].y == food.fzb.y)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			continue;
		}
		else
		{
			food.iseat = 0;
			break;
		}
	}
}
void EatFood()
{
	if (snake.szb[0].x == food.fzb.x && snake.szb[0].y == food.fzb.y)
	{
		food.iseat = 1;
		snake.n++;
	}
}
int main()
{
	GameInit();
	while (1)
	{
		while (!_kbhit())
		{
			if (food.iseat == 1)
			{
				CreateFood();
			}
			DrawSnake();
			Snakemove();
			EatFood();
			Sleep(10);
		}
		
		 ChangeCh();
	}
	
}