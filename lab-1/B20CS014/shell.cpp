#include <stdio.h>
#include<bits/stdc++.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
 #include <dirent.h> 
using namespace std;
#define clear() printf("\033[H\033[J")
#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define HISTORY_MAX_SIZE 500
static char *history[HISTORY_MAX_SIZE];
static unsigned counter = 0;

int relationalOperation(string s1, string s2)
{
 
    if (s1 != s2)
    {
        return -1;
    }
    else
        return 1;
}
// help
void helpfunction()
{
	cout<<"\033[0;33m";
	cout<<endl;
	cout<<"*** ####################  HELP SECTION  ################### ***"<<endl;
	cout<<"Commands :"<<endl;
	cout<<">hello"<<endl;
	cout<<">history"<<endl;
	cout<<">env"<<endl;
	cout<<">help"<<endl;
	cout<<">ls"<<endl;
	cout<<">exit"<<endl;
	cout<<">mkdir"<<endl;
	cout<<">rmdir"<<endl;
	cout<<">cd"<<endl;
	cout<<">pwd"<<endl;
	cout<<">clear"<<endl;
  /*  puts("\n***>>>>>	Help Section   <<<<<***"
        "\nCommands :"
		"\n>hello"
		"\n>history"
		"\n>env"
        "\n>help"
        "\n>ls"
        "\n>exit"
        "\n>mkdir"
		"\n>rmdir"
        "\n>cd"
        "\n>pwd"
		"\n>clear");*/
 	cout<<"\033[0m"; 
    return;
}

// welcome text
int welcometext()
{
    clear();
    cout<<"\033[0;32m";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"******************"
        "************************";
        cout<<"\033[0m";
    cout<<"\033[0;33m"; //Set the text to the color 
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t****Welcome****";
    cout<<"\033[0m"; //Resets the text to default color
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t<<---(⁰ v ⁰)--->>";
    cout<<"\033[0;32m";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"*******************"
        "***********************";
    cout<<"\033[0m";
    string username = getenv("USER");
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"USER is: @"<< username;
    cout<<endl;
    sleep(2);
	return 0;
}


int execute_command(char** tokens){
	if (strcmp(tokens[0],"ls")==0){
		struct dirent *de;
                DIR *dr = opendir(".");
                while ((de = readdir(dr)) != NULL){
			cout<<de->d_name<<" "; 
                }
                cout<<endl;
                closedir(dr);
	}
	if(strcmp(tokens[0],"help")==0){
		helpfunction();
	}
	if(strcmp(tokens[0],"hello")==0){
		string username;
		username = getenv("USER");
		cout<<"\033[0;34m";
		cout<<"Hello"<<username<<endl;
		cout<<"Please type the required command. Type help to see list of commands."<<endl;
		cout<<"\033[0m";
	}
	if(strcmp(tokens[0],"env")==0){
		system("env");
	}
	else if(strcmp(tokens[0],"cd")==0){
		if (access(tokens[1], F_OK) == -1)
        	cout<<"The specified file/directory does not exist."<<endl;
		chdir(tokens[1]);
	}
	else if(!strcmp(tokens[0],"pwd")){
		char pwd[PATH_MAX];
			if (getcwd(pwd, sizeof(pwd)))
			{
				cout<<pwd<<endl;
			}
			else
			{
				perror("getcwd() error");
			}
	}
	else if (strcmp(tokens[0],"exit")==0){
		cout<<"Bbye"<<endl;
        	exit(0);
	}
	else if (strcmp(tokens[0], "history")==0){
		if (!tokens[1]){
			int i=0;
			while(i<counter){
				cout<<i<<" "<<history[i];
				i++;
			}
		}
		else{
			int hist_count = atoi(tokens[1]);
			int i=counter-hist_count;
			while(i<counter){
				cout<<i<<" "<<history[i];
				i++;
			}
		}
	}
	else if (strcmp(tokens[0], "clear") == 0){
        	clear();
    } 
	else if (strcmp(tokens[0], "mkdir") == 0){
		int dirCheck = mkdir(tokens[1], 0777);
		if (!dirCheck){
			cout<<"\033[0;34m";
            		cout<<"Directory created !"<<endl;
			cout<<"\033[0m";
		}
		else {
            		cout<<"\033[0;31m";
            		cout<<"Can't create directory :( There might be another file with the same name."<<endl;
			cout<<"\033[0m";
        }
	}
	else if((strcmp(tokens[0], "rmdir") == 0)){
		int delCheck = remove(tokens[1]);
		if (!delCheck){
            cout<<"\033[0;34m";
            cout<<"Directory Deleted !"<<endl;
			cout<<"\033[0m";
        } //returns 0 if directory is del
        else {
            cout<<"\033[0;31m";
            cout<<"Can't delete directory"<<endl;
			cout<<"\033[0m";
        }
	}
	return 0;
}

int add_to_history(char* line){
	if (line[0] == '\n'){
		return 0;
	}
	if (counter < HISTORY_MAX_SIZE) {
			history[counter] = strdup( line );
			counter++;
	}
	else {
		free( history[0] );
		unsigned index=1;
		while(index<HISTORY_MAX_SIZE){
			history[index - 1] = history[index];
			index++;
		}
		history[HISTORY_MAX_SIZE - 1] = strdup( line );
	}
	return 0;
}

char **tokenize(char *line)
{
	char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i, tokenIndex = 0, tokenNo = 0;
	i=0;
	while(i<strlen(line)){

		char readChar = line[i];

		if (readChar == ' ' || readChar == '\n' || readChar == '\t')
		{
			token[tokenIndex] = '\0';
			if (tokenIndex != 0)
			{
				tokens[tokenNo] = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
				strcpy(tokens[tokenNo], token);
				tokenNo++;
				tokenIndex = 0;
			}
		}
		else
		{
			token[tokenIndex] = readChar;
			tokenIndex++;
		}
		i++;
	}

	free(token);
	tokens[tokenNo] = NULL;
	return tokens;
}

int main(int argc, char *argv[])
{	
	welcometext();
	char line[MAX_INPUT_SIZE];
	char **tokens;
	int i;

	FILE *fp;
	if (argc == 2)
	{
		fp = fopen(argv[1], "r");
		if (fp < 0)
		{
			cout<<"File doesn't exists.";
			return -1;
		}
	}

	while (1)
	{
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		if (argc == 2)
		{ // batch mode
			if (!fgets(line, sizeof(line), fp))
			{ // file reading finished
				break;
			}
			line[strlen(line) - 1] = '\0';
		}
		else
		{ // interactive mode
			char pwd[PATH_MAX];
			if (getcwd(pwd, sizeof(pwd)))
			{
				cout<<pwd;
			}
			else
			{
				perror("getcwd() error");
				return 1;
			}
			cout<<"$ ";
			cin>>line;
			getchar();
		}
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);

		//do whatever you want with the commands, here we just print them
		add_to_history(line);
		execute_command(tokens);
		string xd[5]={"sd","ls","cd","he","hi"};
		for(int i=1;i<3;i++){
			if(relationalOperation(xd[i],xd[i-1])){
					continue;
			}
			else{
				continue;
			}
		}
		// Freeing the allocated memory
		i=0;
		while(tokens[i]){
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
	return 0;
}
