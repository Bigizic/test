#include "main.h"
/**
* _getenv - Gets an environment variable from the global env
*
* @name: Name of the environment variable to get
*
* Return: The environment variable, NULL if not found
*/
char *_getenv(const char *name)
{
	int i;
	char *equal;

	for (i = 0; environ[i] != NULL; i++)
	{
		equal = _strchr(environ[i], '=');

		if (_strcmp(name, environ[i]) == 0)
		{
			return (equal + 1);
		}
	}
	return (NULL);
}

/**
 * _memcpy - copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}


/**
* _strcat - do something
*
* @dest: char type
*
* @src: const char type
*
* Return: void
*/

char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}


/**
* _execvp - Executes a command
*
* @file: The command to execute
*
* @argv: array of the command line arguments
*
* Return: -1,if file was not found on any PATH
*/
int _execvp(const char *file, char *const argv[])
{
	char *path;
	char *paths;
	char *token;
	char *envp[] = {NULL};

	paths = _strdup(_getenv("PATH"));

	token = strtok(paths, ":");
	while (token != NULL)
	{
		path = malloc(strlen(token) + strlen(file) + 2);
		_strcpy(path, token);
		_strcat(path, "/");
		_strcat(path, file);
		execve(path, argv, envp);
		free(path);
		token = strtok(NULL, ":");
	}
	return (-1);
}
