
/****************************************************************************/
/* 提供一个使用的方法，用户可以根据需求重新改写该文件                               */
/****************************************************************************/

#ifndef _LOGDOG_H__
#define _LOGDOG_H__

#include "ILog.h"
#include "LogDogConfig.h"

#include "singleton/singleton.h"
#include "thread/task/SimpleTaskThread.h"
#include <functional>
#include <unordered_map>
#include <thread>

/** 日志对象管理类，用户可以根据需求重新改写
*/
class LogDog :
    public NonCopyable
{
protected:
    /** 构造函数
    */
    LogDog();

public:
    /** 初始化
    @param [in] path 配置文件路径
    @param [in] name 配置文件中对应的secsion
    @return 日志线程是否创建成功
    */
    bool Init(const DogString& path, const DogString& name);

    /** 释放资源，其实这个函数并不是很重要，因为单例在程序退出的时候会自己释放的，
    只是为了和init想对应
    */
    void UnInit();

    /** 向队列中压入一个日志
    */
    void Push(const std::shared_ptr<ILog>& log);

    /** 获得配置
    @return 配置
    */
    std::shared_ptr<LogDogConfig> GetConfig();

private:
    /** 日志任务队列
    */
    std::shared_ptr<SimpleTaskThread> m_spLogQue;

    /** 日志配置
    */
    std::shared_ptr<LogDogConfig> m_spConfig;
};

#endif

