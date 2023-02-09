//
//  DetectWorm.c
//  lab2
//
//  Created by Shashadhar Das on 24/02/22.
//

#include <stdio.h>
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
