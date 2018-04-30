/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoilefaux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:21:09 by mpascaud          #+#    #+#             */
/*   Updated: 2017/11/25 17:42:42 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int				i;
	long int		result;
	long int		neg;

	neg = 1;
	i = 0;
	result = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		neg = -1;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (long long int)(str[i] - '0');
		i++;
	}
	return (result * neg);
}
