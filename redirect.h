#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
int redirectInput(char *args[], int length);
int redirectOutput(char *fileName, char *args[], int length);

int isRedirect(char *args[], int length)
{

    for (int i = 0; i < length; i++)

    {
        if (i != 0 && (strcmp(args[i], ">>") == 0 || strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0))
        {
            return 0;
        }
    }
    return -1;
}

int checkRight(char *args[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {

            if (args[i + 1] == NULL)
            {

                return -1;
            }
        }
    }
    return 0;
}
int checkLeft(char *args[], int length)
{

    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0)
        {
            if (args[i + 1] == NULL)
            {

                return -1;
            }
            index = i;
        }
    }
    if (args[index + 2] != NULL)
    {
        return -1;
    }
    return 0;
}

int checkInputFile(char *args[], int length)
{
    int right = 0;
    int left = 0;
    for (int i = 0; i < length; i++)
    {

        if (strcmp(args[i], "<") == 0)
        {
            right = i;
        }
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0)
        {

            left = i;
        }
    }

    return (left - right) == 2 ? 0 : -1;
}
int count(char *args[], int length)
{
    int c1 = 0, c2 = 0;

    for (int i = 0; i < length; i++)
    {
        if (strcmp(args[i], ">>") == 0 || strcmp(args[i], ">") == 0)
        {
            c1++;
        }

        if (strcmp(args[i], "<") == 0)
        {
            c2++;
        }
    }
    return c1 > 1 || c2 > 1 ? -1 : 0;
}
int getLeft(char *args[], int length)
{
    for (int i = 0; i < length; i++)
    {

        if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0)
        {

            return i;
        }
    }
    return -1;
}
int getRight(char *args[], int length)
{
    for (int i = 0; i < length; i++)
    {

        if (strcmp(args[i], "<") == 0)
        {

            return i;
        }
    }
    return -1;
}

int checkOperator(char *args[], int length)
{

    if (getRight(args, length) != -1 && getLeft(args, length) != -1) //both are exist
    {

        if (checkInputFile(args, length) == 0 && checkRight(args, length) == 0 && checkLeft(args, length) == 0)
        {

            return 0;
        }
        return -1;
    }

    if (getRight(args, length) != -1) //the rigth is exist
    {

        if (checkRight(args, length) == 0)
        {

            return 1;
        }
        return -1;
    }
    if (getLeft(args, length) != -1) //the left is exist
    {

        if (checkLeft(args, length) == 0)
        {

            return 2;
        }
        return -1;
    }
    return -1;
}
int redirectBoth(char *fileName, char *args[], int length)
{
    if (redirectInput(args, length) != -1)
    {
        if (redirectOutput(fileName, args, length) != -1)
        {
            return 0;
        }
    }
    return -1;
}
int redirectInput(char *args[], int length) //right
{

    char *fileName = args[getRight(args, length) + 1];
    int fd;
    fd = open(fileName, O_RDWR, 0777);

    dup2(fd, 0);

    close(fd);
    
    return fd;
}

int redirectOutput(char *fileName, char *args[], int length) //left
{

    int fd;
    if (strcmp(args[getLeft(args, length)], ">") == 0)
    {
        fd = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0777);
    }
    else
    {
        fd = open(fileName, O_CREAT | O_APPEND | O_RDWR, 0777);
    }

    dup2(fd, 1);

    close(fd);
    return fd;
}
int redirect(char *args[], int length)
{

    if (count(args, length) == 0)
    {

        int i = checkOperator(args, length);

        if (i != -1)
        {

            switch (i)
            {
            case 0:

                redirectBoth(args[getLeft(args, length) + 1], args, length);

            case 1:

                if (redirectInput(args, length) == -1)
                {
                    return -1;
                }
                else
                {
                    return 0;
                }

            case 2:

                if (redirectOutput(args[getLeft(args, length) + 1], args, length) == -1)
                {
                    return -1;
                }
                else
                {
                    return 0;
                }

            default:

                return -1;
            };
        }
    }
    return 0;
}
