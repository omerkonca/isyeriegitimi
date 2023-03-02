using System;
using System.IO;
using System.Net;

namespace WifiSpeedTest
{
    class Program
    {
        static void Main(string[] args)
        {
            // Önceki sonuçları saklamak için dosya oluşturma
            string path = "speedtest.txt";
            if (!File.Exists(path))
            {
                using (StreamWriter sw = File.CreateText(path))
                {
                    sw.WriteLine("Previous Speed Test Results:");
                }
            }

            // Hız testi yapmak için HTTP isteği gönderme
            string url = "http://speedtest.net/speedtest";
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Method = "GET";
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            Stream stream = response.GetResponseStream();
            StreamReader reader = new StreamReader(stream);

            // Yanıtı okuma ve hızları hesaplama
            string result = reader.ReadToEnd();
            string[] tokens = result.Split(new string[] { "server-config" }, StringSplitOptions.None);
            string downloadToken = tokens[1].Split(new string[] { "Download" }, StringSplitOptions.None)[1];
            string uploadToken = tokens[1].Split(new string[] { "Upload" }, StringSplitOptions.None)[1];
            double downloadSpeed = double.Parse(downloadToken.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)[1]);
            double uploadSpeed = double.Parse(uploadToken.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)[1]);

            // Konsola sonuçları yazdırma
            Console.WriteLine("Download Speed: " + downloadSpeed + " Mbps");
            Console.WriteLine("Upload Speed: " + uploadSpeed + " Mbps");

            // Sonuçları dosyaya yazdırma
            using (StreamWriter sw = File.AppendText(path))
            {
                sw.WriteLine(DateTime.Now.ToString() + " - Download: " + downloadSpeed + " Mbps, Upload: " + uploadSpeed + " Mbps");
            }

            Console.ReadLine();
        }
    }
}
