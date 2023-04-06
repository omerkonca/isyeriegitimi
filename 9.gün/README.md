# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : İP adresine ping atarak veri aktarım hızının hesaplanması 

Ping komutu, kaynak bilgisayarın belirli bir ağ hedefine erişme yetkisini test etmek için kullanılan bir Komut İstemidir. Ping komutu, genellikle bilgisayarın yazıcı ile ağ üzerinden iletişim kurabildiğini doğrulamanın basit bir yolu olarak kullanılır.

Yazıcınıza atanmış IP adresini edinmek için yazıcıdan bir ayarlar sayfası yazdırın (bu, sistem türünüze göre değişiklik gösterebilir).
IP Adresi "Network" (Ağ) alt başlığının altında listelenir.

Aşağıdaki kodda nasıl ping atılır onu gösterdim.


 	// Ping ölçümü
	PingReply reply = ping.Send(ip);
	if (reply.Status == IPStatus.Success)
         	   {
	Console.WriteLine("Ping {0} başarılı! RoundTripTime: {1} ms", ip,reply.RoundtripTime);
           	 }
	else
           	 {
              	  Console.WriteLine("Ping {0} başarısız! Status: {1}", ip, reply.Status);
            	}

	Console.WriteLine("--------------------------------------------------------------\n");
            Thread.Sleep(1000);
        }
    }
    
    static string GetStringForSSID(Wlan.Dot11Ssid ssid)
    {
        return Encoding.ASCII.GetString(ssid.SSID, 0, (int)ssid.SSIDLength);
    }
	}


Bugünkü kazanımlarım
-  İP adresine ping atarak veri aktarım hızının hesaplamayı öğrendim























 














 	







 





