/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:23:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/03 19:04:08 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}
// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d", ft_isprint(0x1));
// 	return (0);
// }