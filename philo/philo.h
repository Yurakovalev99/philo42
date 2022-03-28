/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:37:56 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/28 18:01:59 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				finish;
	int				number_of_times;
}	t_info;

typedef struct s_philo
{
	int				num;
	int				num_of_eats;
	id_t			finish;
	int				left;
	int				right;
	pthread_t		thread;
	pthread_mutex_t	*left_fork_m;
	pthread_mutex_t	*right_fork_m;
	pthread_mutex_t	*finish_m;
	t_info			*info;
	long long		last_time_eat;
	long long		time;
	long long		time_start;
	long long		last_after_eat;
}	t_philo;

typedef struct s_data
{
	int				number;
	pthread_mutex_t	finish_m;
	t_philo			*state;
	pthread_mutex_t	*forks;
	t_info			*info;
}	t_data;

int			ft_atoi(const char *str);
void		ft_sleep(long long	time);
void		ft_custom_printf(t_philo *philo, char *s);
long long	time_to_ms(struct timeval first);
int			take_forks(t_philo *philo);
void		eating(t_philo *philo);
void		thinking(t_philo *philo);
void		sleeping(t_philo *philo);
void		*func(void *arg);

void		init_structures(int argc, char **argv, t_data *data);
void		philo_fill(t_philo *state, t_data *data);
void		parse(int argc, char **argv, t_data *data);

# endif
