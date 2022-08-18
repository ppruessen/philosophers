/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:46:44 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/18 09:08:04 by pprussen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_var
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					rounds;
	pthread_t			*philos;
	struct s_philo		*philo;
	int					*forks;
	long				starttime;
	int					died;
	pthread_mutex_t		lock_forks;
	pthread_mutex_t		lock_output;
	pthread_mutex_t		lock_died;
}	t_var;

typedef struct s_philo
{
	int				id;
	int				nb_left_fork;
	int				nb_right_fork;
	int				nb_eaten;
	long			last_meal;
	long			sleep_start;
	long			time_to_die;
	int				still_eating;
	t_var			*var;
}	t_philo;

/* helpers.c */
long	pp_current_time(void);
long	pp_time_delta(long timestamp);
int		pp_atoi(const char *str);

/* error_clean.c */
int		pp_init_error(char *error_msg);
int		make_clean(t_var *var);

/* init.c */
int		init_var(t_var *var);
void	init_philos(t_var *var);

/* routine.c */
int		get_forks(t_var *var, t_philo *philo);
void	eat(t_var *var, t_philo *philo);
void	*routine(void *args);
int		check_status(t_var *var, t_philo *philo);

/* prints.c */
void	put_messages(t_var *var, t_philo *philo, char *msg);
void	print_status(t_var *var, t_philo *philo);
void	put_fork_message(t_var *var, t_philo *philo);

#endif