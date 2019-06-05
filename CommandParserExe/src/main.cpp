#include "pch.h"
#include "CP.h"

int main(int argc, char** argv)
{
	CP::CommandParser cmdParser(argc, argv);

	auto cmd_version = CP::Command{ "-v", "Version" };
	auto cmd_version_full = CP::Command{ "-version", "Version" };
	auto cmd_new_path = CP::Command{ "-path", "Add Path" };
	
	cmdParser.RegisterCommand(cmd_version);
	cmdParser.RegisterCommand(cmd_version_full);
	cmdParser.RegisterCommand(cmd_new_path);

	if(cmdParser.HasCommand(cmd_version))
	{
		printf("Command -v found via CommandStruct!\n");
	}

	if(cmdParser.HasCommand("Version"))
	{
		printf("Command Version found via string!\n");
	}

	if(cmdParser.HasCommand(cmd_new_path))
	{
		cmdParser.GetCommand(&cmd_new_path);
		printf("Command -path with parameter '%s' found via CommandStruct!\n", cmd_new_path.Parameter.c_str());
	}
}