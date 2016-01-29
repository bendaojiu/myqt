#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "pub.h"
#include "work.h"

int main(int arg, char *args[])
{
	if (arg < 2)//如果没有参数，main函数返回
	{
		printf("usage:qqserverd port\n");
		return -1;
	}

	int iport = atoi(args[1]);//把第二个参数，转化为整数
	if (iport == 0)
	{
		printf("port %d is invalid\n", iport);
		return -1;
	}

	work w(iport);

	if (w.conn2db("loaclhost", "dbuser1", "dbuser1", "orcl") != 0)
	{
		return -1;
	}

	printf("qqserver begin\n");
	setdaemon();//将程序设置为daemon状态
	signal1(SIGINT, catch_Signal);
	signal1(SIGPIPE, catch_Signal);

	w.run();
	printf("qqserver end\n");
	return 0;
}
