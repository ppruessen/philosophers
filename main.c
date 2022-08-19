/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:29:37 by pprussen          #+#    #+#             */
/*   Updated: 2022/08/14 12:41:02 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Checks if function arguments are correct (in a solvable way). 8000ms is */
/* upper limit that the simulation doesn't take forever. */
static int	input_check(int argc, char **argv, t_var *var)
{
	if (argc != 5 && argc != 6)
		return (print_error("Wrong number of arguments."));
	var->nb_philos = pp_atoi(argv[1]);
	if (var->nb_philos > 200 || var->nb_philos < 1)
		return (print_error("More than 200 or less than 1 philosopher(s)."));
	var->time_to_die = pp_atoi(argv[2]);
	if (var->time_to_die < 60 || var->time_to_die > 8000)
		return (print_error("Time to die is under 60ms or above 8000ms"));
	var->time_to_eat = pp_atoi(argv[3]);
	if (var->time_to_eat < 60 || var->time_to_eat > 8000)
		return (print_error("Time to eat is under 60ms or above 8000ms"));
	var->time_to_sleep = pp_atoi(argv[4]);
	if (var->time_to_sleep < 60 || var->time_to_sleep > 8000)
		return (print_error("Time to sleep is under 60ms or above 8000ms"));
	var->rounds = 0;
	if (argc == 6)
	{
		var->rounds = pp_atoi(argv[5]);
		if (var->rounds < 1)
			return (print_error("Philosophers must eat at least one time."));
	}
	return (0);
}

/* Detroys the mutexes and frees allocated memory. */
static int	destroy_and_free(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philos)
	{
		if (pthread_mutex_destroy(&var->lock_forks[i]) != 0)
			return (print_error("Could not destroy pthread_mutexes\n"));
		i++;
	}
	if (pthread_mutex_destroy(&var->lock_output) != 0
		|| pthread_mutex_destroy(&var->lock_died) != 0)
		return (print_error("Could not destroy pthread_mutexes\n"));
	free(var->lock_forks);
	free(var->philos);
	free(var->philo);
	free(var->forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		i;

	if (input_check(argc, argv, &var) == -1)
		return (-1);
	if (init_var(&var) == -1)
		return (-1);
	if (init_mutexes(&var) != 0)
		return (-1);
	i = 0;
	while (i < var.nb_philos)
	{
		if (pthread_create(&var.philos[i], NULL, &routine, &var.philo[i]) != 0)
			return (print_error("Could not create threads.\n"));
		i++;
	}
	i = 0;
	while (i < var.nb_philos)
	{
		if (pthread_join(var.philos[i], NULL) != 0)
			return (print_error("Could not join threads.\n"));
		i++;
	}
	destroy_and_free(&var);
	return (0);
}
