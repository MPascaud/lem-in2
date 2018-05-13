/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:38:39 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		ft_disizit(t_filist *filist, t_roomlist *roomlist)
{
	int		i;

	i = 0;
	while ((roomlist->name)[i] != '\0')
	{
		if ((roomlist->name)[i] != (filist->line)[i])
		{
			return (0);
		}
		i++;
	}
	if (filist->line[i] != ' ' || ft_isdigit(filist->line[i + 1]) == 0)
		return (0);
	return (1);
}

void	ft_place_start(t_filist *filist, t_roomlist *roomlist)
{
	int		i;

	i = 0;
	filist = filist->next;
	roomlist = roomlist->next;
	while (filist != NULL)
	{
		if (ft_strstr(filist->line, "##start") && (filist->line)[7] == '\0')
		{
			filist = filist->next;
			while (roomlist != NULL)
			{
				if (ft_disizit(filist, roomlist) == 1)
				{
					roomlist->place = 0;
					return ;
				}
				roomlist = roomlist->next;
			}
		}
		filist = filist->next;
	}
}

void	ft_place_end(t_filist *filist, t_roomlist *roomlist)
{
	filist = filist->next;
	roomlist = roomlist->next;
	while (filist != NULL)
	{
		if (ft_strstr(filist->line, "##end") && (filist->line)[5] == '\0')
		{
			filist = filist->next;
			while (roomlist != NULL)
			{
				if (ft_disizit(filist, roomlist) == 1)
				{
					roomlist->place = -2;
					return ;
				}
				roomlist = roomlist->next;
			}
		}
		filist = filist->next;
	}
}
