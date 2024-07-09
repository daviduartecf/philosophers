/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:39:36 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/29 09:49:53 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i ++;
	}
	return (s);
}

/* #include <stdio.h>
int	main()
{
	char string[] = "abcde";
	size_t	n = 2;
	int	c = 129;
	int	i = 0;

	printf("%s \n", string);
	ft_memset(string, c, n);
	printf("%s", string);
} */
