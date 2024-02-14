/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:48:30 by jabreu-d          #+#    #+#             */
/*   Updated: 2024/02/13 21:09:24 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handle(int error)
{
	printf("\033[1;31m");
	if (error == 1)
		printf("Error: Invalid number of arguments\n");
	else if (error == 2)
		printf("Error: Invalid argument\n");
	else if (error == 3)
		printf("Error: Malloc failed\n");
	else if (error == 4)
		printf("Error: Semaphore failed\n");
	else if (error == 5)
		printf("Error: Thread failed\n");
	else if (error == 6)
		printf("Error: Mutex failed\n");
	else if (error == 7)
		printf("Error: Time failed\n");
	else if (error == 8)
		printf("Error: Fork failed\n");
	else if (error == 9)
		printf("Error: Process failed\n");
	else if (error == 10)
		printf("Error: Kill failed\n");
	printf("%s", NORMAL);
	return (1);
}
