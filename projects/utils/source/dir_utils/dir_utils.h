#ifndef _FILE_AND_DIR_UTIL_H__
#define _FILE_AND_DIR_UTIL_H__

#include "typedef/DogString.h"

#include <string>
#include <vector>
#include <functional>

namespace dir_uitls
{
    /** �Ƿ����ļ���
    @param [in] path ·��
    */
    bool IsDir(const DogString& path);

    /** �ж��ļ��Ƿ����
    @param [in] filePath �ļ�·��
    */
    bool IsFileExist(const DogString& filePath);

    /** �ж��ļ����Ƿ����
    @param [in] dirPath �ļ���·��
    */
    bool IsDirExist(const DogString& dirPath);

    /** �ж��ļ����ļ����Ƿ����
    @param [in] path ·��
    */
    bool IsPathExist(const DogString& path);

    /** �����ļ�
    @param [in] filePath �ļ�·��
    */
    bool CreateFile_(const DogString& filePath);

    /** ɾ���ļ���
    @param [in] dfilePath �ļ�·��
    */
    bool DeleteFile_(const DogString& dfilePath);

    /** ɾ���ļ���
    @param [in] dirPath �ļ���·��
    */
    bool DeleteDir(const DogString& dirPath);

    /** �����ļ���
    @param [in] dirPath �ļ���·��
    */
    bool CreateDir(const DogString& dirPath);

    /** �����ļ���(Ƕ�״���)
    @param [in] dirPath �ļ���·��
    */
    bool CreateDirEx(const DogString& dirPath);

    /** ö��Ŀ¼ �������
    @param [in] dirPath Ŀ¼·��
    @param [in] callBack �ص���������ÿһ��·�����д���
                @param [in] path ·��
                @param [in] isDir �Ƿ���Ŀ¼
    */
    void EnumDir(const DogString& dirPath, std::function<void(const DogString& path, bool isDir)> callBack);

    /** ö��Ŀ¼ �������
    @param [in] dirPath Ŀ¼·��
    @param [in] out ���·��vector
    @param [in] filter ��ÿһpath���й��ˣ�����true��ŵ�out����У����򶪵���filterΪ��ʱ��������true
                @param [in] path ·��
                @param [in] isDir �Ƿ���Ŀ¼
                @return true ��path�ŵ�out�����false ����
    */
    void EnumDir(const DogString& dirPath, std::vector<DogString>& out, std::function<bool(const DogString& path, bool isDir)> filter);
}

#endif // _FILE_AND_DIR_UTIL_H__