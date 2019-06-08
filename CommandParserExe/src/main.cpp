#include "pch.h"
#include "CP.h"

int main(int argc, char** argv)
{
	CP::CommandParser cmdParser(argc, argv);

	auto cmdVersion = CP::Command{ "-v", "Version", "Print the Version"};
	auto cmdVersionFull = CP::Command{ "-version", "Version", "Print the Version" };
	auto cmdNotWorking = CP::Command{ "-useless", "Useless", "This actually doesn't do anything" };
	auto cmdNewPath = CP::Command{ "-path", "Path", "Specify a path to whatever", 1 };

	bool b;
	b = cmdParser.RegisterCommand(cmdVersion);
	b = cmdParser.RegisterCommand(cmdVersionFull);
	b = cmdParser.RegisterCommand(cmdVersionFull);
	b = cmdParser.RegisterCommand(cmdNotWorking);
	b = cmdParser.RegisterCommand(cmdNewPath);

	cmdParser.ConsumeFlags();
	if(!cmdParser.RequireParams(1))
	{
		cmdParser.PrintUsage({"name"});
		return 1;
	}

	if(cmdParser.HasCommand("Version"))
	{
		printf("Command Version found via HasCommand(string)!\n");
	}

	if(cmdParser.HasCommand("Useless"))
	{
		printf("Command Useless found via HasCommand(string)!\n");
	}

	if(cmdParser.HasCommand("Path"))
	{
		printf("Command -path with parameter '%s' found!\n", cmdParser.GetCommandParams("Path")->at(0).c_str());
	}
}