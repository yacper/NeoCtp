/********************************************************************
    created:	2022/7/1 17:31:32
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
using NeoCtp.Enums;

namespace NeoCtp.Api;

public class CtpRsp
{
    // 本地返回信息
    public ECtpRtn Rtn { get; protected set; } // 调用函数后直接返回

    // 服务器返回信息
    public int                    RequestId { get; protected set; }
    public bool                   IsLast    { get; protected set; }
    public CThostFtdcRspInfoField Rsp       { get; protected set; }

    public CtpRsp(ECtpRtn rtn) { Rtn = rtn; }

    public CtpRsp(CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast)
    {
        Rsp       = rsp;
        RequestId = nRequestID;
        IsLast    = bIsLast;
    }
}

public class CtpRsp<T2> : CtpRsp
{
    public T2 Rsp2 { get; set; }

    public CtpRsp(ECtpRtn rtn)
        : base(rtn)
    {
    }

    public CtpRsp(T2 rsp2, CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast)
        : base(rsp, nRequestID, bIsLast)
    {
        Rsp2 = rsp2;
    }
}

public class CtpRsp<T2, T3> : CtpRsp<T2>
{
    public T3 Rsp3 { get; set; }

    public CtpRsp(T3 rsp3, CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast, T2 rsp2)
        : base(rsp2, rsp, nRequestID, bIsLast)
    {
        Rsp3 = rsp3;
    }
}