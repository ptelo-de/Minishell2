/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:10:07 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 02:10:22 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}
