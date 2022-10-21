/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:51:26 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/21 15:05:45 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//return 0 if str contain only digit
static int	ft_is_str_digit(char *str)
{
	int	i;

	if (str == NULL)
		return (1);
	i = 0;
	if (str[0] == '-')
		i = 1;
	while (str[i] && ft_isdigit((int)str[i]) == 1)
		i++;
	if (str[i] != '\0')
		return (2);
	return (0);
}

static int	ll_len_limit(void)
{
	long long	pow10;
	int			llmax_len;

	pow10 = LLONG_MAX;
	llmax_len = 0;
	while (pow10 != 0)
	{
		pow10 /= 10;
		llmax_len += 1;
	}
	return (llmax_len + 1);
}

static long long	ft_atoll(char *str)
{
	long long	val;
	int			i;
	long long	pow10;

	i = ft_strlen(str);
	if (i > ll_len_limit())
		return (0);
	pow10 = 1;
	val = 0;
	while (--i >= 0 && str[i] != '-')
	{
		val += (str[i] - '0') * pow10 ;
		pow10 *= 10;
	}
	if (str[i] == '-')
		val *= -1;
	return (val);
}

static int	llstr_modulo_256(char *str)
{
	long long	val;
	int			modulo;

	val = ft_atoll(str);
	modulo = val % 256;
	if (modulo < 0)
		modulo += 256;
	return (modulo);
}

void	builtin_exit(t_ms *ms, t_cmd *cmd)
{
	if (cmd->args[1])
	{
		if (cmd->args[2])
		{
			ms->err_last_child = 1;
			dup2(ms->std_fd[1], 1);
			printf("%s%s%s\n", "ms: ", cmd->args[0], ERR_BUILT_TOOMANYARGS);
		}
		else if (ft_is_str_digit(cmd->args[1]) != 0)
		{
			ms->err_last_child = 255;
			dup2(ms->std_fd[1], 1);
			printf("%s%s%s%s%s\n", "ms: ", cmd->args[0], ": ", cmd->args[1],
				ERR_BUILT_NONNUM);
		}
		else
			ms->err_last_child = llstr_modulo_256(cmd->args[1]);
	}
	if (ms->nb_cmd == 1)
		history_clear_n_exit(ms);
}
