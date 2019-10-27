#ifndef __SIGLETON_CLASS_H_
#define __SIGLETON_CLASS_H_

template<class T>
class SingletonWrapper : public T
{
};


/** ����ģʽ
*/
template <class T>
class Singleton
{
public:
    static T& GetInstance()
    {
        // Ϊ���ܹ���main����ǰ��ʼ��s_pInstance
        s_pInstance;
        static SingletonWrapper<T> instance;
        return *static_cast<T *>(&instance);
    }

private:
    Singleton()
    {
    }

    Singleton(const Singleton&)
    {
    }

    Singleton& operator = (const Singleton&)
    {
    }

    ~Singleton()
    {
    }

    /** ǿ�ƶ���ģʽ������д����Ҫ��Ϊ�˷�ֹ��ʼ����������
    */
    static T* s_pInstance;
};

template<class T>
T* Singleton<T>::s_pInstance = &Singleton<T>::GetInstance();

#endif // __SIGLETON_CLASS_H_
