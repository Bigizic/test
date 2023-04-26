#include "main.h"
/* header */

/**
* _location - function that locates a command in the PATH
*
* @cmd: command passed to locate
*
* Description: this function takes the argument passed to
* it from standard input and it find the argument in the
* PATH variable. returns NULL if a command can't be found
* else it return pathname of the command
*
* Return: NULL or pathname of command
*/
char _location(char *cmd)
{
	list_t *dir_cp, *j;
	struct stat st;
	char *rel, **path = _getenv("PATH");

	if (!path || !(*path))
		return (NULL);

	dir_cp = tokenize_path(*path + 5);
	j = dir_cp;
	while (dir_cp)
	{
		rel = malloc(_strlen(dir_cp->dir) + _strlen(cmd)+ 2);
		if (!rel)
			return (NULL);
		_strcpy(rel, dir_cp->dir);
		_strcat(rel, "/");
		_strcat(rel, cmd);
		if (stat(rel, &st) == 0)
		{
			free_list(j);
			return (j);
		}
		dir_cp = dir_cp->next;
		free(rel);
	}
	free_list(j);
	return (NULL);
}


/**
* tokenize_path - tokenize list_s linked list
*
* @path: a char of colon seperated list of dir
*
* Return: 0 if success
*/
list_t *tokenize_path(char *path)
{
	int i;
	char **dir_cp, *path_copy = put_dir(path);
	list_t *head = NULL;

	if (!path_copy)
		return (NULL);
	dir_cp = _strtok(path_copy, ":");
	free(path_copy);
	if (!dir_cp)
		return (NULL);

	for (i = 0; dir_cp[i]; i++)
	{
		if (node_end(&head, dir_cp[i]) == NULL)
		{
			free_list(head);
			free(dir_cp);
			return (NULL);
		}
	}

	free(dir_cp);

	return (head);
}


/**
* put_dir - copies path
*
* @path: colon-separated list of dir
*
* Return: 0 if success
*/
char *put_dir(char *path)
{
	int i, len = 0;
	char *path_cp, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len ++;
		}
		else
			len ++;
	}
	path_cp = malloc(sizeof(char) * (len + 1));
	if (!path_cp)
		return (NULL);
	path_cp[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_cp, pwd);
				_strcat(path_cp, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_cp, ":");
				_strcat(path_cp, pwd);
			}
			else
				_strcat(path_cp, ":");
		}
		else
		{
			_strncat(path_cp, &path[i], 1);
		}
	}
	return (path_cp);
}
