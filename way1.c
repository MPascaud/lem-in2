/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 19:50:33 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_roomlist_to_first(t_roomlist **roomlist, t_roomlist *roomlistart)
{
	*roomlist = roomlistart;
	*roomlist = (*roomlist)->next;
}

int		ft_no_zero(t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (roomlistart->way == 0 && roomlistart->place != -1)
		{
			return (0);
		}
		roomlistart = roomlistart->next;
	}
	return (1);
}

int		ft_way(t_filist *filist, t_roomlist *roomlist,
		t_roomlist *roomlistart, int way)
{
	int		progress;

	filist = filist->next;
	roomlist = roomlist->next;
	progress = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place == 0 || roomlist->place == -2)
			roomlist->way = way;
		roomlist = roomlist->next;
	}
	ft_roomlist_to_first(&roomlist, roomlistart);
	while (1)
	{
		while (roomlist != NULL)
		{
			ft_searching_way(roomlist, roomlistart, way);
			roomlist = roomlist->next;
		}
		if (ft_no_zero(roomlistart) == 0)
			ft_roomlist_to_first(&roomlist, roomlistart);
		else
			return (ft_is_there_a_way(roomlistart, way));
	}
	return (0);
}
