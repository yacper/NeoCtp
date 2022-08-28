using System;

namespace NeoCtp.Tests
{
    internal class TestConstants
    {

        public const string MdFrontAddr = "tcp://180.168.146.187:10211"; // 模拟行情
        public const string MdFrontAddr24 = "tcp://180.168.146.187:10131"; // 模拟行情24小时

        public static string GetMdFrontAddr()
        {
            DateTime now = DateTime.Now;
            if(now.DayOfWeek == DayOfWeek.Sunday ||
               now.DayOfWeek == DayOfWeek.Saturday)
                return MdFrontAddr24;

            if ((now.Hour >= 9 && now.Hour < 16) ||
                (now.Hour >= 21 && now.Hour < 23) ||
                (now.Hour >= 0 && now.Hour < 3)
               )
                return MdFrontAddr;
            else
                return MdFrontAddr24;
        }

       /// <summary>
        /// 连接地址
        /// </summary>
        public const string TdFrontAddr = "tcp://180.168.146.187:10201"; // 模拟交易
        public const string TdFrontAddr24 = "tcp://180.168.146.187:10130";    // 模拟交易24小时
        public static string GetTdFrontAddr()
        {
            DateTime now = DateTime.Now;
            if(now.DayOfWeek == DayOfWeek.Sunday ||
               now.DayOfWeek == DayOfWeek.Saturday)
                return TdFrontAddr24;

            if ((now.Hour >= 9 && now.Hour < 16) ||
                (now.Hour >= 21 && now.Hour < 23) ||
                (now.Hour >= 0 && now.Hour < 3)
               )
                return TdFrontAddr;
            else
                return TdFrontAddr24;
        }

        /// <summary>
        /// 经纪商代码
        /// </summary>
        public const string BrokerID = "9999";

        /// <summary>
        /// 投资者账号
        /// </summary>
        public const string UserID = "097266";

        /// <summary>
        /// 密码
        /// </summary>
        public const string Password = "hello@1234";
    }
}
