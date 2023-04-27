#include "main.h"

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(char *argv[])
{
	builtin_t builtin[] = {
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0){
            printf("match found- builtin[i].name: %s\n cmd: %s\n" ,builtin[i].name, cmd);
			break;
        }
	}
	return (builtin[i].f);
}
