/**
* main - unix command line interpreter
*
* @argc: int type
*
* @argv: char type
*
* Description: this function prints a prompt and gets user
* input,using the getline function and it stores the input
* in the read_getline variable, it copies the user input
* from the read_getline var to getline_cp, it use the
* strtok function to break down the user input and
* calculate the number of strings, it saves the calculated
* strings in a variable and use the exe_command function
* to execute the calculated string.
*
* Return: 0 if success
*/

int main(int argc, char *argv[])
{
	size_t i = 0;
	ssize_t read_getline;
	char *get_line = NULL, *getline_cp = NULL, *strtoken;
	const char *delim = " \n", *prompt = "($) ";
	int num = 0;
	(void)argc;
	while (1)
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		read_getline = _getline(&get_line, &i, stdin);
		if (read_getline == -1)
		{
			write(STDOUT_FILENO, delim, _strlen(delim));
		}

		getline_cp = malloc(sizeof(char) * read_getline);
		getline_error(getline_cp);
		_strcpy(getline_cp, get_line);
		strtoken = _strtok(get_line, delim);
		while (strtoken != NULL)
		{
			num++;
			strtoken = _strtok(NULL, delim);
		}
		num++;
		argv = malloc(sizeof(char) * num);
		strtoken = _strtok(getline_cp, delim);
		check_strtoken(strtoken, argv, delim);
		exe_command(argv);

		free(getline_cp);
		free(get_line);
		get_line = NULL;
		getline_cp = NULL;
		num = 0;
	}
		return (0);
}
