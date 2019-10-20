//
//#include "big_file_utils.h"
//
//#include <windows.h>
//
//bool HandleBigFileByLineW(const std::wstring & path, const unsigned char * checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback)
//{
//    bool success = false;
//
//    //��ȡģʽ
//    DWORD dAccessType = (GENERIC_READ);
//
//    //����ģʽ
//    DWORD dShareType = FILE_SHARE_READ;
//
//    // ���ļ����
//    HANDLE hFile = ::CreateFile(path.c_str()
//                              , dAccessType           // ����ģʽ
//                              , dShareType            // ����ģʽ
//                              , NULL
//                              , OPEN_EXISTING         // ���������򿪣�����ʧ��
//                              , FILE_FLAG_OVERLAPPED  // ������
//                              , NULL);
//
//
//    if (hFile == INVALID_HANDLE_VALUE)
//    {
//        return false;
//    }
//
//    DWORD dFileSize = ::GetFileSize(hFile, NULL);
//
//    // ����ӳ����
//    HANDLE hFileMap = ::CreateFileMapping(hFile,
//                                          NULL,
//                                          PAGE_READONLY,  // ע�⣬��createfileҪһ��
//                                          0,
//                                          dFileSize,
//                                          NULL);
//
//
//    if (hFileMap == NULL)
//    {
//        ::CloseHandle(hFile);
//        return false;
//    }
//
//    ::CloseHandle(hFile);
//
//    DWORD dFileBlock = 1024 * 1024 * 5;
//    DWORD dBegin = 0;
//    DWORD dLen = 0;
//
//    while (dBegin < dFileSize)
//    {
//        if (dBegin > dFileSize - dFileBlock)
//        {
//            dLen = dFileSize - dBegin;
//        }
//        else
//        {
//            dLen = dFileBlock;
//        }
//
//        LPVOID pFileBlock = ::MapViewOfFile(hFileMap,
//                                            FILE_MAP_READ,  // ע�⣬��createfileҪһ��
//                                            0,
//                                            dBegin,     // ��ʼλ��
//                                            dLen);     // ӳ�䳤��
//
//        LPVOID pFileBlock1 = ::MapViewOfFile(hFileMap,
//                                            FILE_MAP_READ,  // ע�⣬��createfileҪһ��
//                                            0,
//                                            dBegin + dLen,     // ��ʼλ��
//                                            dLen);     // ӳ�䳤��
//
//        if (pFileBlock == NULL)
//        {
//            break;
//        }
//
//        for (DWORD i = 0; i < dLen; ++i)
//        {
//        }
//
//        // ���ͷš��������ڴ�
//        ::UnmapViewOfFile(pFileBlock);
//        dBegin += dLen;
//    }
//
//    ::CloseHandle(hFileMap);
//    return success;
//}
//
//bool HandleBigFileByLine(const std::wstring & path, const unsigned char * checker, const size_t checkSize, std::function<bool(const std::string&line)> callback)
//{
//    return false;
//}
