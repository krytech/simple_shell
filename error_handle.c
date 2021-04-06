#include "shell.h"

int write_error(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}




void error_main(char **av, char *command, int count)
{
	int mul = 1;
	int copy = count;
	int numlen = 1;

	write(STDERR_FILENO, av[0], _strlen(av[0]));
	write(STDERR_FILENO, ": ", 2);

	/* error count */
	while (copy >= 10)
	{
		copy /= 10;
		mul *= 10;
		++numlen;
	}
	while (numlen > 1)
	{
		if ((count / mul) < 10)
			write_error((count / mul) + '0');
		else
			write_error((count / mul) % 10 + '0');
		--numlen;
		mul /= 10;
	}
	/* write command error */
	write_error(count % 10 + '0');
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);
}
