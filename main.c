/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:28:56 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/02/04 17:59:37 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_rules		rules;
	int			return_value;

	// printf ("Hola\n");
	if (argc != 5 && argc != 6)
		return (error_handle(1));
	if ((return_value = init_all(&rules, argv)))
		return (return_value);
	if (launcher(&rules) != 0)
		return (5);
}
