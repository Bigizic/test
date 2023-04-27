#ifndef MAIN_H
#define MAIN_H

extern char **environ;

/* headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char *argv[]);
} builtin_t;

int (*get_builtin(char *cmd))(char *argv[]);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
char *copy_info(char *name, char *value);
int set_env(const char *name_mut, const char *value_mut);
int _setenv(char *argv[]);
int _unsetenv(char *argv[]);

/* error message */
int getline_error(char *getline_cp);
void check_strtoken(char *strtoken, char *argv[], const char *delim);
void child_error(pid_t child_pid);
void path_error(char *path_copy);
void cmd_error(char *cmd_path);


/* system helpers */
char *_getenv(const char *name);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
char *_strcat(char *dest, const char *src);
int _execvp(const char *file, char *const argv[]);


/* system helpers 2 */
int _strlen(const char *s);
char *_strchr(char *s, char c);
int _strcmp(const char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);

/* system helpers 3 */
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _atoi(char *s);
int _strncmp(const char *s1, const char *s2, size_t n);

/* execution command */
int exe_command(char *argv[]);
void exit_shell(char *argv[]);
void access_func(char *cmd_path, char *argv[]);
void env_shell(void);
void string_cmp(char *argv[]);

/* getline function */
void *_realloc(void *ptr, unsigned int old, unsigned int new_ptr);
void _assign(char **line, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **line, size_t *n, FILE *stream);

/* cd.c */
void cd_dot(char *argv[]);
void cd_to(char *argv[]);
void cd_previous(char *argv[]);
void cd_to_home(char *argv[]);

/* cd_shell.c */
int cd_shell(char *argv[]);

/* more_helpers.c */
void rev_string(char *s);

#endif
