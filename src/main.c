/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:29:37 by pprussen          #+#    #+#             */
/*   Updated: 2022/08/25 16:16:16 by pprussen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/* Checks if all characters in function arguments are digits */
int	pp_is_digit_checker(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

/* Checks if function arguments are correct */
int	input_handler(int argc, char **argv, t_var *var)
{
	if (argc != 5 && argc != 6)
		return (pp_init_error("Wrong number of arguments."));
	if (pp_is_digit_checker(argc, argv) != 0)
		return (pp_init_error("Only (positiv) Numbers allowed."));
	var->nb_philos = pp_atoi(argv[1]);
	if (var->nb_philos > 200 || var->nb_philos < 1)
		return (pp_init_error("More than 200 or less than 1 philosopher(s)."));
	var->time_to_die = pp_atoi(argv[2]);
	if (var->time_to_die < 60)
		return (pp_init_error("Time to die is under 60 miliseconds"));
	var->time_to_eat = pp_atoi(argv[3]);
	if (var->time_to_eat < 60)
		return (pp_init_error("Time to eat is under 60 miliseconds"));
	var->time_to_sleep = pp_atoi(argv[4]);
	if (var->time_to_sleep < 60)
		return (pp_init_error("Time to sleep is under 60 miliseconds"));
	var->rounds = 0;
	if (argc == 6)
	{
		var->rounds = pp_atoi(argv[5]);
		if (var->rounds < 1)
			return (pp_init_error("Philosophers must eat at least one time."));
	}
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
		return (pp_init_error("Could not malloc pthread_mutexes\n"));
	while (i < var->nb_philos)
	{
		if (pthread_mutex_init(&var->lock_forks[i], NULL) != 0)
			return (pp_init_error("Could not init pthread_mutexes\n"));
		i++;
	}
	if (pthread_mutex_init(&var->lock_output, NULL) != 0
		|| pthread_mutex_init(&var->lock_died, NULL) != 0)
		return (pp_init_error("Could not init pthread_mutexes\n"));
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
			return (pp_init_error("Could not destroy pthread_mutexes\n"));
		i++;
	}
	if (pthread_mutex_destroy(&var->lock_output) != 0
		|| pthread_mutex_destroy(&var->lock_died) != 0)
		return (pp_init_error("Could not destroy pthread_mutexes\n"));
	free(var->lock_forks);
	free(var->philos);
	free(var->philo);
	free(var->forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var		var;
	int			i;

	if (input_handler(argc, argv, &var) == -1)
		return (-1);
	if (init_var(&var) == -1)
		return (-1);
	if (init_mutexes(&var) != 0)
		return (-1);
	i = 0;
	while (i < var.nb_philos)
	{
		if (pthread_create(&var.philos[i], NULL, &routine, &var.philo[i]) != 0)
			return (pp_init_error("Could not create threads\n"));
		i++;
	}
	i = 0;
	while (i < var.nb_philos)
	{
		if (pthread_join(var.philos[i], NULL) != 0)
			return (pp_init_error("Could not create pthread_joins\n"));
		i++;
	}
	destroy_and_free(&var);
	return (0);
}
