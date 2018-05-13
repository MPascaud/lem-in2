/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 18:01:38 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"


int		ft_search_first_reverse(t_roomlist *end, t_roomlist *roomlistart, int way)
{
	int			maxplace;
	t_roomlist	*roomlist;

	maxplace = 0;
	roomlist = roomlistart;
	roomlist = roomlist->next;

	ft_length(&roomlist, way, &maxplace, end);
	ft_roomlist_to_first(&roomlist, roomlistart);
	ft_smallest_biggest(&roomlist, way, end, &maxplace);
	ft_roomlist_to_first(&roomlist, roomlistart);
	while (roomlist != NULL)
	{
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& roomlist->place == maxplace
				&& ft_check_connection(end, roomlist) == 1)
		{
			roomlist->taken = 1;
			break ;
		}
		roomlist = roomlist->next;
	}
	return (maxplace);
}

int		ft_reverse(t_roomlist *roomlist, int way)
{
	t_roomlist	*roomlistart;
	int		maxplace;

	roomlistart = roomlist;
	roomlist = roomlist->next;
	maxplace = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place == -2)
		{
			maxplace = ft_search_first_reverse(roomlist, roomlistart, way);
		}
		roomlist = roomlist->next;
	}
	if (maxplace == 0)
		return (0);
	roomlist = roomlistart;
	roomlist = roomlist->next;

	ft_search_other_reverses(roomlistart, maxplace, way);

	return (1);
}

void	ft_reset(t_roomlist *roomlistart, int way)
{
	while (roomlistart != NULL)
	{
		if (!(roomlistart->taken == 1
					&& roomlistart->way <= way
					&& roomlistart->place > 0))
		{
			roomlistart->way = 0;
		}
		roomlistart = roomlistart->next;
	}
}



int		ft_is_there_a_way(t_roomlist *roomlistart, int way)
{
	if (ft_reverse(roomlistart, way) == 1)
	{
		ft_reset(roomlistart, way);
			return (1);
	}
	else
		return (0);
}
