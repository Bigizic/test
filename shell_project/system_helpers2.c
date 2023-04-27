#include "main.h"

/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
* _strcmp - Compares two strings
*
* @s1: first string to be compared
* @s2: second string to be compared
*
* Return: Returns (0)
*/
int _strcmp(const char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}
/**
 * _strlen - Returns the lenght of a string.
 * @s: The string to evaluate
 * Return: Returns (0)
 */
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: The dest of the copied str
 * @src: The source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];	}
	dest[a] = '\0';

	return (dest);
}

/**
 * _strdup - duplicates a str in the heap memory.
 * @s: The string to be duplicated
 * Return: duplicated str
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

