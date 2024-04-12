/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:54:44 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/12 22:38:32 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

// while (!(rules->died))
void	smart_sleep(long long time, t_rules *rules)
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
		usleep(50);
	}
}

void	action_print(t_rules *rules, int id, char *string)
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
