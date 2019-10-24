
#ifndef _LOGCONFIG_H_
#define _LOGCONFIG_H_

#include <string>


/** ��־�������ļ�
*/
class LogConfig
{
public:
    /** ���캯��
    */
    LogConfig();

    /** ���캯��������ʼ��
    @param [in] path �����ļ�·��
    */
    LogConfig(const std::wstring& path);

    LogConfig(const LogConfig&) = delete;
    LogConfig& operator=(const LogConfig&) = delete;

public:
    /** ��ʼ��
    @param [in] path �����ļ�·��
    */
    void Init(const std::wstring& path);

private:
    /** ��־���ƣ������Ҫд�ļ��Ļ��������ļ�����һ��Ŀ¼����
    */
    std::wstring m_name;

    /** ��־�ȼ�
    */
    int m_level;


};

#endif // !_LOGCONFIG_H_


