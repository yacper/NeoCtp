/********************************************************************
    created:	2020-07-30 20:12:44
    author:		joshua
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SharpCtp
{
	/// <summary>
	/// 返回结果
	/// </summary>
	[Serializable]
	public class DataResult
	{
		/// <summary>
		/// 返回结果
		/// </summary>
		public object Result { get; set; }

		/// <summary>
		/// 是否成功
		/// </summary>
		public bool IsSuccess { get; set; }

		/// <summary>
		/// 错误信息
		/// </summary>
		public string Error { get; set; }

		/// <summary>
		/// 错误代码
		/// </summary>
		public string ErrorCode { get; set; }

		/// <summary>
		/// 返回代码
		/// </summary>
		public int ReturnCode { get; set; }
	}

	/// <summary>
	/// 返回结果
	/// </summary>
	/// <typeparam name="T">结果对象类型</typeparam>
	[Serializable]
	public class DataResult<T>
	{
		/// <summary>
		/// 返回结果
		/// </summary>
		public T Result { get; set; }

		/// <summary>
		/// 是否成功
		/// </summary>
		public bool IsSuccess { get; set; }

		/// <summary>
		/// 错误信息
		/// </summary>
		public string Error { get; set; }

		/// <summary>
		/// 错误代码
		/// </summary>
		public string ErrorCode { get; set; }

		/// <summary>
		/// 返回代码
		/// </summary>
		public int ReturnCode { get; set; }
	}

	/// <summary>
    /// 集合对象
    /// </summary>
    /// <typeparam name="T">集合元素类型</typeparam>
    [Serializable]
    public class DataListResult<T>
    {
        /// <summary>
        /// 返回结果
        /// </summary>
        public ObservableCollection<T> Result { get; set; }

        /// <summary>
        /// 是否成功
        /// </summary>
        public bool IsSuccess { get; set; }

        /// <summary>
        /// 错误信息
        /// </summary>
        public string Error { get; set; }

        /// <summary>
        /// 错误代码
        /// </summary>
        public string ErrorCode { get; set; }

        /// <summary>
        /// 返回代码
        /// </summary>
        public int ReturnCode { get; set; }

        /// <summary>
        /// 构造函数
        /// </summary>
        public DataListResult()
        {
            Result = new ObservableCollection<T>();
        }
    }


	/// <summary>
	/// 数据回调委托
	/// </summary>
	/// <param name="result">结果对象</param>
	public delegate void DataCallback(DataResult result);

	/// <summary>
	/// 数据回调委托
	/// </summary>
	/// <typeparam name="T">结果对象类型</typeparam>
	/// <param name="result">结果对象</param>
	public delegate void DataCallback<T>(DataResult<T> result);

	/// <summary>
	/// 数据列表回调委托
	/// </summary>
	/// <typeparam name="T">列表元素类型</typeparam>
	/// <param name="result">列表结果对象</param>
	public delegate void DataListCallback<T>(DataListResult<T> result);

	
}
