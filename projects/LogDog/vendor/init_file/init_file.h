#ifndef __INITFILE_H_
#define __INITFILE_H_

#include <vector>

#include "typedef/DogString.h"

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
    static IniFile * CreateObj(const DogString& sPath, bool bAlwaysCreate = false);

    /** ���һ��key
    @param [in] sSection ��һ��section������������򴴽�
    @param [in] sKey ��һ��key
    @param [in] sValue Ҫ���õ�ֵ
    @return �Ƿ�ɹ�
    */
    bool AddKey(const DogChar * sSection, const DogChar * sKey, const DogChar * sValue);

    /** ɾ��һ��key
    @param [in] sSection ��һ��section
    @param [in] sKey ��һ��key
    @return �Ƿ�ɹ�
    */
    bool DelKey(const DogChar * sSection, const DogChar * sKey);

    /** ɾ��һ��section
    @param [in] sSection ��һ��section
    @return �Ƿ�ɹ�
    */
    bool DelSection(const DogChar * sSection);

    /** �޸�һ��key��Ӧ��ֵ
    @param [in] sSection ��һ��section
    @param [in] sKey ��һ��key
    @param [in] sValue Ҫ���õ�ֵ
    @return �Ƿ�ɹ�
    */
    bool ChangKey(const DogChar * sSection, const DogChar * sKey, const DogChar * sValue);

    /** ���һ��key��Ӧ��ֵ
    @param [in] sSection ��һ��section sSection == NULL ʱ��ö�����е�section
    @param [in] sKey ��һ��key sKey == NULL ö��section�����е�key
    @param [in] size �ڲ�buff��С��Ĭ�ϵĲ����õ�ʱ��ָ��
    @return key��Ӧ��ֵ
    */
    std::vector<DogString> Get(const DogChar * sSection, const DogChar * sKey, const int size = 512);

private:
    /** ���캯��
    */
    IniFile(const DogString& sPath);

private:
    /** ȫ·��
    */
    DogString    m_sFileFullPath;
};

#endif
