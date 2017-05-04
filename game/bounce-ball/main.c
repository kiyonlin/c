#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
	int left = 0;
	int right = 100;
	int top = 0;
	int bottom = 50;
	time_t t;
	/* 初始化随机数发生器 */
    srand((unsigned) time(&t));

    // 随机小球的初始位置
	int x = rand() % bottom;
	int y = rand() % right;

	// sleep time 速度，单位微秒us，越大速度越慢
	useconds_t stime = 50000;

	// 每次变化的跨度
	int velocity_x = 1;
	int velocity_y = 1;


	while (1)
	{
		x = x + velocity_x;
		y = y + velocity_y;

		system("clear");   // 清屏函数
		// 输出小球前的空行
		for(int i=0; i<x; i++)
			printf("\n");
		for (int j=0; j<y; j++)
			printf(" ");
		printf("O");  // 输出小球o
		printf("\n");

		// 单位微秒us
		usleep(stime);  // 等待若干毫秒

		// 边界处理
		if ((x <= top) || (x >= bottom)) {
			velocity_x = -velocity_x;
		}
		if ((y <= left)||(y >= right)) {
			velocity_y = -velocity_y;
		}
	}
}