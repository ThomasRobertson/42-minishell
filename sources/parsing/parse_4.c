/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:25 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:37:25 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char *line, int i)
{
	int	j;
	int	k;
	int	l;

	j = 0;
	l = 0;
	k = 0;
	while (line[i] && j < i)
	{
		if (line[j] == '\'' && k == 0 && l == 0)
			k = 1;
		else if (line[j] == '\'' && k == 1 && l == 0)
			k = 0;
		else if (line[j] == '\"' && l == 0 && k == 0)
			l = 1;
		else if (line[j] == '\"' && l == 1 && k == 0)
			l = 0;
		j++;
	}
	if (k == 1)
		return (0);
	return (1);
}

// static char	*echo_env(char *line, char *test, int i)
// {
// 	int	k;
// 	int	j;
// 	int	space;

// 	k = 0;
// 	j = 0;
// 	space = 0;
// 	test = malloc(sizeof(char) + (ft_strlen(line) - 1));
// 	while (line[k] && space != i)
// 	{
// 		k++;
// 		if (line[k] == ' ' || line[k] == '$')
// 		{
// 			while (line[k] != '$')
// 				k++;
// 			space++;
// 		}
// 	}
// 	return (echo_test(line, k, j, test));
// }

char	find_next_line(t_list *env, char *line, t_mini *mini, int i)
{
	char	*test;

	test = NULL;
	// mini->echo += 1;
	mini->check = 1;
	// if (ft_strncmp(line, "echo", 4) == 0)
	// 	test = echo_env(line, test, mini->echo);
	// else
	test = copy_line(line, test, 1, 0);
	while (env && env->content)
	{
		if (ft_strncmp(test, env->content, ft_strlen(test)) == 0)
		{
			mini->check = 1;
			ft_strdel(&test);
			return ((char)(-line[i++]));
		}
		env = env->next;
	}
	ft_strdel(&test);
	if (quote_check(line, i))
		return (-line[i]);
	return (line[i]);
}

char	*line_test(char *new, int j, char *line)
{
	new[j] = '\0';
	ft_strdel(&line);
	return (new);
}

char	if_dollar(char *line, int i, t_mini *mini)
{
	// mini->echo += 1;
	mini->check = 1;
	return ((char)(-line[i++]));
}
