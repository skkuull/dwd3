#include "../stdinc.hpp"
#include "../stuff/stuff.hpp"
#include "iw7.hpp"

namespace iw7
{
    hook::detour dwFetchFileComplete_hook;
    int dwFetchFileComplete_stub(void* task, skull::iw7::dwFileTask* fileTask)
    {
        auto result = ((decltype(dwFetchFileComplete_stub)*)dwFetchFileComplete_hook.get_original())(task, fileTask);

        if (result != 1)
        {
            return result;
        }

        std::printf("\n");

        skull::info("Dumping: %s..\n", fileTask->m_filename);

        FILE* fp;
        FILE* lp = fopen("dwd3/iw7/dwd3.log", "a");

        fprintf(lp, "[" __TIME__ "] File: %s, Size: %i-bytes\n", fileTask->m_filename, fileTask->m_dataResult.m_fileSize);

        fopen_s(&fp, ("dwd3/iw7/"s + fileTask->m_filename).data(), "wb");

        if (fp)
        {
            fwrite(fileTask->m_dataResult.m_fileData, fileTask->m_dataResult.m_fileSize, 1, fp);
            fclose(fp);
        }
        else
        {
            skull::error("(IW7): Failed to dump publisher files.\n");
        }

        fclose(lp);

        skull::info("Dumped: %s, Size: %i-bytes.\n", fileTask->m_filename, fileTask->m_dataResult.m_fileSize);

        return result;
    }

	void dump()
	{
        skull::warning("Game Detected: IW7\n");
        skull::check_directory("dwd3/iw7/");
        dwFetchFileComplete_hook.create(skull::base_address + 0xDB0D70, dwFetchFileComplete_stub);
	}
}