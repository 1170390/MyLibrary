
#ifndef __HTTP_UTILS_H_
#define __HTTP_UTILS_H_

#include "SocketHttpClient.h"

namespace DogHttp
{
    /** http Get����
    @param[in] url�����url
    @param[out] out���󷵻صĽ�����ɹ�����������ͷ�����ɹ�ֻ��������ͷ��
    @return �Ƿ�ɹ���ֻ�з���ͷΪ2XX����ɹ�
    */
    bool HttpGet(const DogStringA& url, DogStringA& out);

    /** http Post����
    @param[in] url�����url
    @param[in] data�����body
    @param[out] out���󷵻صĽ�����ɹ�����������ͷ�����ɹ�ֻ��������ͷ��
    @return �Ƿ�ɹ���ֻ�з���ͷΪ2XX����ɹ�
    */
    bool HttpPost(const DogStringA& url, const DogStringA& data, DogStringA& out);
}

#endif //__HTTP_UTILS_H_
