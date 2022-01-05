#ifdef linux
#include <stdio.h>
#include <string.h>
#include <commands.h>
#endif

#ifndef linux
#include <stdio.h>
#endif

#define DEFINE_COMMAND(COMMAND) { #COMMAND, (void (*)(void)) COMMAND ## _command }


struct command {
	char *c_name;
	void (*c_exec) (void);
	int argc;
};


struct command commands[] = 
{
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
