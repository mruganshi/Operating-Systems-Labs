#include<bits/stdc++.h>
using namespace std;
int main(){
        ifstream file("op.txt");
         string content;
	 ofstream myFile_Handler;
	myFile_Handler.open("op2.txt");
         int count=0;
        while(file >> content) {
                for(int i=0;i<content.length();i++){
                        if((int(content[i]>=97) and int(content[i]<=122)) or (int(content[i]>=65) and int(content[i]<=90))){
                                continue;
                        }       
                        else{
                                count++;
                        }
                }
                myFile_Handler << content << ' ';

        }
        myFile_Handler<<endl;
	myFile_Handler<<endl;
	myFile_Handler<<"Count of special charachters is"<<endl;
	myFile_Handler<<count<<endl;
        return 0;
}

