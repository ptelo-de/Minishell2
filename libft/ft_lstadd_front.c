/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:15:37 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/24 22:21:47 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/* int main()
{
	t_list *node1 = ft_lstnew(ft_strdup("node1"));
	t_list *node2 = ft_lstnew(ft_strdup("node2"));
	ft_lstadd_front(&node2, node1);
	printf("%s\n", (char *)(ft_lstlast(node1)->content));
} */