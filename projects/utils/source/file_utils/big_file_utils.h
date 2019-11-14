
#ifndef __BIG_FILE_UTILS_H_
#define __BIG_FILE_UTILS_H_

#include "noncopyable/noncopyable.h"
#include "typedef/DogString.h"

#include <memory>

/** Ĭ���ļ����С10M
*/
static const int g_file_block_default_size = 1024 * 1024 * 10;

class BigFileMapper;

/** һ�����ļ����ļ���
*/
class FileBlock :
    public NonCopyable
{
public:
    /** ��������
    */
    ~FileBlock();

    /** ����ļ����С
    @return �ļ���Ĵ�С
    */
    inline int GetSize()
    {
        return m_blockSize;
    }

    /** ����������ļ�����ʼ��ַ
    @return �ļ������ʼ��ַ
    */
    inline char* GetBlockAddr()
    {
        return m_pBlock + m_offSet;
    }

private:
    /** �ļ�����ʼ��ַ
    */
    char* m_pBlock = NULL;

    /** �����ļ�ӳ��Ҫ��64k���룬���������offset���������Ŀ�ʼ
    */
    int m_offSet = 0;

    /** �ļ����С
    */
    int m_blockSize = 0;

    friend BigFileMapper;
};

using SPFileBlock = std::shared_ptr<FileBlock>;

/** �ڴ�ӳ���ļ���������ļ����ɶ�д���������ļ���С�ı��˵Ļ���Ҫ����ӳ��
*/
class BigFileMapper :
    public NonCopyable
{
public:
    /** ���캯��
    */
    BigFileMapper();

    /** ��������
    */
    ~BigFileMapper();

public:
    /** ��ʼ�����ظ����û������һ�ε�����
    @param [in] filePath �ļ�·��
    @return �Ƿ�ɹ�
    */
    bool MapFile(const DogString& filePath);

    /** ����ļ���С
    @return �ļ���С
    */
    inline long long GetFileSize()
    {
        return m_fileSize;
    }

    /** ����ļ������һ��
    @param [in] size ָ����С��B�������С�ڵ���0���ߴ���1G�Ļ�ʹ��Ĭ�ϴ�С�������ĩβ���루align != 0�����ص�block��С����ҪС��size
    @param [in] align size ָ���Ĵ�С���ܲ���һ�����ӵ�β�ͣ����Ի���ǰ�ҵ���һ������align�����������ַ���,align == 0 ˵�������룬Ĭ��"\n"
    @return �ļ����share_ptr�����Ϊ��˵��map���ļ�β����
    */
    SPFileBlock GetNextBlock(int sizeRaw = g_file_block_default_size, char align = '\n');

    /** ����ļ������һ��
    @param [in] beginPos ��ʼλ��
    @param [in] size ָ����С��B�������С�ڵ���0���ߴ���1G�Ļ�ʹ��Ĭ�ϴ�С�������ĩβ���루align != 0�����ص�block��С����ҪС��size
    @param [in] align size ָ���Ĵ�С���ܲ���һ�����ӵ�β�ͣ����Ի���ǰ�ҵ���һ������align�����������ַ���,align == 0 ˵�������룬Ĭ��"\n"
    @return �ļ����share_ptr�����Ϊ��˵��map���ļ�β����
    */
    SPFileBlock GetBlock(__int64 beginPos, int sizeRaw = g_file_block_default_size, char align = '\n');

private:
    /** �ļ�ӳ���ڴ�ľ��
    */
    void* m_hFileMap;

    /** ӳ���λ��
    */
    long long m_bginPos;

    /** �ļ�С
    */
    long long m_fileSize;
};

#endif //__BIG_FILE_UTILS_H_
