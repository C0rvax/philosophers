/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:53:08 by aduvilla          #+#    #+#             */
/*   Updated: 2024/05/15 10:01:55 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	a_table(t_academia *academia)
{
	int	i;

	if (academia->nb_philos > 1)
		if (pthread_create(&academia->thanatos, NULL, &thanatos, academia))
			return (print_error("pthread:", " ", "cannot create a thread", 1));
	i = 0;
	while (i < academia->nb_philos)
	{
		if (pthread_create(&academia->philo[i]->thread, NULL, &philo,
				academia->philo[i]))
			return (print_error("pthread:", " ", "cannot create a thread", 1));
		i++;
	}
	return (0);
}

static void	clear_table(t_academia *academia)
{
	int	i;

	i = 0;
	while (i < academia->nb_philos)
	{
		pthread_join(academia->philo[i]->thread, NULL);
		i++;
	}
	if (academia->nb_philos > 1)
		pthread_join(academia->thanatos, NULL);
	clean_exit(academia);
}

int	main(int ac, char **av)
{
	t_academia	academia;
	char		*use;
	char		*use2;

	use = " ./philo [nb of philosophers] [time to die] [time to eat]";
	use2 = " [time to sleep] {number of meals}";
	if (ac != 5 && ac != 6)
		return (print_error("usage:", use, use2, 1));
	if (init_academia(&academia, ac, av))
		return (clear_academia(&academia));
	if (init_philo(&academia))
		return (clean_exit(&academia));
	if (a_table(&academia))
		return (clean_exit(&academia));
	clear_table(&academia);
	return (0);
}
