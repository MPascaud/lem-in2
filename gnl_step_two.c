/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:06:50 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_namelist		*ft_new_name(char *tmp, t_namelist *namelist)
{
	t_namelist	*newlink;
	int			i;
	int			limit;

	i = 0;
	newlink = (t_namelist*)malloc(sizeof(t_namelist));
	newlink->previous = namelist;
	newlink->next = NULL;
	while (tmp[i])
		i++;
	i--;
	while (ft_isdigit(tmp[i]) == 1)
		i--;
	i--;
	while (ft_isdigit(tmp[i]) == 1)
		i--;
	limit = i;
	i = -1;
	newlink->name = ft_strnew(limit);
	while (++i < limit)
		(newlink->name)[i] = tmp[i];
	return (newlink);
}

int				ft_already(char *name, t_namelist *namelistart)
{
	t_namelist	*namelist;

	namelist = namelistart;
	namelist = namelist->next;
	while (namelist->next != NULL)
	{
		if (ft_strcmp(name, namelist->name) == 0)
		{
			return (1);
		}
		namelist = namelist->next;
	}
	return (0);
}

int				ft_step_two(char *tmp, int *step, t_namelist *namelist,
		t_namelist *namelistart)
{
	while (namelist->next != NULL)
		namelist = namelist->next;
	namelist->next = ft_new_name(tmp, namelist);
	namelist = namelist->next;
	if (ft_already(namelist->name, namelistart) == 1)
	{
		return (0);
	}
	*step = 2;
	return (*step);
}
