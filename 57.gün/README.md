# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :    İndexlemenin bellek kullanımına etkisi


Bugün MongoDB veritabanında indeksleme işlemi üzerinde çalıştım. İlk olarak, indeksleme işleminin ne olduğu hakkında genel bir bilgi aldım. MongoDB, NoSQL tabanlı bir veritabanı yönetim sistemidir ve verilerin depolanması ve sorgulanması için kullanılır. Veritabanında sorgulama işlemlerini hızlandırmak için indeksleme işlemi kullanılır.

MongoDB, birçok indeks türü sağlar. Bu indeks türleri arasında tekli indeksler, bileşik indeksler, coğrafi indeksler ve tam metin indeksleri yer alır. Tekli indeksler, bir alanın değerlerine göre indekslenir ve bu alana yapılan sorguların hızlandırılmasına yardımcı olur. Bileşik indeksler, birden fazla alana göre indeksleme işlemi yapar ve bu alanlara yapılan sorguların hızlandırılmasına yardımcı olur. Coğrafi indeksler, coğrafi verilerin depolanmasını ve sorgulanmasını hızlandırırken, tam metin indeksleri, belirli bir metin aralığı içindeki anahtar kelimeleri hızlı bir şekilde bulmak için kullanılır.

Daha sonra, bir uygulamada indeksleme işlemini nasıl gerçekleştireceğimize dair bir örnek çalışma yaptık. Bu çalışma, bir veri kümesinin nasıl indeksleneceği ve performansın nasıl ölçüleceği konusunda bize fikir verdi. Örnek uygulamamızda, bir müşteri veritabanı oluşturduk ve bu veritabanında müşterilerin isimlerine göre tekli indeksleme işlemi yaptık. Daha sonra, bu veritabanında müşteri arama sorgularının performansını ölçtük. İndeksleme işlemi yapılmadan önceki sorgulama süreleri ile indeksleme işlemi yapıldıktan sonraki sorgulama süreleri arasında belirgin bir fark gözlemledik. İndeksleme işlemi yapıldıktan sonra sorgulama sürelerinin oldukça kısalması, indeksleme işleminin veritabanı performansını nasıl artırdığının açık bir göstergesi oldu.

Son olarak, veritabanı boyutu ve indeksleme türüne göre bellek kullanımı üzerindeki etkileri inceledik. İndekslerin bellekte tutulması, sorgulama performansını artırır ancak bellek kullanımını da artırır. Ancak, MongoDB, indeksleri bellekte tutmanın yanı sıra, diske de yazabilir. Bu durumda, sorguların performans etkilenmesi biraz daha yavaş olsa da, bellek kullanımı azaltılabilir.


### İndexlemeden önce bellek kullanımı
 
 ![image](https://user-images.githubusercontent.com/65457096/235866465-0227150a-5d9d-43dd-8a79-179fbf14c2cf.png)


### İndexledikten sonra bellek kullanımı

![image](https://user-images.githubusercontent.com/65457096/235866477-1fcc71a5-e6ae-475f-8827-65de870e48ef.png)



Bugünkü staj deneyimim, MongoDB veritabanı indeksleme işlemlerini anlama ve uygulama konusunda büyük bir fırsat sağladı. İndeksleme işleminin veritabanı performansını nasıl artırdığını ve belirli bir veritabanı boyutu ve indeks türüne göre bellek kullanımı üzerindeki etkilerini anlamak, benim için çok yararlı oldu. Ayrıca, bir örnek uygulama üzerinde indeksleme işlemi gerçekleştirerek, teorik bilgileri pratikte uygulama şansım oldu.

Bu deneyim, veritabanı yönetimi konusunda kariyer hedeflerim doğrultusunda önemli bir adım oldu ve MongoDB gibi popüler bir NoSQL veritabanı yönetim sistemi ile çalışmak, benim için çok değerli bir deneyim oldu.







Bugünkü kazanımlarım
-	MongoDB veritabanında indeksleme işlemi: MongoDB gibi NoSQL tabanlı veritabanı yönetim sistemlerinde indeksleme işlemi, verilerin depolanması ve sorgulanması için büyük bir öneme sahiptir. Bugün, indeksleme işleminin ne olduğu, nasıl yapıldığı ve farklı indeks türlerinin ne işe yaradığı hakkında ayrıntılı bilgi sahibi oldunuz.
-	İndeksleme işleminin performans üzerindeki etkisi: Bugünkü çalışmalarınızda, bir müşteri veritabanında tekli indeksleme işlemi yaptıktan sonra sorgulama sürelerinin belirgin bir şekilde kısalması, indeksleme işleminin veritabanı performansını nasıl artırdığının bir göstergesi oldu.
-	Bellek kullanımı ve indeks türü: Veritabanı boyutu ve indeks türüne göre bellek kullanımı üzerindeki etkileri inceleyerek, MongoDB gibi bir veritabanı yönetim sisteminde indekslerin bellekte tutulması, sorgulama performansını artırırken, bellek kullanımını da artırdığını öğrendiniz.
-	Örnek uygulama üzerinde çalışmak: MongoDB veritabanında indeksleme işlemini teorik olarak anlamak önemlidir, ancak bunu pratikte uygulamak daha da önemlidir. Bugün, bir müşteri veritabanında tekli indeksleme işlemi yaparak, teorik bilgileri pratikte uygulama fırsatı buldunuz.
-	Veritabanı yönetimi konusunda deneyim: MongoDB gibi popüler bir NoSQL veritabanı yönetim sistemiyle çalışmak, veritabanı yönetimi konusunda deneyim kazanmanıza yardımcı olabilir ve kariyer hedefleriniz doğrultusunda önemli bir adım olabilir.





 








Tarih : 23/05/ 2023

 
















































 	







 





