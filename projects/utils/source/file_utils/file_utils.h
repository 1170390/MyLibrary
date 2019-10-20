#ifndef __FILE_UTILS_H_
#define __FILE_UTILS_H_

#include <string>
#include <functional>

/** һ��һ�еĶ��ļ� , ÿ�ζ�һ��wchar
@param [in] path ·��
@param [in] checker �ļ�ͷУ��
@param [in] checkSize checker�Ĵ�С
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool ReadFileByLineW(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback);

/** һ��һ�еĶ��ļ� UCS-2 Little Endian ����
@param [in] path ·��
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool ReadUCS2FileByLine(const std::wstring& path, std::function<bool(const std::wstring&line)> callback);

/** һ��һ�еĶ��ļ� , ÿ�ζ�һ��char
@param [in] path ·��
@param [in] checker �ļ�ͷУ��
@param [in] checkSize checker�Ĵ�С
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool ReadFileByLine(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::string&line)> callback);

/** һ��һ�еĶ��ļ� UTF8 ����
@param [in] path ·��
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool ReadUTF8FileByLine(const std::wstring& path, std::function<bool(const std::string&line)> callback);

/** һ��һ�еĶ��ļ� UTF8-Bom ����
@param [in] path ·��
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool ReadUTF8BomFileByLine(const std::wstring& path, std::function<bool(const std::string&line)> callback);

/** д�ļ�
@param [in] path ·��
@param [in] header �ļ�ͷУ��
@param [in] headSize header�Ĵ�С
@param [in] callback �ص����� ��������׼�����ݣ�׼����֮�����callback��callback
            WriteUCS2FileByBuff(L"D:\\test\\2.txt", [&buff](std::function<bool(void*, size_t)> callback){return true});
@return �Ƿ�ɹ�
*/
bool WriteFileByBuff(const std::wstring& path, const unsigned char* header, const size_t headSize, std::function<bool(std::function<bool(void*, size_t)>)> callback);

/** д�ļ� UCS-2 Little Endian ����
@param [in] path ·��
@param [in] callback �ص����� ��������׼�����ݣ�׼����֮�����callback��callback
            WriteUCS2FileByBuff(L"D:\\test\\2.txt", [&buff](std::function<bool(void*, size_t)> callback){return true});
@return �Ƿ�ɹ�
*/
bool WriteUCS2FileByBuff(const std::wstring& path, std::function<bool(std::function<bool(void*, size_t)>)> callback);

#endif //__FILE_UTILS_H_
