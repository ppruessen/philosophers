/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:43:09 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/14 12:42:53 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Function initialises the philo structures and var->forks */
void	init_philos(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philos)
	{
		var->philo[i].id = i;
		var->philo[i].nb_left_fork = i;
		var->philo[i].nb_right_fork = (i + 1) % var->nb_philos;
		var->philo[i].var = var;
		var->philo[i].nb_eaten = 0;
		var->philo[i].still_eating = 0;
		var->forks[i] = 0;
		i++;
	}
}

/* Function to initialise the var struct and allocate neccessary memory */
int	init_var(t_var *var)
{
	var->philos = malloc(sizeof(pthread_t) * var->nb_philos);
	if (var->philos == NULL)
		return (print_error("Could not allocate memory."));
	var->forks = malloc(sizeof(int) * var->nb_philos);
	if (var->forks == NULL)
	{
		free(var->philos);
		return (print_error("Could not allocate memory."));
	}
	var->philo = (t_philo *)malloc(sizeof(t_philo) * var->nb_philos);
	if (var->philo == NULL)
	{
		free(var->philos);
		free(var->forks);
		return (print_error("Could not allocate memory."));
	}
	var->died = 0;
	init_philos(var);
	return (0);
}

/* initialise mutexes (locks) for forks, output and death to prevent parallel */
/* usage of the same variable by multiple threads at the same time */
int	init_mutexes(t_var *var)
{
	int	i;

	i = 0;
	var->lock_forks = malloc(sizeof(pthread_mutex_t) * var->nb_philos);
	if (var->lock_forks == NULL)
		return (print_error("Could not malloc pthread_mutexes\n"));
	while (i < var->nb_philos)
	{
		if (pthread_mutex_init(&var->lock_forks[i], NULL) != 0)
			return (print_error("Could not init pthread_mutexes\n"));
		i++;
	}
	if (pthread_mutex_init(&var->lock_output, NULL) != 0
		|| pthread_mutex_init(&var->lock_died, NULL) != 0)
		return (print_error("Could not init pthread_mutexes\n"));
	return (0);
}
