#pragma once

namespace CP {
	
	struct Command
	{
		std::string Flag;
		std::string Name;
		uint32_t	NumParams;
		std::vector<std::string> Params;
		bool		Exists;
	};

	class CommandParser
	{
	private:
		int m_Argc;
		std::vector<std::string> m_Args;
		std::vector<Command> m_RegisteredCommands;
		std::vector<Command> m_Commands;

		bool FlagInArgs(const std::string&, std::vector<std::string>*);

	public:
		CommandParser(int, char**);

		bool RegisterCommand(const Command&);
		void ConsumeFlags();
		bool RequireParams(const size_t) const;
		std::string GetParam(const size_t);

		bool HasCommand(const std::string&);
		std::vector<std::string>* GetCommandParams(const std::string&);
		void PrintUsage(const std::vector<std::string>&);
	};
}