#include "pch.h"
#include "CP.h"

namespace CP {

	bool operator==(const Command& left, const Command& right)
	{
		return left.Name == right.Name &&
			left.Flag == right.Flag && 
			left.Params == right.Params;
	}

	bool operator!=(const Command& left, const Command& right)
	{
		return left.Name != right.Name ||
			left.Flag != right.Flag ||
			left.Params != right.Params;
	}

	bool CommandParser::FlagInArgs(const std::string& flag, std::vector<std::string>* out = nullptr)
	{
		auto param_before{ false };
		for (size_t i = 1; i < static_cast<size_t>(m_Argc); ++i)
		{
			if (m_Args.at(i) == flag)
			{
				if(out != nullptr)
				{
					out->emplace_back(m_Args.at(static_cast<size_t>(i + 1)));
				}				
				param_before = true;
			}
		}
		return param_before;
	}

	bool CommandParser::FindInParsedCommands(const Command& cmd)
	{
		for (const auto& command : m_Commands)
		{
			if (cmd == command)
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
			if (cmd == command)
			{
				return true;
			}
		}
		return false;
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
			m_RegisteredCommands.emplace_back(cmd);
		}

		if(m_Commands.empty())
		{
			m_Commands.emplace_back(cmd);
			return true;
		}

		if(!FindInParsedCommands(cmd))
		{
			for(size_t j = 0; j < m_Args.size() - 1; j++)
			{
				if(cmd.Flag == m_Args.at(j))
				{
					m_Commands.emplace_back(cmd);
				}
			}			
			return true;
		}

		return false;
	}

	void CommandParser::ConsumeFlags()
	{
		std::vector<size_t> visited;
		for(auto& cmd : m_Commands)
		{
			for(size_t i = 0; i < m_Args.size() - 1; i++)
			{
				if(m_Args.at(i) == cmd.Flag)
				{
					for(uint32_t j = 1; j <= cmd.NumParams; j++)
					{
						if (m_Args.size() <= i + j)
							continue;
						cmd.Params.emplace_back(m_Args.at(i + j));
						visited.emplace_back(i + j);
					}
					visited.emplace_back(i);
					i += cmd.Params.size();
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
		return needed == m_Args.size();
	}

	std::string CommandParser::GetParam(const size_t index)
	{
		return m_Args.at(index);
	}

	bool CommandParser::HasCommand(const std::string& cmdString)
	{
		for(const auto& command : m_Commands)
		{
			if(command.Name == cmdString)
			{
				return true;
			}
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
		const auto last_slashes = m_Args.at(0).find_last_of("\\") + 1;
		const auto size_last_thing = m_Args.at(0).size() - last_slashes;
		auto me = m_Args.at(0).substr(last_slashes, size_last_thing);


		// Full Usage Command
		printf("Usage: %s", me.c_str());

		for (const auto& str : params)
		{
			printf(" <%s>", str.c_str());
		}

		for(const auto& cmd : m_RegisteredCommands)
		{
			
			printf(" [%s", cmd.Flag.c_str());

			for(uint32_t i = 0; i < cmd.NumParams; i++)
			{
				printf(" something");
			}

			printf("]");
		}

		printf("\n\n");
		printf("Descriptions:");

		// Flag Explanations
		for (const auto& cmd : m_RegisteredCommands)
		{
			printf("\n\n");

			std::string p = "[" + cmd.Flag;

			for (uint32_t i = 0; i < cmd.NumParams; i++)
			{
				p += " something";
			}

			p += "]";

			printf("\t%-*s", 25, p.c_str());

			// TODO(Max): Padding
			printf("%s", cmd.Description.c_str());
		}

		printf("\n");
	}
}

