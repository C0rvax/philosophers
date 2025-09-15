/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:35:54 by aduvilla          #+#    #+#             */
/*   Updated: 2024/05/15 14:26:55 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/***********************	LIBRAIRIES	************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/***********************	STRUCT	****************************************/

typedef struct s_academia
{
	int				nb_philos;
	time_t			die_time;
	time_t			eat_time;
	time_t			sleep_time;
	int				meals_max;
	time_t			start_time;
	int				stop;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		thanatos;
	struct s_philo	**philo;
}		t_academia;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	time_t				starve_time;
	int					n_meals;
	pthread_mutex_t		starve_mutex;
	pthread_mutex_t		selfork_mutex;
	pthread_mutex_t		*taxfork_mutex;
	struct s_academia	*academia;
}		t_philo;

/***********************	EXIT	****************************************/

int		print_error(char *s1, char *s2, char *s3, int status);
int		clear_academia(t_academia *academia);
int		clean_exit(t_academia *academia);

/***********************	UTILS	****************************************/

time_t	get_time(void);
int		phi_atoi(char *arg);
void	print_status(t_philo *philo, char *s);
int		stop_dinner(t_academia *academia);

/***********************	INIT	****************************************/

int		init(t_academia *academia, int ac, char **av);
int		init_academia(t_academia *academia, int ac, char **av);
int		init_philo(t_academia *adm);

/***********************	ROUTINE	****************************************/

void	*thanatos(void *academia);
void	*philo(void *phi);

#endif
