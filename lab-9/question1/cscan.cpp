
#include<bits/stdc++.h>
using namespace std;


int i;
int j;

int getIndex(int val , int arr[] , int n){
    for(i=0; i<n; i++){
    if(val == arr[i]){
      return i;
    }
  }
}

int main(){
    int totalNumOfCylinders;
    cout<<"Enter the total number of cylinders : ";
    cin>>totalNumOfCylinders;

    int requestQueue[20];
    int head,  totalNumberOfRequests, larger;

    cout<<"Input number of requests : ";
    cin>>totalNumberOfRequests;
    double *waitTime;
    double *turnaroundTime;
    double avgWaitTime;
    double avgTurnaroundTime;

    waitTime = (double *)malloc(totalNumberOfRequests * sizeof(double));
    turnaroundTime = (double *)malloc(totalNumberOfRequests * sizeof(double));
    int headIsRequested = 0;

    cout<<"Enter head position : \n";
    cin>>head;
    cout<<"Input requests : \n";
 
    i=0;
    while(i<totalNumberOfRequests){
      cin>>requestQueue[i];
      if(requestQueue[i] == head){
        headIsRequested = 1;
      }
      i++;
    }


    if (headIsRequested == 0){
 
      int headPosition = totalNumberOfRequests;
      requestQueue[headPosition] = head; 
      totalNumberOfRequests++;
    }
    int lastIndex = totalNumberOfRequests-1;
    i=0;
    while(i<totalNumberOfRequests){
        j=i;
        while(j<totalNumberOfRequests){
            if(requestQueue[i]>requestQueue[j]){
                    larger = requestQueue[i];
                    requestQueue[i] = requestQueue[j];
                    requestQueue[j] = larger;
            }
            j++;
        }
        i++;
    }



    int *processedRequests;
    processedRequests = (int *)malloc(totalNumberOfRequests * sizeof(int));
    for( i=0; i<totalNumberOfRequests; i++){
      processedRequests[i] = 0;
    }

//get index of head in sorted queue
    int head_Index = getIndex(head, requestQueue, totalNumberOfRequests);

    int Total_Movement = 0;

    double currentTime = 0;
    double cylShiftTime = 0.001; //ms
    double timeToProcess = 0.100; //ms
    int prevCylinder = head;
    int currentCylinder = head;
 
    if(abs(head-0) <= abs(head-totalNumOfCylinders)){ //to left
    j=head_Index;
    while(j>=0){
        currentCylinder=requestQueue[j];
        Total_Movement += abs(currentCylinder-prevCylinder);
        double timeTakenForShift = abs(currentCylinder-prevCylinder)*cylShiftTime;
        currentTime = currentTime + timeTakenForShift;
        waitTime[j] = currentTime;

        cout<<requestQueue[j]<<" -->";

        prevCylinder = currentCylinder;
        if(requestQueue[j] == head && headIsRequested==1){
          turnaroundTime[j] = currentTime + timeToProcess;
        currentTime = currentTime  + timeToProcess;
    
        }
        else if(requestQueue[j]!=head){
                turnaroundTime[j] = currentTime + timeToProcess;
        currentTime = currentTime  + timeToProcess;
        }
     
        processedRequests[j] = 1;
        j--;
    }
    prevCylinder=totalNumOfCylinders-1;
    currentCylinder=totalNumOfCylinders-1;
    for(j=lastIndex; j>head_Index; j--){
        currentCylinder=requestQueue[j];
        Total_Movement += abs(currentCylinder-prevCylinder);
        double timeTakenForShift = abs(currentCylinder-prevCylinder)*cylShiftTime;
        currentTime = currentTime + timeTakenForShift;
        waitTime[j] = currentTime;
        cout<<requestQueue[j]<<" -->";

        prevCylinder = currentCylinder;
        if(requestQueue[j] == head && headIsRequested==1){
          turnaroundTime[j] = currentTime + timeToProcess;
        currentTime = currentTime  + timeToProcess;
    
        }
        else if(requestQueue[j]!=head){
                turnaroundTime[j] = currentTime + timeToProcess;
        currentTime = currentTime  + timeToProcess;
        }
        processedRequests[j] = 1;
         
  
      }

      }  // one direction left
      
      
      else { //other direction right

      for(j=head_Index+1; j<totalNumberOfRequests; j++){

        // printf("%s\n", "Moving to right");
        // printf("current time : %f\n", currentTime);
        currentCylinder=requestQueue[j];
        Total_Movement += abs(currentCylinder-prevCylinder);
        double timeTakenForShift = abs(currentCylinder-prevCylinder)*cylShiftTime;
        currentTime = currentTime + timeTakenForShift;
        waitTime[j] = currentTime;

          cout<<requestQueue[j]<<" -->";

        prevCylinder = currentCylinder;
           if(requestQueue[j] == head && headIsRequested==1){
          turnaroundTime[j] = currentTime + timeToProcess;
        currentTime = currentTime  + timeToProcess;
    
        }
        else if(requestQueue[j]!=head){
                turnaroundTime[j] = currentTime + timeToProcess;
        currentTime = currentTime  + timeToProcess;
        }
            processedRequests[j] = 1;
      }
      prevCylinder=0;
      currentCylinder=0;
      for(j=0; j<=head_Index; j++){
        // printf("%s\n", "Moving to right");
        //    printf("current time : %f\n", currentTime);
        currentCylinder=requestQueue[j];
        Total_Movement += abs(currentCylinder-prevCylinder);
        double timeTakenForShift = abs(currentCylinder-prevCylinder)*cylShiftTime;
        currentTime = currentTime + timeTakenForShift;
        waitTime[j] = currentTime;

          cout<<requestQueue[j]<<" -->";

        prevCylinder = currentCylinder;
                if(requestQueue[j] == head && headIsRequested==1){
          turnaroundTime[j] = currentTime + timeToProcess;
        currentTime = currentTime  + timeToProcess;
    
        }
        else if(requestQueue[j]!=head){
                turnaroundTime[j] = currentTime + timeToProcess;
        currentTime = currentTime  + timeToProcess;
        }
            processedRequests[j] = 1;
              //  printf("current time : %f\n", currentTime);
      }

  }
cout<<"end"<<endl;
double totalReq = 0.0;
for(j=0;j<totalNumberOfRequests;j++){
    avgWaitTime += waitTime[j];
    avgTurnaroundTime += turnaroundTime[j];
    cout<<"For request :"<<requestQueue[j]<<endl;
    cout<<"Wait Time :"<<waitTime[j]<<endl;
    cout<<"Wait Time :"<<turnaroundTime[j]<<endl;
    totalReq = totalReq+1.0;

}

avgWaitTime = avgWaitTime/totalReq;
avgTurnaroundTime = avgTurnaroundTime/totalReq;
cout<<"Average Wait Time :"<<avgWaitTime<<endl;
cout<<"Average Turnaround Time :"<<avgTurnaroundTime<<endl;
cout<<"\nTotal movement of cylinders :"<<Total_Movement;

  return 0;
}