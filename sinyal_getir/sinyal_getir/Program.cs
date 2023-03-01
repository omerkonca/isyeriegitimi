//using System;
//using System.Net.NetworkInformation;
//using System.Text;
//using NativeWifi;

//class Program
//{
//    static PingReply r;
//    static string ip;
//    static Ping p1;
//    static void Main(string[] args)
//    {
//        Console.Write("ping atmak istediginiz ip adresi : ");
//        Ping p = new Ping();
//        p1 = p;
//        ip = "192.168.68.1";
//        Console.WriteLine("girilen ip adresi = " + ip);      //192.168.68.120 ömerin İP adresi
//        Console.WriteLine("------------------------\n");

//        while (true)
//        {
//            SadeceSinyalGetir();
//            PingFonksiyonu();
//            System.Threading.Thread.Sleep(1000);
//        }
//    }

//    public static void SadeceSinyalGetir()
//    {
//        WlanClient client = new WlanClient();
//        foreach (WlanClient.WlanInterface wlanIface in client.Interfaces)
//        {
//            Wlan.WlanAvailableNetwork[] networks = wlanIface.GetAvailableNetworkList(0);
//            foreach (Wlan.WlanAvailableNetwork network in networks)
//            {
//                Console.WriteLine("Found network with SSID {0} and Signal Quality {1}.", GetStringForSSID(network.dot11Ssid), network.wlanSignalQuality);
//            }
//        }
//    }

//    static string GetStringForSSID(Wlan.Dot11Ssid ssid)
//    {
//        return Encoding.ASCII.GetString(ssid.SSID, 0, (int)ssid.SSIDLength);
//    }

//    public static void PingFonksiyonu()
//    {
//        r = p1.Send(ip);
//        if (r.Status == IPStatus.Success)
//        {
//            Console.WriteLine("belirtilen adrese  " + ip.ToString() + "[" + r.Address.ToString() + "]" + " Başarılı"
//               + " gecikme süresi = " + r.RoundtripTime.ToString() + " ms" + "\n");
//        }
//        if (string.IsNullOrWhiteSpace(ip))
//        {
//            Console.WriteLine("Please use valid IP or web address!!");
//        }
//        Console.WriteLine("------------------------\n");
//    }
//}



using System;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading;
using NativeWifi;

class Program
{
    static bool isRunning = false;
    static Thread thread;
    static string ip = "192.168.68.1"; // ping atmak istediğiniz IP adresi
    static Ping ping = new Ping();
    static WlanClient client = new WlanClient();

    static void Main(string[] args)
    {
        Console.WriteLine("Komutları görmek için . koy");
        while (true)
        {
            string command = Console.ReadLine();
            switch (command.ToLower())
            {
                case "start":
                    Start();
                    break;
                case "stop":
                    Stop();
                    break;
                case ".":
                    Console.WriteLine("start - işlemi başlatır");
                    Console.WriteLine("stop - işlemi durdurur");
                    Console.WriteLine(". - komut listesini gösterir");
                    break;
                default:
                    Console.WriteLine("Geçersiz komut");
                    break;
            }
        }
    }

    static void Start()
    {
        if (!isRunning)
        {
            isRunning = true;
            thread = new Thread(Run);
            thread.Start();
            Console.WriteLine("İşlem başlatıldı");
        }
        else
        {
            Console.WriteLine("İşlem zaten başlatılmış");
        }
    }

    static void Stop()
    {
        if (isRunning)
        {
            isRunning = false;
            thread.Join();
            Console.WriteLine("İşlem durduruldu");
        }
        else
        {
            Console.WriteLine("İşlem zaten durdurulmuş");
        }
    }

    static void Run()
    {
        while (isRunning)
        {
            // Sinyal kalitesi ölçümü
            //foreach (WlanClient.WlanInterface wlanIface in client.Interfaces)
            //{
            //    Wlan.WlanAvailableNetwork[] networks = wlanIface.GetAvailableNetworkList(0);
            //    foreach (Wlan.WlanAvailableNetwork network in networks)
            //    {
            //        Console.WriteLine("Found network with SSID {0} and Siqnal Quality {1}.", GetStringForSSID(network.dot11Ssid), network.wlanSignalQuality);
            //    }
            //}

            foreach (WlanClient.WlanInterface wlanIface in client.Interfaces)
            {
                Wlan.WlanBssEntry[] networks = wlanIface.GetNetworkBssList();
                foreach (Wlan.WlanBssEntry network in networks)
                {
                    Wlan.Dot11Ssid ssid = network.dot11Ssid;
                    string networkName = Encoding.ASCII.GetString(ssid.SSID, 0, (int)ssid.SSIDLength);
                    int signalQuality = (int)network.linkQuality;
                    Console.WriteLine("Found network with SSID {0} and Signal Quality {1}.", networkName, signalQuality);
                }
            }

            // Ping ölçümü
            PingReply reply = ping.Send(ip);
            if (reply.Status == IPStatus.Success)
            {
                Console.WriteLine("Ping {0} başarılı! RoundTripTime: {1} ms", ip, reply.RoundtripTime);
            }
            else
            {
                Console.WriteLine("Ping {0} başarısız! Status: {1}", ip, reply.Status);
            }

            Console.WriteLine("------------------------\n");
            Thread.Sleep(1000);
        }
    }

    static string GetStringForSSID(Wlan.Dot11Ssid ssid)
    {
        return Encoding.ASCII.GetString(ssid.SSID, 0, (int)ssid.SSIDLength);
    }
}

