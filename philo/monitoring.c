/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 14:21:35 by chorse            #+#    #+#             */
/*   Updated: 2022/04/19 15:26:45 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	time_of_finish(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->time);
	time = ft_time();

	if (time - philo->start_eat > philo->time_die)
	{
		if (philo->time_start == 0 && time % 1000 < philo->time_die)
		{
			pthread_mutex_unlock(philo->time);
			return (0);
		}
		pthread_mutex_unlock(philo->time);
		return (time);
	}
	pthread_mutex_unlock(philo->time);
	return (0);
}

static void	kill_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		pthread_detach(data->thread[i]);
		i++;
	}
}

static void	destroy_mt(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->print);
	pthread_mutex_destroy(data->time);
	free(data->philo);
	free(data->forks);
	free(data->time);
	free(data->print);
	free(data->thread);
}

void	*moni(void *arg)
{
	int i;
	long time;
	t_data	*data;

	i = 0;
	data = arg;
	usleep(3000);
	while (1)
	{
		usleep(500);
		pthread_mutex_lock(&data->philo[i].num_times);
		if (data->philo[i].number_of_times == 0)
		{
			kill_philo(data);
			destroy_mt(data);
			pthread_mutex_unlock(&data->philo[i].num_times);
			break ;
		}
		time = time_of_finish(&data->philo[i]);
		if (time > 0)
		{
			pthread_mutex_lock(data->print);
			printf("%lld %d died\n", \
			time - data->philo[i].time_start, data->philo[i].id);
			kill_philo(data);
			destroy_mt(data);
			break ;
		}
		pthread_mutex_unlock(&data->philo[i].num_times);
		i++;
		if (i == data->number)
			i = 0;
	}
	return (NULL);
}

