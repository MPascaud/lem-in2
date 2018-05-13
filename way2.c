/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 19:49:48 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		ft_search_previous(t_roomlist *roomlist, t_roomlist *roomlistart,
		int way)
{
	t_roomlist	*tmp;

	roomlistart = roomlistart->next;
	tmp = roomlistart;
	while (roomlistart != NULL)
	{
		if (roomlistart->place == roomlist->place - 1
				&& roomlistart->taken == 0
				&& roomlistart->way == way
				&& ft_check_connection(roomlistart, roomlist) == 1)
		{
			return (1);
		}
		roomlistart = roomlistart->next;
	}
	while (tmp != NULL)
	{
		if (tmp->place == roomlist->place - 1
				&& tmp->taken == 0
				&& tmp->way == 0
				&& ft_check_connection(tmp, roomlist) == 1)
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}

int		ft_search_next(t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if ((roomlistart->place == roomlist->place + 1
					|| roomlistart->place == -2)
				&& roomlistart->taken == 0
				&& (roomlistart->way == 0 || roomlistart->way == way)
				&& ft_check_connection(roomlistart, roomlist) == 1)
		{
			return (1);
		}
		roomlistart = roomlistart->next;
	}
	return (0);
}

void	ft_searching_way(t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	if (roomlist->way == 0 && roomlist->place != 0 && roomlist->taken == 0
			&& ft_search_previous(roomlist, roomlistart, way) == 1)
		roomlist->way = way;
	if ((roomlist->way == way || roomlist->way == 0)
			&& roomlist->place != 0
			&& roomlist->place != -2
			&& (ft_search_next(roomlist, roomlistart, way) == 0
				|| ft_search_previous(roomlist, roomlistart, way) == -1))
	{
		roomlist->way = -1;
	}
}
