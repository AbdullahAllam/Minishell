/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:46:22 by cclaude           #+#    #+#             */
/*   Updated: 2024/01/07 21:08:39 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	check_sepp(char a, char c)
{
	if (c == a)
		return (1);
	if (a == '\0')
		return (1);
	return (0);
}

int
	count_wd(char *strarray, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (strarray[i])
	{
		if (check_sepp(strarray[i + 1], c) == 1
			&& check_sepp(strarray[i], c) == 0)
			count++;
		i++;
	}
	return (count);
}

void
	copy_wd(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (check_sepp(src[i], c) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void
	ft_write(char **result, char *strarray, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (strarray[i])
	{
		if (check_sepp(strarray[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (check_sepp(strarray[i + j], c) == 0)
				j++;
			result[count] = (char *)malloc(sizeof(char) * (j + 1));
			copy_wd(result[count], strarray + i, c);
			i = i + j;
			count++;
		}
	}
}

char
	**ft_split(char const *s, char c)
{
	int		count;
	char	*ptr;
	char	**result;

	if (!s)
		return (0);
	ptr = (char *) s;
	count = count_wd(ptr, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result[count] = 0;
	ft_write(result, ptr, c);
	return (result);
}
