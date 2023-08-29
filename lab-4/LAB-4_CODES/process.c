#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/msg.h>

#define MAX 1024
#define KEY 130

typedef struct message
{
	long type;
	char data[MAX];

}message;
int counter=0,iterations=0,flag=0,i=0;       
int root_pid;  

int noi,prior,sleeptime,prob,msqid;
pid_t proc_pid;

void notify();
void suspend();
void iterate();

message msg;   
int flg=0;
float power(int a,int n){
    float den = (float)n;
    float num = (float)1;
    float x;    				// Next x - Newton's method
	float x0 = 1;				// Current x - Newton's method, initial value set to 1
	float tol = 1;				// Tolerance - Newton's method
	float atonum = a;			// Variable for computing a^(num)
	float xtoden;				// Variable for computing x0^(den)
	
	for (int i=1; i<num; i++) atonum = atonum*a;
	
	while (tol > 0.0001){							//
		xtoden = x0;							//
		for (int i=1; i<den; i++) xtoden = xtoden*x0;			//
		x = x0 - (xtoden-atonum) / ((den)*(xtoden/x0));			//
		tol = ((x-x0)/x0)*100;						//  Newton's Method Iterations
		if (tol < 0) tol = tol*(-1);					//
		x0 = x;								//
	}
    return x;
}
int main( int argc,char *argv[]  ){
	srand(time(NULL));    
	key_t key=130;
	
	int pid;
	char buff[MAX],buffer[MAX];
	proc_pid=getpid();
	
	printf("PID %d\n",proc_pid);

	signal(SIGUSR1,suspend);
	signal(SIGUSR2,notify);


	if(argc!=5){
		printf("error in the number of passed parameters\n");
		exit(0);
	}

	noi=atoi(argv[1]);
	prior=atoi(argv[2]);
	prob=atoi(argv[3]);
	sleeptime=atoi(argv[4]);

	printf("In round %d prior=%d prob=%d slptime=%d \n",noi,prior,prob,sleeptime);
	iterations=noi;   

	msqid=msgget(key,IPC_CREAT|0644);
	sprintf(buffer,"%d ",proc_pid);   
	sprintf(buff,"%d",prior);        
	strcat(buffer,buff);
	strcat(msg.data,buffer);
	printf("sending message %s\n",msg.data);
	msg.type=1;         
	int stat=msgsnd(msqid,&msg,MAX,0);
	if(stat<0)
		printf("failed\n");


	msgrcv(msqid,&msg,MAX,proc_pid,MSG_NOERROR);
	
	root_pid=atoi(msg.data);
	printf("Sched PID %d \n",root_pid);




	pause(); 
	flag=1;
	

	
	
	iterate();


	return 0;
}


void iterate()
{
	printf("starting iterations\n");
	int pb,stat;
	for(i=counter;i<iterations;i++,counter++)
	{
		
		while(flg==1)
		{
			sleep(1);
		}

		pb=1 + rand()%100;
		if(prob > 0.3)
		{

			kill(root_pid,SIGUSR1); 

			printf("PID: %d Going for IO  at i =%d value of iter %d \n",proc_pid,i,iterations );
			sleep(sleeptime);

	
			sprintf(msg.data,"%d",proc_pid);
			msg.type=2;
			stat=msgsnd(msqid,&msg,MAX,0);
			if(stat==-1)
				printf("not sent\n");

			pause();
			printf("waking\n");
			
		}

	}

	if(i==iterations)
	{
	
		kill(root_pid,SIGUSR2); 
	}
}

void notify()
{
	printf("signal received \n");
	flg=0;
	signal(SIGUSR1,suspend);
}

void suspend()
{
	signal(SIGUSR2,notify);
	printf("being suspended by sched\n");
	counter=i;
	flg=1;
}
