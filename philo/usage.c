/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:28:16 by ysachiko          #+#    #+#             */
/*   Updated: 2022/04/02 18:22:25 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	size_t		i;
	long long	j;
	short		sign;

	i = 0;
	j = 0;
	sign = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (j * 10 + (sign * (str[i] - '0')) < j && sign > 0)
			return (-1);
		if (j * 10 + (sign * (str[i] - '0')) > j && sign < 0)
			return (0);
		j = j * 10 + (sign * (str[i] - '0'));
		i++;
	}
	return (j);
}

// long long		ms;
// 	struct timeval	now;

// 	pthread_mutex_lock(&philo->info->finish_mutex);
// 	gettimeofday(&now, NULL);
// 	ms = time_to_ms(now) - time_to_ms(philo->info->create_at);
// 	if (!philo->info->finish)
// 		printf("%lld\t%d\t %s\n", ms, philo->n + 1, str);
// 	pthread_mutex_unlock(&philo->info->finish_mutex);

int	ft_custom_printf(t_philo *philo, char *s)
{
	struct timeval now;
	long long	ms;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->info->finish_mutex);
	ms = time_to_ms(now) - philo->info->time_start;
	if (!philo->info->finish)
	{
		printf("%lld %d %s\n", ms, philo->num + 1, s);
		pthread_mutex_unlock(&philo->info->finish_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->finish_mutex);
	return (1);
}

long long	time_to_ms(struct timeval first)
{
	long long	tmp;

	tmp = first.tv_sec * 1000 + first.tv_usec / 1000;
	return (tmp);
}
