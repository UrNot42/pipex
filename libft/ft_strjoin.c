/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:27:15 by ulevallo          #+#    #+#             */
/*   Updated: 2023/09/25 17:30:42 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*snew;
	int		i;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	snew = malloc(len * sizeof(char));
	if (!snew)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		snew[i] = s1[i];
		i++;
	}
	len = 0;
	while (s2[len])
	{
		snew[i] = s2[len];
		i++;
		len++;
	}
	snew[i] = '\0';
	return (snew);
}
