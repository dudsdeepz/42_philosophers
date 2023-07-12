/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:40:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/12 18:39:15 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	t_philo philos;

	if (ac < 5 || ac > 6)
    {
        printf("%s./philo %s[%snum of philosophers%s]%s", RED, GREEN, YELLOW, GREEN, DEFAULT);
        printf("%s[%stime to die%s]%s", GREEN, YELLOW, GREEN,DEFAULT);
        printf("%s[%stime to eat%s]%s", GREEN, YELLOW, GREEN,DEFAULT);
        printf("%s[%stime to sleep%s]%s", GREEN, YELLOW, GREEN,DEFAULT);
        printf("%s[%snumber of times each philosopher must eat%s]%s\n", GREEN, YELLOW, GREEN,DEFAULT);
        return (0);
    }
    if (default_times(av))
        philo(&philos);
    else
        return (printf("\033[1;31mError not a number!\033[1;0m\n"));
}

int default_times(char **av)
{
    if (check_digit(av[1]))
        status()->number_of_philosophers = ft_atoi(av[1]);
    else
        return (0);
    if (check_digit(av[2]))
        status()->time_to_die = ft_atoi(av[2]);
    else
        return (0);
    if (check_digit(av[3]))
        status()->time_to_eat = ft_atoi(av[3]);
    else
        return (0);
    if (check_digit(av[4]))
        status()->time_to_sleep = ft_atoi(av[4]);
    else {
        return (0);
    }
   	status()->number_of_times_each_philosopher_must_eat = -1;
    if (av[5])
    {
        if (check_digit(av[5]))
            status()->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
        else
            return (0);
    }
    return (1);
}
