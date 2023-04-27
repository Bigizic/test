#include "main.h"
/* header */

/**
* environ_free - frees the the environment
*
* Return: void
*/
void environ_free(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}


/**
* as_free - frees args memory
*
* @as: a null-terminated double pointer
*
* @fptr: pointer to a pointer to the beginning of args
*
* Return: void
*/
void as_free(char **as, char **fptr)
{
	size_t i;

	for (i = 0; as[i] || as[i + 1]; i++)
		free(as[i]);

	free(fptr);
}


/**
* alias_list_free - frees linked list
*
* @head: head of the list to be freed
*
* Return: void
*/
void alias_list_free(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}


/**
* free_list - frees a list_t list
*
* @head: the head of the list to be freed
*
* Return: void
*/
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
