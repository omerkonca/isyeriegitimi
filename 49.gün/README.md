# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :  Mongodb projection ve sharding yapısı kullanımı 

### Bugün Yapılan Görevler:

Veritabanı sorgularını hızlandırmak için yansıtma (projection) kullanarak gereksiz alanları çıkardık.
Gereksiz alanları projeksiyon kullanarak çıkararak sorguların yanıt süresini hızlandırdık.
Verileri projeksiyon kullanarak daha okunaklı hale getirdik.
Projeksiyon yaparken kullanılan operatörleri inceledik ve nasıl kullanabileceğimize dair örnekler gördük.
Veritabanı sorgularını daha da optimize etmek için indexleme kullanarak sorguların daha hızlı yanıt vermesini sağladık.
Verileri indeksleyerek sorgu performansını artırdık.
Veritabanındaki verileri analiz ederek en sık kullanılan sorguları belirledik ve bunları indeksleyerek sorgu performansını optimize ettik.
İndeksleme yöntemlerini inceledik ve nasıl kullanabileceğimize dair örnekler gördük.
Büyük veri kütleleriyle çalışırken performansı artırmak için sharding kullanarak verileri farklı makinelere dağıttık.
Veri kütlelerini farklı makinelere dağıtarak veritabanı performansını artırdık.
Sharding kullanarak verileri daha etkili bir şekilde yönetebileceğimizi öğrendik.
Sharding konusunda dokümantasyonu inceleyerek ve denemeler yaparak uygulamamızda sharding işlemini gerçekleştirdik.
Sık sık tekrar eden sorguları önbellekleyerek sorgu yanıt süresini azalttık.
Sık sık tekrar eden sorguları önbellekleyerek sorgu yanıt süresini azalttık.
Önbellek kullanmanın avantajlarını ve dezavantajlarını inceledik.
Önbellek yönetimi konusunda dokümantasyonu inceledik ve doğru stratejileri kullanarak önbellek performansını artırdık.


### Bugün Öğrenilenler:

Yansıtma kullanarak veritabanı sorgularını optimize etmek ve gereksiz verileri almamak.
Indexleme kullanarak sorgu performansını artırmak.
Sharding kullanarak veri kütlelerini ölçeklendirmek ve performansı artırmak.
Önbellek kullanarak sorgu performansını artırmak.
Projeksiyon kullanarak verileri daha okunaklı hale getirmek.
Bugün Karşılaşılan Zorluklar ve Çözümleri:
Veritabanındaki büyük veri kütlelerinin yönetiminde sharding kullanmak zor olabilir. Bu zorluğun üstesinden gelmek için sharding konusunda daha fazla dokümantasyon okuyarak ve deneyim kazanarak daha iyi bir yönetim stratejisi oluşturduk.

Önbellek kullanırken, önbellek boyutu ve önbelleklemenin ne zaman temizleneceği konusunda karar vermek zor olabilir. Bu zorluğun üstesinden gelmek için önbellek yönetimi konusunda daha fazla araştırma yaptık ve doğru stratejileri kullanarak önbellek performansını artırdık.

Projeksiyon kullanırken, hangi alanları çıkarmanın performansı en iyi şekilde artıracağına karar vermek zor olabilir. Bu zorluğun üstesinden gelmek için projeksiyon operatörlerini daha iyi anladık ve sorgularımızın yanıt süresini hızlandırmak için doğru alanları çıkardık.

### Bugünün Değerlendirmesi:

Bugünkü staj deneyimi, veritabanı performansı konusunda daha fazla bilgi edinmemize ve nasıl optimize edileceğine dair farklı yöntemleri öğrenmemize yardımcı oldu. Şirketin veritabanı sistemlerinin nasıl yönetildiğini daha iyi anladık ve bunları pratikte uygulama fırsatı bulduk. Ayrıca, ekip çalışması becerilerimizi geliştirdik ve yeni konularla ilgili deneyimlerimizi paylaştık. Bugün öğrendiklerimiz, gelecekteki projelerimizde veritabanı performansını artırmak için bize fayda sağlayacak.
Projection yapısı

     db.DATA_COLLECTION_NAME.find({},{YOUR_FIELD_KEY:BOOLEAN})

Sharding yapısı

     sharding:
       clusterRole: configsvr
     replication:
       replSetName: <replica set name>
     net:
       bindIp: localhost,<hostname(s)|ip address(es)>



























 	







 





