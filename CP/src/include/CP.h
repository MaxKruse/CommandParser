#pragma once

namespace CP {
	
	struct Command
	{
		std::string Flag;
		std::string CommandName;
		std::string Parameter;
	};

	class CommandParser
	{
	private:
		int m_Argc;
		std::vector<std::string> m_Args;
		std::vector<Command> m_Commands;

		bool FlagInArgs(const std::string&, std::string*);

	public:
		CommandParser(int, char**);

		bool RegisterCommand(Command);
		bool HasCommand(const Command&);
		bool HasCommand(const std::string&);
		bool GetCommand(Command*);
		bool GetCommand(const std::string&, std::string*);
	};
}