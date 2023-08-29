 #define MAX 20
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<bits/stdc++.h>
using namespace std;
void *monitor_cut_hair(void *param) {
   int worktime; 
   while(true) {  
	  sem_wait(&(monitor.sem_customer));
	  sem_wait(&(monitor.chairs_mutex));
	  monitor.VacantChairs += 1;
	  cout<<"Barber busy.... Number of chairs available ="<<monitor.VacantChairs<<"\n";
	  if(monitor.VacantChairs==monitor.TotalChairs){
	  	cout<<"No waiting customer . Barber sleeps ......\n";
  	  }
	  sem_post(&(monitor.sem_barber)); //barber get ready
      cout<<"Barber is ready to cut hair\n";
      sem_post(&(monitor.chairs_mutex)); 
      cout<<"Barber is cutting hair...\n";
      sleep(3);
   } 
}

void *monitor_get_hair_cut(void *param) {
   int waittime;
   while(true) { 
	  sem_wait(&(monitor.chairs_mutex));
	  if(monitor.VacantChairs <= 0){
		   cout<<"Customer "<<(unsigned int)pthread_self()-1<<" leaving with no haircut\n"; //no chair avail => cust leaves
		   sem_post(&(monitor.chairs_mutex));
	  }
	  else{ //seat avail
         
		   monitor.VacantChairs -= 1; //given to new cust
		   cout<<"Customer "<<(unsigned int)pthread_self()-1<<" is waiting on seat. Number of seats left = "<<monitor.VacantChairs<<"\n";
		   sem_post(&(monitor.sem_customer));
		   sem_post(&(monitor.chairs_mutex));
		   sem_wait(&(monitor.sem_barber)); //wait for barber to get ready
		   cout<<"Customer "<<(unsigned int)pthread_self()-1<<" is getting a haircut\n";
	  }
	  waittime = (rand() % monitor.customerWait) + 1;
	  sleep(waittime);
    }
}

struct monitor_data{
	int TotalChairs; //global total seats
	sem_t chairs_mutex;
	sem_t sem_customer;
	sem_t sem_barber;
	int VacantChairs; //input -> keep editing
	int customerWait;
};
struct monitor_data monitor;


int main() {
	pthread_t barberid;
	pthread_t customerids[MAX];
	cout<<"Shop opens\n";
    int runTime,numOfCustomers,i;
	cout<<"Enter total number of Customers : \n";
	cin>>numOfCustomers;
   	cout<<"Enter number of chairs : \n";
	cin>>monitor.VacantChairs;
	monitor.TotalChairs = monitor.VacantChairs;
	runTime = 5;
 	monitor.customerWait = 1;
	sem_init(&(monitor.chairs_mutex),0,1);
	sem_init(&(monitor.sem_customer),0,0);
	sem_init(&(monitor.sem_barber),0,0);
   	pthread_create(&barberid, NULL, monitor_cut_hair, NULL);
   	cout<<"Barber is ready to serve\n";
	i=0;
	while(i<numOfCustomers){
		cout<<"Creating customer thread : id  ="<<i+1<< "\n";
	   	pthread_create(&customerids[i], NULL, monitor_get_hair_cut, NULL);
		i++;
	}
	cout<<"End\n";
   	exit(0);
}
