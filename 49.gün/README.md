# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :  Mongodb projection ve sharding yapısı kullanımı 

Bugün Yapılan Görevler:

Veritabanı sorgularını hızlandırmak için yansıtma (projection) kullanarak gereksiz alanları çıkardık.
Veritabanı sorgularını daha da optimize etmek için indexleme kullanarak sorguların daha hızlı yanıt vermesini sağladık.
Büyük veri kütleleriyle çalışırken performansı artırmak için sharding kullanarak verileri farklı makinelere dağıttık.
Sık sık tekrar eden sorguları önbellekleyerek sorgu yanıt süresini azalttık.

Bugün Öğrenilenler:

Yansıtma kullanarak veritabanı sorgularını optimize etmek ve gereksiz verileri almamak.
Indexleme kullanarak sorgu performansını artırmak.
Sharding kullanarak veri kütlelerini ölçeklendirmek ve performansı artırmak.
Önbellek kullanarak sorgu performansını artırmak.
Bugün Karşılaşılan Zorluklar ve Çözümleri:

Veritabanındaki büyük veri kütleleriyle çalışırken, sorgu performansını artırmak için sharding kullanmak gerekiyordu. Bu zorluğu çözmek için MongoDB dokümantasyonunu inceleyerek ve birkaç deneme yaparak sharding işlemini gerçekleştirdik.
Önbellekleme kullanımında doğru sonuçları almak için sorguların benzersizliğine ve verilerin ne kadar süre önce önbelleğe alındığına dikkat etmek gerekiyordu. Bu zorluğu çözmek için önbellek yönetimi hakkında dokümantasyonu inceledik ve doğru stratejileri kullanarak bu sorunu çözdük.




     db.DATA_COLLECTION_NAME.find({},{YOUR_FIELD_KEY:BOOLEAN})







































 	







 





