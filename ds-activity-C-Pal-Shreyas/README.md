# Simple Sign-up and Log-in system using SUN RPC in C language
This short project was done as an assignment for Distributed Systems in 3rd Semester. Platform used is Ubuntu 18.04 LTS.

### Installation Instructions:
1. Execute the following command on a terminal to install 'rpcbind'.
```console
$ sudo apt install rpcbind
```
2. Verify Installation using:
```console
$ rpcinfo
```
### Compilation:
1. Make Changes to login.x and run:
```console
$ rpcgen -a -C login.x
```
New files will be generated.

2. Make changes to login_server.c and login_client.c and run:
```console
$ make -f Makefile.login
```
### Execution:
1. On server terminal run:
```console
$ sudo ./login_server
```
2. On client terminal run:
If client is on seperate terminal on the same computer run:
```console
$ sudo ./login_client localhost
```

If client is on a different computer run:
```console
$ sudo ./login_client <ip address of server>
```

4. Follow instruction on the terminals.

#### Contributors:
###### Abhrajyoti Pal      1NT17IS119
###### Shreyas R Venkat    1NT17IS160