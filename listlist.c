/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 18:13:52 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

t_listlist	*ft_listlistnew(t_listlist *listlist)
{
	t_listlist	*nextlink;

	nextlink = (t_listlist*)malloc(sizeof(t_listlist));
	nextlink->previous = listlist;
	nextlink->next = NULL;
	return (nextlink);
}

void	ft_listlist(t_listlist *listlist, t_roomlist *roomlistart, t_roomlist *roomlist, int way)
{
	int		max;

	max = way;
	way = 1;
	while (way <= max)
	{
		listlist->next = ft_listlistnew(listlist);
		listlist = listlist->next;
		listlist->waylist = ft_waylist(roomlistart, roomlist, way);
		way++;
	}

}

void	ft_first_listlist(t_variables *var)
{
	var->listlist = (t_listlist*)malloc(sizeof(t_listlist));
	var->listlist->previous = NULL;
	var->listlist->waylist = NULL;
	var->listlist->next = NULL;
}
