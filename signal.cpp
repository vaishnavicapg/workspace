#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
#include<iostream>
using namespace std;

//Function declaration
void mystrcat();
//signal handler
void signal_handler(int signum)
{
	cout<<"signal_handler for signal :"<<signum<<" "<<"invoked"<<endl;
	exit(signum);
}
//signal handler for SIGUSR1
void signal_handler1(int signum)
{
	cout<<"Welcome User"<<endl;
}

int main()
{
 	int sigret = 0;
	//Check if there is any error in signal handling
   	if (signal(SIGINT,signal_handler) == SIG_ERR) 
	{
		cout<<"SIGINT set error:"<<errno<<endl;
		return EXIT_FAILURE;
	}
	//calling signal_handler1
	signal(SIGUSR1,signal_handler1);
	//called the SIGSEVG in case of segmentation fault
	signal(SIGSEGV,signal_handler);
	//To raise the signal SIGUSR1
	raise(SIGUSR1);
	//called if the process is paused
	signal(SIGTSTP,signal_handler);
	//Function call to mystrcat function
	mystrcat();
	//infinite loop use ctrl+c or ctrl+z to stop the loop
	while(1) 
	{
		sleep(1);
	 	cout<<"signal demo: while loop"<<endl;
	}
	return EXIT_SUCCESS;
}
//Function definition for mystrcat() function
void mystrcat()
{
	char str1[20];
	char str2[20];
	//Get 2 strings from user
	cout<<"Enter the first string:";
	cin>>str1;
	cout<<"Enter the second string:";
	cin>>str2;
	char *ptr1=NULL;
	char *ptr2=NULL;
	//Attempting to copy the strings to null pointer leads to segmentation fault
	strcpy(ptr1,str1);
	strcpy(ptr2,str2);
	//To display the copied string
	cout<<ptr1<<ptr2<<endl;
}