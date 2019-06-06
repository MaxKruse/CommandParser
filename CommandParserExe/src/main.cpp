#include "pch.h"
#include "CP.h"

int main(int argc, char** argv)
{
	CP::CommandParser cmdParser(argc, argv);

	auto cmd_version = CP::Command{ "-v", "Version" };
	auto cmd_version_full = CP::Command{ "-version", "Version" };
	auto cmd_new_path = CP::Command{ "-path", "Path" };
	
	cmdParser.RegisterCommand(cmd_version);
	cmdParser.RegisterCommand(cmd_version_full);
	cmdParser.RegisterCommand(cmd_new_path);

	if(cmdParser.HasCommand(cmd_version))
	{
		printf("Command -v found via HasCommand(Command)!\n");
	}

	if(cmdParser.HasCommand("Version"))
	{
		printf("Command Version found via HasCommand(string)!\n");
	}

	if(cmdParser.GetCommand(&cmd_new_path))
	{
		printf("Command -path with parameter '%s' found via GetCommand(Command*)!\n", cmd_new_path.Parameter.c_str());
	}

	std::string param;

	if(cmdParser.GetCommand("Path", &param))
	{
		printf("Command -path with parameter '%s' found via GetCommand(string, string*)!\n", param.c_str());
	}
}