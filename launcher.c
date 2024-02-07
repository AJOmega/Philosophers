/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:34:51 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/02/07 21:21:29 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	action_print(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	action_print(rules, philo->id, "\033[1;33mhas taken a fork\033[0m");
	pthread_mutex_lock(&(rules->meal_check));
	action_print(rules, philo->id, "\033[1;32mis eating\033[0m");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	smart_sleep(rules->time_eat, rules);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philosopher)
{
	int				i;
	t_philo			*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philo *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->died))
	{
		philo_eats(philo);
		if (rules->all_ate)
			break ;
		action_print(rules, philo->id, "\033[1;34mis sleeping\033[0m");
		smart_sleep(rules->time_sleep, rules);
		action_print(rules, philo->id, "\033[1;35mis thinking\033[0m");
		i++;
	}
	return (NULL);
}

void	exit_launcher(t_rules *rules, t_philo *philos)
{
	int i;

	i = -1;
	while (++i < rules->philo_num)
	{
		printf("Philo Number: %d, Philo ID: %d\n", i, philos[i].id);
		pthread_join(philos[i].thread_id, NULL);
	}
	printf("É encima CARALHO\n");
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
				r->died = 1;
				printf("Hey Close, YOU DIED, %d\n", r->died);
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->died)
		{
			printf("Entrastes aqui meu filho da PUTA\n");
			break ;	
		}
		i = 0;
		while (r->nb_eat != -1 && i < r->philo_num && p[i].x_ate >= r->nb_eat)
			i++;
		if (i == r->philo_num)
			r->all_ate = 1;
	}
	printf("Saiu do Death Checker\n");
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
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_checker(rules, rules->philosophers);
	exit_launcher(rules, phi);
	return (0);
}
