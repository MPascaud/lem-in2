/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/02 18:36:53 by mpascaud         ###   ########.fr       */
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
	//free(str);
	return (nextlink);
}


void	ft_show_filist(t_filist *filist)
{
	filist = filist->next;
	while (filist != NULL)
	{
		printf("%s\n", filist->line);
		filist = filist->next;
	}
}

t_roomlist	*ft_roomlstnew(t_roomlist *roomlist)
{
	t_roomlist	*nextlink;

	if (!(nextlink = (t_roomlist*)malloc(sizeof(t_roomlist))))
		return (NULL);
	nextlink->previous = roomlist;
	nextlink->place = -1;
	nextlink->next = NULL;
	return (nextlink);
}

int		ft_this_is_new_room(t_filist *filist)
{
	int		result;
	int		i;

	result = 0;
	i = 0;
	if (filist->line == NULL)
		return (0);
	while ((filist->line)[i] != '\0')
	{

		i++;
	}
	i--;
	//printf("i = %d\n", i);
	while (ft_isdigit((filist->line)[i]) == 1)
	{
		i--;
		if (i < 0)
			return (0);
	}
	//printf("i = %d\n", i);
	if ((filist->line)[i] == ' ' && (filist->line)[0] != '#')
	{
		return (1);
	}
	return (0);
}

void	ft_cpyname(t_filist *filist, t_roomlist *roomlist)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((filist->line)[i] != '\0')
		i++;
	//printf("i = %d\n", i);
	i--;
	while (ft_isdigit((filist->line)[i]) == 1)
		i--;
	i--;
	while (ft_isdigit((filist->line)[i]) == 1)
		i--;
	i--;
//	printf("i = %d\n", i);
	roomlist->name = ft_strnew(i + 1);
	while (j <= i)
	{
		(roomlist->name)[j] = (filist->line)[j];
		j++;
	}

//	str = ft_strnew(ft_strlen(filist->line));
//	roomlist
}


void	ft_name(t_filist *filist, t_roomlist *roomlist)
{
	filist = filist->next;
	while (filist != NULL)
	{
		if (ft_this_is_new_room(filist) == 1)
		{
			roomlist->next = ft_roomlstnew(roomlist);
			roomlist = roomlist->next;
			ft_cpyname(filist, roomlist);
			//printf("blop\n");
		}
		filist = filist->next;
	}
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
			//printf("COUCOU\n");
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

//liste des tubes avec un 'pris en compte'
//tant que tous les tubes ne sont pas pris en compte
//a chaque ligne : si place du 2e = -1 et que place du 1er != -1, place du 2e = place du 1er + 1
//tour supplementaire sur liste tubes pour calculer taille du malloc du premier(roomlist->tunnel)
//refaire un tour pour joindre roomlist: les 2e sont ajoutes a la liste du 1er
//




int		ft_disiz_tunnel(t_filist *filist, t_roomlist *roomlist)
{
	int		there_is_tunnel;
	int		i;

	there_is_tunnel = 0;
	i = 0;

	while ((filist->line)[i] != '\0')
	{
		if ((filist->line)[i] == '-')
			there_is_tunnel = 1;
		i++;
	}
	if (there_is_tunnel == 0)
		return (0);

	i = 0;
	while ((roomlist->name)[i] != '\0')
	{
		if ((filist->line)[i] != (roomlist->name)[i] || (filist->line)[i] == '\0')
			return (0);
		i++;
	}
	if ((filist->line)[i] != '-')
		return (0);
	return (1);
}

int		ft_disiz_beftunnel(t_filist *filist, t_roomlist *roomlist)
{
	int		there_is_tunnel;
	int		i;
	int		j;

	there_is_tunnel = 0;
	i = 0;
	j = 0;
	while ((filist->line)[i] != '\0')
	{
		if ((filist->line)[i] == '-')
		{
			there_is_tunnel = 1;
			i++;
			break ;
		}
		i++;
	}
	if (there_is_tunnel == 0)
		return (0);
//	printf("coucou i = %d\n", i);
//	i = 0;

	while ((roomlist->name)[j] != '\0')
	{
		if ((filist->line)[i] != (roomlist->name)[j] || (filist->line)[i] == '\0')
			return (0);
		i++;
		j++;
	}
	if ((filist->line)[i] != '\0')
		return (0);
//	printf("filist->line = %s, roomlist->name = %s\n", filist->line, roomlist->name);

	return (1);
}

char	*ft_link(t_filist *filist, t_roomlist *roomlist)
{
	char	*tunname;
	int		i;
	int		start;
	int		tmp;

	i = 0;
	start = 0;
	tmp = 0;
	while ((filist->line)[start] != '-')
		start++;
	start++;
	tmp = start;
	while ((filist->line)[tmp] != '\0')
	{
		tmp++;
		i++;
	}
	//printf("i = %d\n", i);
	tunname = (char*)malloc(sizeof(char) * (i + 1));
	tmp = start;
	i = 0;
	while ((filist->line)[tmp] != '\0')
	{
		tunname[i] = (filist->line)[tmp];
		i++;
		tmp++;
	}
	tunname[i] = '\0';
	return (tunname);
}

char	*ft_beflink(t_filist *filist, t_roomlist *roomlist)
{
	char	*tunname;
	int		i;
	//int		tmp;

	i = 0;
	//tmp = 0;
	while ((filist->line)[i] != '-')
	{
		i++;
	}
	tunname = (char*)malloc(sizeof(char) * (i + 1));
	//tmp = i;
	i = 0;
	while ((filist->line)[i] != '-')
	{
		tunname[i] = (filist->line)[i];
		i++;
	}
	tunname[i] = '\0';
	return (tunname);
}


void	ft_tunnels(t_filist *filist, t_roomlist *roomlist)
{
	int		i;
	int		tunnbr;
	t_filist	*filistart;
	t_roomlist	*roomlistart;

	i = 0;
	tunnbr = 0;
	filist = filist->next;
	filistart = filist;
	roomlist = roomlist->next;
	roomlistart = roomlist;
	/*while (filist != NULL)
	{
		while ((filist->line)[i] != '\0')
		{
			if ((filist->line)[i] == '-' && (filist->line)[0] != '#')
			{
				tunnbr++;
				break ;
			}
			i++;
		}
		filist = filist->next;
		i = 0;
	}*/
	//printf("i = %d\n", i);
	//printf("tunnbr = %d\n", tunnbr);
	tunnbr = 0;
	filist = filistart;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_tunnel(filist, roomlist) == 1)
			{
				//printf("tunnbr = %d, roomlist->name = %s\n", tunnbr, roomlist->name);
				tunnbr++;
			}
			filist = filist->next;
		}
		//printf("tunnbr = %d, roomlist->name = %s\n", tunnbr, roomlist->name);
		roomlist->tunnels = (char**)malloc(sizeof(char*) * (tunnbr + 1));
		roomlist = roomlist->next;
		filist = filistart;
		tunnbr = 0;
	}

	roomlist = roomlistart;
	i = 0;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_tunnel(filist, roomlist) == 1)
			{
				(roomlist->tunnels)[i] = ft_link(filist, roomlist);
				i++;

			}
			filist = filist->next;
		}
		(roomlist->tunnels)[i] = NULL;
		roomlist = roomlist->next;
		filist = filistart;
		i = 0;
	}
	//(roomlist->tunnels)[i] = ft_link(filist, roomlist);


	tunnbr = 0;
	filist = filistart;
	roomlist = roomlistart;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_beftunnel(filist, roomlist) == 1)
			{
				tunnbr++;
			}
			filist = filist->next;
		}
		roomlist->beftunnels = (char**)malloc(sizeof(char*) * (tunnbr + 1));
		roomlist = roomlist->next;
		filist = filistart;
		tunnbr = 0;
	}

	roomlist = roomlistart;
	i = 0;
	filist = filistart;
	tunnbr = 0;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_beftunnel(filist, roomlist) == 1)
			{
				(roomlist->beftunnels)[i] = ft_beflink(filist, roomlist);
				i++;
			}
			filist = filist->next;
		}
		(roomlist->beftunnels)[i] = NULL;
		roomlist = roomlist->next;
		filist = filistart;
		i = 0;
	}
}

//place, max

//calcul des places
//si le next = end ou -2: place min = place + 1 
//malloc char** place min + 1(end) + 1(NULL), !!une seule fois
//max = place - 1,
//place devient -2,
//name sur way
//si la place d'un predecesseur = max(et pas -1 ou -2), on y va
//
//refaisage









//defilement roomlist
//pour chacun : defilement des precedents; si precedent->place != -1 et -2, place = precedent->place + 1


int		ft_check_previous_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart)
{
	int		empty;

	empty = 0;
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->beftunnels)[i], roomlistart->name) == 0)
		{
			/*//printf("roomlistart->name = %s, (roomlist->beftunnels)[i] = %s, i = %d \n", roomlistart->name, (roomlist->beftunnels)[i], i);
			if (roomlistart->place == -1 && (roomlist->place != -2) && roomlist->place != -1)
			{
				roomlistart->place = roomlist->place + 1;
				return ;
			}
		}*/
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
	//return 1 si place = -1
	return (0);
}

int		ft_check_next_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->tunnels)[i], roomlistart->name) == 0)
		{
			/*if ((roomlistart->place == -1 || (roomlistart->place > roomlist->place + 1)) && roomlist->place != -2 && roomlist->place != -1)
			{
				roomlistart->place = roomlist->place + 1;
				return ;
			}*/
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


void	ft_place(t_filist *filist, t_roomlist* roomlist)
{
	int			i;
	t_filist	*filistart;
	t_roomlist	*roomlistart;

	i = 0;
	filistart = filist;
	roomlistart = roomlist;
	filist = filist->next;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		while ((roomlist->beftunnels)[i] != NULL)
		{
			if (ft_check_previous_place(roomlist, i, roomlistart) == 1)
			{
				roomlist = roomlistart;
				//roomlist = roomlist->next;
				break ;
			}
			//if (ft_check_previous_place(roomlist, i, roomlistart) == 1)
			//{
			//	ft_change_previous_place(roomlist);
				//roomlist = roomlistart;
			//	break ;
			//}
			i++;
		}
		i = 0;
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
	i = 0;
	while (roomlist != NULL)
	{
		while ((roomlist->tunnels)[i] != NULL)
		{
			if (ft_check_next_place(roomlist, i, roomlistart) == 1)
			{
				roomlist = roomlistart;
				break ;
			}
			i++;
		}
		i = 0;
		roomlist = roomlist->next;
	}
}

//t_waylist*, progress
//roomlist->way (0 pour normaux, 1 quand occupe, -1 quand start ou end)
//on fait defiler roomlist
//si place = 0, maillon de way
//si place = 1 && good = 0 && (beftunnels->place = place - 1 || tunnels->place = place - 1), maillon en plus, good = 1, roomlistart
//idem si place = 2 etc
//
//si place = -2 && blablabla, maillon en plus + maillon NULL,
//MAIS si roomlist = NULL et que ya pas eu de maillon en plus depuis roomlistart : le dernier good = -1
//
//
//
//
//on supprime tous les maillons de way + dernier maillon de waylist remplace par NULL
//


//pour previous : que la place du previous = place du suivant - 1;
//                que taken du precedent = 0;
//                que taken du suivant = 0 ou -2;OUPA
//                que un tunnel du precedent = nom du suivant (ou l'inverse);
//                que way du precedent = way;
//                que way du suivant = 0;OUPA
//

int		check_connection(t_roomlist *roomlistart, t_roomlist *roomlist)
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



void	ft_ways_to_zero(t_roomlist *roomlistart)
{
	int			max;
	int			duplicate;
	t_roomlist	*roomlist;

	roomlist = roomlistart;
	roomlist = roomlist->next;
	max = 0;
	duplicate = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place > max && roomlist->place != -2)
			max = roomlist->place;
		if (roomlist->way == -1)
			roomlist->way = 0;
		roomlist = roomlist->next;
	}
	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (max > 0)
	{
		while (roomlist->place != max)
		{
			roomlist = roomlist->next;
		}
		roomlist = roomlist->next;
		while (roomlist != NULL)
		{
			if (roomlist->place == max)
				roomlist->way = 0;
			roomlist = roomlist->next;
		}
		roomlist = roomlistart;
		roomlist = roomlist->next;
		max--;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;


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



int		ft_no_zero(t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;

	while (roomlistart != NULL)
	{
		if (roomlistart->way == 0 && roomlistart->place != -1)
		{
			return (0);
		}
		roomlistart = roomlistart->next;
	}

	
	return (1);
}

int		ft_search_previous(t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	t_roomlist	*tmp;

	roomlistart = roomlistart->next;
	tmp = roomlistart;
	while (roomlistart != NULL)
	{
		if (roomlistart->place == roomlist->place - 1
				&& roomlistart->taken == 0 
				&& roomlistart->way == way
				&& check_connection(roomlistart, roomlist) == 1)
		{
			//printf("COUCOU\n");
			return (1);
		}
		roomlistart = roomlistart->next;
	}
	while (tmp != NULL)
	{
		if (tmp->place == roomlist->place - 1
				&& tmp->taken == 0
				&& tmp->way == 0
				&& check_connection(tmp, roomlist) == 1)
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}

//pour next : que place du next = place de l'actuel + 1 || -2;
//            que taken du suivant = 0;
//            que un tunnel de l'actuel = nom du suivant (ou l'inverse);
//            que way du suivant = 0;
//

/*int		ft_search_next(t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	int		connection;
	int		end;
	int		noway;

	connection = 0;
	end = 0;
	noway = -1;

	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (roomlistart->place == roomlist->place + 1
				&& roomlistart->taken == 0
				&& (roomlistart->way == 0 || roomlistart->way == way)
				&& check_connection(roomlistart, roomlist) == 1)
		{
			connection = 1;
		}
		if (roomlistart->place == -2
				&& check_connection(roomlistart, roomlist) == 1)
		{
			end = -2;
		}
		if (roomlistart->place == roomlist->place + 1
				&& roomlistart->taken == 0
				&& roomlistart->way == way
				&& check_connection(roomlistart, roomlist) == 1)
		{
			noway = 0;
		}

		roomlistart = roomlistart->next;
	}
	if (end == -2)
		return (-2);
	if (connection == 1)
		return (1);
	if (noway == -1)
		return (-1);
	return (0);
}*/


int		ft_search_next(t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if ((roomlistart->place == roomlist->place + 1 || roomlistart->place == -2)
				&& roomlistart->taken == 0
				&& (roomlistart->way == 0 || roomlistart->way == way)
				&& check_connection(roomlistart, roomlist) == 1)
		{
			return (1);
		}

		roomlistart = roomlistart->next;
	}
	return (0);
}


int		ft_search_first_reverse(t_roomlist *end, t_roomlist *roomlistart, int way)
{
	int			maxplace;
	t_roomlist	*roomlist;
//	t_roomlist	*roomax;

	maxplace = 0;
	roomlist = roomlistart;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& roomlist->place > maxplace 
				&& check_connection(end, roomlist) == 1)
			maxplace = roomlist->place;
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
//	roomlistart = roomlistart->next;
	while (roomlist != NULL)
	{
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& (roomlist->place != -1)
				&& check_connection(end, roomlist) == 1)
		{
			if (roomlist->place < maxplace)
			{
				maxplace = roomlist->place;
			}
			//roomax = roomlist;
		}
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& roomlist->place == maxplace
				&& check_connection(end, roomlist) == 1)
		{
			roomlist->taken = 1;
			break ;
		}
		roomlist = roomlist->next;
	}
//	printf("maxplace = %d\n", maxplace);
	return (maxplace);
}


void	ft_search_other_reverses(t_roomlist *roomlistart, int maxplace, int way)
{
	t_roomlist	*roomlist;
	t_roomlist	*roomax;

	roomlist = roomlistart;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		if (roomlist->taken == 1
				&& roomlist->way == way
				&& roomlist->place == maxplace)
		{
			roomax = roomlist;
			break ;
		}
		roomlist = roomlist->next;
	}
/*	if (roomlist == NULL)
	{
		printf("okdfpjasjvpoesjrgpijewrp%d\n", maxplace);//<<<<<<<--------------------- end tout seul
		return ;
	}*/
//	printf("ODHGOEJGREJGROEIGH roomlist->name = %s\n", roomlist->name);
	
	roomlist = roomlistart;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		if (roomlist->place == 0
				&& check_connection(roomlist, roomax) == 1)
		{
			return ;
		}
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& roomlist->place == roomax->place - 1
				&& check_connection(roomlist, roomax) == 1)
		{
			roomlist->taken = 1;
			roomax = roomlist;
			roomlist = roomlistart;
		}
		roomlist = roomlist->next;
	}
}

int		ft_reverse(t_roomlist *roomlist, int way)
{
	//printf("blop\n");
	t_roomlist	*roomlistart;
	t_roomlist	*roomway;
	int		maxplace;

	roomlistart = roomlist;
	roomlist = roomlist->next;
//	maxplace = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place == -2)
		{
			maxplace = ft_search_first_reverse(roomlist, roomlistart, way);
		//	if (roomlist == NULL)
		//		return (0);
		//	roomlist->taken = 1;
		}
		roomlist = roomlist->next;
	}
//	printf("maxplace = %d\n", maxplace);
	if (maxplace == 0)
		return (0);
	roomlist = roomlistart;
	roomlist = roomlist->next;

	ft_search_other_reverses(roomlistart, maxplace, way);

/*	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if (roomlist->
		roomlist = roomlist->next;
	}*/

	return (1);
}

void	ft_reset(t_roomlist *roomlistart, int way)
{
	while (roomlistart != NULL)
	{
		if (!(roomlistart->taken == 1
					&& roomlistart->way <= way
					&& roomlistart->place > 0))
		{
			roomlistart->way = 0;
		}
		roomlistart = roomlistart->next;
	}
}


int		ft_way(t_filist *filist, t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	int		progress;


	filist = filist->next;
	roomlist = roomlist->next;

	progress = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place == 0 || roomlist->place == -2)
		{
			roomlist->way = way;
		}
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;

	while (/*ft_no_zero(roomlistart) == 0*/1/*roomlist != NULL*/)//penser au -2(et au 0)
	{
		while (roomlist != NULL)
		{
			if (roomlist->way == 0 && roomlist->place != 0 && roomlist->taken == 0 && ft_search_previous(roomlist, roomlistart, way) == 1)
			{
		//		printf("COUCOU1111111111\n");
				roomlist->way = way;
			//	roomlist = roomlistart;
			//	roomlist = roomlist->next;
			}

			if (/*!!!!!!!*/(roomlist->way == way || roomlist->way == 0) && roomlist->place != 0 && roomlist->place != -2 && (ft_search_next(roomlist, roomlistart, way) == 0 || ft_search_previous(roomlist, roomlistart, way) == -1))//si pas de connexion avec un +1, ou qu'avec des -1
			{
		//		printf("COUCOU222222222\n");
				roomlist->way = -1;
			//	roomlist = roomlistart;
			//	roomlist = roomlist->next;
			}
		/*	if (roomlist->way == way && ft_search_next(roomlist, roomlistart, way) == -2)//si une des places = -2
			{
				printf("COUCOU3333333333\n");
				if (ft_no_zero(roomlistart) == 1)
				{
					//ft_ways_to_zero(roomlistart);
					//ft_takens_to_one(roomlistart, way);
					printf("RETURN 1\n");
					return (1);
				}
			//	roomlist = roomlistart;
			//	roomlist = roomlist->next;
			}*/
			/*if (roomlist->place == 0 && ft_search_next(roomlist, roomlistart, way) == -1)//si tous les ways = -1
			{
				printf("RETURN 0\n");
				return (0);??????????????????????????????????????????!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}*/
			//if (roomlist->next != NULL)
			roomlist = roomlist->next;
		}
		if (ft_no_zero(roomlistart) == 0)
		{
		//	printf("blop\n");
			roomlist = roomlistart;
	//		ft_show_roomlist(roomlist);
			roomlist = roomlist->next;
		}
		else
		{
			if (ft_reverse(roomlistart, way) == 1)
			{
			//	ft_show_roomlist(roomlistart);
				ft_reset(roomlistart, way);
		//		printf("RETURN 1111\n");
				return (1);
			}
			else
			{
			//	ft_show_roomlist(roomlistart);
		//		printf("RETURN 2222222\n");
				return (0);
			}
		}
	}


	//mettre tous les way = -1 a 0 et tous les doublons
	//mettre tous les taken a 1
	return (0);
}

void	ft_init(t_roomlist *roomlist)
{
	//printf("coucou\n");
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		//printf("coucou\n");
		roomlist->place = -1;
		roomlist->taken = 0;
		roomlist->way = 0;
		roomlist = roomlist->next;
	}
}

t_waylist	*ft_waylistnew(t_roomlist *roomlist, int way, t_waylist *waylist)
{
	t_waylist	*nextlink;

	nextlink = (t_waylist*)malloc(sizeof(t_waylist));
	nextlink->previous = waylist;
	nextlink->next = NULL;
	return (nextlink);
}

t_waylist	*ft_waylist(t_roomlist *roomlistart, t_roomlist *roomlist, int way)
{
	int		max;
	t_waylist	*waylist;
	t_waylist	*waylistart;
	int		place;
	char	*str;

	max = way;
//	way = 1;
	place = 0;

	waylist = (t_waylist*)malloc(sizeof(t_waylist));
	waylist->name = NULL;
	waylist->way = way;
	waylist->place = -1;
	waylist->previous = NULL;
	waylist->next = NULL;
	waylistart = waylist;

	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if ((roomlist->place == 0 || roomlist->way == way) && roomlist->place == place)
		{
			waylist->next = ft_waylistnew(roomlist, way, waylist);
			waylist = waylist->next;
			waylist->place = roomlist->place;
			waylist->way = roomlist->way;
			if (waylist->place == 0)
				waylist->way = way;
			str = ft_strnew(ft_strlen(roomlist->name));
			waylist->name = ft_strcpy(str, roomlist->name);
//			printf("%s\n", waylist->name);
			place++;
			roomlist = roomlistart;
		//	roomlist = roomlist->next;
		}
//		printf("%s\n", roomlist->name);
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if (roomlist->place == -2)
		{
			waylist->next = ft_waylistnew(roomlist, way, waylist);
			waylist = waylist->next;
			waylist->place = roomlist->place;
			waylist->way = way;
			str = ft_strnew(ft_strlen(roomlist->name));
			waylist->name = ft_strcpy(str, roomlist->name);
	//		printf("%s\n", waylist->name);

		}
		roomlist = roomlist->next;
	}
	return (waylistart);
}

t_listlist	*ft_listlistnew(t_listlist *listlist, int way)
{
	t_listlist	*nextlink;

	nextlink = (t_listlist*)malloc(sizeof(t_listlist));
//	nextlink->way = way;
	nextlink->previous = listlist;
	nextlink->next = NULL;
	return (nextlink);
}

void	ft_listlist(t_listlist *listlist, t_roomlist *roomlistart, t_roomlist *roomlist, int way)
{
	int		max;

	max = way;
//	printf("max = %d\n", max);
	way = 1;
	while (way <= max)
	{
		listlist->next = ft_listlistnew(listlist, way);
		listlist = listlist->next;
		listlist->waylist = ft_waylist(roomlistart, roomlist, way);
	//	printf("way = %d, place = %d, name = %s\n", listlist->waylist->way, listlist->waylist->place, listlist->waylist->name);
	//	listlist = listlist->next;
		way++;
	}
//	ft_waylist(roomlistart, roomlist, way);

}

//void	ft_listlist_waylist_ants

void	ft_ants(t_listlist *listlist, t_filist *filistart)
{
	t_listlist	*tmp;
	t_waylist	*waytmp;

	tmp = listlist;
	filistart = filistart->next;
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
//	printf("line = %s\n", filistart->line);
}

void	ft_show_listlist(t_listlist *listlist)
{
	t_listlist *tmp;
	t_waylist *waytmp;
	tmp = listlist;
	printf("ants = %d\n", tmp->ants);
	printf("\n");
	tmp = tmp->next;
//	tmp = tmp->next;
	while (tmp != NULL)
	{
		waytmp = tmp->waylist;
	//	printf("ants = %d\n", tmp->ants);
	//	printf("blop\n");
		while (waytmp != NULL)
		{
			printf("way = %d, place = %d, name = %s, ants = %d\n", waytmp->way, waytmp->place, waytmp->name, waytmp->ants);

			waytmp = waytmp->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	ft_free(t_filist *filistart, t_roomlist *roomlist, t_listlist *listlist)
{
	t_filist	*tmp;
	t_roomlist	*roomlistmp;
	t_listlist	*listlistmp;
	t_waylist	*waylistmp;
	int			i;

	i = 0;
	tmp = filistart;
	while (tmp != NULL)
	{
		tmp = filistart->next;
		free(filistart->line);
		free(filistart);
		filistart = tmp;
	}
	while (roomlistmp != NULL)
	{
		roomlistmp = roomlist->next;
		free(roomlist->name);
		if (roomlist->beftunnels != NULL)
		{
			while ((roomlist->beftunnels)[i] != NULL)
			{
				//printf("beftunnels = %s\n", (roomlist->beftunnels)[i]);
				free((roomlist->beftunnels)[i]);
				i++;
			}
			free((roomlist->beftunnels)[i]);
			free(roomlist->beftunnels);

		}
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
		i = 0;
		free(roomlist);
		roomlist = roomlistmp;
	}


	listlistmp = listlist;
	while (listlistmp != NULL)
	{
		listlistmp = listlist->next;
		while (listlist->waylist != NULL)
		{
			//printf("listlist->waylist->name = %s\n", listlist->waylist->name);
			free(listlist->waylist->name);
			waylistmp = listlist->waylist->next;
			free(listlist->waylist);
			listlist->waylist = waylistmp;
		}
		free(listlist->waylist);//<<<<---------------
		free(listlist);
		listlist = listlistmp;
	}
}


int		main(void)
{
	char		*tmp;
	t_filist	*filist;
	t_filist	*filistart;
	t_roomlist	*roomlist;
	t_roomlist	*roomlistart;
	t_listlist	*listlist;
	t_listlist	*listlistart;
	int			way;
//	t_waylist	*way;

	filist = (t_filist*)malloc(sizeof(t_filist));
	filist->previous = NULL;
	filist->line = NULL;
	filist->next = NULL;
	filistart = filist;
	while (get_next_line(0, &tmp))
	{
		//while (1);
		filist->next = ft_filstnew(tmp, filist);
		filist = filist->next;
		//while (1);
		free(tmp);
		//printf("%s\n", tmp);
	}
	free(tmp);
	//while (1);
	/*while (1)
	{
		while (get_next_line(0, &tmp))
		{
			filist->next = ft_filstnew(tmp, filist);
			filist = filist->next;
			//printf("%s\n", tmp);
		}
		break ;
	}*/
//	printf("filist->line = %s\n", filist->line);
//	free(filist->line);
	//while (1);
//	ft_show_filist(filistart);
	
	
	roomlist = (t_roomlist*)malloc(sizeof(t_roomlist));
	roomlist->previous = NULL;
	roomlist->place = 0;
	roomlist->name = NULL;
	roomlist->previous = NULL;
	roomlist->next = NULL;
	roomlistart = roomlist;


	ft_name(filistart, roomlist);
	ft_init(roomlist);
	ft_place_start(filistart, roomlist);
	ft_place_end(filistart, roomlist);
	ft_tunnels(filistart, roomlist);
	ft_place(filistart, roomlist);
	


	way = 1;
	while (ft_way(filistart, roomlist, roomlistart, way) == 1)
	{
		way++;
	}
	way--;

//	while (1);

	listlist = (t_listlist*)malloc(sizeof(t_listlist));
	listlist->previous = NULL;
	listlist->waylist = NULL;
	listlist->next = NULL;


	ft_listlist(listlist, roomlistart, roomlist, way);
	ft_ants(listlist, filistart);

	listlistart = listlist;	

	ft_show_listlist(listlist);
	listlist = listlistart;







	ft_free(filistart, roomlistart, listlistart);




	while (1);




	return (0);
}
