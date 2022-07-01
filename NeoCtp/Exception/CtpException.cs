/********************************************************************
    created:	2022/7/1 15:55:54
    author:		rush
    email:		yacper@gmail.com	
	
    purpose:
    modifiers:	
*********************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NeoCtp.Exception
{
public class CtpException : System.Exception
{
    /// <summary>
    /// 错误代码
    /// </summary>
    public int ErrorID { get; protected set; }

    /// <summary>
    /// 错误信息
    /// </summary>
    public string ErrorMsg { get; protected set; }

    public int  RequestId { get; protected set; }
    public bool IsLast    { get; protected set; }


    public CtpException(CtpRsp rsp)
    {
        RequestId = rsp.RequestId;
        IsLast    = rsp.IsLast;
        ErrorID   = rsp.Rsp.ErrorID;
        ErrorMsg  = rsp.Rsp.ErrorMsg;
    }
}
}