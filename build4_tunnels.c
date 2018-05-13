/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 17:35:51 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

void	ft_malloc_tunnels(t_roomlist *roomlist, t_filist *filist, int *tunnbr, t_filist *filistart)
{
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_tunnel(filist, roomlist) == 1)
				(*tunnbr)++;
			filist = filist->next;
		}
		roomlist->tunnels = (char**)malloc(sizeof(char*) * (*tunnbr + 1));
		roomlist = roomlist->next;
		filist = filistart;
		*tunnbr = 0;
	}

}

void	ft_link_tunnels(int *i, t_roomlist *roomlist, t_filist *filist, t_filist *filistart)
{
	*i = 0;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_tunnel(filist, roomlist) == 1)
			{
				(roomlist->tunnels)[*i] = ft_link(filist);
				(*i)++;
			}
			filist = filist->next;
		}
		(roomlist->tunnels)[*i] = NULL;
		roomlist = roomlist->next;
		filist = filistart;
		*i = 0;
	}

}


void	ft_malloc_beftunnels(t_roomlist *roomlist, t_filist *filist, t_roomlist *roomlistart, t_filist *filistart)
{
	int		tunnbr;

	tunnbr = 0;

	roomlist = roomlistart;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_beftunnel(filist, roomlist) == 1)
				tunnbr++;
			filist = filist->next;
		}
		roomlist->beftunnels = (char**)malloc(sizeof(char*) * (tunnbr + 1));
		roomlist = roomlist->next;
		filist = filistart;
		tunnbr = 0;
	}
}


void	ft_link_beftunnels(int *i, t_roomlist *roomlist, t_filist *filist, t_filist *filistart)
{
	*i = 0;
	filist = filistart;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_beftunnel(filist, roomlist) == 1)
			{
				(roomlist->beftunnels)[*i] = ft_beflink(filist);
				(*i)++;
			}
			filist = filist->next;
		}
		(roomlist->beftunnels)[*i] = NULL;
		roomlist = roomlist->next;
		filist = filistart;
		*i = 0;
	}

}
void	ft_tunnels(t_filist *filist, t_roomlist *roomlist)
{
	int		i;
	int		tunnbr;
	t_filist	*filistart;
	t_roomlist	*roomlistart;

	tunnbr = 0;
	filist = filist->next;
	filistart = filist;
	roomlist = roomlist->next;
	roomlistart = roomlist;
	tunnbr = 0;
	ft_malloc_tunnels(roomlist, filist, &tunnbr, filistart);
	ft_link_tunnels(&i, roomlist, filist, filistart);
	ft_malloc_beftunnels(roomlist, filist, roomlistart, filistart);
	ft_link_beftunnels(&i, roomlist, filist, filistart);
}
