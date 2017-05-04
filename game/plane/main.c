#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
// 屏幕大小
int screenWidth;
int screenHeight;
// 飞机坐标
int xPlane;
int yPlane;
// 敌机坐标
int xEnemy;
int yEnemy;
// 子弹坐标
int xBullet;
int yBullet;

int isKilled = 0; // is enemy plane killed
int score = 0;

void initial();
void startUp();
void showPlane();
void showScore();
void showEnemy();
void showFire();
void getInput();
int randInt();

int main()
{
	initial();
	startUp();

	while (1)
	{
		clear();   // 清屏函数
		box(stdscr,'|','-');
		showEnemy();
		showFire();
		showPlane();
		// 放在最后显示，将光标也已到坐上面
		showScore();
		getInput();
	}

	return 0;
}
/* 自定開啟 curses 函式 */
void initial()
{
	initscr();
	cbreak();
	nonl();
	noecho();
	// 不等待键盘输入
    nodelay(stdscr, TRUE);
	intrflush(stdscr, TRUE);
	keypad(stdscr, TRUE);
	refresh();
}

void startUp()
{
	screenWidth = getmaxx(stdscr);
	screenHeight = getmaxy(stdscr);
	xPlane = screenWidth / 2 - 10 + randInt() % 20;
	yPlane = screenHeight - 3;

	xEnemy = randInt() % screenWidth / 3 + 2;
	yEnemy = randInt() % screenHeight / 3 + 2;
}

void showPlane()
{
	mvaddch(yPlane, xPlane, '*');
	mvaddch(yPlane + 1, xPlane - 1, '*');
	mvaddch(yPlane + 1, xPlane + 1, '*');
	mvaddch(yPlane - 1, xPlane, '*');
	mvaddch(yPlane - 1, xPlane - 1, '*');
	mvaddch(yPlane - 1, xPlane - 2, '*');
	mvaddch(yPlane - 1, xPlane + 1, '*');
	mvaddch(yPlane - 1, xPlane + 2, '*');
	mvaddch(yPlane - 2, xPlane, '*');
}

void showScore()
{
	mvprintw(0,0, "score:%d", score);
}

void showEnemy()
{
	if (!isKilled)
	{
		// 输出靶子
		mvaddch(yEnemy, xEnemy, '+');
		// mvaddch(yEnemy - 1, xEnemy - 1, '+');
		// mvaddch(yEnemy - 1, xEnemy + 1, '+');
	}

	if ((xBullet == xEnemy) && (yBullet==yEnemy))  // 子弹击中敌机
	{
		score++;                // 分数加1
		yEnemy = -1;           // 产生新的飞机
		xEnemy = randInt() % screenWidth;
		xBullet = -2;          // 子弹无效
	}
	if (yEnemy > screenHeight)   // 敌机跑出显示屏幕
	{
		yEnemy = -1;           // 产生新的飞机
		xEnemy = randInt() % screenWidth;
	}

	// 用来控制敌机向下移动的速度。每隔几次循环，才移动一次敌机
	// 这样修改的话，用户按键交互速度还是保持很快，但我们NPC的移动显示可以降速
	static int speed = 0;
	if (speed < 1000)
		speed++;
	if (speed == 1000) {
		yEnemy++;
		speed = 0;
	}
}

void showFire()
{
	static int speed = 0;
	if(yBullet > -1) {
		mvaddch(yBullet, xBullet, '|');
		if (speed < 1000)
			speed++;
		if (speed == 1000) {
			yBullet--;
			speed = 0;
		}
	}
}

void getInput()
{
	char input = getch();  // 根据用户的不同输入来移动

	if ((input == 'a' || input == 'A') && xPlane > 3)
		xPlane--;
	if ((input == 'd' || input == 'D') && xPlane < screenWidth - 3)
		xPlane++;
	if ((input == 'w' || input == 'W') && yPlane > 3)
		yPlane--;
	if ((input == 's' || input == 'S') && yPlane < screenHeight - 3)
		yPlane++;
	if (input == ' ') {
		xBullet = xPlane;
		yBullet = yPlane - 3;
	}
}

int randInt()
{
	time_t t;
   /* 初始化随机数发生器 */
   srand((unsigned) time(&t));
   return rand();
}