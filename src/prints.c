/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:46:16 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/18 09:17:52 by pprussen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	put_fork_message(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&var->lock_died);
	if (var->died == 0)
	{
		pthread_mutex_unlock(&var->lock_died);
//		pthread_mutex_lock(&var->lock_output);
//		pthread_mutex_lock(&var->lock_output);
		printf("%.3ld %d has taken a fork\n%.3ld %d has taken a fork\n",
			pp_time_delta(var->starttime), philo->id + 1,
			pp_time_delta(var->starttime), philo->id + 1);
//		printf("%.3ld %d has taken a fork\n",
//			pp_time_delta(var->starttime), philo->id + 1);
//		pthread_mutex_unlock(&var->lock_output);
	}
	else
		pthread_mutex_unlock(&var->lock_died);
}

void	put_messages(t_var *var, t_philo *philo, char *msg)
{
	pthread_mutex_lock(&var->lock_died);
	if (var->died == 0)
	{
//		pthread_mutex_unlock(&var->lock_died);
//		pthread_mutex_lock(&var->lock_output);
		printf("%.3ld %d %s\n",
			pp_time_delta(var->starttime), philo->id + 1, msg);
//		pthread_mutex_unlock(&var->lock_output);
		pthread_mutex_unlock(&var->lock_died);
	}
	else
		pthread_mutex_unlock(&var->lock_died);
}

void	print_status(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&var->lock_died);
	if (var->died == 0)
	{
		pthread_mutex_unlock(&var->lock_died);
//		pthread_mutex_lock(&var->lock_output);
		printf("%.3ld\tID: %d\thas eaten %d times\n",
			pp_time_delta(var->starttime), philo->id + 1, philo->nb_eaten);
//		pthread_mutex_unlock(&var->lock_output);
	}
	else
		pthread_mutex_unlock(&var->lock_died);
}
