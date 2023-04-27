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
	*line = new_line;
}
