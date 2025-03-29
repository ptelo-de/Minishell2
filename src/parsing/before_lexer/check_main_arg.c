/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:09:00 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 02:09:08 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_main_args(int ac)
{
	if (ac != 1)
	{
		ft_putendl_fd("do not add parameters to executable", 1);
		exit(0);
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