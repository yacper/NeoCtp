/********************************************************************
    created:	2020-08-06 11:53:10
    author:		rush
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Resources;
using NeoCtp.Imp;

namespace NeoCtp
{
	public struct Error
	{
		public string		id { get; set; }
		public int			value { get; set; }
		public string		prompt { get; set; }
	}

	public static class CtpError
	{
        static Dictionary<int, Error> _Errors = new Dictionary<int, Error>();

        public static Error? GetError(int id)
        {
	        if (!_Errors.Any())
	        {
				Uri uri = new Uri("/NeoCtp;component/Resources/error.xml", UriKind.Relative);
				StreamResourceInfo info = Application.GetResourceStream(uri);

				using (StreamReader reader = new StreamReader(info.Stream))
				{
					 string xml = reader.ReadToEnd();

					 string json = JsonEx.Xml2Json(xml, "errors");

					 List<Error> errors = json.ToJsonObj<List<Error>>();

					 errors.ForEach(p=>_Errors.Add(p.value, p));
				}
			}

	        Error ret;
	        if (_Errors.TryGetValue(id, out ret))
		        return ret;
	        else
		        return null;
        }

	
	}
}
