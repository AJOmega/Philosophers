/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:54:44 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/14 15:13:37 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_action(long long time, t_rules *rules)
{
	long long	i;

	i = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(rules->death_mutex));
		if (rules->died || time_diff(i, timestamp()) >= time)
		{
			pthread_mutex_unlock(&(rules->death_mutex));
			break ;
		}
		pthread_mutex_unlock(&(rules->death_mutex));
		usleep(1);
	}
}

void	print_state(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->writing));
	pthread_mutex_lock(&(rules->death_mutex));
	if (!(rules->died))
	{
		printf("%lli ", timestamp() - rules->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(rules->writing));
	pthread_mutex_unlock(&(rules->death_mutex));
	return ;
}
