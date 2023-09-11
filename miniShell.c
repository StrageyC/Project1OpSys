#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char input[200];
    char *tokenv[30];
    
    while (1) {
        printf("Enter input: ");

        //standard input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; 
        }

        // tokenization
        int count = 0;
        char *token = strtok(input, " \n");

        while (token != NULL) {
            tokenv[count++] = token;
            token = strtok(NULL, " \n");
        }
        
        tokenv[count] = NULL; 

        pid_t pid = fork();

         if (pid == 0) {
            /* I am the child */
            execvp(tokenv[0], tokenv);
        } else {
            /* I am the parent */
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}