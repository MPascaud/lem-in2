/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:15:08 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		ft_step_one(char *tmp, int i, int *step)
{
	while (tmp[i] != '\0')
	{
		if (ft_isdigit(tmp[i]) == 0)
		{
			*step = 0;
			return (0);
		}
		i++;
	}
	*step = 1;
	return (*step);
}

int		ft_valid_line(char *tmp, int check, t_namelist *namelistart)
{
	static int	step;
	t_namelist	*namelist;

	namelist = namelistart;
	if (tmp != NULL)
		if (tmp[0] == '#')
			return (1);
	if (check == 1 && step == 3)
		return (3);
	if (check == 1 && step != 3)
		return (-1);
	if (tmp != NULL && step == 0)
		return (ft_step_one(tmp, 0, &step));
	if (tmp != NULL && (step == 1 || step == 2)
			&& ft_bad_room(tmp, step, -1) == 1)
	{
		return (0);
	}
	if (tmp != NULL && (step == 1 || step == 2)
			&& ft_at_least_one_room(tmp) == 1)
		return (ft_step_two(tmp, &step, namelist, namelistart));
	if (tmp != NULL && (step == 2 || step == 3))
		return (ft_step_three(tmp, &step, namelistart));
	return (step);
}

void	ft_gnl(t_variables *var)
{
	while (get_next_line(0, &var->tmp))
	{
		if (ft_valid_line(var->tmp, 0, var->namelistart) == 0)
			break ;
		var->filist->next = ft_filstnew(var->tmp, var->filist);
		var->filist = var->filist->next;
		free(var->tmp);
	}
	free(var->tmp);
}
