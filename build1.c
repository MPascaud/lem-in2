/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 17:12:51 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

void	ft_init(t_roomlist *roomlist)
{
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		roomlist->place = -1;
		roomlist->taken = 0;
		roomlist->way = 0;
		roomlist->beftunnels = NULL;
		roomlist = roomlist->next;
	}
}

void	ft_first_roomlist(t_variables *var)
{
	var->roomlist = (t_roomlist*)malloc(sizeof(t_roomlist));
	var->roomlist->previous = NULL;
	var->roomlist->place = 0;
	var->roomlist->name = NULL;
	var->roomlist->previous = NULL;
	var->roomlist->next = NULL;
	var->roomlistart = var->roomlist;
}

void	ft_build(t_variables *var)
{
	ft_first_roomlist(var);
	ft_name(var->filistart, var->roomlist);
	ft_init(var->roomlist);
	ft_place_start(var->filistart, var->roomlist);
	ft_place_end(var->filistart, var->roomlist);
	ft_tunnels(var->filistart, var->roomlist);
	ft_place(var->filistart, var->roomlist);
}
