/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:34:51 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/14 16:24:10 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_thread(void *void_philosopher)
{
	t_philo			*philo;
	t_rules			*rules;

	philo = (t_philo *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(100);
	p_thread_part2(philo, rules);
	return (NULL);
}

void	*p_thread_part2(t_philo *philo, t_rules *rules)
{
	while (1)
	{
		if (philo->x_ate == rules->nb_eat)
			break ;
		if (rules->philo_num == 1)
		{
			philo_alone(philo);
			break ;
		}
		else
			philo_eats(philo);
		print_state(rules, philo->id, "\033[1;34mis sleeping\033[0m");
		pthread_mutex_lock(&(rules->death_mutex));
		if (rules->died)
		{
			pthread_mutex_unlock(&(rules->death_mutex));
			break ;
		}
		pthread_mutex_unlock(&(rules->death_mutex));
		sleep_action(rules->time_sleep, rules);
		print_state(rules, philo->id, "\033[1;35mis thinking\033[0m");
	}
	return (NULL);
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
	death(rules, rules->philosophers);
	end(rules, phi);
	return (0);
}
