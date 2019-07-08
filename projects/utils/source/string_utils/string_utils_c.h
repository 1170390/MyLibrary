#ifndef __STRING_UTILS_C_H_
#define __STRING_UTILS_C_H_

/** char* �ַ�������
���������ַ�����Ҫ�ⲿ��֤��Ϊ������Ч
*/
namespace stringutils_c
{
    /** �ַ���ǰn���Ƚ�
    @param [in] src Դ
    @param [in] find �Ƚ�
    @param [in] n ����
    @param [in] icase �Ƿ���Դ�Сд
    @return 0 ��� > 0 src �� < 0 find ��
    */
    int    strncmp(const char* src, const char* find, int n, bool icase);

    /** �ַ����Ƚ�
    @param [in] src Դ
    @param [in] find �Ƚ�
    @param [in] icase �Ƿ���Դ�Сд
    @return 0 ��� > 0 src �� < 0 find ��
    */
    int    strcmp(const char* src, const char* find, bool icase);

    /** ��...��β
    @param [in] src Դ
    @param [in] find 
    @param [in] icase �Ƿ���Դ�Сд
    @return src�Ƿ���find��β
    */
    bool   strendof(const char* src, const char* find, bool icase);

    /** ��...��ʼ
    @param [in] src Դ
    @param [in] find
    @param [in] icase �Ƿ���Դ�Сд
    @return src�Ƿ���find��ʼ
    */
    bool   strbegof(const char* src, const char* find, bool icase);

    /** �ַ�������
    @param [in] src Դ
    @param [in] find
    @param [in] icase �Ƿ���Դ�Сд
    @return src �ҵ� find ? �ǣ������״γ��ֵĵ�ַ����0
    */
    char * strstr(const char* src, const char* find, bool icase);

    /** �ַ������� '*' ����һ�����߶�������ַ���'?' ����һ���ַ���UNICODE�����������ַ���
    @param [in] src Դ
    @param [in] find
    @param [in] icase �Ƿ���Դ�Сд
    @return src �ҵ� find ? �ǣ������״γ��ֵĵ�ַ����0
    */
    bool   strwildcard(const char* src, const char* find, bool icase);
}

#endif // __STRING_UTILS_C_H_
