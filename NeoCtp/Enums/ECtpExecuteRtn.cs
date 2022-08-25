// created: 2022/07/01 17:31
// author:  rush
// email:   yacper@gmail.com
// 
// purpose:
// modifiers:

namespace NeoCtp.Enums;

public enum ECtpExecuteRtn // 本地调用结果
{
    Sucess           = 0,  // 成功
    NetworkFailure   = -1, // 网络连接失败
    ExceedUnHandled  = -2, // 未处理请求超过许可数
    ExceedPerSeceond = -3, // 每秒发送请求超过许可数
}