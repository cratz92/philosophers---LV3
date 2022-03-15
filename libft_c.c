/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:57:48 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/15 23:44:48 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long d)
{
	struct timeval	tmp;
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&tmp, NULL);
		if ((((long)(tmp.tv_sec - start.tv_sec)) * 1000000
			+ ((long)(tmp.tv_usec - start.tv_usec))) >= d)
			return ;
	}
}

int	ft_number_len(unsigned int nb)
{
	int	len;

	len = 1;
	while (nb > 9)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

int	ft_get_number_base(unsigned int nb)
{
	int	len;

	len = 1;
	while (nb > 9)
	{
		len *= 10;
		nb /= 10;
	}
	return (len);
}

void	ft_putnbr_buffer(int n, char *str)
{
	unsigned int	temp;
	unsigned int	len;
	char			minus;

	minus = '-';
	temp = n;
	if (n < 0)
	{
		*str = minus;
		str++;
		temp = -n;
	}
	len = ft_get_number_base(temp);
	while (len >= 10)
	{
		*str = temp / len + 48;
		str++;
		temp %= len;
		len /= 10;
	}
	*str = temp + 48;
}
