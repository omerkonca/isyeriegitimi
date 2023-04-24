# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :   Mongodb İndexleme 2
Bugünkü staj günümde MongoDB indeksleme işlemini daha detaylı bir şekilde inceledim. MongoDB indeksleme, verilerin daha hızlı erişilebilir olmasını sağlamak için kullanılan bir yöntemdir. Indeksleme işlemi, belirli bir sorgunun daha hızlı yürütülmesini sağlar.

MongoDB indeksleme işlemi için createIndex() metodunu kullanırız. Bu metodun kullanımı oldukça basittir. Örneğin, db.collection.createIndex( { name: 1 } ) komutunu kullanarak "name" alanı için artan bir indeks oluşturabiliriz. Bu komut, "name" alanı üzerinde artan bir indeks oluşturacak ve bu indeksi kullanarak sorguları daha hızlı yürütebileceğiz.

MongoDB, indeksler için B-Tree yapısını kullanır. Bu yapının avantajı, verilerin sıralanmış olması ve arama, ekleme ve silme işlemlerinin hızlı bir şekilde yapılabilmesidir.

Indeksleme işlemi yaparken, hangi alanlar üzerinde indeksleme yapacağımıza dikkat etmemiz gerekiyor. Eğer veri kümemiz çok büyük ise, tüm alanlar için indeksleme yapmak performansı kötü etkileyebilir. Bu yüzden, sadece sık sık kullanılan alanlar için indeksleme yapmak daha etkili olabilir.

Ayrıca, indeksleme işlemi yaparken hangi sıralamayı kullanacağımız da önemlidir. Örneğin, bir alanı artan veya azalan sıralama ile indekslemek farklı sonuçlar verebilir. Bu yüzden, kullanım senaryomuza göre doğru sıralamayı belirlememiz gerekiyor.

Indeksleme işlemi, verilerimize yapılan değişikliklere göre otomatik olarak güncellenir. Yani, verilerimize yeni bir belge eklediğimizde veya mevcut bir belgeyi güncellediğimizde, MongoDB indeksi otomatik olarak günceller ve sorgularımızın hızlı kalmasını sağlar.

MongoDB indeksleme işlemi, verilerimize daha hızlı erişim sağlayarak performansı artıran önemli bir araçtır. Indeksleme işlemini doğru kullanarak, verilerimizin işleme hızını artırabilir ve uygulamalarımızın performansını iyileştirebiliriz.

Indeksleme işlemi yaparken dikkat edilmesi gereken diğer bir konu da indeks boyutudur. Eğer indeks boyutu çok büyükse, sorguların hızı düşebilir. Bu yüzden, indeks boyutunu mümkün olduğunca küçük tutmaya çalışmak önemlidir.

MongoDB indeksleme işlemi yaparken, farklı türlerde indeksler de oluşturabiliriz. Örneğin, metin alanları için metin indeksleri veya coğrafi konum verileri için coğrafi indeksler oluşturabiliriz. Bu indeksler, belirli tipte sorguların daha hızlı yürütülmesini sağlar.

Indeksleme işlemi, verilerimizin performansını artırmak için çok önemli bir araçtır. Ancak, indeksleme işlemi yaparken bazı dezavantajları da vardır. Örneğin, indeksleme işlemi bellek kullanımını artırabilir ve verilerimizin güncellenmesi daha yavaş olabilir. Bu nedenle, indeksleme işlemini doğru şekilde kullanarak avantajlarını ve dezavantajlarını dikkate almak önemlidir.

Bugünkü kazanımlarım 
-	MongoDB indeksleme işlemini daha detaylı bir şekilde inceledim. Bu işlemi hangi durumlarda ve nasıl kullanabileceğimizi öğrendim. Ayrıca, indeksleme işlemini yaparken nelere dikkat etmemiz gerektiğini ve nasıl optimize edebileceğimizi de öğrendim. 
















 





