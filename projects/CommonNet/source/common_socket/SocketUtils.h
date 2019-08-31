
#ifndef __SOCKET_UTILS_H_
#define __SOCKET_UTILS_H_

#include <string>

class SocketUtils
{
public:
    /** ���س��������еĻ�������������
    @param [out] name ������� �������еĻ�������������
    @return �Ƿ�ɹ�
    */
    static bool GetHostName(std::string& name);

    /** ͨ���������������ַ��ػ�����IP��ַ
    @param [int] name ������� �������еĻ�������������
    @return hostent
    */
    static hostent* GetHostByName(const std::string& name);
};

#endif //__SOCKET_UTILS_H_
