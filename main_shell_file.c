#include "shell.h"

/**
 * custom_main - entry point
 * @custom_ac: arg count
 * @custom_av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int custom_main(int custom_ac, char **custom_av)
{
	custom_info_t custom_info[] = { INFO_INIT };
	int custom_fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (custom_fd)
		: "r" (custom_fd));

	if (custom_ac == 2)
	{
		custom_fd = open(custom_av[1], O_RDONLY);
		if (custom_fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(custom_av[0]);
				_eputs(": 0: Can't open ");
				_eputs(custom_av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		custom_info->readfd = custom_fd;
	}
	custom_populate_env_list(custom_info);
	custom_read_history(custom_info);
	custom_hsh(custom_info, custom_av);
	return (EXIT_SUCCESS);
}
