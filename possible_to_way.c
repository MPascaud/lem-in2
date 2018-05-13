/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 19:53:49 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		ft_check_connection(t_roomlist *roomlistart, t_roomlist *roomlist)
{
	int		i;

	i = 0;
	while ((roomlist->beftunnels)[i] != NULL)
	{
		if (ft_strcmp((roomlist->beftunnels)[i], roomlistart->name) == 0)
			return (1);
		i++;
	}
	i = 0;
	while ((roomlist->tunnels)[i] != NULL)
	{
		if (ft_strcmp((roomlist->tunnels)[i], roomlistart->name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		ft_start_to_end(t_roomlist *roomlistart)
{
	t_roomlist	*start;
	t_roomlist	*end;

	start = roomlistart->next;
	end = roomlistart->next;
	while (start != NULL)
	{
		if (start->place == 0)
		{
			while (end != NULL)
			{
				if (end->place == -2 && ft_check_connection(start, end) == 1)
				{
					start->way = 1;
					end->way = 1;
					return (1);
				}
				end = end->next;
			}
		}
		start = start->next;
	}
	return (0);
}

int		ft_possible(t_variables *var)
{
	var->way = 1;
	if (ft_start_to_end(var->roomlistart) == 0)
	{
		while (ft_way(var->filistart, var->roomlist,
					var->roomlistart, var->way) == 1)
			(var->way)++;
		(var->way)--;
	}
	if (var->way == 0 || ft_atoi(var->filistart->next->line) == 0
			|| ft_atoi(var->filistart->next->line) < 0)
	{
		printf("ERROR\n");
		ft_free_no_listlist(var->filistart, var->roomlist, var->namelist);
		free(var);
		return (0);
	}
	return (1);
}
