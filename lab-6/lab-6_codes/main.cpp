
#include <iostream>
#include<bits/stdc++.h>
using namespace std;



int FIFO(vector<int>&pages, int size,int frameno)
{
    // 0) Initialize Frames With '-1'
    cout<<"request"<<"  "<<"miss/hit     "<<" "<<"f1   "<<"   "<<"f2   "<<"   "<<"f3"<<endl;
    cout<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    int frames[frameno];
    for (int i = 0; i < frameno; i++)
        frames[i] = -1;

    int paeFaults = 0; // Count The Page Faults
    int victim = 0;    // The Index Of The Frame To Put A Page At, In Case No Free Frames Found

    // Go Through All Pages
    for (int pageIndex = 0; pageIndex < size; pageIndex++)
    {

        // 1) Find Page In The Frames
        bool isFound = false;
        for (int i = 0; i < frameno; i++)
            if (frames[i] == pages[pageIndex])
            {
                isFound = true;
                // Printing
                cout << pages[pageIndex] << "\t";
                cout<<"  HIT  "<<endl;
                 break;
            }

        // If Not Found
        if (!isFound)
        {
            // 2) Find A Free Frame
            bool hasFreeFrame = false;
            for (int i = 0; i < frameno; i++)
                if (frames[i] == -1)
                {
                    hasFreeFrame = true;
                    frames[i] = pages[pageIndex];
                    paeFaults++;

                    // Printing
                    cout << pages[pageIndex] << "\t";
                    cout<<"  MISS  "<<"\t";
                    for (int f = 0; f < frameno; f++)
                        cout << frames[f] << "\t";
                    cout << endl;

                    break;
                }

            // 3) Page Replacement (Not Found & No Free Frame)
            if (!hasFreeFrame)
            {
                frames[victim] = pages[pageIndex];
                victim = (victim + 1) % frameno;
                paeFaults++;

                // Printing
                cout << pages[pageIndex] << "\t";
                cout<<"  MISS  "<<"\t";
                for (int f = 0; f < frameno; f++)
                    cout << frames[f] << "\t";
                cout << endl;
            }
        }
    }
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    return paeFaults;
}
int LRU(vector<int>&pages, int size,int frameno)
{
    // 0) Initialize Frames With '-1'
    cout<<"request"<<"  "<<"miss/hit     "<<" "<<"f1   "<<"   "<<"f2   "<<"   "<<"f3"<<endl;
    cout<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    int frames[frameno];
    for (int i = 0; i < frameno; i++)
        frames[i] = -1;

    int paeFaults = 0; // Count The Page Faults

    // Go Through All Pages
    for (int pageIndex = 0; pageIndex < size; pageIndex++)
    {

        // 1) Find Page In The Frames
        bool isFound = false;
        for (int i = 0; i < frameno; i++)
            if (frames[i] == pages[pageIndex])
            {
                isFound = true;
                // Printing
                cout << pages[pageIndex] <<"\t";
                cout<<"  HIT  "<<endl;
                 break;
            }

        // If Not Found
        if (!isFound)
        {
            // 2) Find A Free Frame
            bool hasFreeFrame = false;
            for (int i = 0; i < frameno; i++)
                if (frames[i] == -1)
                {
                    hasFreeFrame = true;
                    frames[i] = pages[pageIndex];
                    paeFaults++;

                    // Printing
                    cout << pages[pageIndex] << "\t";
                    cout<<"  MISS  "<<"\t";
                    for (int f = 0; f < frameno; f++)
                        cout << frames[f] << "\t";
                    cout << endl;

                    break;
                }

            // 3) Page Replacement (Not Found & No Free Frame)
            if (!hasFreeFrame)
            {
                // Array To Store The Last Index For Each Page In The Frames
                int lastUse[frameno];

                // Assign Last Index For Each Page In The Frames
                for (int i = 0; i < frameno; i++)
                    for (int p = pageIndex; p >= 0; p--)
                        if (pages[p] == frames[i])
                        {
                            lastUse[i] = p;
                            break;
                        }

                // Find The Victim Frame (With The Lowest Index)
                int victim = 0;
                for (int i = 0; i <frameno; i++)
                    if (lastUse[i] < lastUse[victim])
                        victim = i;

                frames[victim] = pages[pageIndex];
                paeFaults++;

                // Printing
                cout << pages[pageIndex] << "\t";
                cout<<"  MISS  "<<"\t";
                for (int f = 0; f < frameno; f++)
                    cout << frames[f] << "\t";
                cout << endl;
            }
        }
    }
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    return paeFaults;
}

int Optimal(vector<int>&pages, int size,int frameno)
{
    // 0) Initialize Frames With '-1'
    cout<<"request"<<"  "<<"miss/hit     "<<" "<<"f1   "<<"   "<<"f2   "<<"   "<<"f3"<<endl;
    cout<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    int frames[frameno];
    for (int i = 0; i < frameno; i++)
        frames[i] = -1;

    int paeFaults = 0; // Count The Page Faults

    // Go Through All Pages
    for (int pageIndex = 0; pageIndex < size; pageIndex++)
    {

        // 1) Find Page In The Frames
        bool isFound = false;
        for (int i = 0; i < frameno; i++)
            if (frames[i] == pages[pageIndex])
            {
                isFound = true;
                // Printing
                cout << pages[pageIndex] << "\t";
                cout<<"  HIT  "<<endl;
                 break;
            }

        // If Not Found
        if (!isFound)
        {
            // 2) Find A Free Frame
            bool hasFreeFrame = false;
            for (int i = 0; i < frameno; i++)
                if (frames[i] == -1)
                {
                    hasFreeFrame = true;
                    frames[i] = pages[pageIndex];
                    paeFaults++;

                    // Printing
                    cout << pages[pageIndex] << "\t";
                    cout<<"  MISS  "<<"\t";
                    for (int f = 0; f < frameno; f++)
                        cout << frames[f] << "\t";
                    cout << endl;

                    break;
                }

            // 3) Page Replacement (Not Found & No Free Frame)
            if (!hasFreeFrame)
            {
                // Init Array To Store The Next Index For Each Page In The Frames
                int nextUse[frameno];
                for (int i = 0; i < frameno; i++)
                    nextUse[i] = size + 1;

                // Assign Next Index For Each Page In The Frames
                for (int i = 0; i < frameno; i++)
                    for (int p = pageIndex; p < size; p++)
                        if (pages[p] == frames[i])
                        {
                            nextUse[i] = p;
                            break;
                        }

                // Find The Victim Frame (With The Highest Index)
                int victim = 0;
                for (int i = 0; i < frameno; i++)
                    if (nextUse[i] > nextUse[victim])
                        victim = i;

                frames[victim] = pages[pageIndex];
                paeFaults++;

                // Printing
                cout << pages[pageIndex] << "\t";
                cout<<"  MISS  "<<"\t";
                for (int f = 0; f < frameno; f++)
                    cout << frames[f] << "\t";
                cout << endl;
            }
        }
    }
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    return paeFaults;
}
int main()
{
    cout<<"Enter no of frame numbers:"<<endl;
    int frame_no;
    cin>>frame_no;
    cout<<"Enter page number:"<<endl;
    int pageno;
    cin>>pageno;
    vector<int>pages;
    for(int i=0;i<pageno;i++){
        int x;
        cin>>x;
        pages.push_back(x);
    }
    //int pages[] = {1, 2, 3, 1, 4, 5, 2, 1, 2, 6, 7, 3, 2};
   for(int i=frame_no;i<=8;i++){
        cout<<"For page frame"<<" "<<i<<endl;
        cout<<endl;
        cout<<"-----------------------------------------------------------------------------------------"<<endl;
        cout<<endl;
         cout<<"FIFO page replacement algorithm"<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout << "Number Of Page Faults = " << FIFO(pages, pageno,i)<<endl;
    cout<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"LRU page replacement algorithm"<<endl;
   cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout << "Number Of Page Faults = " << LRU(pages, pageno,i)<<endl;
    cout<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Optimal page replacement algorithm"<<endl;
   cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout << "Number Of Page Faults = " << Optimal(pages, pageno,i)<<endl;
    cout<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
   }
   
    getchar();
    return 0;
}