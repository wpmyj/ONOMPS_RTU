#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>  
#include <fcntl.h>  
#include <string.h>  
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>  

#define MaxQueueSize    1024  //信号处理队列最大长度
#define MAX_PID_NUM     32  
#define MAX_TEXT        512   //消息队列最大长度


#define OTDR_MESSAGE_TYPE     1
#define CYCLE_MESSAGE_TYPE    2
#define ALARM_MESSAGE_TYPE    3
#define PROTECT_MESSAGE_TYPE  4

#define ALARM_MESSAGE_KEY     2222
#define CYCLE_MESSAGE_KEY     3333 
#define PROTECT_MESSAGE_KEY   4444

union semun   
{  
    int val;  
    struct semid_ds *buf;  
    unsigned short *arry;  
};                                             //信号量，做进程间同步



  
struct msg_st                                  //消息队列，服务器判断设置是否成功
{  
        long int msg_type;  
        char text[BUFSIZ];  
};  
  

typedef struct queue{                          //队列，用户处理信号（SIGMIN和SIGMIN+1）
   int value[MaxQueueSize];
   int head;
   int tail;
   int count;
}queue;



int set_semvalue();  
void del_semvalue();  
int semaphore_p();  
int semaphore_v();  





int sendMessageQueue_Boa(char * message,long msgType);
int sendMessageQueue_Block(char * message,long msgType);
int sendMessageQueue_Function(char * message ,key_t key);


char * recvMessageQueue_Block(char * waitStr ,long msgType);
int  recvMessageQueue_Backstage(char *waitStr,long msgType);
int    recvMessageQueue_OTDR(char * backMSG, key_t key);
void   sigOutime(int signo);

queue *Queue_Initiate();  //初始化队列
int  Queue_Append(queue *q,int  value); //入队
int  Queue_Delete(queue *q,int *value); //出队
int  Queue_isEmpty(queue *q);           //判断队列空
int  Queue_getData(queue *q,int * value); //获取队头数据


char *basename(const char *path);
int get_pid_by_name(const char* process_name, pid_t pid_list[], int list_size);
int is_process_exist(const char* process_name);
#endif // PROCESS_H_INCLUDE
