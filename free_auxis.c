/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:17:06 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_free_beftunnels(t_roomlist *roomlist)
{
	int		i;

	i = 0;
	if (roomlist->beftunnels != NULL)
	{
		while ((roomlist->beftunnels)[i] != NULL)
		{
			free((roomlist->beftunnels)[i]);
			i++;
		}
		free((roomlist->beftunnels)[i]);
		free(roomlist->beftunnels);
	}
}

void	ft_free_tunnels(t_roomlist *roomlist)
{
	int		i;

	i = 0;
	if (roomlist->tunnels != NULL)
	{
		while ((roomlist->tunnels)[i] != NULL)
		{
			free((roomlist->tunnels)[i]);
			i++;
		}
		free((roomlist->tunnels)[i]);
		free(roomlist->tunnels);
	}
}

void	ft_free_filist_namelist(t_filist *filistart, t_namelist *namelist,
		t_filist *tmp, t_namelist *namelistmp)
{
	while (tmp != NULL)
	{
		tmp = filistart->next;
		free(filistart->line);
		free(filistart);
		filistart = tmp;
	}
	free(tmp);
	while (namelist != NULL)
	{
		namelistmp = namelist->next;
		free(namelist->name);
		free(namelist);
		namelist = namelistmp;
	}
	free(namelist);
}

void	ft_free_roomlist(t_roomlist *roomlistmp, t_roomlist *roomlist)
{
	roomlistmp = roomlist->next;
	free(roomlist);
	roomlist = roomlistmp;
	while (roomlist != NULL)
	{
		free(roomlist->name);
		ft_free_beftunnels(roomlist);
		ft_free_tunnels(roomlist);
		roomlistmp = roomlist->next;
		free(roomlist);
		roomlist = roomlistmp;
	}
	free(roomlist);
}

void	ft_free_listlist(t_listlist *listlistmp, t_listlist *listlist,
		t_waylist *waylistmp)
{
	listlistmp = listlist;
	while (listlistmp != NULL)
	{
		listlistmp = listlist->next;
		while (listlist->waylist != NULL)
		{
			free(listlist->waylist->name);
			waylistmp = listlist->waylist->next;
			free(listlist->waylist);
			listlist->waylist = waylistmp;
		}
		free(listlist);
		listlist = listlistmp;
	}
	free(listlist);
}
