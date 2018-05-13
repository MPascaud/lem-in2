/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 18:26:56 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"



t_filist	*ft_filstnew(char *tmp, t_filist *link)
{
	t_filist	*nextlink;
	char		*str;

	if (!(nextlink = (t_filist*)malloc(sizeof(t_filist))))
		return (NULL);
	nextlink->previous = link;
	str = ft_strnew(ft_strlen(tmp));
	nextlink->line = ft_strcpy(str, tmp);
	nextlink->next = NULL;
	return (nextlink);
}

void	ft_show_roomlist(t_roomlist *roomlist)
{
	int		i;

	i = 0;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		printf("roomlist->name = %s\n", roomlist->name);
		printf("roomlist->place = %d\n", roomlist->place);
		while ((roomlist->beftunnels)[i] != NULL)
		{
			printf("roomlist->beftunnels[%d] = %s\n", i, roomlist->beftunnels[i]);
			i++;
		}
		i = 0;
		while ((roomlist->tunnels)[i] != NULL)
		{
			printf("roomlist->tunnels[%d] = %s\n", i, roomlist->tunnels[i]);
			i++;
		}
		printf("way = %d\n", roomlist->way);
		printf("taken = %d\n", roomlist->taken);
		printf("\n");
		i = 0;
		roomlist = roomlist->next;

	}
}


int		ft_check_previous_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart)
{
	int		empty;

	empty = 0;
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->beftunnels)[i], roomlistart->name) == 0)
		{
		if (roomlist->place != 0 && roomlistart->place != -1 && roomlistart->place != -2 && (roomlist->place == -1 || roomlist->place > roomlistart->place + 1))
		{
			roomlist->place = roomlistart->place + 1;
			return (1);
		}
		if (roomlistart->place != 0 && roomlist->place != -1 && roomlist->place != -2 && (roomlistart->place == -1 || roomlistart->place > roomlist->place + 1))
		{
			roomlistart->place = roomlist->place + 1;
			return (1);
		}
	}
	roomlistart = roomlistart->next;
}
return (0);
}

int		ft_check_next_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->tunnels)[i], roomlistart->name) == 0)
		{
			if (roomlist->place != 0 && roomlistart->place != -1 && roomlistart->place != -2 && (roomlist->place == -1 || roomlist->place > roomlistart->place + 1))
			{
				roomlist->place = roomlistart->place + 1;
				return (1);
			}
			if (roomlistart->place != 0 && roomlist->place != -1 && roomlist->place != -2 && (roomlistart->place == -1 || roomlistart->place > roomlist->place + 1))
			{
				roomlistart->place = roomlist->place + 1;
				return (1);
			}
		}
		roomlistart = roomlistart->next;
	}
	return (0);
}


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


void	ft_which_max_and_losts_to_zero(t_roomlist *roomlist, int *max)
{
	*max = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place > *max && roomlist->place != -2)
			*max = roomlist->place;
		if (roomlist->way == -1)
			roomlist->way = 0;
		roomlist = roomlist->next;
	}
}

void	ft_ways_to_zero(t_roomlist *roomlistart)
{
	int			max;
	t_roomlist	*roomlist;

	roomlist = roomlistart;
	roomlist = roomlist->next;
	ft_which_max_and_losts_to_zero(roomlist, &max);

	ft_roomlist_to_first(&roomlist, roomlistart);
	while (max > 0)
	{
		while (roomlist->place != max)
			roomlist = roomlist->next;
		roomlist = roomlist->next;
		while (roomlist != NULL)
		{
			if (roomlist->place == max)
				roomlist->way = 0;
			roomlist = roomlist->next;
		}
		ft_roomlist_to_first(&roomlist, roomlistart);
		max--;
	}
	ft_roomlist_to_first(&roomlist, roomlistart);
}

void	ft_takens_to_one(t_roomlist *roomlistart, int way)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (roomlistart->way == way && roomlistart->place != 0 && roomlistart->place != -2)
			roomlistart->taken = 1;
		roomlistart = roomlistart->next;
	}
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

void	ft_show_listlist(t_listlist *listlist)
{
	t_listlist *tmp;
	t_waylist *waytmp;
	tmp = listlist;
	printf("ants = %d\n", tmp->ants);
	printf("\n");
	tmp = tmp->next;
	while (tmp != NULL)
	{
		waytmp = tmp->waylist;
		while (waytmp != NULL)
		{
			printf("way = %d, place = %d, name = %s, ants = %d\n", waytmp->way, waytmp->place, waytmp->name, waytmp->ants);

			waytmp = waytmp->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
}






t_namelist		*ft_new_name(char *tmp, t_namelist *namelist)
{
	t_namelist	*newlink;
	char		*str;
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

int		ft_already(char	*name, t_namelist *namelistart)
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


int			ft_not_yet_first_room(char *tmp, int i, t_namelist *namelist, int ok)
{
	while (namelist != NULL)
	{
		while (tmp[i] != '-')
		{
			if (tmp[i] != (namelist->name)[i])
			{
				break ;
			}
			if (tmp[i + 1] == '-' && namelist->name[i + 1] == '\0')//<<<<<<<<<<<----------
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

int			ft_not_yet_second_room(char *tmp, int i, t_namelist *namelist, int ok)
{
	int		j;

	j = 0;
	while (namelist != NULL)
	{
		//printf("namelist->name = %s\n", namelist->name);
		while (tmp[i] != '-')
			i++;
		i++;
		while (tmp[i] != '\0')
		{
			if (tmp[i] != (namelist->name)[j])
				break ;
			if (tmp[i + 1] == '\0' && (namelist->name)[j + 1] == '\0')//<<<<<<<<<<<<------------------
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

void	ft_show_filist(t_filist *filistart)
{
	t_filist	*filist;

	filist = filistart;
	filist = filist->next;

	while (filist != NULL)
	{
		filist = filist->next;
	}
}

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



int		main(int argc, char **argv)
{
	t_variables	*var;

	var = (t_variables*)malloc(sizeof(t_variables));
	if (ft_firsts_filist_namelist_argc(var, argc) == 0)
		return (0);
	ft_gnl(var);
	//ft_show_filist(var->filistart);
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
	ft_show_listlist(var->listlist);//<<<<<<<<<<<<----------------------------
	ft_print_anthill(var->filistart);
	ft_free(var->filistart, var->roomlist, var->listlist, var->namelist);
	free(var);
	return (0);
}
