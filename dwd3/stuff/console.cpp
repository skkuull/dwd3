#include "../stdinc.hpp"
#include "console.hpp"
#include "stuff.hpp"

namespace skull
{
	std::string input;
	std::string help =
		R"(Commands List:
  quit    -   Quits the program
  help    -   Shows available commands
  clear   -   Clears console output
  redump  -   Redumps publisher files
)";

	void commands()
	{
	cmd:
		std::printf("\033[4mDWD3 >\033[0m ");
		std::getline(std::cin, input);
		std::printf("\n");

		if (input == "help")
		{
			skull::info(help.data());
			goto cmd;
		}
		else if (input == "quit")
		{
			exit(0);
		}
		else if (input == "clear"
			   || input == "cls")
		{
			system("cls");
			branding();
			goto cmd;
		}
		else if (input == "redump")
		{
			// Testing purposes only.
			goto cmd;
		}
		else
		{
			error("Unknown Command.\n");
			goto cmd;
		}
	}

	DWORD WINAPI console(LPVOID lp)
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());

		SetConsoleTitleA("DWD3 by skkuull");

		FILE* file;
		freopen_s(&file, "CONIN$", "r", stdin);
		freopen_s(&file, "CONOUT$", "w", stdout);
		freopen_s(&file, "CONOUT$", "w", stderr);

		system("cls");
		branding();

		commands();

		FreeLibraryAndExitThread((HMODULE)lp, 0);
	}
}