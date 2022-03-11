/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:50:04 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/11 11:50:04 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Creates an array of threads.
*/
void launch_threads(t_philo *ph)
{
	int i;

	i = -1;
	while (ph[++i].id)
		pthread_create(&(ph[i].thread_id), NULL, &philo_life, &(ph[i]));
}

/*
** Creates an array of mutexs (nb mutexs = nb philosophers).
*/
pthread_mutex_t *create_forks(int nb_forks)
{
	pthread_mutex_t *mutex;
	int i;

	i = 0;
	if (!(mutex = malloc(sizeof(*mutex) * (nb_forks))))
		return (NULL);
	while (i < nb_forks)
		pthread_mutex_init(&mutex[i++], NULL);
	return (mutex);
}

/*
** Inits the different structure's arguments. Nb_each_philo_eat is set
** to -1 if the fifth argument is missing (optional argument).
*/
void init_t_args(t_args *pa, int argc, char **argv)
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

/*
** Creates, initiates and returns an array of struct t_philo. Returns NULL if
** an error occured.
*/
t_philo *create_t_philo_array(pthread_mutex_t *mutex, int *number_ph_done, t_data *ph_die, t_args *pa)
{
	t_philo *ph;
	int number_of_ph;
	long time_start;

	number_of_ph = pa->number_of_ph;
	ph = malloc(sizeof(*ph) * (number_of_ph + 1)); //+1 for NULL-terminated
	if (!ph)
		return (NULL);
	ph[number_of_ph].id = 0;	//end the array
	time_start = get_time_ms(); //ref time for time calculs
	while (number_of_ph - 1 >= 0)
	{
		ph[number_of_ph - 1].id = number_of_ph;
		ph[number_of_ph - 1].mutex = mutex;
		ph[number_of_ph - 1].pa = pa;
		ph[number_of_ph - 1].time_start = time_start; //all structs have the same time_start
		ph[number_of_ph - 1].ph_die = ph_die;
		ph[number_of_ph - 1].number_ph_done = number_ph_done;
		number_of_ph--;
	}
	return (ph);
}
