/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:12:08 by aduvilla          #+#    #+#             */
/*   Updated: 2024/05/15 09:53:50 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *s1, char *s2, char *s3, int status)
{
	printf("philo: %s%s%s\n", s1, s2, s3);
	return (status);
}

int	clear_academia(t_academia *academia)
{
	pthread_mutex_destroy(&academia->print_mutex);
	pthread_mutex_destroy(&academia->end_mutex);
	if (academia->philo)
		free(academia->philo);
	return (1);
}

int	clean_exit(t_academia *academia)
{
	int	i;

	i = 0;
	while (i < academia->nb_philos && academia->philo[i])
	{
		pthread_mutex_destroy(&academia->philo[i]->selfork_mutex);
		pthread_mutex_destroy(&academia->philo[i]->starve_mutex);
		free(academia->philo[i]);
		i++;
	}
	return (clear_academia(academia));
}
