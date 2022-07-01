// created: 2022/07/01 17:30
// author:  rush
// email:   yacper@gmail.com
// 
// purpose:
// modifiers:

namespace NeoCtp.Enums;

public enum EFrontDisconnectedReason
{
    NetworkReadFail   = 0x1001, //  网络读失败
    NetworkWriteFail  = 0x1002, // 网络写失败
    HeartbeatTimeout  = 0x2001, // 接收心跳超时
    SendHeartbeatFail = 0x2002, // 发送心跳失败
    RcvWrongPacket    = 0x2003, // 收到错误报文
}