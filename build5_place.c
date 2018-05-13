/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:25:10 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		ft_check_previous_place(t_roomlist *roomlist, int i,
		t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->beftunnels)[i], roomlistart->name) == 0)
		{
			if (roomlist->place != 0 && roomlistart->place != -1
					&& roomlistart->place != -2 && (roomlist->place == -1
						|| roomlist->place > roomlistart->place + 1))
			{
				roomlist->place = roomlistart->place + 1;
				return (1);
			}
			if (roomlistart->place != 0 && roomlist->place != -1
					&& roomlist->place != -2 && (roomlistart->place == -1
						|| roomlistart->place > roomlist->place + 1))
			{
				roomlistart->place = roomlist->place + 1;
				return (1);
			}
		}
		roomlistart = roomlistart->next;
	}
	return (0);
}

int		ft_check_next_place(t_roomlist *roomlist, int i,
		t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->tunnels)[i], roomlistart->name) == 0)
		{
			if (roomlist->place != 0 && roomlistart->place != -1
					&& roomlistart->place != -2 && (roomlist->place == -1
						|| roomlist->place > roomlistart->place + 1))
			{
				roomlist->place = roomlistart->place + 1;
				return (1);
			}
			if (roomlistart->place != 0
					&& roomlist->place != -1
					&& roomlist->place != -2
					&& (roomlistart->place == -1
						|| roomlistart->place > roomlist->place + 1))
			{
				roomlistart->place = roomlist->place + 1;
				return (1);
			}
		}
		roomlistart = roomlistart->next;
	}
	return (0);
}

void	ft_place_by_beftunnels(t_roomlist *roomlist, int i,
		t_roomlist *roomlistart)
{
	while (roomlist != NULL)
	{
		while ((roomlist->beftunnels)[i] != NULL)
		{
			if (ft_check_previous_place(roomlist, i, roomlistart) == 1)
			{
				roomlist = roomlistart;
				break ;
			}
			i++;
		}
		i = 0;
		roomlist = roomlist->next;
	}
}

void	ft_place_by_tunnels(t_roomlist *roomlist, int i,
		t_roomlist *roomlistart)
{
	while (roomlist != NULL)
	{
		while ((roomlist->tunnels)[i] != NULL)
		{
			if (ft_check_next_place(roomlist, i, roomlistart) == 1)
			{
				roomlist = roomlistart;
				break ;
			}
			i++;
		}
		i = 0;
		roomlist = roomlist->next;
	}
}

void	ft_place(t_filist *filist, t_roomlist *roomlist)
{
	int			i;
	t_filist	*filistart;
	t_roomlist	*roomlistart;

	i = 0;
	filistart = filist;
	roomlistart = roomlist;
	filist = filist->next;
	roomlist = roomlist->next;
	ft_place_by_beftunnels(roomlist, i, roomlistart);
	ft_place_by_tunnels(roomlist, i, roomlistart);
}
