#ifdef linux
#include <stdio.h>
#include <string.h>
#include <commands.h>
#include <malloc.h>
#endif

#ifndef linux
#include <stdio.h>
#endif

#define DEFINE_COMMAND(COMMAND, ARGC, ALIAS) { #COMMAND, (void (*)(void)) &COMMAND ## _command, ARGC, #ALIAS}


struct command {
	char *c_name;
	void (*c_exec) (void);
	int c_argc;
	char *c_alias;
};


// Available commands.
struct command commands[] =
{
	DEFINE_COMMAND(available_amount,	  0, aam),
	DEFINE_COMMAND(available_category_amount, 1, acm),
	DEFINE_COMMAND(set_budget,		  1, sbt),
	DEFINE_COMMAND(change_budget,		  1, cbt),
	DEFINE_COMMAND(add_category,		  2, ac ),
	DEFINE_COMMAND(delete_category,		  1, dc ),
	DEFINE_COMMAND(show_statistics,		  0, st ),
	DEFINE_COMMAND(show_prefered_daily_spend, 0, spd),
	DEFINE_COMMAND(show_future_spend,   	  0, sfs),
	DEFINE_COMMAND(show_categories,		  0, scs),
	DEFINE_COMMAND(show_category,		  1, sc ),
	DEFINE_COMMAND(show_merchant,		  1, sm ),
	DEFINE_COMMAND(show_merchants,		  0, sms),
	DEFINE_COMMAND(show_all_expenses,	  2, sae),
	DEFINE_COMMAND(add_expenses,		  3, aes),
	DEFINE_COMMAND(help,			  0, h  ),
	DEFINE_COMMAND(associate_merchant,   	  2, amt),
	{.c_name = NULL}
};


static inline char *replace_with_underscores(const char *c_name)
{
	char *tmp = calloc(strlen(c_name) + 1, sizeof(char));
	if (tmp == NULL) return NULL;
	
	strcpy(tmp, c_name);
	char *curr_minus = strstr(tmp, "-");
	for (int i = 0; curr_minus; i++)
	{
		*curr_minus = '_';
		curr_minus = strstr(tmp, "-");
	}
	return tmp;
}

/**
 * Finds the command the has been requested.
 * @param c_name The name of the requested command.
 * @return an number witch refers to the array of commands on success.
 * On error -1 is returned.
 */
static inline int find_command(const char *c_name)
{
	if (c_name[0] != '-') return -1;

	int cmd;
	char *shortcut;
	char * traslated_name = replace_with_underscores(c_name);
	if (traslated_name == NULL) return -1;

	const char *full_c = traslated_name + 2;
	const char *alias_c = traslated_name + 1;
	for (cmd = 0; commands[cmd].c_name; cmd++)
	{
		// Recognize full name command.
		if (!strcmp(commands[cmd].c_name, full_c)) 
		{
			free(traslated_name);
			return cmd;
		}
		// Recognize alias command
		else if (!strcmp(commands[cmd].c_alias, alias_c))
		{
			free(traslated_name);
			return cmd; 
		}
	}

	if (!commands[cmd].c_name) 
	{	
		free(traslated_name);	
		return -1;
	}
}

int main(int argc, char **argv)
{

#ifdef linux
	if (argc < 2)
	{
		help_command();
		return 0;
	}

	int cmd_index;
	cmd_index = find_command(argv[1]);

	if (commands[cmd_index].c_argc - (argc - 2) < 0
	    || cmd_index == -1)
	{
		help_command();
		return 0;
	}
	else
	{
		// Execute the command.
		if (commands[cmd_index].c_argc == 0) (commands[cmd_index].c_exec)();
		else if (commands[cmd_index].c_argc == 1)
			((void (*)(const char *)) commands[cmd_index].c_exec)(argv[2]);
		else if (commands[cmd_index].c_argc == 2)
			((void (*)(const char *, const char *)) commands[cmd_index].c_exec)(argv[2], argv[3]);
		else if (commands[cmd_index].c_argc == 3)
			((void (*)(const char *, const char *, const char *)) commands[cmd_index].c_exec)
									      (argv[2], argv[3], argv[4]);
	}
#else
	printf("The oparation system is not compatible.");

	return 0;

#endif
}
