using System;
using System.Diagnostics;
using System.Net;
using System.Net.NetworkInformation;

public class InternetSpeedTest
{

    public static void Main(string[] args)
    {
        Ping ping = new Ping();
        Stopwatch stopwatch = new Stopwatch();
        string url = "192.168.1.1";
        int timeout = 120;

        while (true)
        {
            Console.WriteLine("Testing download speed...");
            stopwatch.Start();
            using (var client = new WebClient())
            {
                try
                {
                    client.DownloadString(url);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
            stopwatch.Stop();
            double downloadSpeed = Math.Round((double)(8 * 1000) / stopwatch.ElapsedMilliseconds, 2);
            Console.WriteLine($"Download speed: {downloadSpeed} kbps");

            Console.WriteLine("\nTesting upload speed...");
            stopwatch.Reset();
            byte[] data = new byte[1024];
            new Random().NextBytes(data);
            stopwatch.Start();
            try
            {
                ping.Send(url, timeout, data);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            stopwatch.Stop();
            double uploadSpeed = Math.Round((double)(8 * data.Length) / (stopwatch.ElapsedMilliseconds * 1000), 2);
            Console.WriteLine($"Upload speed: {uploadSpeed} kbps");

            Console.WriteLine("\n--------------------------------------------------\n");

            // 5 saniye bekleyerek tekrar başlat
            System.Threading.Thread.Sleep(1000);
        }
    }
}
