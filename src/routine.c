/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:46:51 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/18 09:24:18 by pprussen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	check_status(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&var->lock_died);
	if (var->died != 0)
	{
		pthread_mutex_unlock(&var->lock_died);
		return (-1);
	}
	pthread_mutex_unlock(&var->lock_died);
	if (philo->last_meal && pp_current_time() > philo->time_to_die)
	{
		put_messages(var, philo, "died");
		pthread_mutex_lock(&var->lock_died);
		var->died++;
		pthread_mutex_unlock(&var->lock_died);
		return (-1);
	}
	return (0);
}

int	get_forks(t_var *var, t_philo *philo)
{
	if (philo->nb_eaten == var->rounds && var->rounds != 0)
	{
		philo->still_eating = 1;
		return (-1);
	}
	while (1)
	{
		if (check_status(var, philo) == -1)
			return (-1);
		pthread_mutex_lock(&var->lock_forks);
		if (var->forks[philo->nb_left_fork] == 0
			&& var->forks[philo->nb_right_fork] == 0)
		{
			var->forks[philo->nb_left_fork] = 1;
			var->forks[philo->nb_right_fork] = 1;
			pthread_mutex_unlock(&var->lock_forks);
			put_fork_message(var, philo);
//			put_messages(var, philo, "has taken a fork");
//			put_messages(var, philo, "has taken a fork");
			return (0);
		}
		pthread_mutex_unlock(&var->lock_forks);
		usleep(5);
	}
}

void	eat(t_var *var, t_philo *philo)
{
	put_messages(var, philo, "is eating");
	philo->last_meal = pp_current_time();
	philo->time_to_die = philo->last_meal + var->time_to_die;
	while (pp_current_time() <= philo->last_meal + var->time_to_eat)
	{
		if (check_status(var, philo) == -1)
			break ;
		usleep(50);
	}
	philo->nb_eaten++;
	print_status(var, philo);
	pthread_mutex_lock(&var->lock_forks);
	var->forks[philo->nb_left_fork] = 0;
	var->forks[philo->nb_right_fork] = 0;
	pthread_mutex_unlock(&var->lock_forks);
	put_messages(var, philo, "is sleeping");
	philo->sleep_start = pp_current_time();
	while (pp_current_time() <= philo->sleep_start + var->time_to_sleep)
	{
		if (check_status(var, philo) == -1)
			break ;
		usleep(50);
	}
	put_messages(var, philo, "is thinking");
}

static void	*single_philo(t_var *var, t_philo *philo)
{
	long	start_time;

	start_time = pp_current_time();
	put_messages(var, philo, "has taken a fork");
	while (pp_current_time() < start_time + var->time_to_die)
		usleep(50);
	put_messages(var, philo, "died");
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;
	t_var	*var;

	philo = (t_philo *)args;
	var = philo->var;
	if (var->nb_philos == 1)
		return (single_philo(var, philo));
	if (philo->nb_eaten == 0)
	{
		philo->last_meal = var->starttime;
		philo->time_to_die = var->starttime + var->time_to_die;
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
