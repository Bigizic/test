#include "main.h"

/**
* copy_info - copies info to create
* a new env or alias
* @name: name (env or alias)
* @value: value (env or alias)
*
* Return: new env or alias.
*/
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
* set_env - sets an environment variable
*
* @name_mut: name of the environment variable
* @value_mut: value of the environment variable
* Return: no return
*/

int set_env(const char *name_mut, const char *value_mut)
{
	size_t namelen, valuelen;
	char *envstr;
	int i;
	char *name = (char *)name_mut;
	char *value = (char *)value_mut;

	/* Check for valid arguments */
	if (name == NULL || name[0] == '\0' ||
			_strchr(name, '=') != NULL || value == NULL)
		return (-1);

	/* Calculate the lengths of the name and value */
	namelen = _strlen(name);
	valuelen = _strlen(value);

	/* Allocate memory for the environment string */
	envstr = (char *)malloc(namelen + valuelen + 2);
	if (envstr == NULL)
		return (-1);

	/* Build the environment string */
	_strcpy(envstr, name);
	_strcat(envstr, "=");
	_strcat(envstr, value);

	/* Search for an existing environment variable with the same name */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, namelen) == 0 && environ[i][namelen] == '=')
		{
			environ[i] = envstr;
			return (0);
		}
	}

	/* No existing variable was found, add a new one */
	environ[i] = envstr;
	environ[i + 1] = NULL;
	return (0);
}

/**
* _setenv - compares env variables names
* with the name passed.
* @argv: data relevant (env name and env value)
*
* Return: 1 on success.
*/
int _setenv(char *argv[])
{

	if (argv[1] == NULL || argv[2] == NULL)
	{
		/*get_error(datash, -1);*/
		return (1);
	}

	set_env(argv[1], argv[2]);

	return (1);
}


/**
* _unsetenv -  deletes a environment variable
* @argv: char type
* Return: 0
*/

int _unsetenv(char *argv[])
{
	size_t namelen;
	int i;
	char *name;

	name = argv[1];

	/* Check for valid argument */
	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);

	/* Calculate the length of the name */
	namelen = _strlen(name);

	/* Search for the environment variable with the same name */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, namelen) == 0 && environ[i][namelen] == '=')
		{
			/* The variable was found, remove it */
			free(environ[i]);
			for (; environ[i] != NULL; i++)
				environ[i] = environ[i + 1];
			return (0);
		}
	}

	/* The variable was not found */
	return (0);
}
