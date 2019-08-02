
#ifndef __FILE_UTILS_WRITER_H_
#define __FILE_UTILS_WRITER_H_

#include <string>

/** �ļ���ȡ�࣬ÿ�ζ�ȡwchar
*/
class FileWriter
{
public:
    /** ���캯��
    */
    FileWriter(const std::wstring& path, const unsigned char * header, const size_t headSize);

    /** ��������
    */
    virtual ~FileWriter();

    /** �Ƿ��д��󣨴��ļ��Ƿ�ɹ���
    @return �Ƿ�ɹ�
    */
    inline bool HasError()
    {
        return m_pFile == NULL;
    }

    /** дwchar
    @param [in] buff ��������
    @param [in] size �����С��������
    @return �Ƿ�ɹ�
    */
    bool WriteBuffW(const wchar_t* buff, const size_t size);

    /** дchar
    @param [out] line ���
    @return �Ƿ�ɹ�
    */
    bool WriteBuffA(const char* buff, const size_t size);

protected:
    FILE* m_pFile;
};


/** ����һ��UCS-2 Little Endian ������ļ� ʹ��WriteBuffW()
@return FileReaderָ�룬�������Լ��ͷ�
*/
inline FileWriter* CreateUCS2File(const std::wstring& path)
{
    unsigned char header[] = {0xff, 0xfe, '\0'};
    FileWriter* pFileWriter = new (std::nothrow) FileWriter(path, header, 2);

    if (pFileWriter == NULL)
    {
        return NULL;
    }

    if (pFileWriter->HasError())
    {
        delete pFileWriter;
        return NULL;
    }
}

/** ����һ��UTF8 ������ļ� ʹ��WriteBuffA()
@return FileReaderָ�룬�������Լ��ͷ�
*/
inline FileWriter* CreateUTF8File(const std::wstring& path)
{
    FileWriter* pFileWriter = new (std::nothrow) FileWriter(path, NULL, 0);

    if (pFileWriter == NULL)
    {
        return NULL;
    }

    if (pFileWriter->HasError())
    {
        delete pFileWriter;
        return NULL;
    }
}

/** ����һ��UTF8 BOM ������ļ� ʹ��WriteBuffA()
@return FileReaderָ�룬�������Լ��ͷ�
*/
inline FileWriter* CreateUTF8BomFile(const std::wstring& path)
{
    unsigned char header[] = {0xef, 0xbb, 0xbf, '\0'};
    FileWriter* pFileWriter = new (std::nothrow) FileWriter(path, header, 3);

    if (pFileWriter == NULL)
    {
        return NULL;
    }

    if (pFileWriter->HasError())
    {
        delete pFileWriter;
        return NULL;
    }
}

#endif // __FILE_UTILS_WRITER_H_