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

	public:
		CommandParser(int, char**);

		bool RegisterCommand(Command);
		bool HasCommand(const Command&);
		bool GetCommand(Command*);
	};
}