/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:24:02 by aduvilla          #+#    #+#             */
/*   Updated: 2024/05/15 09:52:53 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_academia(t_academia *academia)
{
	if (academia->nb_philos < 0 || academia->die_time < 0
		|| academia->eat_time < 0 || academia->sleep_time < 0
		|| academia->meals_max == -1)
		return (1);
	if (academia->nb_philos > 250)
		return (print_error("usage:", " ", "too much philosophers", 1));
	if (academia->nb_philos == 0 || academia->die_time == 0)
		return (1);
	return (0);
}

int	init_academia(t_academia *academia, int ac, char **av)
{
	memset(academia, 0, sizeof(t_academia));
	academia->nb_philos = phi_atoi(av[1]);
	academia->die_time = phi_atoi(av[2]);
	academia->eat_time = phi_atoi(av[3]);
	academia->sleep_time = phi_atoi(av[4]);
	academia->meals_max = -2;
	if (ac == 6)
		academia->meals_max = phi_atoi(av[5]);
	academia->stop = 0;
	academia->start_time = get_time();
	if (check_academia(academia))
		return (1);
	if (pthread_mutex_init(&academia->print_mutex, NULL))
		return (print_error("pthread:", " ", "could not create mutex", 1));
	if (pthread_mutex_init(&academia->end_mutex, NULL))
		return (print_error("pthread:", " ", "could not create mutex", 1));
	academia->philo = malloc(sizeof(t_philo *) * academia->nb_philos);
	if (!academia->philo)
		return (print_error("pthread:", " ", "cannot allocate memory", 1));
	memset(academia->philo, 0, sizeof(t_philo *));
	return (0);
}

int	init_philo(t_academia *adm)
{
	int	i;

	i = 0;
	while (i < adm->nb_philos)
	{
		adm->philo[i] = malloc(sizeof(t_philo) * 1);
		if (!adm->philo[i])
			return (1);
		memset(adm->philo[i], 0, sizeof(t_philo));
		adm->philo[i]->id = i + 1;
		adm->philo[i]->starve_time = adm->start_time + adm->die_time;
		adm->philo[i]->academia = adm;
		adm->philo[i]->n_meals = 0;
		if (pthread_mutex_init(&adm->philo[i]->selfork_mutex, NULL))
			return (print_error("pthread:", " ", "could not create mutex", 1));
		if (pthread_mutex_init(&adm->philo[i]->starve_mutex, NULL))
			return (print_error("pthread:", " ", "could not create mutex", 1));
		if (i != 0)
			adm->philo[i]->taxfork_mutex = &adm->philo[i - 1]->selfork_mutex;
		i++;
	}
	if (adm->nb_philos > 0)
		adm->philo[0]->taxfork_mutex = &adm->philo[i - 1]->selfork_mutex;
	return (0);
}
