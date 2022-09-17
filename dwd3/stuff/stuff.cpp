#include "../stdinc.hpp"
#include "stuff.hpp"

namespace skull
{
	uintptr_t base_address = (uintptr_t)GetModuleHandleA(0);

	void print(const unsigned int conCode, std::string text, ...)
	{
		if (conCode == 0)
		{
			std::printf("[" __TIME__ "]: ");
		}
		else
		{
			std::printf("[" __TIME__ "]:\033[%im ", conCode);
		}

		va_list arg;
		va_start(arg, text);

		vprintf(text.data(), arg);
		std::printf("\033[0m"); // Clear colors
		va_end(arg);
	}

	std::vector<std::string> split(const std::string& s, const std::string& delimiter, const bool& removeEmptyEntries)
	{
		std::vector<std::string> tokens;

		for (size_t start = 0, end; start < s.length(); start = end + delimiter.length())
		{
			size_t position = s.find(delimiter, start);
			end = position != std::string::npos ? position : s.length();

			std::string token = s.substr(start, end - start);
			if (!removeEmptyEntries || !token.empty())
			{
				tokens.push_back(token);
			}
		}

		if (!removeEmptyEntries &&
			(s.empty() || (s.size() >= delimiter.size() && s.substr(s.size() - delimiter.size()) == delimiter)))
		{
			tokens.push_back("");
		}

		return tokens;
	}

	std::string exe()
	{
		TCHAR module_file_name_c[MAX_PATH];

		GetModuleFileName(0, module_file_name_c, MAX_PATH);

		std::wstring module_file_name_wstr(&module_file_name_c[0]);
		std::string module_file_name_str(module_file_name_wstr.begin(), module_file_name_wstr.end());

		std::vector <std::string> module_file_name_s;
		module_file_name_s = split(module_file_name_str, "\\", false);

		std::string module_file_name = module_file_name_s[module_file_name_s.size() - 1];

		return module_file_name;
	}

	inline bool mkdir(const std::string& dir_name)
	{
		return std::filesystem::create_directories(dir_name);
	}

	inline bool isdir(const std::string& dir_name)
	{
		return std::filesystem::is_directory(dir_name);
	}

	void check_directory(const std::string dir_name)
	{
		if (!isdir(dir_name))
		{
			mkdir(dir_name);
		}
	}

	void branding()
	{
		// Looks a bit woinky here but the output is perfect
		print(0, "----------------- DWD3 -----------------\n");
		print(0, " __   __   DWD3: " VERSION " - By Skull \n");
		print(0, "|  \\ |  |  Info: Publisher Files Dumper\n");
		print(0, "| --  --|  github.com/skkuull           \n");
		print(0, "|__/ |__|  BaseAddress: 0x%llX          \n", skull::base_address);
		print(0, "----------------------------------------\n");
	}
}