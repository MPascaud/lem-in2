/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 19:55:42 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_waylist	*ft_waylistnew(t_waylist *waylist)
{
	t_waylist	*nextlink;

	nextlink = (t_waylist*)malloc(sizeof(t_waylist));
	nextlink->previous = waylist;
	nextlink->next = NULL;
	return (nextlink);
}

void		ft_build_waylist(t_roomlist *roomlist, t_waylist **waylist,
		int way, t_roomlist *roomlistart)
{
	int		place;
	char	*str;

	place = 0;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if ((roomlist->place == 0 || roomlist->way == way)
				&& roomlist->place == place)
		{
			(*waylist)->next = ft_waylistnew(*waylist);
			*waylist = (*waylist)->next;
			(*waylist)->place = roomlist->place;
			(*waylist)->way = roomlist->way;
			if ((*waylist)->place == 0)
				(*waylist)->way = way;
			str = ft_strnew(ft_strlen(roomlist->name));
			(*waylist)->name = ft_strcpy(str, roomlist->name);
			place++;
			roomlist = roomlistart;
		}
		roomlist = roomlist->next;
	}
}

void		ft_waylist_first(t_waylist *waylist, int way)
{
	waylist->name = NULL;
	waylist->way = way;
	waylist->place = -1;
	waylist->previous = NULL;
	waylist->next = NULL;
}

t_waylist	*ft_waylist(t_roomlist *roomlistart, t_roomlist *roomlist, int way)
{
	t_waylist	*waylist;
	t_waylist	*waylistart;
	char		*str;

	waylist = (t_waylist*)malloc(sizeof(t_waylist));
	ft_waylist_first(waylist, way);
	waylistart = waylist;
	ft_build_waylist(roomlist, &waylist, way, roomlistart);
	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if (roomlist->place == -2)
		{
			waylist->next = ft_waylistnew(waylist);
			waylist = waylist->next;
			waylist->place = roomlist->place;
			waylist->way = way;
			str = ft_strnew(ft_strlen(roomlist->name));
			waylist->name = ft_strcpy(str, roomlist->name);
		}
		roomlist = roomlist->next;
	}
	return (waylistart);
}
