#ifndef __INITFILE_H_
#define __INITFILE_H_

#include <string>

/** windows ini �ļ��Ķ�д��
*/
class IniFile
{
public:
    ~IniFile();

    /** ����һ��ʵ��
    @param [in] sPath �ļ�·��
    @param [in] bAlwaysCreate �ļ�������ʱ�Ƿ��Զ��������ļ�������ʱ���Ϊfalse������0�������Զ������ļ�
    @return ����ʵ���������Լ��ͷ��ڴ�
    */
    static IniFile * CreateObj(const std::string sPath, bool bAlwaysCreate = false);

    /** ���һ��key
    @param [in] sSection ��һ��section������������򴴽�
    @param [in] sKey ��һ��key
    @param [in] sValue Ҫ���õ�ֵ
    @return �Ƿ�ɹ�
    */
    bool AddKey(const char * sSection, const char * sKey, const char * sValue);

    /** ɾ��һ��key
    @param [in] sSection ��һ��section
    @param [in] sKey ��һ��key
    @return �Ƿ�ɹ�
    */
    bool DelKey(const char * sSection, const char * sKey);

    /** ɾ��һ��section
    @param [in] sSection ��һ��section
    @return �Ƿ�ɹ�
    */
    bool DelSection(const char * sSection);

    /** �޸�һ��key��Ӧ��ֵ
    @param [in] sSection ��һ��section
    @param [in] sKey ��һ��key
    @param [in] sValue Ҫ���õ�ֵ
    @return �Ƿ�ɹ�
    */
    bool ChangKey(const char * sSection, const char * sKey, const char * sValue);

    /** ���һ��key��Ӧ��ֵ
    @param [in] sSection ��һ��section
    @param [in] sKey ��һ��key
    @return key��Ӧ��ֵ
    */
    std::string GetKey(const char * sSection, const char * sKey);

private:
    /** ���캯��
    */
    IniFile(std::string sPath);

private:
    /** ȫ·��
    */
    std::string    m_sFileFullPath;
};

#endif
