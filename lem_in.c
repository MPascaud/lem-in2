/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:00:04 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_print_anthill(t_filist *filistart)
{
	t_filist	*filist;

	filist = filistart->next;
	while (filist != NULL)
	{
		printf("%s\n", filist->line);
		filist = filist->next;
	}
}

int		ft_firsts_filist_namelist_argc(t_variables *var, int argc)
{
	var->tmp = NULL;
	if (argc != 1)
	{
		printf("ERROR\n");
		free(var);
		return (0);
	}
	var->filist = (t_filist*)malloc(sizeof(t_filist));
	var->filist->previous = NULL;
	var->filist->line = NULL;
	var->filist->next = NULL;
	var->filistart = var->filist;
	var->namelist = (t_namelist*)malloc(sizeof(t_namelist));
	var->namelist->name = NULL;
	var->namelist->previous = NULL;
	var->namelist->next = NULL;
	var->namelistart = var->namelist;
	return (1);
}

void	ft_ants(t_listlist *listlist, t_filist *filistart)
{
	t_listlist	*tmp;
	t_waylist	*waytmp;

	tmp = listlist;
	filistart = filistart->next;
	if (filistart != NULL)
		tmp->ants = ft_atoi(filistart->line);
	while (tmp != NULL)
	{
		waytmp = tmp->waylist;
		while (waytmp != NULL)
		{
			waytmp->ants = 0;
			waytmp = waytmp->next;
		}
		tmp = tmp->next;
	}
}

int		main(int argc, char **argv)
{
	t_variables	*var;

	var = (t_variables*)malloc(sizeof(t_variables));
	if (ft_firsts_filist_namelist_argc(var, argc) == 0)
		return (0);
	ft_gnl(var);
	if (ft_valid_line(NULL, 1, NULL) != 3)
	{
		printf("ERROR\n");
		ft_free_only_two(var->filistart, var->namelist);
		free(var);
		return (0);
	}
	ft_build(var);
	if (ft_possible(var) == 0)
		return (0);
	ft_first_listlist(var);
	ft_listlist(var->listlist, var->roomlistart, var->roomlist, var->way);
	ft_ants(var->listlist, var->filistart);
	ft_print_anthill(var->filistart);
	ft_free(var->filistart, var->roomlist, var->listlist, var->namelist);
	free(var);
	return (0);
}
