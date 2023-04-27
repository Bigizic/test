#include "main.h"
/* header */

/**
* _handle - read line from standard input as needed
*
* @line: char pointer
*
* @read: The length of line
*
* Return: void
*/
void _handle(char **line, ssize_t read)
{
	char *old, *new;
	char previous, current, next;
	size_t i, j;
	ssize_t len;

	len = get_new_len(*line);
	if (len == read - 1)
		return;
	new = malloc(len + 1);
	if (!new)
		return;
	j = 0;
	old = *line;
	for (i = 0; old[i]; i++)
	{
		current = old[i];
		next = old[i + 1];
		if (i != 0)
		{
			previous = old[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new[j++] = ' ';
					new[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new[j++] = ';';
					new[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new[j++] = ' ';
				new[j++] = ';';
				if (next != ' ')
					new[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new[j++] = '&';
					new[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new[j++] = '|';
					new[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old[i - 1] != ' ')
				new[j++] = ' ';
			new[j++] = ';';
			if (next != ' ' && next != ';')
				new[j++] = ' ';
			continue;
		}
		new[j++] = old[i];
	}
	new[j] = '\0';

	free(*line);
	*line = new;
}


/**
* get_new_len - gets new length of line partitioned
*
* @line: char type
*
* Return: 0
*
*/

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
