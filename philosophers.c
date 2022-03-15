/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:27:06 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/15 23:45:31 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo			*ph;
	t_data			ph_die;
	int				number_ph_done;
	pthread_mutex_t	*mutex;
	t_args			pa;

	if (check_arguments(argc, argv))
		return (FAILURE);
	pthread_mutex_init(&(ph_die.mutex), NULL);
	ph_die.data = 0;
	number_ph_done = 0;
	init_t_args(&pa, argc, argv);
	if (pa.number_of_ph < 1)
		return (error_msg("Not enough philosphers, must be at least 1\n"));
	mutex = create_forks(pa.number_of_ph);
	if (!(mutex))
		return (error_msg("Malloc failed\n"));
	ph = create_t_philo_array(mutex, &number_ph_done, &ph_die, &pa);
	if (!(ph))
		return (error_msg("Malloc failed\n"));
	launch_threads(ph);
	join_all_threads(ph);
	clean_exit(ph);
	return (0);
}
