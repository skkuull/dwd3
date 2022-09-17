#include "../stdinc.hpp"
#include "../stuff/stuff.hpp"
#include "iw6.hpp"

namespace iw6
{
    hook::detour dwFetchFileComplete_hook;
    int dwFetchFileComplete_stub(void* task, skull::iw6::dwFileTask* fileTask)
    {
        auto result = ((decltype(dwFetchFileComplete_stub)*)dwFetchFileComplete_hook.get_original())(task, fileTask);

        if (result != 1)
        {
            return result;
        }

        std::printf("\n");

        skull::info("Dumping: %s..\n", fileTask->m_filename);

        FILE* fp;
        FILE* lp = fopen("dwd3/iw6/dwd3.log", "a");

        fprintf(lp, "[" __TIME__ "] File: %s, Size: %i-bytes\n", fileTask->m_filename, fileTask->m_dataResult.m_fileSize);

        fopen_s(&fp, ("dwd3/iw6/"s + fileTask->m_filename).data(), "wb");

        if (fp)
        {
            fwrite(fileTask->m_dataResult.m_fileData, fileTask->m_dataResult.m_fileSize, 1, fp);
            fclose(fp);
        }
        else
        {
            skull::error("(IW6): Failed to dump publisher files.\n");
        }

        fclose(lp);

        skull::info("Dumped: %s, Size: %i-bytes.\n", fileTask->m_filename, fileTask->m_dataResult.m_fileSize);

        return result;
    }

    void dump()
    {
        skull::warning("Game Detected: IW6\n");
        skull::check_directory("dwd3/iw6/");
        dwFetchFileComplete_hook.create(skull::base_address + 0x58E6C0, dwFetchFileComplete_stub);
    }
}