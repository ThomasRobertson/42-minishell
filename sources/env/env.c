/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:36 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:36:36 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env(t_mini *mini, char **env)
{
	t_list	*env1;
	t_list	*env2;
	int		i;

	env1 = malloc(sizeof(t_list));
	env1->content = ft_strdup(env[0]);
	env1->next = NULL;
	mini->env = env1;
	i = 1;
	while (env && env[i])
	{
		env2 = malloc(sizeof(t_list));
		env2->content = ft_strdup(env[i]);
		env2->next = NULL;
		env1->next = env2;
		env1 = env2;
		i++;
	}
	return (0);
}

t_list	*set_export(char *value)
{
	t_list	*new_export;

	new_export = malloc(sizeof(t_list));
	if (value == NULL)
		new_export->content = NULL;
	else
		new_export->content = ft_strdup(value);
	new_export->next = NULL;
	return (new_export);
}

char	*check_env(char *line)
{
	char	*replace;
	int		i;

	replace = malloc(sizeof(char) + (ft_strlen(line) + 1));
	i = 0;
	while (line[i])
	{
		if (!ft_isascii(line[i]))
			replace[i] = '$';
		else
			replace[i] = line[i];
		i++;
	}
	replace[i] = '\0';
	free(line);
	return (replace);
}

char	*name_env(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUF_SIZE
		&& src[i] != ' ')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
