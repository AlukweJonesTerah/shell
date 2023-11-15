#ifndef MAIN_SHELL_HEADER_FILE
#define MAIN_SHELL_HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct custom_liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct custom_liststr
{
	int num;
	char *str;
	struct custom_liststr *next;
} custom_list_t;

/**
 * struct custom_passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for the function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct custom_passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	custom_list_t *env;
	custom_list_t *history;
	custom_list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} custom_info_t;

#define CUSTOM_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct custom_builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct custom_builtin
{
	char *type;
	int (*func)(custom_info_t *);
} custom_builtin_table;

/* input_run.c */
int custom_hsh(custom_info_t *custom_info, char **custom_av);
int custom_find_builtin(custom_info_t *custom_info);
void custom_find_cmd(custom_info_t *custom_info);
void custom_fork_cmd(custom_info_t *custom_info);

/* __parser.c */
int custom_is_cmd(custom_info_t *info, char *custom_path);
char *custom_dup_chars(char *custom_pathstr, int custom_start, int custom_stop);
char *custom_find_path(custom_info_t *info, char *custom_pathstr, char *custom_cmd);

/* input_run.c */
int custom_hsh(custom_info_t *custom_info, char **custom_av);
int custom_find_builtin(custom_info_t *custom_info);
void custom_find_cmd(custom_info_t *custom_info);
void custom_fork_cmd(custom_info_t *custom_info);

/* errors.c */
void _custom_eputs(char *str);
int _custom_eputchar(char c);
int _custom_putfd(char c, int fd);
int _custom_putsfd(char *str, int fd);

/* str_token.c */
int custom_strlen(char *s);
int custom_strcmp(char *s1, char *s2);
char *custom_starts_with(const char *haystack, const char *needle);
char *custom_strcat(char *dest, char *src);

/* str_token1.c */
char *custom_strcpy(char *dest, char *src);
char *custom_strdup(const char *str);
void custom_puts(char *str);
int custom_putchar(char c);

/* exit.c */
char *_custom_strncpy(char *custom_dest, char *custom_src, int n);
char *_custom_strncat(char *custom_dest, char *custom_src, int n);
char *_custom_strchr(char *custom_s, char custom_c);

/* custom_tokenizer.c */
char **custom_strtow(char *str, char *d);
char **custom_strtow2(char *str, char d);

/* reallocate_mem.c */
char *custom_memset(char *custom_s, char custom_b, unsigned int custom_n);
void custom_ffree(char **custom_pp);
void *custom_realloc(void *custom_ptr, unsigned int custom_old_size, unsigned int custom_new_size);

/* memory.c */
int free_pointer(void **ptr);

/* atoi.c */
int isInteractive(custom_info_t *infoStruct);
int isDelimiter(char character, char *delimiterString);
int isAlpha(int character);
int stringToInteger(char *inputString);

/* errors1.c */
int _custom_erratoi(char *s);
void custom_print_error(custom_info_t *info, char *estr);
int custom_print_d(int input, int fd);
char *custom_convert_number(long int num, int base, int flags);
void custom_remove_comments(char *buf);

/* builtin.c */
int exitShell(custom_info_t *shellInfo);
int changeDirectory(custom_info_t *shellInfo);
int showHelp(custom_info_t *shellInfo);

/* builtin1.c */
int _custom_history(custom_info_t *info);
int unset_custom_alias(custom_info_t *info, char *str);
int set_custom_alias(custom_info_t *info, char *str);
int _custom_alias(custom_info_t *info);
int print_custom_alias(custom_list_t *node);

/* get_line.c */
ssize_t custom_input_buf(custom_info_t *custom_info, char **custom_buf, size_t *custom_len);
ssize_t custom_get_input(custom_info_t *custom_info);
ssize_t custom_read_buf(custom_info_t *custom_info, char *custom_buf, size_t *i);
int custom_getline(custom_info_t *custom_info, char **ptr, size_t *length);
void custom_sigintHandler(__attribute__((unused))int sig_num);

/* getinformation.c */
void custom_clear_info(custom_info_t *custom_info);
void custom_set_info(custom_info_t *custom_info, char **custom_av);
void custom_free_info(custom_info_t *custom_info, int all);

/* environment.c */
int _custom_env(custom_info_t *info);
char *_custom_getenv(custom_info_t *info, const char *name);
int _custom_setenv(custom_info_t *info);
int _custom_unsetenv(custom_info_t *info);
int populate_custom_env_list(custom_info_t *info);


/* get_environment.c */
char **custom_get_environ(custom_info_t *info);
int custom_unsetenv(custom_info_t *info, char *var);
int custom_setenv(custom_info_t *info, char *var, char *value);

/* history.c */
char *custom_get_history_file(custom_info_t *custom_info);
int custom_write_history(custom_info_t *custom_info);
int custom_read_history(custom_info_t *custom_info);
int custom_build_history_list(custom_info_t *custom_info, char *custom_buf, int linecount);
int custom_renumber_history(custom_info_t *custom_info);

/* list.c */
custom_list_t *custom_add_node(custom_list_t **custom_head, const char *custom_str, int custom_num);
custom_list_t *custom_add_node_end(custom_list_t **custom_head, const char *custom_str, int custom_num);
size_t custom_print_list_str(const custom_list_t *custom_h);
int custom_delete_node_at_index(custom_list_t **custom_head, unsigned int custom_index);
void custom_free_list(custom_list_t **custom_head_ptr);

/* list1.c */
size_t custom_list_len(const custom_list_t *current_node);
char **custom_list_to_strings(custom_list_t *head);
size_t custom_print_list(const custom_list_t *current_node);
custom_list_t *custom_node_starts_with(custom_list_t *current_node, char *prefix, char c);
ssize_t custom_get_node_index(custom_list_t *head, custom_list_t *target_node);

/* _variables.c */
int custom_is_chain(custom_info_t *info, char *buf, size_t *p);
void custom_check_chain(custom_info_t *info, char *buf, size_t *p, size_t i, size_t len);
int custom_replace_alias(custom_info_t *info);
int custom_replace_vars(custom_info_t *info);
int custom_replace_string(char **old, char *new);

#endif

