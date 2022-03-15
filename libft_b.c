/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:56:51 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/15 23:44:23 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (FAILURE);
	}
	return (SUCCESS);
}

long	actual_time(void)
{
	struct timeval	tmp_time;
	long			ms;

	gettimeofday(&tmp_time, NULL);
	ms = tmp_time.tv_sec * 1000;
	ms += tmp_time.tv_usec / 1000;
	return (ms);
}

int	ft_compare_nbr(long a, long b)
{
	if (a > b)
		return (1);
	else if (a == b)
		return (2);
	else
		return (0);
}

int	ft_ternary(int condition, int true_value, int false_value)
{
	if (condition)
		return (true_value);
	return (false_value);
}
