#include "main.h"

/**
 * cd_shell - changes current directory
 *
 * @argv: data relevant
 * Return: 1 on success
 */
int cd_shell(char *argv[])
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = argv[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(argv);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(argv);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(argv);
		return (1);
	}

	cd_to(argv);

	return (1);
}
