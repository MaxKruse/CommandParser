#include "pch.h"
#include "CP.h"

namespace CP {

	bool operator==(const Command& left, const Command& right)
	{
		return left.CommandName == right.CommandName &&
			left.Flag == right.Flag &&
			left.Parameter == right.Parameter;
	}

	bool CommandParser::FlagInArgs(const std::string& flag, std::string* out = nullptr)
	{
		auto param_before{ false };
		for (size_t i = 1; i < m_Argc; ++i)
		{
			if (m_Args.at(i) == flag)
			{
				if(out != nullptr)
				{
					*out = m_Args.at(static_cast<size_t>(i + 1));
				}				
				param_before = true;
			}
		}
		return param_before;
	}

	CommandParser::CommandParser(int argc, char** args)
		: m_Argc{argc}
	{
		for (int i = 0; i < argc; ++i)
		{
			m_Args.emplace_back(std::string(args[i]));
		}
	}

	bool CommandParser::RegisterCommand(Command cmd)
	{
		if(HasCommand(cmd))
		{
			m_Commands.emplace_back(cmd);
			return true;
		}
		return false;
	}

	bool CommandParser::HasCommand(const Command& cmd)
	{
		bool found {false};

		for (const auto& command : m_Args)
		{
			if(found)
			{
				break;
			}
			found = cmd.Flag == command;
		}

		return found;
	}

	bool CommandParser::HasCommand(const std::string& cmdString)
	{
		bool found{ false };

		for(const auto& command : m_Commands)
		{
			if(command.CommandName == cmdString)
			{
				Command cmd = command;

				for (const auto& arg : m_Args)
				{
					if (found)
					{
						break;
					}

					found = cmd.Flag == arg;
				}
			}
		}
		return found;
	}

	bool CommandParser::GetCommand(Command* cmd)
	{
		if (!HasCommand(*cmd)) return false;

		return FlagInArgs(cmd->Flag, &cmd->Parameter);
	}

	bool CommandParser::GetCommand(const std::string& cmdString, std::string* out)
	{
		if (!HasCommand(cmdString)) return false;
		auto param_before{ false };

		for (const auto& command : m_Commands)
		{
			if (command.CommandName == cmdString)
			{
				param_before = FlagInArgs(command.Flag, out);
			}
		}
		return param_before;

	}
}

