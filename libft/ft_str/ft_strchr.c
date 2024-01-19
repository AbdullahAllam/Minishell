/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:14:19 by cclaude           #+#    #+#             */
/*   Updated: 2024/01/15 22:11:35 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	to_find;

	i = 0;
	if (s == NULL)
		return (NULL);
	to_find = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == to_find)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == to_find)
		return ((char *) &s[i]);
	return (NULL);
}
