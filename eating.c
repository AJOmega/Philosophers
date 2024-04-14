/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:38:26 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/14 15:18:46 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_alone(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	print_state(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
}

void	philo_eats(t_philo *philo)
{
	t_rules	*rules;
	t_philo	*next_philo;

	rules = philo->rules;
	if (philo->id % 2)
		usleep(100);
	if (philo->id < rules->philo_num - 1)
		next_philo = &rules->philosophers[philo->id + 1];
	else
		next_philo = &rules->philosophers[0];
	if (philo->id < next_philo->id)
	{
		pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
		print_state(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
		pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
		print_state(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
	}
	else
	{
		pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
		print_state(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
		pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
		print_state(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
	}
	philo_eats_part2(philo, rules);
}

void	philo_eats_part2(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&(rules->meal_check));
	print_state(rules, philo->id, "\033[1;32mis eating\033[0m");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	sleep_action(rules->time_eat, rules);
	pthread_mutex_lock(&(rules->x_ate_mutex));
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->x_ate_mutex));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}
