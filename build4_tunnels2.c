/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:32:03 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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
		if ((filist->line)[i] != (roomlist->name)[i]
				|| (filist->line)[i] == '\0')
			return (0);
		i++;
	}
	if ((filist->line)[i] != '-')
		return (0);
	return (1);
}

int		ft_disiz_beftunnel(t_filist *filist, t_roomlist *rmlst)
{
	int		there_is_tunnel;
	int		i;
	int		j;

	there_is_tunnel = 0;
	i = -1;
	j = -1;
	while ((filist->line)[++i] != '\0')
		if ((filist->line)[i] == '-')
		{
			there_is_tunnel = 1;
			i++;
			break ;
		}
	if (there_is_tunnel == 0)
		return (0);
	while ((rmlst->name)[++j] != '\0')
	{
		if ((filist->line)[i] != (rmlst->name)[j] || (filist->line)[i] == '\0')
			return (0);
		i++;
	}
	if ((filist->line)[i] != '\0')
		return (0);
	return (1);
}

char	*ft_link(t_filist *filist)
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
	tmp = start - 1;
	while ((filist->line)[++tmp] != '\0')
		i++;
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

char	*ft_beflink(t_filist *filist)
{
	char	*tunname;
	int		i;

	i = 0;
	while ((filist->line)[i] != '-')
	{
		i++;
	}
	tunname = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while ((filist->line)[i] != '-')
	{
		tunname[i] = (filist->line)[i];
		i++;
	}
	tunname[i] = '\0';
	return (tunname);
}
