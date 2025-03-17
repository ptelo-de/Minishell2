
#include "minishell.h"

void check_main_args(int ac)
{
	if (ac != 1)
	{
		ft_putendl_fd("do not add parameters to executable", 1);
		exit(0); //! exit(1)?
	}
}
/* [] Check main_args
    [] if ac != 1
		[] printf("do not add parameters to executable");
		[] exit(0) ou exit (1)
	[if !env
			handle_env_i
	[]else
			shell.env = array_dup(env);
	
*/