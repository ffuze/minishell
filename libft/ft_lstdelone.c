/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:10:32 by adegl-in          #+#    #+#             */
/*   Updated: 2024/11/27 09:57:25 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/*void	del(void *c)
{
	free(c);
}*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !*del)
		return ;
	(*del)(lst->content);
	free(lst);
}

/*int main(void)
{
    t_list *head = NULL;
	t_list *node1 = ft_lstnew(ft_strdup("Nodo 1"));
    
	head = node1;
	printf("Head presente: %s\n", (char *)head->content);

    ft_lstdelone(head, del);

	head = NULL;

	if (!head)
    	printf("Head eliminato con successo");
	else
		printf("Ha coglione non funziona");

    return 0;
}*/