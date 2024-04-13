/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:34:51 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/13 13:12:31 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo)
{
	t_rules	*rules;
	t_philo	*next_philo;

	rules = philo->rules;
	if (philo->id < rules->philo_num - 1)
		next_philo = &rules->philosophers[philo->id + 1];
	else
		next_philo = &rules->philosophers[0];
	if (philo->id < next_philo->id)
	{
		pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
		action_print(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
		pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
		action_print(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
	}
	else
	{
		pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
		action_print(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
		pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
		action_print(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
	}
	philo_eats_part2(philo, rules);
}

// printf("p_threads: %p\n", philo); // debug
void	*p_thread(void *void_philosopher)
{
	int				i;
	t_philo			*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philo *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(100);
	p_thread_part2(i, philo, rules);
	return (NULL);
}

void	exit_launcher(t_rules *rules, t_philo *philos)
{
	int	i;

	i = -1;
	if (rules->philo_num > 0)
	{
		i = -1;
		while (++i < rules->philo_num)
			pthread_join(philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < rules->philo_num)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
}

void	death_checker(t_rules *r, t_philo *p)
{
	int	i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->philo_num && !(r->died))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
			{
				action_print(r, i, "\033[1;31mdied\033[0m");
				pthread_mutex_lock(&(r->death_mutex));
				r->died = 1;
				pthread_mutex_unlock(&(r->death_mutex));
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->died)
			break ;
		i = 0;
		death_checker_part2(r, p, i);
	}
}

int	launcher(t_rules *rules)
{
	int				i;
	t_philo			*phi;

	i = 0;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (i < rules->philo_num)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		pthread_mutex_lock(&(rules->meal_check));
		phi[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal_check));
		i++;
	}
	death_checker(rules, rules->philosophers);
	exit_launcher(rules, phi);
	return (0);
}
