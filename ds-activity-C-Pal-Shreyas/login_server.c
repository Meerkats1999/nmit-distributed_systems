#include "login.h"
#include<stdbool.h>

#define SUCCESS 100
#define FAILURE 0

static long registeredUserCount = 0;

void addUser(userDetails *argp){
	FILE *fp = fopen("./login.db", "ab");

	if(fp != NULL){
		char data[512] = "";
		strcpy(data, argp->username);
		strcat(data, "$");
		strcat(data, argp->password);
		strcat(data, "\n");
		fputs(data, fp);
		fclose(fp);
	}
}

long getLineCount(){
	FILE *fp;
   	char *line = NULL;
   	size_t len = 0;
   	ssize_t read;
   	long lineCount = 0;

   	fp = fopen("./login.db","r");
   	if(fp == NULL){
		return 0;
   	}

   	while((read = getline(&line, &len, fp)) != -1) {
    	lineCount++;
   	}

	return lineCount;
}

long getRegisteredUserCount() {
	registeredUserCount = getLineCount();
	return registeredUserCount;
}

bool isValidUser(userDetails *argp) {
	FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    bool validuser = 0;
    char data[512];
	
    strcpy(data,argp->username);
    strcat(data,"$");
    strcat(data,argp->password);
    strcat(data,"\n");

    fp = fopen("./login.db","r");
    if(fp == NULL){
	return validuser;
    }

    while((read = getline(&line, &len, fp)) != -1) {
		if(strcmp(line,data)==0){
	    	validuser = 1;
	    	break;
		}
	}

	return validuser;
}

userStatus *
registerprocess_1_svc(userDetails *argp, struct svc_req *rqstp)
{
	static userStatus  result;

	if(!isValidUser(argp)){
		addUser(argp);
		result.rescode = SUCCESS;
		registeredUserCount++;
	}
	else{
		result.rescode = FAILURE;
	}

	return &result;
}

userStatus *
loginprocess_1_svc(userDetails *argp, struct svc_req *rqstp)
{
	static userStatus  result;

	if(isValidUser(argp)){
		result.rescode = SUCCESS;
		result.usercount = getRegisteredUserCount();
	}
	else{
		result.rescode = FAILURE;
	}

	return &result;
}