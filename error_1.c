#include "main.h"
/* header */

/**
* env_error - error message for env errors
*
* @args: char type
*
* Return: error
*/
char *env_error(char **args)
{
	char *error, *list;
	int len;

	list = _itoa(history);
	if (!list)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(list) + _strlen(args[0]) + 45;
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
	_strcat(error, "Error\n");
	free(list);
	return (error);
}


/**
* error_1 - error message 1
*
* @args: char type
*
* Return: error
*/
char *error_1(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");
	return (error);
}


/**
* error_2 - error message 2
*
* @args: char type
*
* Return: error
*/
char *error_2(char **args)
{
	char *error, *list;
	int len;

	list = _itoa(history);
	if (!list)
		return (NULL);

	len = _strlen(name) + _strlen(list) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(list);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, list);
	_strcat(error, " Error ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(list);
	return (error);
}


/**
* syntax_error - error message for syntax errors
*
* @args: char type
*
* Return: error
*/
char *syntax_error(char **args)
{
	char *error, *list;
	int len;

	list = _itoa(history);
	if (!list)
		return (NULL);

	len = _strlen(name) + _strlen(list) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(list);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, list);
	_strcat(error, ": Syntax error \"");
	_strcat(error, args[0]);
	_strcat(error, "\" Error\n");

	free(list);
	return (error);
}


/**
* cd_error - error message for cd
*
* @args: char type
*
* Return: error
*/
char *cd_error(char **args)
{
	char *error, *list;
	int len;

	list = _itoa(history);
	if (!list)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		_strcat(error, " Error ");
	else
		_strcat(error, " Error ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(list);
	return (error);
}
