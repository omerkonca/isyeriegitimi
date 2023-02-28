using System;
using System.Net.NetworkInformation;
using System.Threading;

class Program
{
    static void Main()
    {
        // IP adresi belirleme
        string ipAddress;
        Console.Write("ip adresi giriniz: ");
        ipAddress = Console.ReadLine();

        while (true)
        {
            // Ping gönderme
            Ping pingSender = new Ping();
            PingReply reply = pingSender.Send(ipAddress);

            // Ping sonucunu ekrana yazdırma
            if (reply.Status == IPStatus.Success)
            {
                Console.WriteLine("Ping to {0} took {1}ms.", ipAddress, reply.RoundtripTime);
            }
            else
            {
                Console.WriteLine("Ping failed: {0}", reply.Status);
            }

            // Belirtilen süre kadar bekleyerek tekrar ping gönderme
            Thread.Sleep(1000);
        }
    }
}
