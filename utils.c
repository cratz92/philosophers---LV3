/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:28:20 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/16 00:08:35 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_msg(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (FAILURE);
}

int	check_arguments(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (error_msg("Wrong arguments\n"));
	i = 1;
	while (i < argc)
		if (ft_isnumber(argv[i++]))
			return (error_msg("Only numbers (>= 0) are accepted\n"));
	if (ft_atoi(argv[1]) > 200 || ft_strlen(argv[1]) > 3)
		return (error_msg("Max number of philosophers : 200\n"));
	i = 2;
	while (i < argc)
	{
		if ((argc != 6) && (ft_atoi(argv[i]) > INT_MAX
				|| ft_strlen(argv[i]) > 10))
			return (error_msg("Max time in ms for args 2/3/4 : MAX INT ms\n"));
		else if ((argc == 6) && (ft_atoi(argv[i]) > INT_MAX
				|| ft_strlen(argv[i]) > 10))
			return (error_msg("Max nb of time philo can eat : MAX INT\n"));
		i++;
	}
	return (SUCCESS);
}

int	print_full_message(int id, int ms, char *str_msg)
{
	int		len_id;
	int		len_ms;
	char	tmp[100];

	len_id = -1;
	while (++len_id <= 99)
		tmp[len_id] = '\0';
	len_id = ft_number_len(id);
	len_ms = ft_number_len(ms);
	ft_putnbr_buffer(ms, tmp);
	ft_strlcpy(tmp + len_ms, "ms ", 4);
	ft_putnbr_buffer(id, tmp + len_ms + 3);
	ft_strlcpy(tmp + len_id + len_ms + 3, str_msg, ft_strlen(str_msg) + 1);
	ft_putstr_fd(tmp, 1);
	return (SUCCESS);
}

int	print_state_msg(t_philo *ph, int id_philo, suseconds_t ms, int type)
{
	pthread_mutex_lock(&(ph->ph_die->mutex));
	if (!ph->ph_die->data && type == EAT)
		print_full_message(id_philo, ms, " is eating\n");
	else if (!ph->ph_die->data && type == RFORK)
		print_full_message(id_philo, ms, " has taken a r_fork\n");
	else if (!ph->ph_die->data && type == LFORK)
		print_full_message(id_philo, ms, " has taken a l_fork\n");
	else if (!ph->ph_die->data && type == SLEEP)
		print_full_message(id_philo, ms, " is sleeping\n");
	else if (!ph->ph_die->data && type == THINK)
		print_full_message(id_philo, ms, " is thinking\n");
	else if (!ph->ph_die->data && type == DIE)
		print_full_message(id_philo, ms, " has died\n");
	pthread_mutex_unlock(&(ph->ph_die->mutex));
	return (SUCCESS);
}

void	clean_exit(t_philo *ph)
{
	int	i;

	i = -1;
	while (ph[++i].id)
		pthread_mutex_destroy(&((ph[i].mutex)[i]));
	pthread_mutex_destroy(&(ph->ph_die->mutex));
	free(ph->mutex);
	free(ph);
}
