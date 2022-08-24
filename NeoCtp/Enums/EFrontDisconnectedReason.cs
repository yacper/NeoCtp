// created: 2022/07/01 17:30
// author:  rush
// email:   yacper@gmail.com
// 
// purpose:
// modifiers:

namespace NeoCtp.Enums;

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败 4097
///        0x1002 网络写失败 4098
///        0x2001 接收心跳超时 8193
///        0x2002 发送心跳失败 8194
///        0x2003 收到错误报文 8195
public enum EFrontDisconnectedReason
{
    NetworkReadFail   = 0x1001, //  网络读失败
    NetworkWriteFail  = 0x1002, // 网络写失败
    HeartbeatTimeout  = 0x2001, // 接收心跳超时
    SendHeartbeatFail = 0x2002, // 发送心跳失败
    RcvWrongPacket    = 0x2003, // 收到错误报文
}