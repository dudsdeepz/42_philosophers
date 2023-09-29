/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:50:03 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/20 16:04:42 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		++i;
	}
	return (result * sign);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && str[i])
			++i;
		else
			return (0);
	}
	return (1);
}

t_status	*status(void)
{
	static t_status	status;

	return (&status);
}

long long	gettime(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
		return (0);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&status()->philo->print);
	if (check_things(philo))
	{
		pthread_mutex_unlock(&status()->philo->print);
		return ;
	}
	pthread_mutex_lock(&status()->philo->time);
	printf("%s%lli %s%i %s %s\n", YELLOW, (gettime() - status()->starting_time) \
		, RED, philo->num, DEFAULT, str);
	pthread_mutex_unlock(&status()->philo->time);
	pthread_mutex_unlock(&status()->philo->print);
	return ;
}
