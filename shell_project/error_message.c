#include "main.h"

/* header */

/**
* getline_error - error message for read_getline
*
* @getline_cp: char type
*
* Return: void
*/

int getline_error(char *getline_cp)
{
	if (getline_cp == NULL)
	{
		perror("Memory allocation error");
		return (-1);
	}
	return (0);
}


/**
* check_strtoken - a for loops that check while str is not equal to NULL
*
* @strtoken: char type
*
* @argv: char type
*
* @delim: char type
*
* return: void
*/

void check_strtoken(char *strtoken, char *argv[], const char *delim)
{
	int n;

	for (n = 0; strtoken != NULL; n++)
	{
		argv[n] = malloc(sizeof(char) * _strlen(strtoken));
		_strcpy(argv[n], strtoken);
		strtoken = _strtok(NULL, delim);
	}
	argv[n] = NULL;
}


/**
* child_error - handles error message for childpid
*
* @child_pid: pid_t type
*
* return: void
*/

void child_error(pid_t child_pid)
{
	if (child_pid == -1)
	{
		perror("Error: forking child process failed");
		exit(EXIT_FAILURE);
	}
}


/**
* path_error - handles error message for path_copy
*
* @path_copy: char type
*
* Return: void
*/

void path_error(char *path_copy)
{
	if (path_copy == NULL)
	{
		perror("Error: string duplicate failed");
		exit(EXIT_FAILURE);
	}
}


/**
* cmd_error - handles error message for command path
*
* @cmd_path: char tpe
*
* Return: void
*/

void cmd_error(char *cmd_path)
{
	if (cmd_path == NULL)
	{
		perror("Error: malloc() failed");
		exit(EXIT_FAILURE);
	}
}
