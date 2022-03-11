/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:57:48 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/11 11:57:48 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** More opti than usleep function.
*/
void better_sleep(long d)
{
	struct timeval tmp;
	struct timeval start;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&tmp, NULL);
		if ((((long)(tmp.tv_sec - start.tv_sec)) * 1000000 + ((long)(tmp.tv_usec - start.tv_usec))) >= d)
			return;
	}
}

int lennb_for_str(unsigned int nb)
{
	int len;

	len = 1;
	while (nb > 9)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

int lennb(unsigned int nb)
{
	int len;

	len = 1;
	while (nb > 9)
	{
		len *= 10;
		nb /= 10;
	}
	return (len);
}

void ft_putnbr_buffer(int n, char *str)
{
	unsigned int temp;
	unsigned int len;
	char carac;

	carac = '-';
	temp = n;
	if (n < 0)
	{
		*str = carac;
		str++;
		temp = -n;
	}
	len = lennb(temp);
	while (len >= 10)
	{
		*str = temp / len + 48;
		str++;
		temp %= len;
		len /= 10;
	}
	*str = temp + 48;
}
