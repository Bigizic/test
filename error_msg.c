#include "main.h"
/* header */

/**
 * error_handler - error message to stderr
 *
 * @args: char type
 *
 * @err: int type
 *
 * Return: err
 */
int error_handler(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = env_error(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = syntax_error(args);
		else
			error = cd_error(args);
		break;
	case 100:
		error = error_100(args);
		break;
	case 101:
		error = error_101(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}


/**
* error_100 - error message for permission denied
*
* @args: char type
*
* Return: error message
*/
char *error_100(char **args)
{
	char *error, *list;
	int len;

	list = _itoa(history);
	if (!list)
		return (NULL);

	len = _strlen(name) + _strlen(list) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(list);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, list);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(list);
	return (error);
}

/**
 * error_101 - error message for command not found
 *
 * @args: char type
 *
 * Return: error message
 */
char *error_101(char **args)
{
	char *error, *list;
	int len;

	list = _itoa(history);
	if (!list)
		return (NULL);

	len = _strlen(name) + _strlen(list) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(list);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, list);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(list);
	return (error);
}


/**
* _itoa - converts an integer to a string
*
* @num: int type
*
* Return: 0
*/
char *_itoa(int num)
{
	char *buffer;
	int len;
	unsigned int num1, num2;
	int l = 1;

	if (num < 0)
	{
		l++;
		num2 = num * -1;
	}
	else
		num2 = num;
	while (num2 > 0)
	{
		l++;
		num2 /= 10;
	}
	len = l;
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}
