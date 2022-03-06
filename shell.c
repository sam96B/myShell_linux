#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <math.h>
#include </home/sami/Desktop/myShell/redirect.h>

#define BUFFER_LEN 1024

int isNumber(char *num);
int isOperator(char *ch);
int getSize(char *arr[]);

int checkAdjacent(char *arg[], int length)
{

    for (int i = 0; i < length - 1; i++)
    {
        if ((isNumber(arg[i]) == 0 && isNumber(arg[i + 1]) == 0))
        {

            return -1;
        }
    }

    return 0;
}

int checkOperators(char *arg[], int length)
{

    for (int i = 0; i < length; i++)
    {

        if (isOperator(arg[i]) == 0)
        {
            int j = i + 1;
            int count = 1;
            while (arg[j] != NULL)
            {
                if (isOperator(arg[j]) == 0)
                {
                    count++;
                }
                else
                {
                    break;
                }
                j++;
            }
            if (count > 2)
            {

                return -1;
            }
            if (count == 1)
            {
                continue;
            }

            if (strcmp("/", arg[i]) == 0 || strcmp("*", arg[i]) == 0)
            {
                if (strcmp("-", arg[i + 1]) != 0)
                {

                    return -1;
                }
            }
            else
            {

                if (strcmp("-", arg[i + 1]) == 0 || strcmp("+", arg[i + 1]) == 0)
                {

                    return -1;
                }
            }
        }
    }

    return 0;
}

int checkInput(char *arg[], int length)
{
    if (length < 3)
    {
        return -1;
    }
    if (!(isNumber(arg[length - 1]) == 0 && (strcmp(arg[0], "-") == 0 || isNumber(arg[0]) == 0)))
    {
        printf("%s*\n", arg[length - 1]);

        return -1;
    }

    for (int j = 1; j < length - 1; j++)
    {

        if (!(isNumber(arg[j]) == 0 || isOperator(arg[j]) == 0))
        {

            return -1;
        }
    }

    if (!(checkOperators(arg, length) == 0 && checkAdjacent(arg, length) == 0))
    {

        return -1;
    }
    return 0;
}

int isOperator(char *ch)
{

    if (strcmp(ch, "*") == 0 || strcmp(ch, "/") == 0 || strcmp(ch, "-") == 0 || strcmp(ch, "+") == 0)
    {

        return 0;
    }

    return -1;
}

int isNumber(char *num)
{

    if (strlen(num) == 0)
    {

        return -1;
    }

    for (int i = 0; i < strlen(num); i++)
    {

        if (isdigit(num[i]) == 0)
        {
            return -1;
        }
    }

    return 0;
}

int getOperands(float nums[], char *arg[])
{
    int size = 0;
    for (int i = 0; arg[i] != NULL; i++)
    {

        if (isNumber(arg[i]) == 0)
        {

            if (i != 0 && strcmp(arg[i - 1], "-") == 0)
            {
                nums[size++] = atoi(arg[i]) * -1;
            }
            else
            {

                nums[size++] = atoi(arg[i]);
            }
        }
    }
    return size;
}
int getOperators(char *ops[], char *arg[])
{
    int size = 0;
    for (int i = 0; arg[i] != NULL; i++)
    {

        if (isOperator(arg[i]) == 0)
        {
            if (strcmp(arg[i], "-") == 0)
            {
                continue;
            }
            ops[size++] = arg[i];
        }
    }
    return size;
}

int countHighOps(char *op[], int index)
{

    int count = 1;

    for (int i = index + 1; op[i] != NULL; i++)
    {

        if (strcmp(op[i], "+") == 0 || strcmp(op[i], "-") == 0)
        {
            return count;
        }

        count++;
    }

    return count;
}

int isHigh(char *op)
{

    if (strcmp(op, "/") == 0 || strcmp(op, "*") == 0)
    {

        return 0;
    }
    return -1;
}

int check(int index, char *operators[], int length)
{

    if (index >= length)

    {

        return 0;
    }

    if (isHigh(operators[index]) != 0)
    {

        return 0;
    }

    return -1;
}
void prepareInput(char *args[])
{

    for (int i = 0; i < 11; i++)
    {
        args[i] = args[i + 1];
    }
}
void calc(char *args[])

{

    prepareInput(args);

    int length;
    char *operators[20];
    float operands[25];
    for (length = 0; args[length] != NULL; length++)
        ;

    int operatorsLength;

    if (checkInput(args, length) == 0)
    {

        getOperands(operands, args);
        operatorsLength = getOperators(operators, args);

        float res = 0;
        if (isHigh(operators[0]) == 0)
        {
            res = 0;
        }
        else
        {

            res = operands[0];
        }

        for (int i = 0; i < operatorsLength;)
        {

            if (isHigh(operators[i]) != 0)
            {

                if (check(i + 1, operators, operatorsLength) == 0)
                {

                    res += operands[i + 1];
                }
                i++;
            }
            else
            {
                float inRes = operands[i];
                int count = countHighOps(operators, i);
                for (int j = i; j < count + i; j++)
                {
                    if (strcmp(operators[j], "*") == 0)
                    {

                        inRes *= operands[j + 1];
                    }
                    else if (strcmp(operators[j], "/") == 0)
                    {
                        inRes /= operands[j + 1];
                    }
                }

                res += inRes;

                i += count;
            }
        }
        printf("%.2f\n", res);
    }
    else
    {

        printf("syntax error !!\n");
    }
}
int dir(char *dir)
{

    char _files[50][100];

    int x = 0;
    int y = 0;
    char _directories[50][100];
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    if (dir != NULL)
    {

        char c[100] = {'.', '/', '\0'};
        strcat(c, dir);
        char *currentDir = c;
        folder = opendir(currentDir);
    }
    else
    {
        folder = opendir(".");
    }

    if (folder == NULL)
    {

        perror("Unable to read directory");
        return -1;
    }
    for (int o = 0; o < 50; o++)
    {
        for (int d = 0; d < 100; d++)
        {
            _directories[o][d] = '\0';
        }
    }
    while ((entry = readdir(folder)))
    {

        switch (entry->d_type)
        {
        case 8:

            strcpy(_files[x++], entry->d_name);
            printf("%-70s%s\n", _files[x - 1], "FILE");

            break;
        case 4:

            strcpy(_directories[y++], entry->d_name);
            printf("%-70s%s\n ", _directories[y - 1], "DIR");

            break;
        }
    }

    closedir(folder);
    

    return 0;
}

void cd(int argscounter, char *args[], char pwd[])
{

    if (argscounter == 1)
    {
        chdir("/");
    }
    else
    {

        char path[100] = "/";
        strcat(path, args[1]);
        strcat(pwd, path);

        if (chdir(pwd) < 0)
        {
            printf("No Such Dierctory!\n");
        };
    }
}

int getIndex(char *commands[], char *command)
{

    for (int i = 0; i < 8; i++)
    {

        if (strcmp(command, commands[i]) == 0)
        {

            return i;
        }
    }

    return -1;
}

void printEnv(char *envp[])
{
    char **cur = envp;

    while (*cur != NULL)
    {
        printf("%s\n", *cur);
        cur++;
    }
}
int help()
{
    int id, st;
    id = fork();
    if (id == 0)
    {
        char *ag[] = {"cat", "help", NULL};
        if (execvp("cat", ag) == -1)
        {

            return -1;
        }
    }
    else
    {

        wait(&st);
    }
    return 0;
}

int nonExcecCommands(char *args[], int argsCounter, char pwd[], char *envp[])
{
    char *commands[9] = {"quit", "clear", "pause", "dir", "cd", "calc", "help", "environ"};

    int index = getIndex(commands, args[0]);

    if (index == -1)
    {

        return -1;
    }
    else
    {

        switch (index)
        {
        case 0:
            exit(0);

        case 1:
            system("cls||clear");

            break;
        case 2:
            printf("Press enter to continue ..");
            getchar();

            break;

        case 3:

            if (argsCounter > 2)
            {
                printf("Too many arguments !\n");
            }
            else
            {
                dir(args[1]);
            }

            break;
        case 4:
            if (argsCounter > 2)
            {
                printf("Too many arguments !\n");
            }
            else
            {
                cd(argsCounter, args, pwd);
            }

            break;
        case 5:

            calc(args);

            break;
        case 6:
            if (help() == -1)
            {
                printf("Error has occurred!\n");
            }

            break;
        case 7:
            printEnv(envp);
            break;

        default:
            return -1;
        }

        return 0;
    }
}
int main(int argc, char *argv[], char *envp[])
{

    char pwd[BUFFER_LEN];
    int status;
    getcwd(pwd, BUFFER_LEN);
    FILE *in_file;
    int batchFile = argv[1] == NULL ? -1 : 0;
    if (batchFile == 0)
    {

        in_file = fopen(argv[1], "r");
        if (in_file == NULL)
        {
            printf("Error! Could not open file\n");
            exit(-1);
        }
    }
    else
    {
        system("cls||clear");
        help();
    }

    while (1)
    {

        int _stdout, _stdin;
        _stdout = dup(1);
        _stdin = dup(0);

        getcwd(pwd, BUFFER_LEN);

        char command[100];
        if (batchFile == 0)
        {
            fgets(command, 100, in_file);
            int k;
            for (k = 0; command[k] != '\n'; k++)
                ;

            command[k] = '\0';
        }
        else
        {
            printf("%s> ", pwd);
            scanf("%[^\n]99s", command);

            getchar();
        }

        char *args[11];

        for (int i = 0; i < 11; i++)
        {

            args[i] = (char *)malloc(sizeof(char));
        }

        char *command_token = strtok(command, " ");

        int argscounter = 0;

        while (command_token != NULL && argscounter < 10)
        {

            strcpy(args[argscounter], command_token);

            command_token = strtok(NULL, " ");
            argscounter++;
        }

        args[argscounter] = NULL;

        if (isRedirect(args, argscounter) == 0)
        {

            if (redirect(args, argscounter) == -1)
            {
                continue;
            }

            int i;

            for (i = 0; args[i] != NULL; i++)
            {
                if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0 || strcmp(args[i], "<") == 0)
                {
                    break;
                }
            }
            int newLength = i;

            for (i; i < argscounter; i++)
            {
                args[i] = NULL;
            }

            argscounter = newLength;
        }

        if (nonExcecCommands(args, argscounter, pwd, envp) == -1)
        {

            int pid;

            if ((pid = fork()) < 0)
            {
                perror("fork failed");
                exit(2);
            }
            if (pid == 0)
            {

                if (execvp(args[0], args) == -1)
                {

                    printf("Command '%s' not found !\n", args[0]);
                }
            }
            else
            {
                if (strcmp(args[argscounter - 1], "&") == 0)
                {
                    printf("Child process id:%d \n", pid);
                }
                else
                {

                    wait(&status);
                }
            }
        }
        dup2(_stdout, 1);
        dup2(_stdin, 0);
        close(_stdin);
        close(_stdout);
    }

    return 0;
}
