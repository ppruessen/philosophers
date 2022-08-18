/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:46:29 by mschiman          #+#    #+#             */
/*   Updated: 2022/06/30 16:55:37 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/* Function to initialise the var struct and allocate neccessary memory */
int	init_var(t_var *var)
{
	var->philos = malloc(sizeof(pthread_t) * var->nb_philos);
	if (var->philos == NULL)
		return (pp_init_error("Could not allocate memory."));
	var->forks = malloc(sizeof(int) * var->nb_philos);
	if (var->forks == NULL)
	{
		free(var->philos);
		return (pp_init_error("Could not allocate memory."));
	}
	var->philo = (t_philo *)malloc(sizeof(t_philo) * var->nb_philos);
	if (var->philo == NULL)
	{
		free(var->philos);
		free(var->forks);
		return (pp_init_error("Could not allocate memory."));
	}
	var->died = 0;
	init_philos(var);
	var->starttime = pp_current_time();
	return (0);
}

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
