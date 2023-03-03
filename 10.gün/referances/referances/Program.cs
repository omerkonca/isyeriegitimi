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