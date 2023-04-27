#include "main.h"
/* header */

/**
* _realloc - Function that reallocate a memory block using malloc and free()
*
* @ptr: void pointer type
*
* @old: unsigned int type
*
* @new_ptr: unsigned int type
*
* Return: void
*/

void *_realloc(void *ptr, unsigned int old, unsigned int new_ptr)
{
	char *ptr_cp, *string;
	void *n;
	unsigned int i;

	if (new_ptr == old)
		return (ptr);

	if (ptr == NULL)
	{
		n = malloc(new_ptr);
		if (n == NULL)
		{
			return (NULL);
		}
		return (n);
	}
	if (new_ptr == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_cp = ptr;
	n = malloc(new_ptr * sizeof(ptr_cp));
	if (n == NULL)
	{
		free(ptr);
		return (NULL);
	}
	string = n;
	for (i = 0; i < old && i < new_ptr; i++)
	{
		string[i] = *ptr_cp++;
	}
	free(ptr);
	return (n);
}


/**
* _assign - Function that reassigns the line variable for _getline
*
* @line: char double pointer
*
* @n: size_t type
*
* @buffer: char type
*
* @b: size_t type
*
* Return: void
*/

void _assign(char **line, size_t *n, char *buffer, size_t b)
{
	if (*line == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*line = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*line = buffer;
	}
	else
	{
		_strcpy(*line, buffer);
		free(buffer);
	}
}


/**
* _getline - Function that acts line getline()
*
* @line: char double pointer
*
* @n: size_t type
*
* @stream: stream to read from
*
* Return: 0
*/
ssize_t _getline(char **line, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t tem;
	char word = 'x', *buffer;
	int i;

	if (input == 0)
		fflush(stream);

	else
		return (-1);
	input = 0;

	buffer = malloc(120 * sizeof(char));
	if (!buffer)
		return (-1);

	while (word != '\n')
	{
		i = read(STDIN_FILENO, &word, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = word;
		input++;
	}
	buffer[input] = '\0';
	_assign(line, n, buffer, input);
	tem = input;
	if (i != 0)
		input = 0;
	return (tem);
}
