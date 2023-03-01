using signal_ping_library;

namespace my_app
{
    class Program
    {
        static void Main(string[] args)
        {
            WifiAndPing wifiAndPing = new("192.168.68.1");
            wifiAndPing.Start();
        }
    }
}