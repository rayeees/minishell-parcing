/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:34:32 by araysse           #+#    #+#             */
/*   Updated: 2022/10/10 11:03:47 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	word_size(char const *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start] && s[start] != c)
	{
		start++;
		len++;
	}
	return (len);
}

void	ft_free_struct(t_cmd **cmd)
{
	int		i;
	t_cmd	*com;
	t_redir	*red;

	while ((*cmd))
	{
		com = (*cmd)->next;
		i = 0;
		while ((*cmd)->cmd[i])
			free((*cmd)->cmd[i++]);
		free((*cmd)->cmd);
		while ((*cmd)->redirection)
		{
			red = (*cmd)->redirection->next;
			free ((*cmd)->redirection->value);
			free ((*cmd)->redirection->type);
			free ((*cmd)->redirection);
			(*cmd)->redirection = red;
		}
		free (*cmd);
		(*cmd) = com;
	}
	free((*cmd));
}

void	increment(t_token **tok1, t_lexer *lexer1, char **env)
{
	(*tok1) = lexer_next(lexer1, env);
	free((*tok1)->value);
	free (*tok1);
}

void	tok1_word(t_redir *redir, t_token *tok1, t_token *token)
{
	redir->value = tok1->value;
	if (token)
	{
		free (token ->value);
		free(token);
	}
}

char	*struct_cmd(t_lexer *lexer, t_token *token, char *str, char **env)
{
	char	*s;

	(void)lexer;
	(void)env;
	if (token->value)
	{
		s = ft_getchar(127);
		str = ft_tstrjoin(str, token->value);
		str = ft_tstrjoin(str, s);
		free(s);
	}
	return (str);
}