/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/07 16:19:45 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_philo(t_philo *philo)
{
    
	if (philo->status->number_of_philosophers == 1)
	{
		print_action(philo, "has taken a fork");
		print_action(philo, "has died");
		return ;
	}
	while (1)
	{
		if (forks(philo, 1))
            return ;
		if (eating(philo))
            return ;
		if (forks(philo, 0))
            return ;
	    if (sleeping(philo))
            return ;
	}
	return ;
}

int eating(t_philo *philo)
{
    if (check_dead(philo))
        return (1);
    print_action(philo, "is eating");
    pthread_mutex_lock(&philo->food);
    philo->last_meal = gettime();
    philo->eat_count++;
    pthread_mutex_unlock(&philo->food);
    wait(philo, philo->status->time_to_eat);
    return (0);
}
int sleeping(t_philo *philo)
{
    if (check_dead(philo))
        return (1);
    print_action(philo, "is sleeping");
    wait(philo, philo->status->time_to_sleep);
    print_action(philo, "is thinking");
    return (0);
}


int forks(t_philo *philo, int stats)
{
    if (check_dead(philo))
        return (1);
    if (stats)
    {  
        if (philo->num % 2 == 0)
        {
            pthread_mutex_lock(&philo->fork_right);
            print_action(philo, "has taken a fork");
            pthread_mutex_lock(philo->fork_left);
            print_action(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(philo->fork_left);
            print_action(philo, "has taken a fork");
            pthread_mutex_lock(&philo->fork_right);
            print_action(philo, "has taken a fork");
        }
    }
    else if (!stats)
    {
        pthread_mutex_unlock(&philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
    }
    return (0);
}

void wait(t_philo *philo, time_t time)
{
    time_t start;
    time_t current;

    start = gettime();
    usleep(time);
    while (1)
    {
		pthread_mutex_lock(&philo->life);
		if (philo->is_dead)
		{
			pthread_mutex_unlock(&philo->life);
			return ;
		}
		pthread_mutex_unlock(&philo->life);
        current = gettime();
        if (current - start >= time)
            break ;
    }
}

long long gettime(void)
{
    struct timeval current_time;

    if (gettimeofday(&current_time, NULL) < 0)
        return (0);
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void print_action(t_philo *philo, char *str)
{
    check_dead(philo);
    pthread_mutex_lock(&philo->life);
    printf("%s%lli %s%i %s %s\n", YELLOW, (gettime() - philo->status->starting_time)
    , RED, philo->num, DEFAULT, str);
    pthread_mutex_unlock(&philo->life);
}

void free_all(t_philo *philo)
{
    int i;

    i = -1;
    while (++i < philo->status->number_of_philosophers)
    {
        pthread_mutex_destroy(&philo[i].fork_right);
    }
    pthread_mutex_destroy(&philo->food);
    pthread_mutex_destroy(&philo->life);
    if (philo)
        free(philo);
    philo = NULL;
}

int check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->life);
    if(gettime() - philo->last_meal >= philo->status->time_to_die)    
	{
		philo->is_dead = 1;
		printf("%s%lli %s%i %s %s\n", YELLOW, (gettime() - philo->status->starting_time)
    	, RED, philo->num, DEFAULT, "is dead");
        pthread_mutex_unlock(&philo->life);
        return (philo->is_dead);
	}
	pthread_mutex_unlock(&philo->life);
	return (philo->is_dead);
}
