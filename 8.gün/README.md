# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Windows wifideki sinyal kalitesini ölçme 
Bugün wifideki sinyali kod üzerinden ölçtüm. Ölçmemin sebebi ise veri hızı, gelen sinyal ile birebir bağlantılı olduğu için.

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
                    break;
                }
            }





### Bugünkü kazanımlarım
- kod üzerinden pcye gelen wifi sinyalinin kalitesini ölçme





























 














 	







 





