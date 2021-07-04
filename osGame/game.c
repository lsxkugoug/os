# include <stdio.h>
# include <curses.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <stdbool.h>

# define CHAR_BIRD 'O'  // bird
# define CHAR_STONE '*'  // obstacle
# define CHAR_BLANK ' '  // space

typedef struct node {
    int x, y;
    struct node *next;
}node, *Node;

Node head, tail;
int bird_x, bird_y;
int ticker;

void init();  // 初始化函数，统筹游戏各项的初始化工作
void init_bird();  // 初始化 bird 位置坐标
void init_draw();  // 初始化背景
void init_head();  // 初始化存放柱子的链表的链表头
void init_wall();  // 初始化存放柱子的链表
void drop(int sig);  // 信号接收函数，用来接收到系统信号，从右向左移动柱子
int set_ticker(int n_msec);  // 设置内核的定时周期
int main(){


}

int set_ticker(int n_msec)
{
    struct itimerval timeset;
    long n_sec, n_usec;

    n_sec = n_msec / 1000;
    n_usec = (n_msec % 1000) * 1000L;

    timeset.it_interval.tv_sec = n_sec;
    timeset.it_interval.tv_usec = n_usec;

    timeset.it_value.tv_sec = n_sec;
    timeset.it_value.tv_usec = n_usec;

    return setitimer(ITIMER_REAL, &timeset, NULL);
}