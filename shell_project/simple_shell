#include "main.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @argv: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(char *argv[])
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd);
	dir = argv[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/");
	}
	/*datash->status = 0;*/
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @argv: data relevant (directories)
 * Return: no return
 */
void cd_to(char *argv[])
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = argv[1];
	if (chdir(dir) == -1)
	{
		/*get_error(datash, 2);*/
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir);

	free(cp_pwd);
	free(cp_dir);

	/*datash->status = 0;*/

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @argv: data relevant (environ)
 * Return: no return
 */
void cd_previous(char *argv[])
{
	char *error;
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD");

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd);
	else
		set_env("PWD", cp_oldpwd);

	p_pwd = _getenv("PWD");

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	/*datash->status = 0;*/

	/*chdir(p_pwd);*/
	if (chdir(p_pwd) == -1)
        {
		error = malloc(sizeof(char) * 30);
		_strcpy(error, "wrong use of command: ");
		_strcat(error, argv[0]);
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
        }
}

/**
 * cd_to_home - changes to home directory
 *
 * @argv: data relevant (environ)
 * Return: no return
 */
void cd_to_home(char *argv[])
{
	char *error;
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME");

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		/*get_error(datash, 2);*/
		error = malloc(sizeof(char) * 30);
		_strcpy(error, "wrong use of command: ");
		_strcat(error, argv[0]);
		write(STDERR_FILENO, error, _strlen(error));
		free(error);

		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd);
	set_env("PWD", home);
	free(p_pwd);
	/*datash->status = 0;*/
}

