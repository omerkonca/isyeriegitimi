# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Publisher subscriber vs client server kavramlarının araştırılması 

   Bugünkü araştırma konum abone yayıncı mantığı,bir önceki gün araştırmış olduğum zeromq kütüphanesine entegre edeceğim ve bu mantığı forkliftimizde kullanacağız forklifte kurmuş olduğumuz sunucu yayın açarak bizde düz mantıkla o yayının abonesi olacağız yeni birşey yayınlandığında ilk bizim haberimiz olacak anlık olarak verileri bu şekilde alacağız. Benim görevim ise şuanlık araştırma ilerki günlerde uygulamaya geçeceğim.
Aşağıdada yayıncı abone mantığını teorik olarak açıklayacağım.
 
Publisher-Subscriber" ve "Client-Server
"Publisher-Subscriber" ve "Client-Server" kavramları, bilgisayar bilimleri ve yazılım mühendisliği alanlarında sıklıkla kullanılan terimlerdir.
"Publisher-Subscriber" (yayımcı-abone) modeli, birçok bağımsız abonenin, bir yayıncı tarafından üretilen mesajları dinlediği bir iletişim modelidir. Bu modelde, yayıncı mesajları oluşturur ve aboneler bu mesajları dinler. Yayıncı, mesajları doğrudan belirli abonelere gönderebileceği gibi, yayıncı tüm abonelere de gönderebilir.
"Client-Server" (istemci-sunucu) modeli, bir sunucunun bir veya daha fazla istemci tarafından istekleri işlediği bir iletişim modelidir. Bu modelde, istemci, sunucuya bir istek gönderir ve sunucu bu isteği işleyerek istemciye bir yanıt gönderir. Bu modelde, sunucu genellikle bir merkezi otoriteyi temsil ederken, istemciler ise bu merkezi otoritenin hizmetlerinden yararlanan kullanıcılardır.
İki model arasındaki temel fark, "Publisher-Subscriber" modelinin daha dağıtık bir yapıya sahip olmasıdır. Bu modelde, yayıncı ve aboneler aynı anda çalışabilir ve birbirleriyle doğrudan etkileşimde bulunabilirler. Öte yandan, "Client-Server" modelinde, sunucu ve istemciler birbirlerine doğrudan bağlıdır ve sunucu, istemcilerin isteklerini işleme yeteneğine sahiptir.

Aşağıdada c++ kodunu yazıyorum


	#include <iostream>

    int main() {
        std::cout << "Merhaba Dünya!";
        return 0;
    }


Bu programın çıktısı, "Merhaba Dünya!" yazısıdır. Yukarıdaki program, "iostream" başlıklı bir kütüphaneyi kullanarak "cout" fonksiyonu aracılığıyla çıktıyı ekrana yazdırır. "int main()" satırı, programın ana fonksiyonunu belirtir ve program çalıştırıldığında bu fonksiyon ilk olarak çağrılır. "return 0;" satırı, programın başarılı bir şekilde sonlandığını belirtir.


Bugünkü kazanımlarım
-	Publisher subscriber vs client server kavramlarını öğrendim






























 














 	







 





