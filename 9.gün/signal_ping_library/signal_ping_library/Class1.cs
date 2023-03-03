using System;
using System.Diagnostics.Metrics;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading;
using NativeWifi;

namespace signal_ping_library
{
    public class WifiAndPing
    {
        string ip;
        Ping ping;
        WlanClient client;
        Thread thread;
        bool isRunning;
        public event EventHandler<string> OnMeasurement;

        private void RaiseOnMeasurement(string measurement)
        {
            OnMeasurement?.Invoke(this, measurement);
        }
        public WifiAndPing(string ip)
        {
            this.ip = ip;
            ping = new Ping();
            client = new WlanClient();
            isRunning = false;
        }

        public void Start()
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

        public void Stop()
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

        private void Run()
        {
            while (isRunning)
            {
                // Sinyal kalitesi ölçümü
                foreach (WlanClient.WlanInterface wlanIface in client.Interfaces)
                {
                    Wlan.WlanBssEntry[] networks = wlanIface.GetNetworkBssList();
                    foreach (Wlan.WlanBssEntry network in networks)
                    {
                        Wlan.Dot11Ssid ssid = network.dot11Ssid;
                        string networkName = Encoding.ASCII.GetString(ssid.SSID, 0, (int)ssid.SSIDLength);

                        if (networkName.Equals("ROBUTEL_TM"))
                        {

                         
                            int signalQuality = (int)network.linkQuality;
                                                
                            // Ping ölçümü
                            PingReply reply = ping.Send(ip);
                            if (reply.Status == IPStatus.Success)
                            {
                                //    Console.WriteLine("Ping {0} başarılı! ping :                    {1} ms", ip, reply.RoundtripTime);
                            }
                            else
                            {
                                //Console.WriteLine("Ping {0} başarısız! Status :     {1}", ip, reply.Status);
                            }

                            /*   static long MeasureWifiBandwidth()
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
                               }*/
                            //Console.WriteLine("Found network with SSID {0} and Signal Quality:%{1}", networkName, signalQuality);
                            string measurement = $"SSID: {networkName}, Signal Quality: %{signalQuality}, Ping: {reply.RoundtripTime} ms, WiFi bandwidth: {MeasureWifiBandwidth()} bps ({MeasureWifiBandwidth() / 8000000} MB/s)";
                            RaiseOnMeasurement(measurement);
                            //Console.WriteLine("WiFi bant genişliği:" + MeasureWifiBandwidth() + "bps:                     " + (MeasureWifiBandwidth() / 8000000) + " MB/s");

                            Console.WriteLine(measurement);
                            Console.WriteLine("------------------------------------------------------------------------------------\n");

                            Thread.Sleep(1000);
                            break;
                           
                        }
                    }
                  
                }
                
            }
        }
    }
}


//using System;
//using System.Net.NetworkInformation;
//using System.Text;
//using System.Threading;
//using NativeWifi;

//namespace signal_ping_library
//{
//    public class SignalPingEventArgs : EventArgs
//    {
//        public string Ip { get; set; }
//        public int SignalQuality { get; set; }
//        public int Ping { get; set; }
//        public long Bandwidth { get; set; }

//        public SignalPingEventArgs(string ip, int signalQuality, int ping, long bandwidth)
//        {
//            Ip = ip;
//            SignalQuality = signalQuality;
//            Ping = ping;
//            Bandwidth = bandwidth;
//        }
//    }

//    public class WifiAndPing
//    {
//        string ip;
//        Ping ping;
//        WlanClient client;
//        Thread thread;
//        bool isRunning;

//        public event EventHandler<SignalPingEventArgs> SignalPingEvent;

//        public WifiAndPing(string ip)
//        {
//            this.ip = ip;
//            ping = new Ping();
//            client = new WlanClient();
//            isRunning = false;
//        }

//        public void Start()
//        {
//            if (!isRunning)
//            {
//                isRunning = true;
//                thread = new Thread(Run);
//                thread.Start();
//                Console.WriteLine("İşlem başlatıldı");
//            }
//            else
//            {
//                Console.WriteLine("İşlem zaten başlatılmış");
//            }
//        }

//        public void Stop()
//        {
//            if (isRunning)
//            {
//                isRunning = false;
//                thread.Join();
//                Console.WriteLine("İşlem durduruldu");
//            }
//            else
//            {
//                Console.WriteLine("İşlem zaten durdurulmuş");
//            }
//        }

//        static long MeasureWifiBandwidth()
//        {
//            long bandwidth = 0;
//            NetworkInterface[] interfaces = NetworkInterface.GetAllNetworkInterfaces();
//            foreach (NetworkInterface networkInterface in interfaces)
//            {
//                if (networkInterface.NetworkInterfaceType == NetworkInterfaceType.Wireless80211 && networkInterface.OperationalStatus == OperationalStatus.Up)
//                {
//                    IPv4InterfaceStatistics statistics = networkInterface.GetIPv4Statistics();
//                    bandwidth = networkInterface.Speed;
//                }
//            }
//            return bandwidth;
//        }

//        private void Run()
//        {
//            while (isRunning)
//            {
//                // Sinyal kalitesi ölçümü
//                foreach (WlanClient.WlanInterface wlanIface in client.Interfaces)
//                {
//                    Wlan.WlanBssEntry[] networks = wlanIface.GetNetworkBssList();
//                    foreach (Wlan.WlanBssEntry network in networks)
//                    {
//                        Wlan.Dot11Ssid ssid = network.dot11Ssid;
//                        string networkName = Encoding.ASCII.GetString(ssid.SSID, 0, (int)ssid.SSIDLength);

//                        if (networkName.Equals("ROBUTEL_TM"))
//                        {
//                            int signalQuality = (int)network.linkQuality;
//                            Console.WriteLine("Found network with SSID {0} and Signal Quality:%{1}", networkName, signalQuality);

//                            //Ping ölçümü
//                                                        PingReply reply = ping.Send(ip);
//                            if (reply.Status == IPStatus.Success)
//                            {
//                                Console.WriteLine("Ping {0} başarılı! ping :                    {1} ms", ip, reply.RoundtripTime);
//                            }
//                            else
//                            {
//                                Console.WriteLine("Ping {0} başarısız! Status :     {1}", ip, reply.Status);
//                            }

//                            /*   static long MeasureWifiBandwidth()
//                               {
//                                   long bandwidth = 0;
//                                   NetworkInterface[] interfaces = NetworkInterface.GetAllNetworkInterfaces();
//                                   foreach (NetworkInterface networkInterface in interfaces)
//                                   {
//                                       if (networkInterface.NetworkInterfaceType == NetworkInterfaceType.Wireless80211 && networkInterface.OperationalStatus == OperationalStatus.Up)
//                                       {
//                                           IPv4InterfaceStatistics statistics = networkInterface.GetIPv4Statistics();
//                                           bandwidth = networkInterface.Speed;
//                                       }
//                                   }
//                                   return bandwidth;
//                               }*/
//                            Console.WriteLine("WiFi bant genişliği:" + MeasureWifiBandwidth() + "bps:                     " + (MeasureWifiBandwidth() / 8000000) + " MB/s");


//                            Console.WriteLine("------------------------------------------------------------------------------------\n");

//                            Thread.Sleep(1000);
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//    }
//}