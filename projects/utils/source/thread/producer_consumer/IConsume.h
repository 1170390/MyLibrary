
#ifndef __CONSUMER_H_
#define __CONSUMER_H_
#include "IGoods.h"

/** �����߽ӿ�
*/
class IConsumer
{
public:
    /** ����һ����Ʒ���������Ժ����ͷ������Ʒ
    @param [in] goods ��Ʒָ��
    @return �Ƿ�ɹ�
    */
    virtual bool Consumer(IGoods* goods) = 0;
    virtual ~IConsumer() {}
};

#endif // __CONSUMER_H_



