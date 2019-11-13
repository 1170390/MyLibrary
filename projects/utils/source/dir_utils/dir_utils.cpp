#include "dir_utils.h"

#include <queue>
#include <tchar.h>
#include <Windows.h>

bool dir_uitls::IsDir(const DogString & path)
{
    DWORD ftyp = ::GetFileAttributes(path.c_str());

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    {
        // ����һ���ļ���
        return true;
    }

    return false;
}

bool dir_uitls::IsFileExist(const DogString& filePath)
{
    DWORD dwAttrib = ::GetFileAttributes(filePath.c_str());
    return (INVALID_FILE_ATTRIBUTES != dwAttrib) && (0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool dir_uitls::IsDirExist(const DogString& dirPath)
{
    DWORD dwAttrib = ::GetFileAttributes(dirPath.c_str());
    return (INVALID_FILE_ATTRIBUTES != dwAttrib) && (0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool dir_uitls::IsPathExist(const DogString& path)
{
    DWORD dwAttrib = ::GetFileAttributes(path.c_str());
    return INVALID_FILE_ATTRIBUTES != dwAttrib;
}

bool dir_uitls::DeleteFile_(const DogString& dfilePath)
{
    return (::DeleteFile(dfilePath.c_str()) == TRUE);
}

bool dir_uitls::DeleteDir(const DogString & dirPath)
{
    if (!IsDirExist(dirPath))
    {
        return false;
    }

    HANDLE hFile = NULL;
    WIN32_FIND_DATA fileInfo;
    ::memset(&fileInfo, 0, sizeof(LPWIN32_FIND_DATA));

    DogString wsTemp(dirPath);
    if (_T('\\') != wsTemp[wsTemp.length() - 1] && _T('/') != wsTemp[wsTemp.length() - 1])
    {
        wsTemp.append(_T("\\"));
    }

    DogString rootPath(wsTemp);
    wsTemp.append(_T("*"));
    hFile = ::FindFirstFile(wsTemp.c_str(), &fileInfo);

    if (INVALID_HANDLE_VALUE == hFile)
    {
        return false;
    }

    do
    {
        //����ǵ�ǰĿ¼�������ϼ�Ŀ¼����ֱ�ӽ�����һ��ѭ��  
        if (_tcscmp(fileInfo.cFileName, _T(".")) == 0 ||
            _tcscmp(fileInfo.cFileName, _T("..")) == 0)
        {
            continue;
        }

        DogString subPath = rootPath + fileInfo.cFileName;
        if (IsDir(subPath))
        {
            if (!DeleteDir(subPath))
            {
                return false;
            }
        }
        else
        {
            if (!DeleteFile_(subPath))
            {
                return false;
            }
        }

    } while (::FindNextFile(hFile, &fileInfo));

    ::FindClose(hFile);
    ::RemoveDirectory(rootPath.c_str());
    return true;
}

bool dir_uitls::CreateDir(const DogString& dirPath)
{
	if (IsDirExist(dirPath))
	{
		return true;
	}

    return ::CreateDirectory(dirPath.c_str(), NULL) == TRUE;
}

bool dir_uitls::CreateDirEx(const DogString& dirPath)
{
    if (dirPath.empty())
    {
        return false;
    }

    if (IsDirExist(dirPath))
    {
        return true;
    }

    DogString tmp = _T("");
    tmp.resize(dirPath.size(), 0);

    for (size_t i = 0; i < dirPath.length(); ++i)
    {
        if (dirPath[i] == _T('\\') || dirPath[i] == _T('/'))
        {
            if (!CreateDir(tmp))
            {
                return false;
            }
        }
        
        tmp[i] = dirPath[i];
    }

    if (tmp[tmp.size() - 1] != _T('\\') && tmp[tmp.size() - 1] != _T('/'))
    {
        if (!CreateDir(tmp))
        {
            return false;
        }
    }

    return true;
}

void dir_uitls::EnumDir(const DogString& dirPath, std::function<void(const DogString& path, bool isDir)> callBack)
{
    DogString rootPath = dirPath;

    if (rootPath.length() < 2)
    {
        return;
    }

    if (rootPath[rootPath.length() - 1] != _DogT('/') &&
        rootPath[rootPath.length() - 1] != _DogT('\\'))
    {
        rootPath.append(1, _DogT('\\'));
    }

    if (callBack == NULL || !IsDirExist(rootPath))
    {
        return;
    }

    // ö��·��
    std::queue<DogString> dirPathQue;
    dirPathQue.push(rootPath);

    while (!dirPathQue.empty())
    {
        std::wstring path = dirPathQue.front();
        std::wstring pathRoot = dirPathQue.front();
        dirPathQue.pop();
        WIN32_FIND_DATA fileInfo;
        ::memset(&fileInfo, 0, sizeof(LPWIN32_FIND_DATA));
        path.append(L"*");
        HANDLE hFile = NULL;
        hFile = ::FindFirstFile(path.c_str(), &fileInfo);

        if (INVALID_HANDLE_VALUE == hFile)
        {
            continue;
        }

        do
        {
            //����ǵ�ǰĿ¼�������ϼ�Ŀ¼����ֱ�ӽ�����һ��ѭ��  
            if (::wcscmp(fileInfo.cFileName, L".") == 0 ||
                ::wcscmp(fileInfo.cFileName, L"..") == 0)
            {
                continue;
            }

            std::wstring subPath = pathRoot + fileInfo.cFileName;

            if (IsDir(subPath))
            {
                subPath += L"\\";
                dirPathQue.push(subPath);
                callBack(subPath, true);
            }
            else
            {
                callBack(subPath, false);
            }
        } while (::FindNextFile(hFile, &fileInfo));

        ::FindClose(hFile);
    }
}

void dir_uitls::EnumDir(const DogString & dirPath, std::vector<DogString>& out, std::function<bool(const DogString&, bool)> filter)
{
    EnumDir(dirPath, [filter, &out](const DogString& path, bool isDir)
    {
        if (filter == NULL || filter(path, isDir))
        {
            out.push_back(path);
            return;
        }

        return;
    });
}

bool dir_uitls::CreateFile_(const DogString& filePath)
{
    DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    DWORD dwShareMode = 0;
    LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0;
    DWORD dwCreationDisposition = CREATE_NEW;
    DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
    HANDLE hTemplateFile = 0;
    HANDLE handle = CreateFile(filePath.c_str(),
                               dwDesiredAccess,
                               dwShareMode,
                               lpSecurityAttributes,
                               dwCreationDisposition,
                               dwFlagsAndAttributes,
                               hTemplateFile);

    if (handle == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    ::CloseHandle(handle);
    return true;
}
