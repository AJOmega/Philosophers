/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:40:25 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/14 16:12:19 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death(t_rules *r, t_philo *p)
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
				print_state(r, i, "\033[1;31mdied\033[0m");
				pthread_mutex_lock(&(r->death_mutex));
				r->died = 1;
				pthread_mutex_unlock(&(r->death_mutex));
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->died || r->all_ate)
			break ;
		i = 0;
		death_part2(r, p, i);
	}
}

void	death_part2(t_rules *r, t_philo *p, int i)
{
	pthread_mutex_lock(&(r->x_ate_mutex));
	while (r->nb_eat != -1 && i < r->philo_num && p[i].x_ate == r->nb_eat)
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

void	end(t_rules *rules, t_philo *philos)
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
