/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:28:56 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/04/14 15:14:18 by jabreu-d         ###   ########.fr       */
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
