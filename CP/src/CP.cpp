#include "pch.h"
#include "CP.h"
#include <sstream>

namespace CP {

	bool operator==(const Command& left, const Command& right)
	{
		return left.Name == right.Name &&
			left.Flag.find(right.Flag) != std::string::npos && 
			left.Params == right.Params;
	}

	bool operator!=(const Command& left, const Command& right)
	{
		return left.Name != right.Name ||
			left.Flag != right.Flag ||
			left.Params != right.Params;
	}

	bool CommandParser::FindInParsedCommands(const Command& cmd)
	{
		for (const auto& command : m_Commands)
		{
			if (command == cmd)
			{
				return true;
			}
		}
		return false;
	}

	bool CommandParser::FindInRegisteredCommands(const Command& cmd)
	{
		for (const auto& command : m_RegisteredCommands)
		{
			if (command == cmd)
			{
				return true;
			}
		}
		return false;
	}

	std::vector<std::string> CommandParser::SplitVector(const std::string& s, const char& delim) {
		std::vector<std::string> result;
		std::stringstream ss(s);
		std::string item;

		while (std::getline(ss, item, delim)) {
			result.push_back(item);
		}

		return result;
	}

	CommandParser::CommandParser(int argc, char** args)
		: m_Argc{argc}
	{
		for (int i = 0; i < argc; ++i)
		{
			m_Args.emplace_back(std::string(args[i]));
		}
	}

	bool CommandParser::RegisterCommand(const Command& cmd)
	{
		if(!FindInRegisteredCommands(cmd))
		{
			bool found{ false };
			for (auto& command : m_RegisteredCommands)
			{
				found = cmd.Name == command.Name && command.Flag.find(cmd.Flag) == std::string::npos;
				if (found)
				{
					command.Flag += "/" + cmd.Flag;
					break;
				}
			}

			if(!found)
			{
				m_RegisteredCommands.emplace_back(cmd);
			}
		}

		return false;
	}

	void CommandParser::ConsumeFlags()
	{
		std::vector<size_t> visited;
		for(auto& cmd : m_RegisteredCommands)
		{
			auto flags = SplitVector(cmd.Flag, '/');

			for (const auto& flag : flags)
			{
				for(size_t i = 0; i < m_Args.size(); i++)
				{
					if (m_Args.at(i) == flag)
					{
						for (uint32_t j = 1; j <= cmd.NumParams; j++)
						{
							if (m_Args.size() <= i + j)
								continue;
							cmd.Params.emplace_back(m_Args.at(i + j));

							visited.emplace_back(i + j);
						}
						m_Commands.emplace_back(cmd);
						visited.emplace_back(i);
						i += cmd.Params.size();
					}
				}				
			}
		}

		std::sort(visited.begin(), visited.end());
		std::reverse(visited.begin(), visited.end());

		for (size_t i : visited)
		{
			m_Args.erase(m_Args.begin() + i);
		}

		
	}

	bool CommandParser::RequireParams(const size_t needed) const
	{
		return needed + 1 == m_Args.size();
	}

	std::string CommandParser::GetParam(const size_t index)
	{
		return m_Args.at(index);
	}

	bool CommandParser::HasCommand(const std::string& cmdString)
	{
		bool found{ false };
		for(const auto& command : m_Args)
		{
			found = command == cmdString;
			if (found)
				return found;
		}

		for (const auto& command : m_Commands)
		{
			found = command.Name == cmdString || command.Flag == cmdString;
			if (found)
				return found;
		}

		return false;
	}

	std::vector<std::string>* CommandParser::GetCommandParams(const std::string& cmdString)
	{
		if (!HasCommand(cmdString)) return nullptr;

		for (auto& command : m_Commands)
		{
			if (command.Name == cmdString)
			{
				return &command.Params;
			}
		}
		return nullptr;

	}

	void CommandParser::PrintUsage(const std::vector<std::string>& params)
	{
		const auto lastSlashes = m_Args.at(0).find_last_of("\\") + 1;
		const auto sizeLastThing = m_Args.at(0).size() - lastSlashes;
		const auto me = m_Args.at(0).substr(lastSlashes, sizeLastThing);


		// Full Usage Command
		printf("Usage: %s", me.c_str());

		for (const auto& str : params)
		{
			printf(" <%s>", str.c_str());
		}

		std::vector<std::string> usedCommandNames(m_RegisteredCommands.size() - 1);

		for(const auto& cmd : m_RegisteredCommands)
		{
			
			printf(" [%s", cmd.Flag.c_str());

			for(uint32_t i = 0; i < cmd.NumParams; i++)
			{
				printf(" param%i", i + 1);
			}

			printf("]");
		}

		printf("\n\n");
		printf("Descriptions:");

		// Flag Explanations
		for (const auto& cmd : m_RegisteredCommands)
		{
			printf("\n\n");
			auto p = "[" + cmd.Flag;

			for (uint32_t i = 0; i < cmd.NumParams; i++)
			{
				p += " param" + std::to_string(i + 1);
			}

			p += "]";

			printf("\t%-*s", 25, p.c_str());

			printf("%s", cmd.Description.c_str());
		}

		printf("\n");
	}
}

