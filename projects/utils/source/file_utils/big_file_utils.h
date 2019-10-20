
#ifndef __BIG_FILE_UTILS_H_
#define __BIG_FILE_UTILS_H_

#include <string>
#include <functional>

/** һ��һ�еĶ��ļ� , ÿ�ζ�һ��wchar
@param [in] path ·��
@param [in] checker �ļ�ͷУ��
@param [in] checkSize checker�Ĵ�С
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool HandleBigFileByLineW(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback);


/** һ��һ�еĶ��ļ� , ÿ�ζ�һ��char
@param [in] path ·��
@param [in] checker �ļ�ͷУ��
@param [in] checkSize checker�Ĵ�С
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool HandleBigFileByLine(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::string&line)> callback);


#endif //__BIG_FILE_UTILS_H_
