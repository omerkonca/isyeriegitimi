using System;
using System.Net.NetworkInformation;
using System.Threading;

class Program
{
    static void Main(string[] args)
    {
        while (true)
        {
            long wifiBandwidth = MeasureWifiBandwidth();
            Console.WriteLine("WiFi bant genişliği: {0} bps", wifiBandwidth);
            Thread.Sleep(1000); // 1 saniye bekle
        }
    }

    static long MeasureWifiBandwidth()
    {
        long bandwidth = 0;
        NetworkInterface[] interfaces = NetworkInterface.GetAllNetworkInterfaces();
        foreach (NetworkInterface networkInterface in interfaces)
        {
            if (networkInterface.NetworkInterfaceType == NetworkInterfaceType.Wireless80211 && networkInterface.OperationalStatus == OperationalStatus.Up)
            {
                IPv4InterfaceStatistics statistics = networkInterface.GetIPv4Statistics();
                bandwidth = networkInterface.Speed;
            }
        }
        return bandwidth;
    }
}
