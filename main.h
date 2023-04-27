#ifndef MAIN_H
#define MAIN_H


/* headers */
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

/* envirnoment variable */
extern char **environ;

/* history */
int history;

/* program name */
char *name;


#define END_OF_FILE -2
#define EXIT -3

/**
* struct list_s - defines a list
*
* @dir: char directory path
*
* @next: pointer to another strucxture list
*/
typedef struct list_s
{
	char *dir;
	struct list_s *next;
}list_t;

/**
* struct helper_s - defines builtin commands
*
* @name: char type
*
* @fptr: function pointer to the builtin command
*/
typedef struct helper_s
{
	char *name;
	int (*f)(char **argv, char **fptr);
}helper_t;


typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
}alias_t;

alias_t *verb;

/* main function */
void _signal_(int si);
int exe_command(char **args, char **fptr);

/*str functions */
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strtok(char str[], const char *delim);
char *_strcat(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strcmp(const char *s1, char *s2);
int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);
char *_strncat(char *dest, const char *src, size_t n);


/* system helpers */
char *_itoa(int num);


/* args handlers */
char *_args_1(char *line, int *rel);
int _args_2(char **args, char **fptr, int *rel);
int _args_3(char **args, char **fptr, int *rel);
int _args_4(int *rel);
int _args_5(char **args);


/* more args handlers */
void _replacement(char **line, int *rel);
char *get_pid(void);
char *get_env_value(char *start, int len);


/* error messages */
char *env_error(char **args);
char *error_1(char **args);
char *error_2(char **args);
char *syntax_error(char **args);
char *cd_error(char **args);
int error_handler(char **args, int err);
char *error_100(char **args);
char *error_101(char **args);


/* handles free */
void environ_free(void);
void as_free(char **as, char **fptr);
void alias_list_free(alias_t *head);
void free_list(list_t *head);
void args_free(char **args, char **fptr);

/* location */
char _location(char *cmd);
list_t *tokenize_path(char *path);
char *put_dir(char *path);

#endif
