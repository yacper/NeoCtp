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
    public ECtpExecuteRtn ExecuteRtn { get; protected set; } // 调用函数后直接返回

    // 服务器返回信息
    public int                    RequestID { get; set; }
    public bool                   IsLast    { get; set; } = true;
    public CThostFtdcRspInfoField Rsp       { get; set; }

    public CtpRsp() {  }
    public CtpRsp(ECtpExecuteRtn executeRtn) { ExecuteRtn = executeRtn; }

    public CtpRsp(CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast)
    {
        Rsp       = rsp;
        RequestID = nRequestID;
        IsLast    = bIsLast;
    }

    public override string ToString()
    {
        if (Rsp.ErrorID != 0)
        {
            return $"Ctp Rsp Error:{Rsp.ErrorID} Msg:{Rsp.ErrorMsg} RequestID:{RequestID}";
        }
        else
            return $"Ctp local call Error:{ExecuteRtn}";
    }
}

public class CtpRsp<T2> : CtpRsp
{
    public T2 Rsp2 { get; set; }

    public CtpRsp() {  }
    public CtpRsp(ECtpExecuteRtn executeRtn)
        : base(executeRtn)
    {
    }

    public CtpRsp(T2 rsp2, CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast)
        : base(rsp, nRequestID, bIsLast)
    {
        Rsp2 = rsp2;
    }

    public override string ToString()
    {
        if (Rsp.ErrorID != 0)
        {
            return $"Ctp Rsp Error:{Rsp.ErrorID} Msg:{Rsp.ErrorMsg} RequestID:{RequestID} \n {Rsp2.Dump()}";
        }
        else
            return $"Ctp local call Error:{ExecuteRtn}";
    }

}

public class CtpRsp<T2, T3> : CtpRsp<T2>
{
    public T3 Rsp3 { get; set; }

    public CtpRsp() {  }

    public CtpRsp(ECtpExecuteRtn executeRtn)
        : base(executeRtn)
    {
    }

    public CtpRsp(T3 rsp3, T2 rsp2, CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast)
        : base(rsp2, rsp, nRequestID, bIsLast)
    {
        Rsp3 = rsp3;
    }

    public override string ToString()
    {
        if (Rsp.ErrorID != 0)
        {
            return $"Ctp Rsp Error:{Rsp.ErrorID} Msg:{Rsp.ErrorMsg} RequestID:{RequestID} \n {Rsp2.Dump()} \n {Rsp3.Dump()}";
        }
        else
            return $"Ctp local call Error:{ExecuteRtn}";
    }


}