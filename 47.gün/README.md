# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :  Mongodb İndexleme
Bugünkü staj konum mongodb dizinlemeyi araştırıp ne işe yaradığını nerelerde kullanıldığını öğrenmek.
MongoDB, verileri hızlı bir şekilde sorgulamak için dizinleme kullanır. Dizinler, belirli bir alanın değerine göre belgeleri gruplandıran özel veri yapılarıdır. Bu, verilerin çok daha hızlı bir şekilde sorgulanmasına olanak tanır.

MongoDB, bir koleksiyonda birden fazla dizin oluşturmanıza izin verir. Dizinler, tek bir alan veya birden fazla alanın bir kombinasyonu üzerinde oluşturulabilir. Dizinleme işlemi, bir koleksiyondaki belirli bir alan veya alan kombinasyonu için bir dizin oluşturma işlemidir.

Dizinleme işlemi, öncelikle bir alanın tüm değerlerini tarar ve benzersiz değerleri saklayarak bir dizin oluşturur. Daha sonra, sorgulama yapılırken, dizin belirli bir değere sahip belgeleri hızlı bir şekilde bulabilir ve getirebilir.
Dizinler, verilerdeki sorgulama hızını artırırken, aynı zamanda bellek kullanımını artırabilir. Bu nedenle, dizinlerin dikkatli bir şekilde oluşturulması ve yönetilmesi önemlidir.

MongoDB dizinlerinin yönetimi, dizinlerin oluşturulması, güncellenmesi, silinmesi ve izlenmesi gibi çeşitli işlemleri içerir. Aşağıda MongoDB dizinlerinin yönetimi için kullanılabilecek bazı önemli yöntemler açıklanmaktadır:

Dizin oluşturma: Dizinler, bir koleksiyondaki belirli bir alan veya alan kombinasyonu için oluşturulabilir. Dizinler, createIndex() yöntemi kullanılarak oluşturulabilir. Bu yöntem, bir dizin için alan adı veya adları ve dizin türü gibi parametreleri alır.

Dizin güncelleme: Dizinler, var olan bir dizini güncellemek veya yeni bir dizin eklemek için güncellenebilir. Dizini güncellemek için, collMod komutu veya updateOne() yöntemi kullanılabilir.

Dizin silme: Dizinler, dropIndex() yöntemi kullanılarak silinebilir. Bu yöntem, bir koleksiyondan bir dizin siler.
Dizin istatistikleri: MongoDB, bir dizinin kullanımı hakkında faydalı istatistikler toplar. Bu istatistiklere, collStats() yöntemi kullanılarak erişilebilir.

Dizinlerin yönetimi, bir koleksiyonun performansını etkileyebilir. Dizinler, sorgulama hızını artırırken, aynı zamanda bellek kullanımını da artırır. Bu nedenle, dizinlerin oluşturulması ve yönetimi dikkatli bir şekilde yapılmalıdır. Örneğin, gereksiz dizinlerin silinmesi ve nadiren kullanılan dizinlerin kapatılması, koleksiyonun performansını artırabilir.

 




![image](https://user-images.githubusercontent.com/65457096/233914432-e6528561-962b-4d88-b9bd-ec6c56e117a3.png)

















 	







 





