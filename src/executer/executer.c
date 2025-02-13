/* ***********************
*************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:09:19 by bde-luce          #+#    #+#             */
/*   Updated: 2025/02/12 15:45:48 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/*int	get_last_fd_in(t_cmd *cmd)
{
	
}*/

/*int	executer(t_cmd *cmd)
{
	//t_shell	*shell;
	t_cmd	*temp;
	int		i;

	//shell = get_shell();
	temp = cmd;
	i = 0;
	while (temp->red[i])
	{
		if (temp->red[i]->type == INFILE && access(temp->red[i]->str, F_OK) == -1)
		{
			printf("Error: %s: No such file or directory\n", temp->red[i]->str);
			return (0);
		}
		i++;
	}
	return (1);
}*/