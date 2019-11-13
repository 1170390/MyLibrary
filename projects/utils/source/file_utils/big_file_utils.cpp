#include "big_file_utils.h"

#include <windows.h>

/** ȡ64λ��λ
*/
#define L64(l) ((__int64)(l) & 0xffffffff)

/** ȡ64λ��λ
*/
#define H64(l) (((__int64)(l) >> 32) & 0xffffffff)

/** ���루64K��
*/
#define ALIGN_SIZE 65536

BigFileMapper::BigFileMapper():
    m_hFileMap(NULL),
    m_bginPos(0)
{
}

BigFileMapper::~BigFileMapper()
{
    if (m_hFileMap != NULL)
    {
        ::CloseHandle(m_hFileMap);
        m_hFileMap = NULL;
    }
}

bool BigFileMapper::MapFile(const DogString& filePath)
{
    // ���ļ����
    HANDLE hFile = ::CreateFile(filePath.c_str(),
                                GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                NULL,
                                OPEN_EXISTING,
                                FILE_FLAG_OVERLAPPED,
                                NULL);

    if (INVALID_HANDLE_VALUE == hFile)
    {
        return false;
    }

    LARGE_INTEGER fileSizeLar;

    if (!::GetFileSizeEx(hFile, &fileSizeLar))
    {
        ::CloseHandle(hFile);
        return false;
    }

    // ����ӳ��
    void* hFileMap = ::CreateFileMapping(hFile,
                                         NULL,
                                         PAGE_READWRITE,
                                         fileSizeLar.HighPart,
                                         fileSizeLar.LowPart,
                                         NULL);

    ::CloseHandle(hFile);

    if (hFileMap == NULL)
    {
        return false;
    }

    if (m_hFileMap != NULL)
    {
        ::CloseHandle(m_hFileMap);
        m_hFileMap = NULL;
    }

    m_hFileMap = hFileMap;
    m_fileSize = (long long)fileSizeLar.QuadPart;
    m_bginPos = 0;
    return true;
}

SPFileBlock BigFileMapper::GetNextBlock(int sizeRaw/* = g_file_block_default_size */, char align /* = '\n' */)
{
    SPFileBlock spFileBlock = GetBlock(m_bginPos, sizeRaw, align);

    if (spFileBlock != NULL)
    {
        m_bginPos += spFileBlock->m_blockSize;
    }

    return spFileBlock;
}

SPFileBlock BigFileMapper::GetBlock(__int64 beginPos, int sizeRaw, char align)
{
    SPFileBlock spFileBlock(new(std::nothrow) FileBlock());

    if (m_hFileMap == NULL || spFileBlock == NULL)
    {
        return NULL;
    }

    if (beginPos >= m_fileSize)
    {
        return NULL;
    }

    // �����ӳ��Ĵ�С
    int size = sizeRaw;
    if (size <= 0 || size >= 1024 * 1024 * 1024)
    {
        size = g_file_block_default_size;
    }

    // ����
    int offset = (int)(beginPos % ALIGN_SIZE);
    beginPos -= offset;
    size += offset;

    if (size + beginPos > m_fileSize)
    {
        size = (int)(m_fileSize - beginPos);
    }

    char* pFileBlock = (char*)::MapViewOfFile(m_hFileMap,
                                              PAGE_READWRITE,
                                              H64(beginPos),
                                              L64(beginPos),
                                              size);

    if (pFileBlock == NULL)
    {
        return NULL;
    }

    if (align == 0)
    {
        spFileBlock->m_pBlock = pFileBlock;
        spFileBlock->m_offSet = offset;
        spFileBlock->m_blockSize = size - offset;
        return spFileBlock;
    }

    int tmp = size - 1;
    while (tmp >= offset)
    {
        if (pFileBlock[tmp] == align)
        {
            break;
        }

        --tmp;
    }

    if (tmp == offset - 1)
    {
        // û���ҵ������ַ�
        return NULL;
    }

    // ����ӳ��
    size = tmp + 1;
    ::UnmapViewOfFile(pFileBlock);
    pFileBlock = NULL;
    pFileBlock = (char*)::MapViewOfFile(m_hFileMap,
                                        FILE_MAP_READ,
                                        H64(beginPos),
                                        L64(beginPos),
                                        size);
    if (pFileBlock == NULL)
    {
        // ʧ��
        return NULL;
    }

    spFileBlock->m_pBlock = pFileBlock;
    spFileBlock->m_offSet = offset;
    spFileBlock->m_blockSize = size - offset;
    return spFileBlock;
}

FileBlock::~FileBlock()
{
    if (m_pBlock != NULL)
    {
        ::UnmapViewOfFile(m_pBlock);
        m_pBlock = NULL;
    }
}
