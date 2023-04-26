#include "main.h"
/* header */

/**
* _signal_ - prints new prompt upon a signal
*
* @si: int type
*
* Return: void
*/
void _signal_(int si)
{
	char *prompt = "\n# ";

	void(si);
	signal(SIGINT, _signal_);
	write(STDIN_FILENO, prompt, 3);
}


/**
* exe_command - executes a command in child proccess
*
* @args: pointer to an array that contains the arguments
*
* @fptr: pointer to a pointer to the beginning of args
*
* Return: 0
*/
int exe_command(char **args, char **fptr)
{
	pid_t child_pid;
	int flag = 0, i = 0, status;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = _location(cmd);
	}
	if (!cmd || access(cmd, F_OK) == -1)
	{
		if (errno == EACCES)
			i = (error_handler(args, 100));
		else
			i = (error_handler(args, 101));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child forking error");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				i = (error_handler(args, 100));
			environ_free();
			as_free(args, fptr);
			alias_list_free(aliases);
			_exit(i);
		}
		else
		{
			wait(&status);
			i = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (i);
}

/**
* main - unix command line interpreter
*
* @ac: int type
*
* @av: char type
*
* Description: this function prints a prompt and gets user
* input,using the getline function and it stores the input
* in the read_getline variable, it copies the user input
* from the read_getline var to getline_cp, it use the
* strtok function to break down the user input and
* calculate the number of strings, it saves the calculated
* strings in a variable and use the exe_command function
* to execute the calculated string.
*
* Return: 0 if success
*/

int main(int ac, char **av)
{
	int i = 0, x, m = 2;
	int *cve = &x;
	char *prompt = "$ ", *line = "\n";

	history = 1; /* update global history */
	name = argv[0]; /* update program name */
	verb = NULL; /* update alias linked list */
	signal(SIGINT, _signal_);
	*cve = 0;
	environ = _copyenviron();
	if (!environ)
		exit(100);
	if (argc != 1)
	{
		i = file_commands(argv[1], cve);
		environ_free();
		alias_list_free(verb);
		return (*cve);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (i != END_OF_FILE && i != EXIT)
			i = args_control(cve);
		environ_free();
		alias_list_free(aliases);
		return (*cve);
	}
	while (1) /*continous loop */
	{
		write(STDOUT_FILENO, prompt, m);
		i = args_control(cve);
		if (i == END_OF_FILE || i == EXIT) /*handles ctrl + D*/
		{
			if (i == END_OF_FILE)
				write(STDOUT_FILENO, line, 1);
			environ_free();
			alias_list_free(verb);
			exit(*cve);
		}
	}
	environ_free();
	alias_list_free(verb);
	return (*cve);
}
