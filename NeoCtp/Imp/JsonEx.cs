/********************************************************************
    created:	2019/12/17 17:34:59
    author:		rush
    email:		
	
    purpose:	newtonjson的扩展
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;
using Exception = System.Exception;

namespace NeoCtp.Imp
{
    public static class JsonEx
    {
        public static JsonSerializerSettings _settings = new JsonSerializerSettings()
        {
            Converters = new List<JsonConverter>()
            {
                new Newtonsoft.Json.Converters.StringEnumConverter(),
                new DoubleExConverter(),
            }
        };
        public static string ToJson(this object o)
        {
            return JsonConvert.SerializeObject(o, _settings);
        }
        public static bool ToJsonFile(this object o, string path)
        {
            try
            {
                string str = o.ToJson();
                File.WriteAllText(path, str);
                return true;
            }
            catch (System.Exception)
            {
            }

            return false;
        }

        public static string ToJsonNoLoop(this object o)
        {
            JsonSerializerSettings settings = new JsonSerializerSettings();
            settings.ReferenceLoopHandling = ReferenceLoopHandling.Ignore;
            settings.Converters = new List<JsonConverter>()
                                  {
                                      new Newtonsoft.Json.Converters.
                                          StringEnumConverter(),
                new DoubleExConverter(),
                                  };
            return JsonConvert.SerializeObject(o, settings);
        }

        public static bool ToJsonNoLoopFile(this object o, string path)
        {
            try
            {
                string str = o.ToJsonNoLoop();
                File.WriteAllText(path, str);
                return true;
            }
            catch (Exception e)
            {
            }

            return false;
        }

        public static object ToJsonObj(this string o, Type t)
        {
            if (string.IsNullOrWhiteSpace(o))
                return null;

            return JsonConvert.DeserializeObject(o, t, _settings);
        }

        public static T ToJsonObj<T>(this string o)
        {
            if (string.IsNullOrWhiteSpace(o))
                return default(T);

            return JsonConvert.DeserializeObject<T>(o, _settings);
        }

        public static T FileToJsonObj<T>(this string o)
        {
            if (string.IsNullOrWhiteSpace(o))
                return default(T);

            try
            {
                if (File.Exists(o))
                {
                    string str = File.ReadAllText(o);
                    return ToJsonObj<T>(str);
                }
            }
            catch (Exception e)
            {
            }

            return default(T);
        }

        #region Json 与Xml

        public static string Xml2Json(string str, string nodename)
        {
            string result = null;
            XmlDocument xmldoc = new XmlDocument();
            xmldoc.LoadXml(str);
            XmlNode node = xmldoc.SelectSingleNode(nodename);
            result = Newtonsoft.Json.JsonConvert.SerializeXmlNode(node);
            return result;
        }

        public static string Json2Xml(string str)
        {
            string result = null;
            XmlDocument xml = Newtonsoft.Json.JsonConvert.DeserializeXmlNode(str);
            result = xml.OuterXml;
            return result;
        }


        #endregion

    }



    //public class NAConverter : JsonConverter   // N/A
    //{
    //    public override bool CanRead
    //    {
    //        get
    //        {
    //            return true;
    //        }
    //    }
    //    public override bool CanWrite
    //    {
    //        get
    //        {
    //            return true;
    //        }
    //    }
    //    public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
    //    {
    //        if (value == null)
    //        {
    //            writer.WriteNull();
    //            return;
    //        }

    //        var val = Convert.ToDouble(value);
    //        if (Double.IsNaN(val) || Double.IsInfinity(val))
    //        {
    //            writer.WriteNull();
    //            return;
    //        }
    //        // Preserve the type, otherwise values such as 3.14f may suddenly be
    //        // printed as 3.1400001049041748.
    //        if (value is float)
    //            writer.WriteValue((float)value);
    //        else
    //            writer.WriteValue((double)value);
    //    }
    //    public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
    //    {
    //        var type = reader.TokenType;

    //        //获取JObject对象，该对象对应着我们要反序列化的json
    //            var jobj = serializer.Deserialize<JObject>(reader);

    //        var unit = jobj.Value<string>("unit");


    //        string tempStr = reader.ReadAsString();


    //        double temp;

    //        if (!Double.TryParse(tempStr, out temp))
    //        {
    //            if (tempStr == "N/A" ||
    //                tempStr == "NA" )
    //                return double.NaN;
    //        }

    //        return temp;
    //    }
    //    public override bool CanConvert(Type objectType)
    //    {
    //        return objectType == typeof(double) || objectType == typeof(float);
    //    }

    //    public string Key { get; set; }
    //}

    public class DoubleExConverter : JsonConverter
    {
        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            //if (value == null)
            //{
            //    writer.WriteNull();
            //    return;
            //}

            //Enum e = (Enum)value;

            //if (!EnumUtils.TryToString(e.GetType(), value, NamingStrategy, out string? enumName))
            //{
            //    if (!AllowIntegerValues)
            //    {
            //        throw JsonSerializationException.Create(null, writer.ContainerPath, "Integer value {0} is not allowed.".FormatWith(CultureInfo.InvariantCulture, e.ToString("D")), null);
            //    }

            //    // enum value has no name so write number
            //    writer.WriteValue(value);
            //}
            //else
            //{
            //    writer.WriteValue(enumName);
            //}
        }
        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            double ret = Double.NaN;
            try
            {
                switch (reader.TokenType)
                {
                    case JsonToken.Null:
                        return double.NaN;
                    case JsonToken.String:
                        {
                            string text = reader.Value?.ToString();
                            if (double.TryParse(text, out ret))
                                return ret;

                            //if (text == "N/A" ||
                            //    text == "NA")
                            //    return double.NaN;
                        }
                        break;
                    case JsonToken.Float:
                    case JsonToken.Integer:
                        return Convert.ToDouble(reader.Value);
                }
            }
            catch (Exception)
            {
                return ret;
            }

            return ret;
        }

        public override bool CanConvert(Type t)
        {
            // check if numeric
            switch (Type.GetTypeCode(t))
            {
                case TypeCode.Byte:
                case TypeCode.SByte:
                case TypeCode.UInt16:
                case TypeCode.UInt32:
                case TypeCode.UInt64:
                case TypeCode.Int16:
                case TypeCode.Int32:
                case TypeCode.Int64:
                case TypeCode.Decimal:
                case TypeCode.Double:
                case TypeCode.Single:
                    return true;
                default:
                    return false;
            }
        }

        public override bool CanWrite => false;

    }


}
