/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:28:56 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/13 13:03:42 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_rules		rules;
	int			return_value;

	if (argc != 5 && argc != 6)
		return (error_handle(1));
	return_value = init_all(&rules, argv);
	if (return_value)
		return (return_value);
	if (launcher(&rules) != 0)
		return (5);
}

void	philo_alone(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	action_print(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
}

void	philo_eats_part2(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&(rules->meal_check));
	action_print(rules, philo->id, "\033[1;32mis eating\033[0m");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	smart_sleep(rules->time_eat, rules);
	pthread_mutex_lock(&(rules->x_ate_mutex));
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->x_ate_mutex));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}

void	*p_thread_part2(int i, t_philo *philo, t_rules *rules)
{
	while (1 || i++)
	{
		if (rules->philo_num == 1)
			philo_alone(philo);
		else
			philo_eats(philo);
		pthread_mutex_lock(&(rules->all_ate_mutex));
		if (rules->all_ate || rules->philo_num == 1)
		{
			pthread_mutex_unlock(&(rules->all_ate_mutex));
			break ;
		}
		pthread_mutex_unlock(&(rules->all_ate_mutex));
		action_print(rules, philo->id, "\033[1;34mis sleeping\033[0m");
		pthread_mutex_lock(&(rules->death_mutex));
		if (rules->died)
		{
			pthread_mutex_unlock(&(rules->death_mutex));
			break ;
		}
		pthread_mutex_unlock(&(rules->death_mutex));
		smart_sleep(rules->time_sleep, rules);
		action_print(rules, philo->id, "\033[1;35mis thinking\033[0m");
	}
	return (NULL);
}

void	death_checker_part2(t_rules *r, t_philo *p, int i)
{
	pthread_mutex_lock(&(r->x_ate_mutex));
	while (r->nb_eat != -1 && i < r->philo_num && p[i].x_ate >= r->nb_eat)
	{
		pthread_mutex_unlock(&(r->x_ate_mutex));
		i++;
		pthread_mutex_lock(&(r->x_ate_mutex));
	}
	pthread_mutex_unlock(&(r->x_ate_mutex));
	if (i == r->philo_num)
	{
		pthread_mutex_lock(&(r->all_ate_mutex));
		r->all_ate = 1;
		pthread_mutex_unlock(&(r->all_ate_mutex));
	}
}
