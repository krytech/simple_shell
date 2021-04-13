#include "shell.h"

/**
 * cd - changes present working directory
 * @input_ll: linked list containing any arguments
 * Return: 0 if success, 2 on error
 */
int cd(str_list_t *input_ll)
{
	char *dir;
	int status = 0;
	str_list_t *HOME = split_str(get_env_var("HOME="), "="),
		   *OLDPWD = split_str(get_env_var("OLDPWD="), "=");

	/* still need to allow variable expansion for $HOME */
	/* And update env vars */
	if (input_ll)
	{
		dir = input_ll->str;
		/* Check for - */
		if (_strncmp(dir, "-", 0) == 0)
			/* Check OLDPWD for NULL first? */
			status = chdir(OLDPWD->next->str);
		else
			status = chdir(dir);
		/* if chdir worked, Update PWD & OLDPWD*/
		/* char *getcwd(char *buf, size_t size); */
	}
	else if (HOME->next)
		status = chdir(HOME->next->str);
		/* if chdir worked, Update PWD & OLDPWD */
	else
		status = 2;
	/* print error message */
	free_list(HOME);
	return (status);
}
