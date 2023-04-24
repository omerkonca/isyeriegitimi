# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :   Mongodb Loglama yavaşlığı sıkıntısı giderilmesi 

Bugünkü staj konum, MongoDB yavaşlığı sorunlarına yönelik bir çözüm arayışı oldu. MongoDB yavaşlığı sorunları, genellikle yetersiz dizinleme, büyük veri hacmi, aşırı yüklenme ve yanlış veritabanı tasarımı nedeniyle ortaya çıkabilir.

Bu sorunları ele almak için, öncelikle sorgu performansını etkileyen faktörleri anlamak gerekiyor. Ardından, doğru çözüm yöntemleri uygulanarak MongoDB performansı artırılabilir.

Bugünkü staj sürecinde, aşağıdaki yöntemler üzerinde çalıştım:
Dizinleme: MongoDB dizinleri, sorgu performansını artırmak için kullanılan önemli araçlardır. Bu nedenle, yeterli ve doğru dizinleme yapılması, sorgu performansını artırmaya yardımcı olabilir. Örneğin, sık kullanılan alanlar için dizin oluşturmak, sorgu sürelerini azaltabilir.

Veri hacmini azaltma: Büyük veri hacmi, sorgu performansını olumsuz etkileyebilir. Bu nedenle, gereksiz verilerin koleksiyondan kaldırılması veya ayrı bir koleksiyonda saklanması, sorgu performansını artırabilir.

Yük azaltma stratejileri: MongoDB, yüksek trafiğe maruz kalan uygulamalar için optimize edilmiştir. Ancak, yoğun yük altındaki bir uygulama, sorgu performansını etkileyebilir. Bu nedenle, yük azaltma stratejileri uygulanarak, uygulama performansı artırılabilir. Örneğin, verilerin önbelleğe alınması veya işlemci gücünün artırılması.

Veritabanı tasarımı: MongoDB'nin esnek yapısı, yanlış tasarlanmış bir veritabanı yapısına neden olabilir. Bu da, sorgu performansını etkileyebilir. Veritabanı tasarımının doğru yapılandırılması, sorgu performansını artırmaya yardımcı olabilir

Bugünkü staj sürecinde, yukarıdaki yöntemleri kullanarak, MongoDB performansını artırma üzerine çalıştım. Bu süreçte, özellikle yeterli dizinleme ve veri hacmini azaltma konularına odaklandım. Bu sorunların çözümü için kullanılan yöntemlerin detaylı bir şekilde ele alındığı ve uygulama sürecinde nasıl uygulandığına ilişkin bilgileri öğrendim. Ve sorunun sebebinin indexleme olduğuna karar verdim bu sayede.

Aşağıdaki kodda 1yıllık veri çekiyorum çok hızlı çekiyor sebebi ise okısmın indexlenmiş olmasından kaynaklanıyor

 ![image](https://user-images.githubusercontent.com/65457096/233003458-83759cf1-ab4c-453f-bbcf-3a95d96156aa.png)



Aşağıdada aynı şekilde ver çekiyorum fakat 4 günlük veri çekiyorum yukarı göre daha yavaş geliyor sebebi ise veritabanının indexleme yapmamış olmasından kaynaklanıyor
 
![image](https://user-images.githubusercontent.com/65457096/233003483-bbc6ab8d-bda9-4215-8947-713c3b9917ee.png)











































 	







 





