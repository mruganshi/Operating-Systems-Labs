#include <bits/stdc++.h>
using namespace std;
  
int main()
{
    
    ifstream file("gfg.txt");
    string content;
   ofstream myFile_Handler;
    // File Open
    myFile_Handler.open("op.txt");
    while(file >> content) {
	    for(auto &it : content){
      		 if(isalpha(it)){
        		 it ^= (1 << 5);
      		 }
    		}
        myFile_Handler << content << ' ';
    }
    myFile_Handler.close();
    return 0;
}
