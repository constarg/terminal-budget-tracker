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
	int argc;
};


struct command commands[] = 
{
	DEFINE_COMMAND(available_amount, 			0),
	DEFINE_COMMAND(available_category_amount,	1),
	DEFINE_COMMAND(set_budget, 					1),
	DEFINE_COMMAND(change_budget,				1),
	DEFINE_COMMAND(add_category, 				2),
	DEFINE_COMMAND(change_budget, 				2),
	DEFINE_COMMAND(delete_category, 			1),
	DEFINE_COMMAND(show_statistics, 			0),
	DEFINE_COMMAND(show_prefered_daily_spend, 	0),
	DEFINE_COMMAND(show_future_spend, 			0),
	DEFINE_COMMAND(show_categories, 			0),
	DEFINE_COMMAND(show_category, 				1),
	DEFINE_COMMAND(show_merchant, 				1),
	DEFINE_COMMAND(show_merchants, 				0),
	DEFINE_COMMAND(show_all_expenses, 			2),
	DEFINE_COMMAND(add_expenses, 				3),
	DEFINE_COMMAND(associate_merchant, 			2),
	{.c_name = NULL}
};

__attribute__((always_inline)) static inline int find_command(const char *c_name)
{
	int cmd;
	for (cmd = 0; commands[cmd].c_name; cmd)
		if (!strcmp(commands[cmd].c_name, c_name)) return cmd;

	if (!commands[cmd].c_name)
		return -1;
}

int main(int argc, char **argv) 
{

#ifdef linux
	if (argc < 2)
	{
		// TODO - Print help.
		return 0;
	}

	int cmd_index;
	find_command(argv[1]);

	if (commands[cmd_index].argc - (argc + 1) < 0
		|| cmd_index == -1)
	{
		// TODO - Print Help.
		return 0;
	}
	else 
	{
		// TODO - Execute command
	}

#else
	printf("The oparation system is not compatible.");

	return 0;

#endif
}
