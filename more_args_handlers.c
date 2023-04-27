#include "main.h"
/* header */

/**
* _replacement - replace a variable
*
* @line: char double pointer
*
* @rel: int type
*
* Return: void
*/
void _replacement(char **line, int *rel)
{
	int j, i = 0, len;
	char *replace = NULL, *old = NULL, *new;

	old = *line;
	for (j = 0; old[j]; j++)
	{
		if (old[j] == '$' && old[j + 1] && old[j + 1] != ' ')
		{
			if (old[j + 1] == '$')
			{
				replace = get_pid();
				i = j + 2;
			}
			else if (old[j + 1] == '?')
			{
				replace = _itoa(*rel);
				i = j + 2;
			}
			else if (old[j + 1])
			{
				for (i = j + 1; old[i] && old[i] != '$' &&
						old[i] != ' '; i++);
				len = i - (j + 1);
				replace = get_env_value(&old[j + 1], len);
			}
			new = malloc(j + _strlen(replace)+ _strlen(&old[i]) + 1);
			if (!line)
				return;
			new[0] = '\0';
			_strncat(new, old, j);
			if (replace)
			{
				_strcat(new, replace);
				free(replace);
				replace = NULL;
			}
			_strcat(new, &old[i]);
			free(old);
			*line = new;
			old = new;
			j = -1;
		}
	}
}


/**
* get_pid - gets the current process ID
*
* Return: NULL || proccess id
*/
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Error cannot read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}


/**
* get_env_value - gets the value corresponding to an environmental variable
*
* @start: environmental variable to search for
*
* @len: int type
*
* Return: NULL if variable not found
*/
char *get_env_value(char *start, int len)
{
	char **address;
	char *replace = NULL, *word, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, start, len);

	address = _getenv(var);
	free(var);
	if (address)
	{
		word = *address;
		while (*word != '=')
			word++;
		word++;
		replace = malloc(_strlen(word) + 1);
		if (replace)
			_strcpy(replace, word);
	}

	return (replace);
}
