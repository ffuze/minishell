/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:55:40 by adegl-in          #+#    #+#             */
/*   Updated: 2024/11/23 18:34:22 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*int main()
{
	t_list *head = NULL;

	t_list *nodo1 = ft_lstnew("Nodo 1");
	t_list *nodo2 = ft_lstnew("Nodo 2");
	t_list *nodo3 = ft_lstnew("Nodo 3");

	nodo1->next = nodo2;
	nodo2->next = nodo3;

	head = nodo1;

	t_list *ultimonodo = ft_lstlast(head);
	if (ultimonodo)
		printf("Contenuto dell'ultimo nodo: %s\n", (char *)ultimonodo->content);
	else
		printf("Ultimo nodo assente");
}*/