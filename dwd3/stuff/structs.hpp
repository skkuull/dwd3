#pragma once

namespace skull
{
    struct bdFileData
    {
        void* m_fileData;        // 00
        unsigned int m_fileSize; // 08
    }; // size = 16

    namespace h1
    {
        struct dwFileTask
        {
            char __pad0[8];          // 00
            const char* m_filename;  // 08
            char __pad1[60];         // 16
            unsigned int m_fileSize; // 76
            char __pad2[21872];      // 80
            bdFileData m_dataResult; // 21952
        }; // size = 21968
    }

    namespace s1
    {
        struct dwFileTask
        {
            const char* m_filename;  // 00
            int m_error;             // 08
            unsigned int m_fileSize; // 12
            char __pad1[434];        // 16
            bdFileData m_dataResult; // 456
        }; // size = 472
    }

    namespace iw6
    {
        struct bdFileData
        {
            char __pad0[8];          // 00
            void* m_fileData;        // 08
            unsigned int m_fileSize; // 16
        };

        struct dwFileTask
        {
            const char* m_filename;  // 00
            int m_error;             // 08
            unsigned int m_fileSize; // 12
            char __pad2[368];        // 16
            bdFileData m_dataResult; // 384
        }; // size = ?
    }
}