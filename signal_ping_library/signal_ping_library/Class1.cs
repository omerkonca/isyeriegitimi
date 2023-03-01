using System;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading;
using NativeWifi;

namespace signal_ping_library
{
    public class WifiAndPing
    {
        private string _ip;
        private Ping _ping;
        private WlanClient _client;
        private Thread _thread;
        private bool _isRunning;

        public WifiAndPing(string ip)
        {
            _ip = ip;
            _ping = new Ping();
            _client = new WlanClient();
            _isRunning = false;
        }

        public void Start()
        {
            if (!_isRunning)
            {
                _isRunning = true;
                _thread = new Thread(Run);
                _thread.Start();
                Console.WriteLine("İşlem başlatıldı");
            }
            else
            {
                Console.WriteLine("İşlem zaten başlatılmış");
            }
        }

        public void Stop()
        {
            if (_isRunning)
            {
                _isRunning = false;
                _thread.Join();
                Console.WriteLine("İşlem durduruldu");
            }
            else
            {
                Console.WriteLine("İşlem zaten durdurulmuş");
            }
        }

        private void Run()
        {
            while (_isRunning)
            {
                // Sinyal kalitesi ölçümü
                foreach (WlanClient.WlanInterface wlanIface in _client.Interfaces)
                {
                    Wlan.WlanBssEntry[] networks = wlanIface.GetNetworkBssList();
                    foreach (Wlan.WlanBssEntry network in networks)
                    {
                        Wlan.Dot11Ssid ssid = network.dot11Ssid;
                        string networkName = Encoding.ASCII.GetString(ssid.SSID, 0, (int)ssid.SSIDLength);

                        if (networkName.Equals("ROBUTEL_TM"))
                        {
                            int signalQuality = (int)network.linkQuality;
                            Console.WriteLine("Found network with SSID {0} and Signal Quality {1}.", networkName, signalQuality);

                            // Ping ölçümü
                            PingReply reply = _ping.Send(_ip);
                            if (reply.Status == IPStatus.Success)
                            {
                                Console.WriteLine("Ping {0} başarılı! RoundTripTime: {1} ms", _ip, reply.RoundtripTime);
                            }
                            else
                            {
                                Console.WriteLine("Ping {0} başarısız! Status: {1}", _ip, reply.Status);
                            }
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