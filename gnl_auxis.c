/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/13 20:13:34 by mpascaud         ###   ########.fr       */
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

int			ft_at_least_one_room(char *tmp)
{
	int		i;

	i = 0;
	if (tmp == NULL || tmp[0] == '\0' || tmp[0] == '\n')
		return (0);
	while (tmp[i] != '\0')
		i++;
	i--;
	while (ft_isdigit(tmp[i]) == 1)
	{
		i--;
		if (i < 0)
			return (0);
	}
	i--;
	while (ft_isdigit(tmp[i]) == 1)
	{
		i--;
		if (i < 0)
			return (0);
	}
	if (tmp[i] == ' ' && tmp[0] != '#')
		return (1);
	return (0);
}

int			ft_bad_room(char *tmp, int step, int i)
{
	if (tmp[0] == '#')
		return (0);
	while (tmp[++i] != '\0' && step == 2)
		if (tmp[i] == '-')
			return (0);
	i = 0;
	while (tmp[i] != '\0')
		i++;
	i--;
	if (i < 0 || ft_isdigit(tmp[i]) == 0)
		return (1);
	while (i >= 0 && ft_isdigit(tmp[i]) == 1)
		i--;
	if (i < 0 || tmp[i] != ' ')
		return (1);
	i--;
	if (i < 0 || ft_isdigit(tmp[i]) == 0)
		return (1);
	while (i > 0 && ft_isdigit(tmp[i]) == 1)
		i--;
	if (i <= 0 || tmp[i] != ' ')
		return (1);
	return (0);
}
