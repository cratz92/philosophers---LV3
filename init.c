/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:50:04 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/15 23:43:18 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	launch_threads(t_philo *ph)
{
	int	i;

	i = -1;
	while (ph[++i].id)
		pthread_create(&(ph[i].thread_id), NULL, &philo_life, &(ph[i]));
}

pthread_mutex_t	*create_forks(int nb_forks)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = malloc(sizeof(*mutex) * (nb_forks));
	if (!(mutex))
		return (NULL);
	while (i < nb_forks)
		pthread_mutex_init(&mutex[i++], NULL);
	return (mutex);
}

void	init_t_args(t_args *pa, int argc, char **argv)
{
	pa->number_of_ph = ft_atoi(argv[1]);
	pa->time_to_die = ft_atoi(argv[2]);
	pa->time_to_eat = ft_atoi(argv[3]);
	pa->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		pa->number_times_must_eat = ft_atoi(argv[5]);
	else
		pa->number_times_must_eat = -1;
}

t_philo	*create_t_philo_array(pthread_mutex_t *mutex, int *number_ph_done,
		t_data *ph_die, t_args *pa)
{
	t_philo	*ph;
	int		number_of_ph;
	long	time_start;

	number_of_ph = pa->number_of_ph;
	ph = malloc(sizeof(t_philo) * (number_of_ph + 1));
	if (!ph)
		return (NULL);
	time_start = actual_time();
	ph[number_of_ph].id = 0;
	while (number_of_ph - 1 >= 0)
	{
		ph[number_of_ph - 1].id = number_of_ph;
		ph[number_of_ph - 1].mutex = mutex;
		ph[number_of_ph - 1].pa = pa;
		ph[number_of_ph - 1].time_start = time_start;
		ph[number_of_ph - 1].ph_die = ph_die;
		ph[number_of_ph - 1].number_ph_done = number_ph_done;
		number_of_ph--;
	}
	return (ph);
}
