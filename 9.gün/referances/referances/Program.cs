using signal_ping_library;


class Program
{
    static void Main(string[] args)
    {

        WifiAndPing wifiAndPing = new WifiAndPing("192.168.1.1");
        wifiAndPing.Start();

        WifiAndPingEvent wifiAndPingEvent = new WifiAndPingEvent();
        wifiAndPingEvent.OnMeasurement += OnMeasurementReceived;

        Console.ReadLine();
        wifiAndPing.Stop();
    }

    static void OnMeasurementReceived(object sender, string measurement)
    {
        Console.WriteLine(measurement);
    }



    //WifiAndPing wifiAndPing = new WifiAndPing("192.168.1.1");


    //wifiAndPing.Start();

    //Console.ReadLine();

    //wifiAndPing.Stop();









    //string ip = "192.168.68.1"; // ping yapılacak IP adresi
    //var wifiAndPing = new WifiAndPing(ip);


    //string command = "";
    //while (command != "exit")
    //{
    //    Console.WriteLine("Komut girin (start/stop/exit):");
    //    a = Console.ReadLine();

    //    switch (a)
    //    {
    //        case "start":
    //            wifiAndPing.Start();
    //            break;

    //        case "stop":
    //            wifiAndPing.Stop();
    //            break;

    //        case "exit":
    //            Console.WriteLine("Çıkış yapılıyor...");
    //            break;

    //        default:
    //            Console.WriteLine("Geçersiz komut.");
    //            break;
    //    }
    //}


}
        //private static void WifiAnd() { 
        //     static void WifiAndPingEventHandler(object sender, WifiAndPingEventArgs e)
        //{
        //    Console.WriteLine("SSID: {0}, Signal Quality: %{1}, Ping Time: {3} ms, WiFi Bandwidth: {4} bps ({5} MB/s)",
        //    e.SSID, e.SignalQuality,  e.PingTime,  e.Bandwidth);
        //}
    
