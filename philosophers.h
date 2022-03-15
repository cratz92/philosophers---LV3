/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:28:20 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/15 23:46:02 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

# define SUCCESS 0
# define FAILURE 1

# define EAT 0
# define RFORK 1
# define LFORK 10
# define THINK 2
# define SLEEP 3
# define DIE 4

typedef struct s_args
{
	int	number_of_ph;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_times_must_eat;
}		t_args;

typedef struct s_data
{
	pthread_mutex_t	mutex;
	int				data;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	*mutex;
	t_args			*pa;
	long			time_start;
	long int		time_last_meal;
	t_data			*ph_die;
	int				*number_ph_done;
}					t_philo;

//libft_a.c

size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
long			ft_atoi(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

//libft_b.c

int				ft_isdigit(int c);
int				ft_isnumber(char *str);
long			actual_time(void);
int				ft_compare_nbr(long a, long b);
int				ft_ternary(int condition, int true_value, int false_value);

//libft_c.c

void			ft_usleep(long d);
int				ft_get_number_base(unsigned int nb);
int				ft_number_len(unsigned int nb);
void			ft_putnbr_buffer(int n, char *str);

//utils.c

int				error_msg(char *str);
int				check_arguments(int argc, char **argv);
int				print_full_message(int id, int ms, char *str_msg);
int				print_state_msg(t_philo *ph, int id_philo,
					suseconds_t ms, int type);
void			clean_exit(t_philo *ph);

//init.c

void			init_t_args(t_args *pa, int argc, char **argv);
t_philo			*create_t_philo_array(pthread_mutex_t *mutex,
					int *number_ph_done, t_data *ph_die, t_args *pa);
pthread_mutex_t	*create_forks(int nb_forks);
void			launch_threads(t_philo *ph);

//threads.c

void			*philo_life(void *ph);
void			join_all_threads(t_philo *ph);
void			*check_philo_alive(void *tmp);
void			philo_eat(t_philo *ph, int *number_times_ph_ate);
void			check_philo_is_fed(t_philo *ph, int *number_times_ph_ate);

#endif
