/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:40:26 by ysachiko          #+#    #+#             */
/*   Updated: 2022/04/02 18:54:36 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->info->finish_mutex);
	while (i < data->number)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

int	ft_isdigit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	else
		return (0);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	long long	ms;
	struct timeval now;

	philo = arg;
	while(1)
	{
		usleep(1100);
		pthread_mutex_lock(&philo->check_mutex);
		pthread_mutex_lock(&philo->info->finish_mutex);
		// printf("%d\n", philo->num);
		if (philo->info->finish)
		{
			pthread_mutex_unlock(&philo->info->finish_mutex);
			pthread_mutex_unlock(&philo->check_mutex);
			return ((void*)0);
		}
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - philo->last_time_eat; // 1
		gettimeofday(&now, NULL);
		if (ms >= philo->info->time_die && philo->info->finish == 0)
		{
			philo->info->finish = 1;
			pthread_mutex_unlock(philo->right_fork_m);
			pthread_mutex_unlock(philo->left_fork_m);
			printf("%lld %d %s\n", ms, philo->num + 1, "died");
			pthread_mutex_unlock(&philo->info->finish_mutex);
			pthread_mutex_unlock(&philo->check_mutex);
			// pthread_mutex_destroy(&philo->info->finish_mutex);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->info->finish_mutex);
		pthread_mutex_unlock(&philo->check_mutex);
	}
}


void	create_philo(t_data *data)
{
	int			i;
	struct timeval	tv;
	pthread_t	thread;

	i = 0;
	gettimeofday(&tv, NULL);
	data->info->time_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (i < data->number)
	{
		data->state[i].last_time_eat = data->info->time_start;
		pthread_create(&data->state[i].thread, NULL, func, (void *)(&data->state[i]));
		pthread_create(&thread, NULL, monitor, (void *)(&data->state[i]));
		pthread_detach(thread);
		i++;
	}

	// if (data->info->number_of_times != 0)
	// {
	// 	pthread_create(thread, NULL, monitor_of_eats, (void *)(&data->info));
	// 	pthread_detach(thread);
	// }
}

int	main(int argc, char **argv)
{
	t_data			*data;
	int				i;

	i = 0;
	if(ft_check_args(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	init_structures(argc, argv, data);
	create_philo(data);
	i = 0;
	while (i < data->number)
	{
		pthread_join(data->state[i].thread, NULL);
		// pthread_mutex_destroy(&data->state[i++].check_mutex);
		i++;
	}

	// printf("numbers of philo = %d\n", data->number);
	// printf("t_die of philo = %d\n", data->time_die);
	// printf("t_eat of philo = %d\n", data->time_eat);
	// printf("t_sleep of philo = %d\n", data->time_sleep);
	// printf("number_of_times_each_philosopher_must_eat = %d\n", data->number_of_times);
	// printf("forks: = %d\n", data->forks); //CHECHS FOR VALUE
	destroy_mutex(data);
	// free(data->array_number_of_times);
	free(data->info);
	free(data->forks);
	free(data->state);
	free(data);
}
