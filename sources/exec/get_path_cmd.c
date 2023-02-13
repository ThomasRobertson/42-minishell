/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:27:26 by troberts          #+#    #+#             */
/*   Updated: 2023/02/13 20:53:23 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_cmd_path(char *path_env, char *cmd_name)
{
	char	*path_cmd;
	char	*path_cmd_tmp;

	if (path_env == NULL)
		return (NULL);
	path_cmd_tmp = ft_strjoin(ft_strchr(path_env, '/'), "/");
	if (path_cmd_tmp == NULL)
	{
		perror("generate_cmd_path: Malloc return NULL");
		return (NULL);
	}
	path_cmd = ft_strjoin(path_cmd_tmp, cmd_name);
	free(path_cmd_tmp);
	return (path_cmd);
}

// t_cmd	*clean_error(t_cmd *cmd, t_bool display_message,
// 								t_bool return_null)
// {
// 	if (display_message)
// 		ft_printf("bash: %s: command not found\n", cmd->cmd_name);
// 	if (return_null == true)
// 	{
// 		free_cmd(cmd);
// 		return (NULL);
// 	}
// 	else
// 	{
// 		cmd->path = NULL;
// 		return (cmd);
// 	}
// }

int	test_correct_access_cmd(char *cmd_name, char **path_env,
			char **cmd_path)
{
	int		i;

	(*cmd_path) = ft_strdup(cmd_name);
	if ((*cmd_path) == NULL)
		return (RETURN_FAILURE);
	if (ft_strchr((*cmd_path), '/'))
		return (RETURN_SUCCESS);
	free((*cmd_path));
	i = 0;
	while (path_env[i])
	{
		(*cmd_path) = generate_cmd_path(path_env[i], cmd_name);
		if ((*cmd_path) == NULL)
			return (RETURN_FAILURE);
		if (access((*cmd_path), F_OK | X_OK) == 0)
			break ;
		free((*cmd_path));
		i++;
	}
	if (path_env[i] == NULL)
	{
		(*cmd_path) = NULL;
		return (CMD_NOT_FOUND);
	}
	return (RETURN_SUCCESS);
}

int	get_path_of_cmd(char *cmd_name, char **envp, char **cmd_path)
{
	int		i;
	char	**path_env;
	int		return_code;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path_env = ft_split(envp[i], ':');
	if (path_env == NULL)
		return (RETURN_FAILURE);
	return_code = test_correct_access_cmd(cmd_name, path_env, cmd_path);
	ft_free_double_ptr(path_env);
	return (return_code);
}
