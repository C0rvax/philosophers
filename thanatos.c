/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thanatos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:43:57 by aduvilla          #+#    #+#             */
/*   Updated: 2024/05/15 21:26:42 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_academia(t_academia *academia)
{
	pthread_mutex_lock(&academia->end_mutex);
	academia->stop = 1;
	pthread_mutex_unlock(&academia->end_mutex);
}

static int	is_dead(t_philo *philo)
{
	int	dead;

	dead = 0;
	if (get_time() >= philo->starve_time)
		dead = 1;
	pthread_mutex_unlock(&philo->starve_mutex);
	return (dead);
}

static int	is_over(t_academia *academia)
{
	int	i;
	int	full;
	int	max_meals;

	i = 0;
	full = 1;
	max_meals = academia->meals_max;
	while (i < academia->nb_philos)
	{
		pthread_mutex_lock(&academia->philo[i]->starve_mutex);
		if (max_meals > 0 && academia->philo[i]->n_meals < max_meals)
			full = 0;
		else if (max_meals < 0)
			full = 0;
		if (is_dead(academia->philo[i]))
			return (print_status(academia->philo[i], "died"), 1);
		i++;
	}
	if (full)
		return (stop_academia(academia), 1);
	return (0);
}

void	*thanatos(void *academia)
{
	t_academia	*adm;

	usleep(800);
	adm = (t_academia *)academia;
	if (adm->meals_max == 0)
		return (NULL);
	while (1)
	{
		if (is_over(adm))
			return (NULL);
		usleep(900);
	}
	return (NULL);
}
