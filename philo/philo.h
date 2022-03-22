/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:37:56 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/22 19:17:52 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num;
	int				hungry;
	int				eating;
	int 			thinking;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				left;
	int				right;
	int				number_of_times;
	int				*array_of_eats;
	pthread_t		thread;
	pthread_mutex_t	left_fork_m;
	pthread_mutex_t	right_fork_m;
	struct timeval	last_time_eat;
}	t_philo;

typedef struct s_data
{
	int				number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				number_of_times;
	int				*array_number_of_times;
	t_philo 		*state;
	pthread_mutex_t	*forks;
}	t_data;

int	ft_atoi(const char *str);

# endif
