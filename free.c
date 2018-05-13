/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:19:25 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_free_only_two(t_filist *filistart, t_namelist *namelist)
{
	t_filist	*tmp;
	t_namelist	*namelistmp;

	tmp = filistart;
	namelistmp = namelist;
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

void	ft_free_no_listlist(t_filist *filistart, t_roomlist *roomlist,
		t_namelist *namelist)
{
	t_filist	*tmp;
	t_roomlist	*roomlistmp;
	t_namelist	*namelistmp;

	tmp = filistart;
	namelistmp = namelist;
	roomlistmp = roomlist->next;
	ft_free_filist_namelist(filistart, namelist, tmp, namelistmp);
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

void	ft_free(t_filist *filistart, t_roomlist *roomlist,
		t_listlist *listlist, t_namelist *namelist)
{
	t_filist	*tmp;
	t_roomlist	*roomlistmp;
	t_listlist	*listlistmp;
	t_waylist	*waylistmp;
	t_namelist	*namelistmp;

	tmp = filistart;
	roomlistmp = NULL;
	listlistmp = NULL;
	waylistmp = NULL;
	namelistmp = namelist;
	ft_free_filist_namelist(filistart, namelist, tmp, namelistmp);
	ft_free_roomlist(roomlistmp, roomlist);
	ft_free_listlist(listlistmp, listlist, waylistmp);
}
