
#include "../header.h"
int update_env_pwd(char *new_cwd, t_env_copy *env)
{

	int flag = 0;

	while (env)
	{
		if (ft_strcmp("PWD", env->name) == 0)
		{
			flag = 1;
			free(env->value);
			env->value = strdup(new_cwd);
			return 0;
		}
		env = env->next;
	}
	return 1;
}
int update_env_oldpwd(char *old_cwd, t_env_copy *env)
{
	int flag = 0;

	while (env)
	{
		if (ft_strcmp("OLDPWD", env->name) == 0)
		{
			flag = 1;
			free(env->value);
			env->value = strdup(old_cwd);
			return 0;
		}
		env = env->next;
	}
	return 1;
}
char *get_home_direc(t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp("HOME", env->name) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return NULL;
}
void ft_cd(t_command **cmd, t_env_copy *env)
{

	char new_cwd[MAX_PATH];
	char *old_cwd;
	char *target;
	struct stat check;
	if (!(cmd[0]->args[1]))
	{
		target = get_home_direc(env);
		if (!target)
		{
			fprintf(stderr, "bash: cd: HOME not set\n");
			update_environment(env, "?", "1");
			return;
		}
		if (*target == 0)
		{
			update_environment(env, "?", "0");
			return;
		}
	}
	// else if ((cmd[0]->args[2]) != NULL)
	// {
	// 	fprintf(stderr, "bash: cd: too many arguments\n");
	// 	update_environment(env, "?", "1");
	// 	return;
	// }
	else
		target = cmd[0]->args[1];
	old_cwd = getcwd(NULL, 0);
	if (cmd[0]->args[1])
	{
		if (stat(cmd[0]->args[1], &check) == -1)
		{
			dprintf(2, "bash: cd: %s %s\n", cmd[0]->args[1], strerror(errno)); // change to ft_putstr_fd
			update_environment(env, "?", "1");
			return;
		}
		if (!S_ISDIR(check.st_mode))
		{
			perror("cd:");
			update_environment(env, "?", "1");
			return;
		}
		// free(command_path), command_path = NULL;
	}
	if (chdir(target) != 0)
	{
		dprintf(2, "bash: cd: %s: %s\n", target, strerror(errno));
		free(old_cwd);
		update_environment(env, "?", "1");
		return;
	}
	if (!getcwd(new_cwd, sizeof(new_cwd)))
	{
		perror("bash: cd: getcwd failed");
		free(old_cwd);
		update_environment(env, "?", "1");
		return;
	}
	if (update_env_pwd(new_cwd, env))
	{
		add_to_list_pwd(env, ft_strdup("PWD"), ft_strdup(new_cwd));
	}
	if (update_env_oldpwd(old_cwd, env))
	{
		add_to_list_pwd(env, ft_strdup("OLDPWD"), ft_strdup(old_cwd));
	}
	update_environment(env, "?", "0");
}