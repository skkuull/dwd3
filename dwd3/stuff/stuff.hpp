#pragma once
#include "structs.hpp"
#include "hook.hpp"
#include "console.hpp"

#define VERSION "0.1"

namespace skull
{
	extern uintptr_t base_address;

	void print(unsigned int conCode, std::string text, ...);

	std::string exe();

	inline bool mkdir(const std::string& dir_name);
	inline bool isdir(const std::string& dir_name);

	void check_directory(const std::string dir_name);

	void branding();
	
	//https://github.com/h1-mod/h1-mod/blob/develop/src/client/component/console.hpp
	template <typename... Args>
	void error(std::string text, Args&&... args)
	{
		return print(0x1F, "[ ERROR ]: " + text, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void warning(std::string text, Args&&... args)
	{
		return print(0x21, "[ WARNING ]: " + text, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void info(std::string text, Args&&... args)
	{
		return print(0, "[ INFO ]: " + text, std::forward<Args>(args)...);
	}
}