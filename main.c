#ifdef linux
#include <stdio.h>
#include <string.h>
#include <commands.h>
#endif

#ifndef linux
#include <stdio.h>
#endif

#define DEFINE_COMMAND(COMMAND, ARGC) { #COMMAND, (void (*)(void)) &COMMAND ## _command, ARGC }


struct command {
	char *c_name;
	void (*c_exec) (void);
	int c_argc;
};


// Available commands.
struct command commands[] = 
{
	DEFINE_COMMAND(available_amount, 			0),
	DEFINE_COMMAND(available_category_amount,	1),
	DEFINE_COMMAND(set_budget,					1),
	DEFINE_COMMAND(change_budget,				1),
	DEFINE_COMMAND(add_category, 				2),
	DEFINE_COMMAND(change_budget,				2),
	DEFINE_COMMAND(delete_category,				1),
	DEFINE_COMMAND(show_statistics,				0),
	DEFINE_COMMAND(show_prefered_daily_spend,	0),
	DEFINE_COMMAND(show_future_spend,			0),
	DEFINE_COMMAND(show_categories,				0),
	DEFINE_COMMAND(show_category,				1),
	DEFINE_COMMAND(show_merchant,				1),
	DEFINE_COMMAND(show_merchants,				0),
	DEFINE_COMMAND(show_all_expenses,			2),
	DEFINE_COMMAND(add_expenses,				3),
	DEFINE_COMMAND(help,						0),
	DEFINE_COMMAND(associate_merchant,			2),
	{.c_name = NULL}
};

// Find the command that the user has colled.
static inline int find_command(const char *c_name)
{
	int cmd;
	const char *tmp = (char *) c_name + 2;
	for (cmd = 0; commands[cmd].c_name; cmd++)
		if (!strcmp(commands[cmd].c_name, tmp)) return cmd;

	if (!commands[cmd].c_name)
		return -1;
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
