# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :    Mongodb indexleme hızı ölçümü

Bugünkü staj konumum MongoDBde indexlemenin hız üzerindeki etkisi.


MongoDB, açık kaynaklı bir veritabanı yönetim sistemidir ve ölçeklenebilirliği ve hızlı erişim özellikleriyle tercih edilmektedir. Ancak, veri hacmi arttıkça ve karmaşık sorguların kullanıldığı durumlarda, performansı olumsuz etkilenebilmektedir.


Bugün öğrendiğim konu, MongoDB'de indexlemenin hız üzerindeki önemli etkisi. Indexleme, veritabanındaki verilerin hızlı bir şekilde erişilebilir olmasını sağlar. Indexleme işlemi doğru bir şekilde planlandığında, veritabanındaki verilerin hızlı bir şekilde erişilebilir olması ve uygulamanın daha hızlı yanıt vermesi mümkün hale gelir.


Indexleme işlemi, MongoDB'de tekli alan ve bileşik alan olarak iki farklı şekilde yapılabilir. Tekli alan indexlemesi, bir alana göre indexlemeyi sağlar. Bileşik alan indexlemesi ise birden fazla alana göre indexlemeyi sağlar. Tekli alan indexlemesi daha hızlı çalışırken, bileşik alan indexlemesi daha esnek bir yapıya sahiptir.


Indexleme işlemi, veritabanının boyutuna ve indexleme yapılan alan sayısına bağlı olarak biraz zaman alabilir ve veritabanının yavaşlamasına neden olabilir. Bu nedenle, indexleme işlemi dikkatli bir şekilde planlanmalı ve uygun bir zaman diliminde gerçekleştirilmelidir.


Bugünkü stajım boyunca, MongoDB'de indexleme işleminin önemli bir konu olduğunu ve hız üzerindeki etkisinin büyük olduğunu öğrendim. Bu bilgiler, ileride yapacağım veritabanı yönetimi çalışmalarında bana büyük fayda sağlayacak.




Indexli alan bu şekilde id yi default kendi indexliyor timestampi biz indexledik



![image](https://user-images.githubusercontent.com/65457096/235068797-a9ffce73-2703-48a3-ad33-15fcdf9c816d.png)




Burda index olmadan tarihe göre filtre yaptığımız zaman 2.58 saniyede aram yapıyor

 ![image](https://user-images.githubusercontent.com/65457096/235068843-57ba0e2b-c8f6-43aa-9964-d3bbaf2928c2.png)





Burda ise index olunca tarihe göre filtre yaptığımız zaman 0.008 saniyede arama yapıyor. Hızı baya etkiliyor

 ![image](https://user-images.githubusercontent.com/65457096/235068865-83786170-c7b4-45eb-8055-5d6d66b6bb64.png)






Bugünkü kazanımlarım
-	MongoDB veritabanı yönetim sistemleri hakkında daha fazla bilgi edindim.
-	MongoDB'de indexleme işleminin önemini ve hız üzerindeki etkisini öğrendim.
-	MongoDB'de tekli alan ve bileşik alan indexlemesi gibi farklı indexleme yöntemlerinin olduğunu öğrendim.
-	Indexleme işleminin doğru bir şekilde planlanması ve uygun bir zaman diliminde gerçekleştirilmesi gerektiğini öğrendim.
-	Veritabanı yönetimi alanında farklı kavramlar ve teknikler hakkında deneyim kazandım.
-	Stajınız boyunca edindiğiniz bilgi ve deneyimlerin, ileride yapacağınız çalışmalarda size büyük fayda sağlayacağını fark ettim.








Tarih : 17/05/ 2023

 
















































 	







 





