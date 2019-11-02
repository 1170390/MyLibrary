#ifndef _FILE_AND_DIR_UTIL_H__
#define _FILE_AND_DIR_UTIL_H__

#include "typedef/DogString.h"

#include <string>

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
}

#endif // _FILE_AND_DIR_UTIL_H__