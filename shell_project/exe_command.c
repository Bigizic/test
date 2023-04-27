#include "main.h"
#include <stdlib.h>
/* header */

/**
* env_shell - prints the current environment to standard output
*
* Return: void
*/
void env_shell(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		i++;
	}
}

/**
* string_cmp - handles the string compare for argv[0]
*
* @argv: char type
*
* Return: void
*/
void string_cmp(char *argv[])
{
	if (_strcmp(argv[0], "env") == 0)
	{
		env_shell();
		return;
	}
}


/**
* exe_command - handles executuion of user input
*
* @argv: pointer to a pointer of char type
*
* Return: void
*/

int exe_command(char *argv[])
{
	pid_t child_pid;
	int status;
	char *path, *path_copy, *dir, *cmd_path;
	int (*builtin)(char *argv[]);

	if (argv)
	{
		exit_shell(argv);
		builtin = get_builtin(argv[0]);
		string_cmp(argv);
		child_pid = fork();
		child_error(child_pid);
		if (child_pid == 0)
		{
			if (builtin != NULL)
				return (builtin(argv));
			execvp(argv[0], argv);
			path = _getenv("PATH");
			if (path != NULL)
			{
				path_copy = _strdup(path);
				path_error(path_copy);
				dir = _strtok(path_copy, ":");
				while (dir != NULL)
				{
					cmd_path = malloc(_strlen(dir) + _strlen(argv[0]) + 2);
					cmd_error(cmd_path);
					_strcpy(cmd_path, dir);
					_strcat(cmd_path, "/");
					_strcat(cmd_path, argv[0]);
					access_func(cmd_path, argv);

					dir = _strtok(NULL, ":");
				}
				free(path_copy);
			}
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else
			waitpid(child_pid, &status, WUNTRACED);
	}
	return (0);
}


/**
* exit_shell - implement the exit built-in, that exits the shell
*
* @argv: char type
*
* Return: void
*/

void exit_shell(char *argv[])
{
	int status;

	if (_strcmp(argv[0], "exit") == 0)
	{
		status = EXIT_SUCCESS;
		if (argv[1] != NULL)
		{
			status = _atoi(argv[1]);
		}
		exit(status);
	}
}


/**
* access_func - handles command execution
*
* @cmd_path: char type
*
* @argv: char type
*
* Return: void
*/
void access_func(char *cmd_path, char *argv[])
{
	if (access(cmd_path, X_OK) == 0)
	{
		execve(cmd_path, argv, NULL);
	}
	free(cmd_path);
}
