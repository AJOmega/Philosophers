/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:28:56 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/13 01:39:06 by jabreu-d         ###   ########.fr       */
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
