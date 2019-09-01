
#ifndef __SOCKET_UTILS_H_
#define __SOCKET_UTILS_H_

#include <string>

struct hostent;

class SocketUtils
{
public:
    /** ���س��������еĻ�������������
    @param [out] name ������� �������еĻ�������������
    @return �Ƿ�ɹ�
    */
    static bool GetHostName(std::string& name);

    /** ͨ���������������ַ��ػ�����IP��ַ
        h_name �C ��ַ����ʽ���ơ�
        h_aliases �C ���ֽ�-��ַ��Ԥ�����Ƶ�ָ�롣
        h_addrtype �C��ַ����; ͨ����AF_INET��
        h_length �C ��ַ�ı��س��ȡ�
        h_addr_list �C ���ֽ�-���������ַָ�롣�����ֽ�˳��
        h_addr - h_addr_list�еĵ�һ��ַ��
        gethostbyname() �ɹ�ʱ����һ��ָ��ṹ�� hostent ��ָ�룬���� �Ǹ��� (NULL) ָ�롣
    @param [int] name ������� �������еĻ�������������
    @return hostent
    */
    static hostent* GetHostByName(const std::string& name);
};

#endif //__SOCKET_UTILS_H_
