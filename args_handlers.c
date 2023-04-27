#include "main.h"
/* header */

/**
* _args_1 - collect and handles a command from standard input
*
* @line: char buffer
*
* @rel: int type
*
* Return: NULL
*/
char *_args_1(char *line, int *rel)
{
	size_t n = 0;
	ssize_t read_line;
	char *prompt = "$ ";

	if (line)
		free(line);

	read_line = _getline(&line, &n, STDIN_FILENO);
	if (read_line == -1)
		return (NULL);
	if (read_line == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (_args_1(line, rel));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, rel);
	handle_line(&line, read_line);

	return (line);
}

/**
* _args_2 - calls command passed and execute them
*
* @args: array of arguments
*
* @fptr: pointer to the beginning of args
*
* @rel: int type
 *
 * Return: value of the last executed command
 */
int _args_2(char **args, char **fptr, int *rel)
{
	int rex, i;

	if (!args[0])
		return (*rel);
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			rex = _args_3(args, fptr, rel);
			if (*rel != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (rex);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			rex = _args_3(args, fptr, rel);
			if (*rel == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (rex);
			}
		}
	}
	args = replace_aliases(args);
	rex = _args_3(args, fptr, rel);
	return (rex);
}

/**
* _args_3 - run execution of a command
*
* @args: array of arguments
*
* @fptr: double pointer to the beginning of args
*
* @rel: int type
*
* Return: value of the last executed command
*/
int _args_3(char **args, char **fptr, int *rel)
{
	int rex, i;
	int (*builtin)(char **args, char **fptr);

	builtin = get_builtin(args[0]);
	if (builtin)
	{
		rex = builtin(args + 1, fptr);
		if (rex != EXIT)
			*rel = rex;
	}
	else
	{
		*rel = execute(args, fptr);
		rex = *rel;
	}

	history++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (rex);
}

/**
* _args_4 - Gets, calls, and run the execution of a command
*
* @rel: int type
*
* Return: value of the last executed command.
*/
int _args_4(int *rel)
{
	int rex = 0, i;
	char **args, *line = NULL, **fptr;

	line = _args_1(line, rel);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (rex);
	if (_args_5(args) != 0)
	{
		*rel = 2;
		args_free(args, args);
		return (*rel);
	}
	fptr = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			rex = _args_2(args, fptr, rel);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		rex = _args_2(args, fptr, rel);

	free(fptr);
	return (ret);
}

/**
 * _args_5 - checks if there are ';', ';;', '&&', or '||'
 *
 * @args: 2D pointer to tokenized commands and arguments
 *
 * Return: - 2 Otherwise - 0
 */
int _args_5(char **args)
{
	size_t i;
	char *word, *ne;

	for (i = 0; args[i]; i++)
	{
		word = args[i];
		if (word[0] == ';' || word[0] == '&' || word[0] == '|')
		{
			if (i == 0 || word[1] == ';')
				return (create_error(&args[i], 2));
			ne = args[i + 1];
			if (ne && (ne[0] == ';' || ne[0] == '&' || ne[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
