/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:57:48 by aduvilla          #+#    #+#             */
/*   Updated: 2024/05/15 14:25:40 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[0] == 0)
		return (0);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	phi_atoi(char *arg)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	if (!is_valid(arg))
		return (print_error(arg, ":", " is not a valid number", -1));
	while (arg[i])
	{
		res = res * 10 + arg[i] - '0';
		i++;
	}
	if (res > 2147483647)
		return (print_error(arg, ":", " is higher than INT_MAX", -1));
	return ((int)res);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	stop_dinner(t_academia *academia)
{
	int	stop_adm;

	pthread_mutex_lock(&academia->end_mutex);
	stop_adm = academia->stop;
	pthread_mutex_unlock(&academia->end_mutex);
	return (stop_adm);
}

void	print_status(t_philo *philo, char *s)
{
	time_t	time;

	time = get_time() - philo->academia->start_time;
	pthread_mutex_lock(&philo->academia->end_mutex);
	if (!philo->academia->stop)
	{
		pthread_mutex_lock(&philo->academia->print_mutex);
		printf("%ld %d %s\n", time, philo->id, s);
		if (s && s[0] == 'd')
			philo->academia->stop = 1;
		pthread_mutex_unlock(&philo->academia->print_mutex);
	}
	pthread_mutex_unlock(&philo->academia->end_mutex);
}
