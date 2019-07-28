
#ifndef __PRODUCER_H_
#define __PRODUCER_H_

#include "IGoods.h"
#include <functional>

/** �����߽ӿ�
*/
class IProducer
{
public:
    /** ����һ����Ʒ
    @param [in] functional 
    */
    virtual void Product(std::function<void(IGoods*)>) = 0;
    virtual ~IProducer() {}
};

#endif // __PRODUCER_H_
