#include "login.h"

void
rpclogin_prog_1(char *host)
{
	CLIENT *clnt;
	userStatus *result_2;
	userDetails loginprocess_1_arg;

	char username[256];
    char password[256];

#ifndef	DEBUG
	clnt = clnt_create (host, RPCLOGIN_PROG, RPCLOGIN_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	printf("\n*********************** User Login ***********************\n");
    	printf("Enter Username: ");
    	scanf("%s", username);

    	printf("Enter Password: ");
    	scanf("%s%*c", password);

       strcpy(loginprocess_1_arg.username, username);
       strcpy(loginprocess_1_arg.password, password);

#endif	// DEBUG 

	result_2 = loginprocess_1(&loginprocess_1_arg, clnt);
	if (result_2 == (userStatus *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	if(result_2->rescode != 0){
    	printf("\nWelcome %s !\n",username);
	   	if(strcmp(username,"admin")==0) {
			printf("\nNumber of registered Users: %ld\n", (result_2->usercount - 1));
	   	}
	   	exit(0);
    }
	else {
        printf("Invalid user. Try again!");
    }

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 // DEBUG 
}

void rpcregister_prog_2(char *host)
{
	CLIENT *clnt;

	userStatus  *result_1;
	userDetails  registerprocess_1_arg;

	char req;
	char username[256];
	char password[256];

	clnt = clnt_create (host, RPCLOGIN_PROG, RPCLOGIN_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	printf("\n******************** User Registration *************************\n");

	printf("Enter Username: ");
	scanf("%s", username);

	printf("Enter Password: ");
	scanf("%s%*c", password);

	strcpy(registerprocess_1_arg.username,username);
	strcpy(registerprocess_1_arg.password,password);

	result_1 = registerprocess_1(&registerprocess_1_arg, clnt);
	if (result_1 == (userStatus *) NULL) {
		clnt_perror (clnt, "call failed: got err.");
	}

	if(result_1->rescode != 0) {
	  printf("\n Registration Successful !\n");
	  printf("Like to login? (Y/N): ");
	  scanf("%c",&req);
	  if(req == 'Y' || req == 'y'){
	     rpclogin_prog_1(host);
	  }else {
	     exit(0);
          }

	}else {
	  printf("User with same Username already exist. Please try using different Username\n");
	} 
	
	clnt_destroy (clnt);
}


int
main (int argc, char *argv[])
{
	char *host;
	int type;

	if (argc < 2) {
		printf ("Command Options: %s server host\n", argv[0]);
		exit (1);
	}

	host = argv[1];

	while(type != 3 ) {
	   	printf("1. Sign Up\n");
	   	printf("2. Login\n");
	   	printf("3. Quit\n");
	   	printf("Enter Choice: ");
        scanf("%d",&type);
	
	   switch(type){
		case 1:
		  	rpcregister_prog_2(host);
			break;

		case 2:
		  	rpclogin_prog_1(host);
		  	break;

		case 3:
			break;

		default:
		  	printf("Invalid Option\n");
		  	type = 3;
		  	break;
	    }	
	}

	exit (0);
}