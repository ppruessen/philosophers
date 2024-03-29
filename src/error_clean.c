/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:05:06 by pprussen          #+#    #+#             */
/*   Updated: 2022/08/25 16:16:56 by pprussen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	pp_init_error(char *error_msg)
{
	printf("Error: %s\n", error_msg);
	return (-1);
}
/*
int	make_clean(t_var *var)
{
	if (pthread_mutex_destroy(&var->lock_forks) != 0
		|| pthread_mutex_destroy(&var->lock_output) != 0
		|| pthread_mutex_destroy(&var->lock_died) != 0)
		return (pp_init_error("Could not destroy pthread_mutexes\n"));
	free(var->philos);
	free(var->philo);
	free(var->forks);
	return (0);
}
*/