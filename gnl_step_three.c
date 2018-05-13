/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:10:33 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int			ft_not_yet_second_room(char *tmp, int i,
		t_namelist *namelist, int ok)
{
	int		j;

	j = 0;
	while (namelist != NULL)
	{
		while (tmp[i] != '-')
			i++;
		i++;
		while (tmp[i] != '\0')
		{
			if (tmp[i] != (namelist->name)[j])
				break ;
			if (tmp[i + 1] == '\0' && (namelist->name)[j + 1] == '\0')
				ok = 1;
			i++;
			j++;
		}
		i = 0;
		j = 0;
		namelist = namelist->next;
	}
	if (ok == 0)
		return (1);
	return (0);
}

int			ft_not_yet_first_room(char *tmp, int i,
		t_namelist *namelist, int ok)
{
	while (namelist != NULL)
	{
		while (tmp[i] != '-')
		{
			if (tmp[i] != (namelist->name)[i])
			{
				break ;
			}
			if (tmp[i + 1] == '-' && namelist->name[i + 1] == '\0')
				ok = 1;
			i++;
		}
		i = 0;
		namelist = namelist->next;
	}
	if (ok == 0)
		return (1);
	return (0);
}

int			ft_not_yet(char *tmp, t_namelist *namelistart)
{
	t_namelist	*namelist;
	int			i;
	int			ok;

	namelist = namelistart;
	namelist = namelist->next;
	i = 0;
	ok = 0;
	if (ft_not_yet_first_room(tmp, i, namelist, ok) == 1)
		return (1);
	namelist = namelistart;
	namelist = namelist->next;
	if (ft_not_yet_second_room(tmp, i, namelist, ok) == 1)
		return (1);
	return (0);
}

int			ft_step_three(char *tmp, int *step, t_namelist *namelistart)
{
	int		i;
	int		tunnel;

	i = 0;
	tunnel = 0;
	while (tmp[i])
	{
		if (tmp[i] == '-')
			tunnel++;
		i++;
	}
	if (tunnel > 1 || (tunnel == 0 && tmp[0] != '#'))
		return (0);
	if (tunnel == 1)
	{
		if (ft_not_yet(tmp, namelistart) == 1)
			return (0);
	}
	*step = 3;
	return (*step);
}
