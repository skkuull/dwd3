#include "stdinc.hpp"
#include "stuff/stuff.hpp"

// Games
#include "iw6/iw6.hpp"
#include "iw7/iw7.hpp"
#include "h1/h1.hpp"
#include "s1/s1.hpp"

static void initialize()
{
	CreateThread(0, 0, skull::console, 0, 0, 0);

	if (skull::exe() == "iw6mp64_ship.exe")
	{
		iw6::dump();
	}
	else if (skull::exe() == "iw7_ship.exe")
	{
		iw7::dump();
	}
	else if (skull::exe() == "h1_mp64_ship.exe")
	{
		h1::dump();
	}
	else if (skull::exe() == "s1_mp64_ship.exe")
	{
		s1::dump();
	}
	else
	{
		throw std::runtime_error("Failed to find supported game\nExiting..");
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		initialize();
	}

	return TRUE;
}