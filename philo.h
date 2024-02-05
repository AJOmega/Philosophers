/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:17:48 by jabreu-d          #+#    #+#             */
/*   Updated: 2023/12/07 00:20:56 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define ERROR	"\033[1;31m"
# define NORMAL	"\033[0m"

struct	s_rules;

typedef struct s_philo
{
	int				id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		t_last_meal;
	struct s_rules	*rules;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_rules
{
	int					philo_num;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					died;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philo				philosophers[250];
}	t_rules;

// Init.c

int	init_mutex(t_rules *rules);
int	init_philosophers(t_rules *rules);
int	init_all(t_rules *rules, char *argv[]);

// utils.c

int			ft_atoi(char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time, t_rules *rules);
void		action_print(t_rules *rules, int id, char *string);

// error_handle.c

int	error_handle(int error);

// launcher.c
void	philo_eats(t_philo *philo);
void	*p_thread(void *void_philosopher);
void	exit_launcher(t_rules *rules, t_philo *philos);
void	death_checker(t_rules *r, t_philo *p);
int		launcher(t_rules *rules);

#endif