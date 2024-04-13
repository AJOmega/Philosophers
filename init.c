/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:16:50 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/13 16:52:03 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->philo_num - 1;
	while (i >= 0)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (error_handle(6));
		i--;
	}
	if (pthread_mutex_init(&rules->writing, NULL) != 0)
		return (error_handle(6));
	if (pthread_mutex_init(&rules->meal_check, NULL) != 0)
		return (error_handle(6));
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		return (error_handle(6));
	if (pthread_mutex_init(&rules->x_ate_mutex, NULL) != 0)
		return (error_handle(6));
	if (pthread_mutex_init(&rules->all_ate_mutex, NULL) != 0)
		return (error_handle(6));
	return (0);
}

int	init_philosophers(t_rules *rules)
{
	int	i;

	i = rules->philo_num - 1;
	while (i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].x_ate = 0;
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->philo_num;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].rules = rules;
		i--;
	}
	return (0);
}

int	init_all(t_rules *rules, char *argv[])
{
	rules->philo_num = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (rules->philo_num == -1 || rules->time_death == -1 || \
		rules->time_eat == -1 || rules->time_sleep == -1)
		return (error_handle(2));
	rules->all_ate = 0;
	rules->died = 0;
	if (rules->philo_num < 1 || rules->time_death < 0 || rules->time_eat < 0 || \
		rules->time_sleep < 0 || (argv[5] && ft_atoi(argv[5]) < 0) || \
		rules->philo_num > 200)
		return (error_handle(2));
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (error_handle(2));
	}
	else
		rules->nb_eat = -1;
	if (init_mutex(rules) != 0)
		return (error_handle(6));
	init_philosophers(rules);
	return (0);
}
