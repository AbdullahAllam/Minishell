/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:07:58 by cclaude           #+#    #+#             */
/*   Updated: 2024/01/07 21:06:39 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (s1 && s2)
	{
		i = 0;
		j = 0;
		ptr = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
		if (!ptr)
			return (NULL);
		while ((char)s1[i])
		{
			ptr[i] = (char)s1[i];
			i++;
		}
		while ((char)s2[j])
		{
			ptr[i + j] = (char)s2[j];
			j++;
		}
		ptr[i + j] = '\0';
		return (ptr);
	}
	return (NULL);
}
