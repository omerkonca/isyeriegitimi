using System;
using System.Diagnostics;
using System.Net.NetworkInformation;

public class NetworkMonitor
{
    private readonly string _interfaceName;
    private readonly PerformanceCounter _bytesSentCounter;
    private readonly PerformanceCounter _bytesReceivedCounter;

    public NetworkMonitor(string interfaceName)
    {
        _interfaceName = interfaceName;

        _bytesSentCounter = new PerformanceCounter("Network Interface", "Bytes Sent/sec", _interfaceName);
        _bytesReceivedCounter = new PerformanceCounter("Network Interface", "Bytes Received/sec", _interfaceName);
    }

    public void Start()
    {
        Console.WriteLine("Gerçek zamanlı ağ trafiği ölçümü başladı...");

        while (true)
        {
            long bytesSent = (long)_bytesSentCounter.NextValue();
            long bytesReceived = (long)_bytesReceivedCounter.NextValue();

            Console.WriteLine($"Gönderilen: {bytesSent / 1024} KB/s, Alınan: {bytesReceived / 1024} KB/s");

            System.Threading.Thread.Sleep(1000);
        }
    }
}

public class Program
{
    public static void Main()
    {
        // Ağ arayüzü seçimi
        string interfaceName = "Ethernet0"; // Değiştirin

        // Gerçek zamanlı ağ trafiği ölçümü
        NetworkMonitor monitor = new NetworkMonitor(interfaceName);
        monitor.Start();
    }
}