#pragma once

namespace CP {
	
	struct Command
	{
		std::string Flag;
		std::string Name;
		std::string Description;
		uint32_t	NumParams;
		std::vector<std::string> Params;
		bool		Required;
	};

	class CommandParser
	{
	private:
		int m_Argc;
		size_t m_NeededParams;
		std::vector<std::string> m_Args;
		std::vector<Command> m_RegisteredCommands;
		std::vector<Command> m_Commands;

		bool FindInParsedCommands(const Command&);
		bool FindInRegisteredCommands(const Command&);
		std::vector<std::string> SplitVector(const std::string&, const char& delim);
		void PrintUsage(const std::vector<std::string>&);
		void ConsumeFlags();

	public:
		CommandParser(int, char**);

		bool RegisterCommand(const Command&);
		void RequireParams(size_t, const std::vector<std::string>& fillers);
		std::string GetParam(const size_t);

		bool HasCommand(const std::string&);
		std::vector<std::string>* GetCommandParams(const std::string&);
		bool Failed();
	};
}

#ifdef CP_SINGLE_HEADER

#include "../CP.cpp"

#endif
