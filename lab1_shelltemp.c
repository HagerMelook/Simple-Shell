#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100
char exportVar[100][100];
char exportVal[100][100];
int count = 0;

// to release zombie process
void on_child_exit()
{
    //pid_t pid;
    waitpid(-1,NULL,WNOHANG);
    FILE *fptr;
    fptr = fopen("/home/hager101/OS1/Lab1/child_exit.txt", "a");
    fprintf(fptr, "Child terminated\n");
    fclose(fptr);
}
//default path
void setup_environment()
{
    chdir("/home/hager101");
}
// to execute pwd,ls,cp,chmod,mv,rm,mkdir
void execute_command(char *command, int n, int space)
{
    pid_t pid = fork();
    int size = n;
    // if it is the child process
    if (pid == 0)
    {
        if (command[n - 2] == '&')
        {
            // command[n-2]=='\0';
            n--;
            for (int i = n - 2; i >= 0; i--)
            {
                if (!isspace(command[i]))
                    break;
                n--;
            }
        }
        // pwd command
        if (command[space] == 'p' && command[space + 1] == 'w' && command[space + 2] == 'd')
        {
            int start = space + 3;
            for (int i = space + 3; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start++;
                else
                    break;
            }
            if (n == start + 1 || n == start)
            {
                char *args[] = {"pwd", NULL, NULL};
                execvp("pwd", args);
            }
            if (n == start + 3 && isspace(command[3]) && command[start] == '-')
            {
                if (command[start + 1] == 'L')
                {
                    char *args[] = {"pwd", "-L", NULL};
                    execvp("pwd", args);
                }
                if (command[start + 1] == 'P')
                {
                    char *args[] = {"pwd", "-P", NULL};
                    execvp("pwd", args);
                }
            }
            if (n == start + 7 && isspace(command[space + 3]) && command[start] == '-' && command[start + 1] == '-' && command[start + 2] == 'h' && command[start + 3] == 'e' && command[start + 4] == 'l' && command[start + 5] == 'p')
            {
                char *args[] = {"pwd", "--help", NULL};
                execvp("pwd", args);
            }
            if (n != 4 + start){
                printf("pwd: %c%c: invalid option\n", command[start], command[start + 1]);
                exit(0);
            }
            return;
        }

        // if (command[space] == 'c' && command[space + 1] == 'd')
        // {
        //     if (n == space + 3)
        //     {
        //         chdir("/home/hager101");
        //     }
        //     else if (isspace(command[space + 2]))
        //     {
        //         int start = 2 + space;
        //         // int space = start;
        //         for (int i = 2 + space; i < n - 1; i++)
        //         {
        //             if (isspace(command[i]))
        //                 start++;
        //             else
        //                 break;
        //         }
        //         char subString[n - start];
        //         for (int i = start; i < n; i++)
        //         {
        //             subString[i - start] = command[i];
        //         }
        //         subString[n - start - 1] = '\0';
        //         if (subString[0] != '~')
        //             chdir(subString);
        //         else
        //         {
        //             if (strlen(subString) == 1)
        //             {
        //                 chdir("/home/hager101");
        //             }
        //             else
        //             {
        //                 char substring2[14];
        //                 substring2[0] = '\0';
        //                 char subString2[strlen(subString)];
        //                 for (int i = 1; i < strlen(subString); i++)
        //                 {
        //                     subString2[i - 1] = subString[i];
        //                 }
        //                 subString2[strlen(subString)-1]='\0';
        //                 strcat(substring2, "/home/hager101");
        //                 strcat(substring2, subString2);
        //                 substring2[13 + strlen(subString)] = '\0';
        //                 chdir(substring2);
        //             }
        //         }
        //     }
        //     return;
        // }
        // ls command
        if (command[space] == 'l' && command[space + 1] == 's')
        {
            if (n == 3 + space)
            {
                char *args[] = {"ls", NULL, NULL};
                execvp("ls", args);
            }
            if (!isspace(command[2 + space]))
            {
                printf("%s: command not found\n", command);
                exit(0);
            }
            int start = 3 + space;
            for (int i = 3 + space; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start++;
                else
                    break;
            }
            if (command[start] == '-' && command[start + 1] == 'l')
            {
                if (!isspace(command[start - 1]))
                {
                    printf("%s: command not found\n", command);
                     exit(0);
                }
                if (n == start + 3)
                {
                    char *args[] = {"ls", "-l", NULL};
                    execvp("ls", args);
                }
            }
            if (command[start] == '-' && command[start + 1] == 'a' && n == start + 3)
            {
                if (!isspace(command[start - 1]))
                {
                    printf("%s: command not found\n", command);
                     exit(0);
                }
                char *args[] = {"ls", "-a", NULL};
                execvp("ls", args);
            }
            if (command[start] == '-' && command[start + 1] == 'h' && n == start + 3)
            {
                if (!isspace(command[start - 1]))
                {
                    printf("%s: command not found\n", command);
                     exit(0);
                }
                char *args[] = {"ls", "-a", NULL};
                execvp("ls", args);
            }
            if (n == start + 6 && ((command[start] == '-' && command[start + 1] == 'l' && command[start + 3] == '-' && command[start + 4] == 'a') || (command[start] == '-' && command[start + 1] == 'a' && command[start + 3] == '-' && command[start + 4] == 'l')))
            {
                if (!isspace(command[start - 1]) || !isspace(command[start + 2]))
                
                {
                    printf("%s: command not found\n", command);
                     exit(0);
                }
                    char *args[] = {"ls", "-l", "-a",NULL};
                    execvp("ls", args);
            }
            if (n == start + 6 && ((command[start] == '-' && command[start + 1] == 'h' && command[start + 3] == '-' && command[start + 4] == 'a') || (command[start] == '-' && command[start + 1] == 'a' && command[start + 3] == '-' && command[start + 4] == 'h')))
            {
                if (!isspace(command[start - 1]) || !isspace(command[start + 2]))
                {
                    printf("%s: command not found\n", command);
                     exit(0);
                }
                char *args[] = {"ls", "-h", "-a",NULL};
                execvp("ls", args);
            }
            if (n == start + 6 && ((command[start] == '-' && command[start + 1] == 'l' && command[start + 3] == '-' && command[start + 4] == 'h') || (command[start] == '-' && command[start + 1] == 'h' && command[start + 3] == '-' && command[start + 4] == 'l')))
            {
                if (!isspace(command[start - 1]) || !isspace(command[start + 2]))
                {
                    printf("%s: command not found\n", command);
                     exit(0);
                }
                char *args[] = {"ls", "-l", "-h",NULL};
                execvp("ls", args);
            }
            if (n == start + 9 && ((command[start] == '-' && command[start + 1] == 'l' && command[start + 3] == '-' && command[start + 4] == 'a' && command[start + 6] == '-' && command[start + 7] == 'h') || (command[start] == '-' && command[start + 1] == 'l' && command[start + 3] == '-' && command[start + 4] == 'h' && command[start + 6] == '-' && command[start + 7] == 'a') || (command[start] == '-' && command[start + 1] == 'a' && command[start + 3] == '-' && command[start + 4] == 'l' && command[start + 6] == '-' && command[start + 7] == 'h') || (command[start] == '-' && command[start + 1] == 'a' && command[start + 3] == '-' && command[start + 4] == 'h' && command[start + 6] == '-' && command[start + 7] == 'l') || (command[start] == '-' && command[start + 1] == 'h' && command[start + 3] == '-' && command[start + 4] == 'a' && command[start + 6] == '-' && command[start + 7] == 'l') || (command[start] == '-' && command[start + 1] == 'h' && command[start + 3] == '-' && command[start + 4] == 'l' && command[start + 6] == '-' && command[start + 7] == 'a')))
            {
                if (!isspace(command[start - 1]) || !isspace(command[start + 2]) || !isspace(command[start + 5]))
                {
                    printf("%s: command not found\n", command);
                     exit(0);
                }

                char *args[] = {"ls", "-l", "-a", "-h",NULL};
                execvp("ls", args);
            }
            if (command[start] == '-' && command[start + 1] == '-' && command[start + 2] == 'h' && command[start + 3] == 'e' && command[start + 4] == 'l' && command[start + 5] == 'p' && n == start + 7)
            {
                if (!isspace(command[start - 1]))
                {
                    printf("%s: command not found\n", command);
                     exit(0);
                }
                char *args[] = {"ls", "--help", NULL};
                execvp("ls", args);
            }
            printf("Command \'%s\' not found\n",command);
             exit(0);
        }
        // rm command
        if (command[space] == 'r' && command[space + 1] == 'm')
        {
            int space2 = 0;
            int start = space + 2;
            for (int i = space + 2; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start++;
                else
                    break;
            }
            if (n == start + 1)
            {
                printf("rm: missing operand\n");
               exit(0);
            }
            if (!isspace(command[space + 2]))
            {
                printf("Command \'%s\' not found\n", command);
                exit(0);
            }
            if (command[start] == '-' && command[start + 1] == '-' && command[start + 2] == 'h' && command[start + 3] == 'e' && command[start + 4] == 'l' && command[start + 5] == 'p' && n == start + 7)
            {
                char *args[] = {"rm", "--help", NULL};
                execvp("rm", args);
            }
            if (command[start] == '-' && command[start + 1] == 'r')
            {
                if (!isspace(command[start + 2]))
                {
                    if(n==start+3){
                                        printf("rm: missing operand\n");
              exit(0);
                    }
                    printf("rm: invalid option -- \'%c\'\n", command[start + 2]);
                     exit(0);
                }
                start += 3;
                for (int i = start; i < n - 1; i++)
                {
                    if (!isspace(command[i]))
                        break;
                    space2++;
                }
            }
            char subString[n - start - space2];
            for (int i = start + space2; i < n - 1; i++)
            {
                subString[i - start - space2] = command[i];
            }
            subString[n - start - space2 - 1] = '\0';
            if (subString[0] == '~')
            {
                //char substring2[14 + strlen(subString) - 1];
                char substring2[100];
                char subString2[strlen(subString)];
                for (int i = 1; i < strlen(subString); i++)
                {
                    subString2[i - 1] = subString[i];
                }
                subString2[strlen(subString)-1]='\0';
                strcat(substring2, "/home/hager101");
                strcat(substring2, subString2);
                substring2[13 + strlen(subString)] = '\0';
                if (command[start - 3] == '-' && command[start - 2] == 'r')
                {
                    char *args[] = {"rm", "-r", substring2, NULL};
                    execvp("rm", args);
                }

                char *args[] = {"rm", substring2, NULL};
                execvp("rm", args);
            }
            if (command[start - 3] == '-' && command[start - 2] == 'r')
            {
                char *args[] = {"rm", "-r", subString, NULL};
                execvp("rm", args);
            }

            char *args[] = {"rm", subString, NULL};
            execvp("rm", args);
        }
        // chmod command
        if (command[space] == 'c' && command[space + 1] == 'h' && command[space + 2] == 'm' && command[space + 3] == 'o' && command[space + 4] == 'd')
        {
            if (n == space + 6)
            {
                printf("chmod: missing operand\n");
                 exit(0);
            }
            int start = space + 6;
            for (int i = space + 6; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start++;
                else
                    break;
            }
            if (n == start + 7 && isspace(command[space + 5]) && command[start] == '-' && command[start + 1] == '-' && command[start + 2] == 'h' && command[start + 3] == 'e' && command[start + 4] == 'l' && command[start + 5] == 'p')
            {
                char *args[] = {"chmod", "--help", NULL};
                execvp("chmod", args);
            }
            if (isspace(command[space + 5]))
            {
                if (n == start + 4)
                {
                    printf("chmod: missing operand after \'%c%c%c\'\n", command[start], command[start + 1], command[start + 2]);
                     exit(0);
                }
                char permission[4];
                permission[0] = command[start];
                permission[1] = command[start + 1];
                permission[2] = command[start + 2];
                //permission[4] ='\0';
                start += 3;
                if (isspace(command[start]))
                {
                    start++;
                    for (int i = start; i < n - 1; i++)
                    {
                        if (isspace(command[i]))
                            start++;
                        else
                            break;
                    }
                    char subString[n - start];
                    for (int i = start; i < n; i++)
                    {
                        subString[i - start] = command[i];
                    }
                    subString[n - start - 1] = '\0';
                    if (subString[0] == '~')
                    {
                        //char substring2[14 + strlen(subString)];
                        char substring2[100];
                        substring2[0]='\0';
                        char subString2[strlen(subString)];
                        for (int i = 1; i < strlen(subString); i++)
                        {
                            subString2[i - 1] = subString[i];
                        }
                        subString2[strlen(subString)-1]='\0';
                        strcat(substring2, "/home/hager101");
                        strcat(substring2, subString2);
                         substring2[13+strlen(subString)]='\0';
                        char *args[] = {"chmod", permission, substring2,NULL};
                        execvp("chmod", args);
                    }
                    char *args[] = {"chmod", permission, subString, NULL};
                    execvp("chmod", args);
                }
            }
        }
        // mkdir command
        if (command[space] == 'm' && command[space + 1] == 'k' && command[space + 2] == 'd' && command[space + 3] == 'i' && command[space + 4] == 'r')
        {
            int start = space + 5;
            for (int i = space + 5; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start++;
                else
                    break;
            }
            if (n == start + 1)
            {
                printf("mkdir: missing operand\n");
                 exit(0);
            }
            if (n == start + 7 && isspace(command[space + 5]) && command[start] == '-' && command[start + 1] == '-' && command[start + 2] == 'h' && command[start + 3] == 'e' && command[start + 4] == 'l' && command[start + 5] == 'p')
            {
                char *args[] = {"mkdir", "--help", NULL};
                execvp("mkdir", args);
            }
            char subString[n - start];
            for (int i = start; i < n - 1; i++)
            {
                subString[i - start] = command[i];
            }
            subString[n - start - 1] = '\0';
            if (subString[0] == '~')
            {
                //char substring2[14 + strlen(subString) - 1];
                char substring2[100];
                char subString2[strlen(subString)];
                for (int i = 1; i < strlen(subString); i++)
                {
                    subString2[i - 1] = subString[i];
                }
                subString2[strlen(subString)-1]='\0';
                strcat(substring2, "/home/hager101");
                strcat(substring2, subString2);
                substring2[13 + strlen(subString)] = '\0';
                           // printf("%s",substring2);
                char *args[] = {"mkdir", substring2,NULL};
                execvp("mkdir", args);
            }

            char *args[] = {"mkdir", subString, NULL};
            execvp("mkdir", args);
        }
        // cp command
        if (command[space] == 'c' && command[space + 1] == 'p')
        {
            int space2 = 2;
            if (n == space + 3)
            {
                printf("cp: missing file operand\n");
                exit(0);
            }
            int start = space + 3;
            for (int i = space + 3; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start++;
                else
                    break;
            }
            if (n == start + 7 && isspace(command[space + 2]) && command[start] == '-' && command[start + 1] == '-' && command[start + 2] == 'h' && command[start + 3] == 'e' && command[start + 4] == 'l' && command[start + 5] == 'p')
            {
                char *args[] = {"cp", "--help", NULL};
                execvp("cp", args);
            }
            if (command[start] == '-' && command[start + 1] == 'r')
            {
                if (!isspace(command[start + 2]))
                {
                    printf("cp: invalid option -- \'%c\'\n", command[start + 2]);
                   exit(0);
                }
                start += 3;
                space2 = start;
                for (int i = space2; i < n - 1; i++)
                {
                    if (!isspace(command[i]))
                        break;
                    start++;
                }
            }
            int start2 = start;
            for (int i = start; i < n - 1; i++)
            {
                start2++;
                if (isspace(command[i]))
                    break;
            }
            if(start2==n-1)
            start2++;
            char source[start2 - start];
            //

            for (int i = start; i < start2; i++)
            {
                source[i - start] = command[i];
            }
           source[start2 - start-1] = '\0';

            if (start2 == n)
            {
                printf("cp: missing destination file operand after \'%s\'\n", source);
                 exit(0);
            }
            for (int i = start2; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start2++;
                else
                    break;
            }
            char destination[n - start2];
            for (int i = start2; i < n; i++)
            {
                destination[i - start2] = command[i];
            }
            destination[n - start2 -1] = '\0';
            if (source[0] == '~')
            {
                char *substring2=(char*)malloc(MAX_SIZE*sizeof(char));              
                //char substring2[14 + strlen(source)-1];
                 substring2[0]='\0';
                char subString2[strlen(source)];
                for (int i = 1; i < strlen(source); i++)
                {
                    subString2[i - 1] = source[i];
                }
                subString2[strlen(source)-1]='\0';
                strcat(substring2, "/home/hager101");
                strcat(substring2, subString2);
                substring2[13 + strlen(source)] = '\0';

                if (destination[0] == '~')
                {                        
                    //char substring3[14 + strlen(destination)-1];
                    //char *substring3=(char*)malloc(MAX_SIZE*sizeof(char));
                    char substring3[14];
                    substring3[0]='\0';
                    char subString3[strlen(destination)];
                    for (int i = 1; i < strlen(destination); i++)
                    {
                        subString3[i - 1] = destination[i];
                    }
                    subString3[strlen(destination)-1]='\0';
                    strcat(substring3, "/home/hager101");
                    strcat(substring3, subString3);
                    substring3[13 + strlen(destination)] = '\0';
                    if (command[space2 - 2] == 'r')
                    {
                        char *args[] = {"cp", "-r", substring2, substring3,NULL};
                       execvp("cp", args);
                    }
                    char *args[] = {"cp", substring2, substring3,NULL};
                  execvp("cp", args);
                    return;
                }
                if (command[space2 - 2] == 'r')
                {
                    char *args[] = {"cp", "-r", substring2, destination,NULL};
                   execvp("cp", args);
                }
                char *args[] = {"cp", substring2, destination,NULL};
                execvp("cp", args);
            }
            if (destination[0] == '~')
            {
                //char substring3[14 + strlen(destination) - 1];
                char substring3[14];
                substring3[0]='\0';
                char subString2[strlen(destination)];
                for (int i = 1; i < strlen(destination); i++)
                {
                    subString2[i - 1] = destination[i];
                }
                subString2[strlen(destination)-1]='\0';
                strcat(substring3, "/home/hager101");
                strcat(substring3, subString2);
                substring3[13 + strlen(destination)] = '\0';
                if (command[space2 - 2] == 'r')
                {
                    char *args[] = {"cp", "-r", source, substring3};
                   execvp("cp", args);
                }
                char *args[] = {"cp", source, substring3};
               execvp("cp", args);
             }
            if (command[space2 - 2] == 'r')
            {
                char *args[] = {"cp", "-r", source, destination};
               execvp("cp", args);
            }
            char *args[] = {"cp", source, destination};
           execvp("cp", args);
        }
        // mv command
        if (command[space] == 'm' && command[space + 1] == 'v')
        {
            if (n == space + 3){
                printf("mv: missing file operand\n");
                 exit(0);
            }
            
            int start = space + 3;
            for (int i = space + 3; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start++;
                else
                    break;
            }
            int start2 = start;
            for (int i = start; i < n - 1; i++)
            {
                start2++;
                if (isspace(command[i]))
                    break;
            }
            if (n == start + 7 && isspace(command[space + 2]) && command[start] == '-' && command[start + 1] == '-' && command[start + 2] == 'h' && command[start + 3] == 'e' && command[start + 4] == 'l' && command[start + 5] == 'p')
            {
                char *args[] = {"mv","--help",NULL};
                execvp("mv", args);
                return;
            }
            if(start2==n-1){
                start2++;
            }
            char source[start2 - start];
            //printf("%li,%li,%li",start2,start,n);
            for (int i = start; i < start2-1; i++)
            {
                source[i - start] = command[i];
            }
            source[start2 - start-1] = '\0';
            //printf("%s",source);
    //         if(source[0]=='~')
    //             source[start2 - start] = '\0';
    //         else
    //             
            if (start2 == n){
                printf("mv: missing destination file operand after \'%s\'\n", source);
                 exit(0);
            }
            for (int i = start2; i < n - 1; i++)
            {
                if (isspace(command[i]))
                    start2++;
                else
                    break;
            }

           char destination[n - start2];
            for (int i = start2; i < n ; i++)
            {
                destination[i - start2] = command[i];
            }

           destination[n - start2-1] = '\0';
                              
            if (source[0] == '~')
            {
                char *substring2=(char*)malloc(MAX_SIZE*sizeof(char)); 
                substring2[0]='\0';
                char subString2[strlen(source)];
                for (int i = 1; i < strlen(source); i++)
                {
                    subString2[i - 1] = source[i];
                }
                subString2[strlen(source)-1] = '\0';
                strcat(substring2, "/home/hager101");
                strcat(substring2, subString2);
                substring2[13 + strlen(source)] = '\0';
                if (destination[0] == '~')
                {
                char substring3[14];
                substring3[0]='\0';
                char subString3[strlen(destination)];
                for (int i = 1; i <strlen(destination); i++)
                {
                    subString3[i - 1] = destination[i];
                }
                subString3[strlen(destination)-1] = '\0';
                strcat(substring3, "/home/hager101");
                strcat(substring3, subString3);
               substring3[13+ strlen(destination)] = '\0';
                char *args[] = {"mv", substring2, substring3,NULL};
                execvp("mv", args);
                return;
               }
               char *args[] = {"mv", substring2, destination,NULL};
               execvp("mv", args);
            }
            else if (destination[0] == '~')
            {                               
                char substring4[14];
                char subString4[strlen(destination)];
                for (int i = 1; i < strlen(destination); i++)
                {
                    subString4[i - 1] = destination[i];
                }
                subString4[strlen(destination)-1] = '\0';
                strcat(substring4, "/home/hager101");
                strcat(substring4, subString4);
                substring4[13 + strlen(destination)] = '\0';
                char *args[] = {"mv", source, substring4,NULL};
            execvp("mv", args);
             return;
            }

            char *args[] = {"mv", source, destination,NULL};
            execvp("mv", args);
         return;
        }
        if(command[space]=='f'&&command[space+1]=='i'&&command[space+2]=='r'&&command[space+3]=='e'&&command[space+4]=='f'&&command[space+5]=='o'&&command[space+6]=='x'&&n==space+8){
        char *args[] = {"firefox",NULL};
          execvp("firefox", args);
        }
         printf("%s: command not found\n", command);
                     exit(0);
    }
    // parent process
    if (pid > 0 && command[size - 2] != '&')
    {
        //printf("parent\n");
        waitpid(pid, NULL, 0);
        //printf("\n");
    }
    // error
    if (pid < 0)
    {
        printf("Error\n");
    }
}

// echo command
void echo(char *command, int n, int start)
{
    for (int i = start; i < n - 1; i++)
    {
        if (!isspace(command[i]))
            break;
        start++;
    }
    for (int i = start; i < n - 1; i++)
    {
        if (command[i] == '\"')
            continue;
        printf("%c", command[i]);
    }
    printf("\n");
}
 // export command
void export(char *command, int n, int start)
{
    start += 6;
    // if (!isspace(command[start]))
    //     return;
    int start2 = start;
    for (int i = start; i < n - 1; i++)
    {
        if (!isspace(command[i]))
            break;
        start2++;
    }
    int value = 0;
    for (int i = start2; i < n - 1; i++)
    {
        if (command[i] == '=')
        {
            if (isspace(command[i + 1]) && isdigit(command[i + 2]))
            {
                printf("export: `%c': not a valid identifier\n", command[i + 2]);
                return;
            }
        }
    }
    for (int i = start2; i < n; i++)
    {
        if(i==n-1){
            exportVar[count][i - start2]='\0';
            break;
        }
        if (command[i] == '=')
        {
            exportVar[count][i - start2] = command[i];
            value = i;
            break;
        }
        exportVar[count][i - start2] = command[i];
    }
    int  j =1;
    for (int i = value + 1; i < n; i++)
    {
        if(i==n-1){
            exportVal[count][i - value - j]='\0';
            break;
        }
        if (isspace(command[value + 1]))
        {
            exportVal[count][0] = '\0';
            break;
        }
        if (command[i] == '\"'){
            j++;
            continue;
        }
        exportVal[count][i - value - j] = command[i];
    }
    count++;
    // if(n-start2==7  && command[start2]=='-'&&command[start2+1]=='-'&&command[start2+2]=='h'&&command[start2+3]=='e'&&command[start2+4]=='l'&&command[start2+5]=='p'){
    //     pid_t pid = fork();
    //     if(pid==0){
    //     char *args[] = {"export","--help", NULL};
    //     execvp("export",args);
    //     }
    //     if(pid >0){
    //         wait(&pid);
    //      }
    // }
}

void determineCommand(char *command, int n, int start)
{
    if (command[start] == 'e' && command[start + 1] == 'c' && command[start + 2] == 'h' && command[start + 3] == 'o')
    {
        if (n - start == 5)
        {
            printf("\n");
            return;
        }
        if (isspace(command[start + 4]))
            echo(command, n, start + 5);
    }
    // exit command
    else if (command[start] == 'e' && command[start + 1] == 'x' && command[start + 2] == 'i' && command[start + 3] == 't')
    {
        exit(0);
    }
    else if (command[start] == 'e' && command[start + 1] == 'x' && command[start + 2] == 'p' && command[start + 3] == 'o' && command[start + 4] == 'r' && command[start + 5] == 't'&& isspace(command[start + 6]))
    {
        export(command, n, start);
    }
    //cd command
    else if (command[start] == 'c' && command[start + 1] == 'd')
        {
            int space =start;
            if (n == space + 3)
            {
                chdir("/home/hager101");
            }
            else if (isspace(command[space + 2]))
            {
                int start = 2 + space;
                // int space = start;
                for (int i = 2 + space; i < n - 1; i++)
                {
                    if (isspace(command[i]))
                        start++;
                    else
                        break;
                }
                char subString[n - start];
                for (int i = start; i < n; i++)
                {
                    subString[i - start] = command[i];
                }
                subString[n - start - 1] = '\0';
                if (subString[0] != '~')
                    chdir(subString);
                else
                {
                    if (strlen(subString) == 1)
                    {
                        chdir("/home/hager101");
                    }
                    else
                    {
                        char *substring2=(char*)malloc(MAX_SIZE*sizeof(char*));
                        substring2[0] = '\0';
                        char subString2[strlen(subString)];
                        for (int i = 1; i < strlen(subString); i++)
                        {
                            subString2[i - 1] = subString[i];
                        }
                       
                        subString2[strlen(subString)-1]='\0';
                        strcat(substring2, "/home/hager101");
                        strcat(substring2, subString2);
                        substring2[13 + strlen(subString)] = '\0';
                        chdir(substring2);
                    }
                }
            }
            else{
printf("Command \'%s\' not found\n",command);
            }
        }
    else
       execute_command(command, n, start);
}

// check existence of variable and replace it by its value
void evaluate_expression(char *command, int n,int start)
{
char temp_array[100];
    int stop =-1;
    for (int i = 0; i < n; i++)
    {
        // test if this command has variable or not
        if (command[i] == '$')
        {
            stop = i;
            break;
        }
        temp_array[i] = command[i];
    }
    if(stop == -1){
        temp_array[n-1] = '\0';
       determineCommand(temp_array,n,start);
       return;
    }
    int repeat = 0;
    int j = 0;
    int found = 1;
    int index = 101;
    // test if that variable aready exist or not
    for (int i = 0; i < count; i++)
    {
        j = 0;
        found = 1;
        while (exportVar[i][j] != '=')
        {
            if (command[stop + j + 1] != exportVar[i][j])
            {
                found = 0;
                break;
            }
            j++;
        }
        if (found == 1)
        {
            index = i;
            break;
        }
    }
    // variable exist
    if (index != 101)
    {
        for (int i = 0; i < strlen(exportVal[index]); i++)
        {
            temp_array[stop + i] = exportVal[index][i];
        }
    for(int i = stop;i<n;i++){
        if(i+strlen(exportVar[index])==n-1){
            temp_array[i+strlen(exportVal[index])]='\0';
            break;
        }
        if(command[i+strlen(exportVar[index])]=='$'){
             repeat=1;
        }
        temp_array[i+strlen(exportVal[index])]=command[i+strlen(exportVar[index])];
    }
    }

    else{
    int stop2=0;
    for(int i = stop+1;i<n-1;i++){
        if(isspace(command[i])){
            stop2=i+1;
        break;
        }
        
    }
    if(stop2==0){
        temp_array[stop-1]='\0';
        determineCommand(temp_array,stop,start);
        return;
    }
        else{
            int stop3=stop2;
            for(int i =stop2;i<n-1;i++){
                if(!isspace(command[i])){
                    stop3=i;
                    break;
                }
            }
            for(int i =stop2;i<n;i++){
                if(command[i]=='$'){
                    repeat=1;
                }
                if(i==n-1){
                   temp_array[stop+i-stop2]='\0';
                }
                temp_array[stop+i-stop2]=command[i];
            }

        }
    }
    // if there is more than one $
    if(repeat==1){
        n=strlen(temp_array)+1;
        evaluate_expression(temp_array,n,start);
        return;
    }
    n=strlen(temp_array)+1;
    determineCommand(temp_array,n,start);
    return;
}

void shell()
{
    int n;
    char read_input[100];
    do
    {
        fgets(read_input, sizeof(read_input), stdin);
        n = strlen(read_input);
        int start = 0;
        //removing leading zeros
        for (int i = 0; i < strlen(read_input) - 1; i++)
        {
            if (!isspace(read_input[i]))
                break;
            start++;
        }
        //removing trailing zeros
        for (int i = strlen(read_input) - 2; i >= 0; i--)
        {
            if (!isspace(read_input[i]))
                break;
            n--;
        }
        read_input[n - 1] = '\0';
        evaluate_expression(read_input,n,start);
    } while (1);
}

void main()
{
    signal(SIGCHLD, on_child_exit);
    setup_environment();
    shell();
}