# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Ping ve sinyal değerini veren kodların birleştirilmesi ve kütüphaneye çevirme 

Bugün haftanın ilk günü olduğu için toplantı yaptık ve bana düşen görev ping ve sinyal kodlarını birleştirip kütüphane yapmaktı. Bugün ping veren kod ile sinyal değeri veren kodu birleştirdim. Eş zamanlı şekilde hem sinyal değeri hemde ping atıp çıkan değeri veriyor. Ve yazdığım kodu kütüphaneye çevirdim ve .dll uzantısını koduma ekleyip başka koddan çağırabiliyorum. Ve bu şekilde kütüphane yazmak daha kolay oluyor hem clean kod açısından hemde daha anlaşılır karışıklık olmadan temiz bir koda çevirdim.

	namespace signal_ping_library
	{
   	 public class WifiAndPing
   	 {
     	   string ip;
      	  Ping ping;
      	  WlanClient client;
      	  Thread thread;
      	  bool isRunning;

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
                            Console.WriteLine("Found network with SSID {0} and Signal Quality:%{1}", networkName, signalQuality);

                            // Ping ölçümü
                            PingReply reply = ping.Send(ip);
                            if (reply.Status == IPStatus.Success)
                            {
                                Console.WriteLine("Ping {0} başarılı! ping :                    {1} ms", ip, reply.RoundtripTime);
                            }
                            else
                            {
                                Console.WriteLine("Ping {0} başarısız! Status :     {1}", ip, reply.Status);
                            }

                            Console.WriteLine("WiFi bant genişliği:" + MeasureWifiBandwidth() + "bps:                     " + (MeasureWifiBandwidth() / 8000000) + " MB/s");

                            Thread.Sleep(1000);
                            break;
                        }
       

Bu kodda kütüphaneyi çağırdığım kod


	using signal_ping_library;

	class Program
	{
    static void Main(string[] args)
    {
        string ip = "192.168.68.1"; // ping yapılacak IP adresi
        var wifiAndPing = new WifiAndPing(ip);

        string command = "";
        while (command != "exit")
        {
            Console.WriteLine("Komut girin (start/stop/exit):");
            command = Console.ReadLine();

            switch (command)
            {
                case "start":
                    wifiAndPing.Start();
                    break;

                case "stop":
                    wifiAndPing.Stop();
                    break;

                case "exit":
                    Console.WriteLine("Çıkış yapılıyor...");
                    break;

                default:
                    Console.WriteLine("Geçersiz komut.");
                    break;
            }
        }
    }
	}




Bugünkü kazanımlarım
- Bugün kodları birleştirip eş zamanlı nasıl çalıştırım ve bir kodu kütüphaneye nasıl çeviririm ,onları öğrendim ve uyguladım











 














 	







 





