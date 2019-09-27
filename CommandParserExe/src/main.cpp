#include "pch.h"
#include "CP.h"

int main(int argc, char** argv)
{
	CP::CommandParser cmdParser(argc, argv);

	auto cmdVersion = CP::Command{ "-v", "Version", "Print the Version" };
	auto cmdVersionFull = CP::Command{ "-version", "Version", "Print the Version" };
	auto cmdNotWorking = CP::Command{ "-useless", "Useless", "This actually doesn't do anything" };
	auto cmdNewPath = CP::Command{ "-path", "Path", "Specify a path to whatever", 1 };

	bool b;
	b = cmdParser.RegisterCommand(cmdVersion);		// Success
	b = cmdParser.RegisterCommand(cmdVersionFull);	// Success
	b = cmdParser.RegisterCommand(cmdVersionFull);	// Fail
	b = cmdParser.RegisterCommand(cmdNotWorking);	// Success
	b = cmdParser.RegisterCommand(cmdNewPath);		// Success

	cmdParser.ConsumeFlags();


	if (cmdParser.HasCommand("-v"))
	{
		printf("Command Version found via HasCommand(string)!\n");
		return;
	}

	if (cmdParser.HasCommand("Useless"))
	{
		printf("Command Useless found via HasCommand(string)!\n");
		return;
	}

	if (cmdParser.HasCommand("Path"))
	{
		printf("Command -path with parameter '%s' found!\n", cmdParser.GetCommandParams("Path")->at(0).c_str());
		return;
	}

	if (!cmdParser.RequireParams(1))
	{
		cmdParser.PrintUsage({ "name" });
		return 1;
	}

	printf("GetParam(1) is %s\n", cmdParser.GetParam(1).c_str());
	return;
}