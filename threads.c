/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:28:20 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/15 23:46:23 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_philo_is_fed(t_philo *ph, int *number_times_ph_ate)
{
	pthread_mutex_lock(&(ph->ph_die->mutex));
	if (++(*number_times_ph_ate) == ph->pa->number_times_must_eat)
	{
		if (++(*(ph->number_ph_done)) == ph->pa->number_of_ph)
		{
			if (!(ph->ph_die->data))
				ft_putstr_fd("All philosphers have eaten enough\n", 1);
			ph->ph_die->data = 1;
		}
	}
	pthread_mutex_unlock(&(ph->ph_die->mutex));
}

void	philo_eat(t_philo *ph, int *number_times_ph_ate)
{
	int	r_fork;
	int	l_fork;

	r_fork = ph->id - 1;
	l_fork = ft_ternary(r_fork != 0, r_fork - 1, ph->pa->number_of_ph - 1);
	if (r_fork == l_fork)
		return ;
	if ((ph->id % 2 == 0 && !pthread_mutex_lock(&((ph->mutex)[l_fork])))
		|| !pthread_mutex_lock(&((ph->mutex)[r_fork])))
		print_state_msg(ph, ph->id, actual_time() - ph->time_start, LFORK);
	if ((ph->id % 2 == 0 && !pthread_mutex_lock(&((ph->mutex)[r_fork])))
		|| !pthread_mutex_lock(&((ph->mutex)[l_fork])))
		print_state_msg(ph, ph->id, actual_time() - ph->time_start, RFORK);
	ph->time_last_meal = actual_time();
	print_state_msg(ph, ph->id, actual_time() - ph->time_start, EAT);
	check_philo_is_fed(ph, number_times_ph_ate);
	ft_usleep(ph->pa->time_to_eat * 1000);
	pthread_mutex_unlock(&((ph->mutex)[l_fork]));
	pthread_mutex_unlock(&((ph->mutex)[r_fork]));
	print_state_msg(ph, ph->id, actual_time() - ph->time_start, SLEEP);
	ft_usleep(ph->pa->time_to_sleep * 1000);
	print_state_msg(ph, ph->id, actual_time() - ph->time_start, THINK);
	usleep(100);
}

void	*check_philo_alive(void *tmp)
{
	t_philo	*ph;
	long	time_death;

	ph = (t_philo *)tmp;
	while (1)
	{
		time_death = actual_time();
		pthread_mutex_lock(&(ph->ph_die->mutex));
		if ((time_death - ph->time_last_meal) > ph->pa->time_to_die)
		{
			if (!ph->ph_die->data)
				print_full_message(ph->id, time_death
					- ph->time_start, " has died\n");
			ph->ph_die->data = 1;
			pthread_mutex_unlock(&(ph->ph_die->mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(ph->ph_die->mutex));
		if (ph->ph_die->data)
			return (NULL);
	}
}

void	*philo_life(void *ph)
{
	pthread_t	control_die;
	int			number_times_ph_ate;

	number_times_ph_ate = 0;
	((t_philo *)ph)->time_last_meal = actual_time();
	pthread_create(&control_die, NULL, &check_philo_alive, ph);
	while (1)
	{
		philo_eat((t_philo *)ph, &number_times_ph_ate);
		if (((t_philo *)ph)->ph_die->data)
		{
			pthread_join(control_die, NULL);
			return (ph);
		}
	}
	return (ph);
}

void	join_all_threads(t_philo *ph)
{
	int	i;

	i = -1;
	while (ph[++i].id)
		pthread_join(ph[i].thread_id, NULL);
}
