using System.Net.NetworkInformation;


class PingStats
{
    public int Sent { get; set; }
    public int Received { get; set; }
    public int Lost { get { return Sent - Received; } }
    public double SuccessRate { get { return (double)Received / Sent * 100; } }
    public double AverageRoundtripTime { get { return RoundtripTimes.Count > 0 ? RoundtripTimes.Average() : 0; } }
    public List<long> RoundtripTimes { get; set; } = new List<long>();
}

class Program
{
    static void Main(string[] args)
    {
        string ipAddress = "192.168.68.1"; // Ping gönderilecek hedef IP adresi
        int interval = 1000; // Ping istekleri arasındaki süre (milisaniye cinsinden)
        int duration = 60000; // Ping istekleri gönderilecek süre (milisaniye cinsinden)

        PingStats stats = new PingStats(); // Ping istatistiklerini tutan nesne

        Ping pingSender = new Ping();
        PingOptions options = new PingOptions();
        byte[] buffer = new byte[32];

        DateTime startTime = DateTime.Now;
        while (DateTime.Now - startTime < TimeSpan.FromMilliseconds(duration))
        {
            PingReply reply = pingSender.Send(ipAddress, interval, buffer, options);
            if (reply.Status == IPStatus.Success)
            {
                stats.Received++;
                stats.RoundtripTimes.Add(reply.RoundtripTime);
                Console.WriteLine("Ping işlemi başarılı! Gecikme süresi: " + reply.RoundtripTime + " ms");
            }
            else
            {
                Console.WriteLine("Ping işlemi başarısız: " + reply.Status.ToString());
            }

            stats.Sent++;
            Thread.Sleep(interval);
        }

        Console.WriteLine("Ping istekleri: " + stats.Sent);
        Console.WriteLine("Başarılı ping istekleri: " + stats.Received);
        Console.WriteLine("Kaybedilen ping istekleri: " + stats.Lost);
        Console.WriteLine("Başarı oranı: " + stats.SuccessRate + "%");
        Console.WriteLine("Ortalama gecikme süresi: " + stats.AverageRoundtripTime + " ms");
        Console.WriteLine("En düşük gecikme süresi: " + stats.RoundtripTimes.Min() + " ms");
        Console.WriteLine("En yüksek gecikme süresi: " + stats.RoundtripTimes.Max() + " ms");

        Console.ReadKey();
    }
}


