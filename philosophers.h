/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:12:17 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/23 13:15:31 by pprussen         ###   ########.fr       */
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
	pthread_mutex_t		*lock_forks;
	pthread_mutex_t		lock_output;
	pthread_mutex_t		lock_died;
}	t_var;

typedef struct s_philo
{
	long			starttime;
	int				id;
	int				nb_left_fork;
	int				nb_right_fork;
	int				nb_forks;
	int				nb_eaten;
	long			last_meal;
	long			time_to_die;
	int				still_eating;
	t_var			*var;
}	t_philo;

/* init.c */
void	init_philos(t_var *var);
int		init_var(t_var *var);
int		init_mutexes(t_var *var);

/*check_status.c */
int		check_status(t_var *var, t_philo *philo);

/* helpers.c */
long	pp_current_time(void);
long	pp_time_delta(long timestamp);
int		pp_atoi(const char *str);

/* routine.c */
void	*routine(void *args);

/* print.c */
int		print_error(char *error_msg);
void	print_status(t_var *var, t_philo *philo, char *msg);
void	print_meal_count(t_var *var, t_philo *philo);

/* ft_putnbr_fd.c */
void	ft_putnbr_fd(int n, int fd);

#endif