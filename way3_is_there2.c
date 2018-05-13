/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 18:08:57 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"



void	ft_length(t_roomlist **roomlist, int way, int *maxplace, t_roomlist *end)
{
	while (*roomlist != NULL)
	{
		if ((*roomlist)->taken == 0
				&& (*roomlist)->way == way
				&& (*roomlist)->place > *maxplace 
				&& ft_check_connection(end, *roomlist) == 1)
			*maxplace = (*roomlist)->place;
		*roomlist = (*roomlist)->next;
	}

}

void	ft_smallest_biggest(t_roomlist **roomlist, int way, t_roomlist *end, int *maxplace)
{
	while (*roomlist != NULL)
	{
		if ((*roomlist)->taken == 0
				&& (*roomlist)->way == way
				&& ((*roomlist)->place != -1)
				&& ft_check_connection(end, *roomlist) == 1
				&& (*roomlist)->place < *maxplace)
			*maxplace = (*roomlist)->place;
		*roomlist = (*roomlist)->next;
	}

}

void	ft_room_max(t_roomlist *roomlist, t_roomlist **roomax, int maxplace, int way)
{
	while (roomlist != NULL)
	{
		if (roomlist->taken == 1
				&& roomlist->way == way
				&& roomlist->place == maxplace)
		{
			*roomax = roomlist;
			break ;
		}
		roomlist = roomlist->next;
	}

}


void	ft_search_other_reverses(t_roomlist *roomlistart, int maxplace, int way)
{
	t_roomlist	*roomlist;
	t_roomlist	*roomax;
	roomlist = roomlistart;
	roomlist = roomlist->next;

	ft_room_max(roomlist, &roomax, maxplace, way);
	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if (roomlist->place == 0
				&& ft_check_connection(roomlist, roomax) == 1)
			return ;
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& roomlist->place == roomax->place - 1
				&& ft_check_connection(roomlist, roomax) == 1)
		{
			roomlist->taken = 1;
			roomax = roomlist;
			roomlist = roomlistart;
		}
		roomlist = roomlist->next;
	}
}
