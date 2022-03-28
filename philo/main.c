/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:40:26 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/28 17:44:43 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
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

int	main(int argc, char **argv)
{
	t_data			*data;
	int				i;

	i = 0;
	if(ft_check_args(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	init_structures(argc, argv, data);
	while (i < data->number)
	{
		pthread_create(&data->state[i].thread, NULL, func, (void *)(&data->state[i]));
		i++;
	}
	i = 0;
	while (i < data->number)
	{
		pthread_join(data->state[i].thread, NULL);
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
