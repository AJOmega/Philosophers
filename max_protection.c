/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_protection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:17:12 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/14 18:49:46 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	int_protected(long long result)
{
	if (result > 2147483647 || result < -2147483648)
		return (-1);
	return (0);
}

int	check_extremes(t_rules *rules)
{
	if (int_protected(rules->philo_num) == -1)
		return (-1);
	if (int_protected(rules->time_death) == -1)
		return (-1);
	if (int_protected(rules->time_eat) == -1)
		return (-1);
	if (int_protected(rules->time_sleep) == -1)
		return (-1);
	return (0);
}
