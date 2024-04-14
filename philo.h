/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:17:48 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/14 18:49:50 by jabreu-d         ###   ########.fr       */
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
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		x_ate_mutex;
	pthread_mutex_t		all_ate_mutex;
	t_philo				philosophers[250];
}	t_rules;

// main.c

// error_handle.c

int			error_handle(int error);

// init.c

int			init_mutex(t_rules *rules);
int			init_philosophers(t_rules *rules);
int			init_all(t_rules *rules, char *argv[]);

// atoi.c

long long	ft_atoi(char *str);

// time_manager.c

long long	timestamp(void);
long long	time_diff(long long past, long long pres);

// threads.c

void		*p_thread(void *void_philosopher);
void		*p_thread_part2(t_philo *philo, t_rules *rules);
int			launcher(t_rules *rules);

// eating.c

void		philo_alone(t_philo *philo);
void		philo_eats(t_philo *philo);
void		philo_eats_part2(t_philo *philo, t_rules *rules);

// actions.c

void		sleep_action(long long time, t_rules *rules);
void		print_state(t_rules *rules, int id, char *string);

// exit.c

void		death(t_rules *r, t_philo *p);
void		death_part2(t_rules *r, t_philo *p, int i);
void		end(t_rules *rules, t_philo *philos);

// max_protection.c

int			int_protected(long long result);
int			check_extremes(t_rules *rules);

#endif