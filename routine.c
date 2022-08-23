/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:40:16 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/19 13:36:10 by pprussen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	grab_left_fork(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&var->lock_forks[philo->nb_left_fork]);
	if (var->forks[philo->nb_left_fork] == 0)
	{
		var->forks[philo->nb_left_fork] = 1;
		philo->nb_forks++;
		print_status(var, philo, "has taken a fork");
	}
	pthread_mutex_unlock(&var->lock_forks[philo->nb_left_fork]);
}

static void	grab_right_fork(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&var->lock_forks[philo->nb_right_fork]);
	if (var->forks[philo->nb_right_fork] == 0)
	{
		var->forks[philo->nb_right_fork] = 1;
		philo->nb_forks++;
		print_status(var, philo, "has taken a fork");
	}
	pthread_mutex_unlock(&var->lock_forks[philo->nb_right_fork]);
}

static int	get_forks(t_var *var, t_philo *philo)
{
	philo->nb_forks = 0;
	if (philo->nb_eaten == var->rounds && var->rounds != 0)
	{
		philo->still_eating = 1;
		return (-1);
	}
	while (1)
	{
		if (check_status(var, philo) == -1)
			return (-1);
		grab_left_fork(var, philo);
		grab_right_fork(var, philo);
		if (philo->nb_forks == 2)
			return (0);
	}
}

/* add:  print_meal_count(var, philo); in line 72 to see the meal counter*/
static void	eat(t_var *var, t_philo *philo)
{
	print_status(var, philo, "is eating");
	philo->last_meal = pp_current_time();
	philo->time_to_die = philo->last_meal + var->time_to_die;
	usleep (var->time_to_eat * 1000);
	pthread_mutex_lock(&var->lock_forks[philo->nb_left_fork]);
	var->forks[philo->nb_left_fork] = 0;
	pthread_mutex_unlock(&var->lock_forks[philo->nb_left_fork]);
	pthread_mutex_lock(&var->lock_forks[philo->nb_right_fork]);
	var->forks[philo->nb_right_fork] = 0;
	pthread_mutex_unlock(&var->lock_forks[philo->nb_right_fork]);
	philo->nb_eaten++;
	print_status(var, philo, "is sleeping");
	usleep (var->time_to_sleep * 1000);
	print_status(var, philo, "is thinking");
}

void	*routine(void *args)
{
	t_philo	*philo;
	t_var	*var;

	philo = (t_philo *)args;
	var = philo->var;
	philo->starttime = pp_current_time();
	if (philo->nb_eaten == 0)
	{
		if (philo->id % 2 == 1)
			usleep(2000);
		philo->last_meal = philo->starttime;
		philo->time_to_die = philo->last_meal + var->time_to_die;
	}
	while (philo->still_eating == 0)
	{
		if (get_forks(var, philo) == 0)
			eat(var, philo);
		else
			break ;
	}
	return (NULL);
}
