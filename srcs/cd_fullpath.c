#include "minishell_sikeda.h"

static int
	make_current_path_list(t_list **path_list)
{
	char	**split;
	size_t	i;

	split = ft_split(g_pwd, '/');
	if (!split)
		return (UTIL_ERROR);
	*path_list = NULL;
	i = 0;
	while (split[i])
	{
		if (!ft_strcmp(split[i], ".."))
			ft_lstdelend(path_list, free);
		else if (!ft_strcmp(split[i], "."))
			;
		else if (ft_lstnew_and_lstadd_back(path_list, split[i]) == UTIL_ERROR)
			break ;
		i++;

	}
	ft_free_split(&split);
	if (0 < i && !*path_list)
		return (UTIL_ERROR);
	return (UTIL_SUCCESS);
}

static char
	*generate_path(const t_list *path_list)
{
	char	*path;
	char	*tmp;

	if (!path_list)
		path = ft_strdup("/");
	else
	{
		tmp = ft_strdup("");
		if (!tmp)
			return (NULL);
		while (path_list)
		{
			path = ft_join_path(tmp, path_list->content);
			ft_free(&tmp);
			if (!path)
				return (NULL);
			tmp = path;
			path_list = path_list->next;
		}
	}
	return (path);
}

static int
	make_path_list(t_list **path_list,
		const char *input_path, char **input_split, size_t *i)
{
	*path_list = NULL;
	*i = 0;
	if (input_path && *input_path == '/')
	{
		while (input_split[*i])
		{
			if (ft_strcmp(input_split[*i], "..")
				&& ft_strcmp(input_split[*i], "."))
			{
				if (ft_lstnew_and_lstadd_back(path_list, input_split[(*i)++])
					== UTIL_ERROR)
					ft_free_split_and_return_int(&input_split, UTIL_ERROR);
			}
			else
				break ;
		}
	}
	else if (make_current_path_list(path_list) == UTIL_ERROR)
		ft_free_split_and_return_int(&input_split, UTIL_ERROR);
	return (UTIL_SUCCESS);
}

static char
	*add_slash_to_front(const char *input_path, char **full_path)
{
	char	*tmp;

	if (2 <= ft_strlen(input_path)
		&& !ft_strncmp(input_path, "//", 2)
		&& input_path[2] != '/')
	{
		tmp = ft_join_path("", *full_path);
		ft_free(full_path);
		if (!tmp)
			return (NULL);
		*full_path = tmp;
	}
	return (*full_path);
}

char
	*ft_make_full_path(const char *input_path)
{
	char	*full_path;
	char	**input_split;
	t_list	*path_list;
	size_t	i;

	input_split = ft_split(input_path, '/');
	if (!input_split || make_path_list(&path_list, input_path, input_split, &i)
		== UTIL_ERROR)
		return (NULL);
	while (input_split[i])
	{
		if (!ft_strcmp(input_split[i], ".."))
			ft_lstdelend(&path_list, free);
		else if (!ft_strcmp(input_split[i], "."))
			;
		else if (ft_lstnew_and_lstadd_back(&path_list, input_split[i])
			== UTIL_ERROR)
			ft_free_split_and_return_str(&input_split, NULL);
		i++;
	}
	ft_free_split(&input_split);
	full_path = generate_path(path_list);
	ft_lstclear(&path_list, free);
	return (add_slash_to_front(input_path, &full_path));
}
