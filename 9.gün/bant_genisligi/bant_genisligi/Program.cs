using System;
using System.Diagnostics;
using System.Net;
using System.Threading;

class BandwidthTester
{
    static void Main(string[] args)
    {
        // İndirme işleminin yapılacağı dosyanın URL'sini tanımla
        string url = "https://speed.hetzner.de/1GB.bin";

        // İndirme işlemi için kullanılacak WebClient nesnesini yarat
        WebClient wc = new WebClient();

        // İndirme işlemi başlamadan önce geçen süreyi hesaplamak için Stopwatch nesnesi yarat
        Stopwatch sw = new Stopwatch();
        sw.Start();

        // İndirme işlemi başlamadan önce ağ trafiğini ölçmek için NetworkInterface'ı yarat
        var interfaceStats = System.Net.NetworkInformation.NetworkInterface.GetAllNetworkInterfaces()[0].GetIPv4Statistics();

        // İndirme işlemi başlat
        byte[] data = wc.DownloadData(url);

        // İndirme işlemi bittiğinde geçen süreyi ve indirilen verinin boyutunu hesapla
        sw.Stop();
        double elapsedTime = sw.Elapsed.TotalSeconds;
        double dataSize = (double)data.Length / 1024 / 1024;

        // İndirme işlemi sırasında ağ trafiğinin toplam boyutunu hesapla
        long totalBytes = interfaceStats.BytesReceived + interfaceStats.BytesSent;
        double totalData = (double)totalBytes / 1024 / 1024;

        // İndirme işlemi sırasında geçen süreyi hesapla
        double totalElapsedTime = elapsedTime;

        // Bant genişliğini (MB/s cinsinden) hesapla ve ekrana yazdır
        double bandwidth = totalData / totalElapsedTime;
        Console.WriteLine("Bant genişliği: " + bandwidth.ToString("0.00") + " MB/s");

        // Programın kapatılması için bir tuşa basılmasını bekle
        Console.WriteLine("\nProgramı kapatmak için bir tuşa basın...");
        Console.ReadKey();
    }
}
