/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:58:36 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 17:58:40 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	inside_charset(char c)
{
	char	*charset;
	int		i;

	charset = "|><";
	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	find_token_end(const char *str, int start, 
	int *single_quote, int *double_quote)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == '\'' && !*double_quote)
			*single_quote = !*single_quote;
		else if (str[i] == '\"' && !*single_quote)
			*double_quote = !*double_quote;
		if ((!*single_quote && !*double_quote) && inside_charset(str[i]))
			break ;
		i++;
	}
	return (i);
}

int	count_words(const char *str)
{
	int	i;
	int	count;
	int	single_qoute;
	int	double_qoute;

	single_qoute = ((i = 0), (double_qoute = 0), (count = 0), 0);
	while (str[i])
	{
		if ((!single_qoute && !double_qoute) && inside_charset(str[i]))
		{
			if ((str[i] == '>' && str[i + 1] == '>') || 
				(str[i] == '<' && str[i + 1] == '<'))
				i++;
			i++;
			count++;
			continue ;
		}
		i = find_token_end(str, i, &single_qoute, &double_qoute);
		count++;
	}
	return (count);
}
