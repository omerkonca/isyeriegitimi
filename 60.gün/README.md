# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :    Filtrelemeyle İlgili Düzenleme 
Bugün, geçen gün yaptığım kodu gösterdim. Ancak, yaptığım şekilde istenilen tarih aralığındaki tüm verileri çektiğini ve büyük veri setleri için bekleme süresini arttıracağını öğrendim. Bu nedenle, tarihe göre sürekli olarak filtreleme yapacak şekilde değiştirmem istendi.

Konu üzerinde araştırma yaparak, ilk veri sayfasındaki son verinin tarih değişkenine ulaşabildiğimi fark ettim. Ancak, sonraki süreçte yeni başlangıç ve bitiş tarihlerini verirken sorun yaşıyorum. Özellikle ileri sayfalarda ileri gitme kısmını mantıken hallettim gibi görünüyor, ancak geri gitme kısmını henüz çözemedim.


    while (true){   //sonsuz döngü ile klavye üzerinden sürekli sorgu yapabiliyorum.

      if (Console.ReadKey(true).Key == ConsoleKey.F)
        {
         filter = Builders<BsonDocument>.Filter.And(
         Builders<BsonDocument>.Filter.Gte("Timestamp", midDate),
         Builders<BsonDocument>.Filter.Lte("Timestamp", endDate));
         c = (int)await collection.CountAsync(filter);
                             
        Task.Run(async () =>
          {
         var findOptions = new FindOptions<BsonDocument>();
         findOptions.Limit = limit;
         Result = await collection.FindAsync(filter);
         var a=Result.ToList();
         var d = a[limit - 1].GetValue("Timestamp");
         midDate = ((DateTime)d);
         Console.WriteLine(a);}).Wait();
         sayac++;

      }
      else if (Console.ReadKey(true).Key == ConsoleKey.B){
          filter = Builders<BsonDocument>.Filter.And(
          Builders<BsonDocument>.Filter.Gte("Timestamp", startDate),
          Builders<BsonDocument>.Filter.Lte("Timestamp", midDate));
          c = (int)await collection.CountAsync(filter);
          Task.Run(async () =>
               {
                  //  var findOptions = new FindOptions<BsonDocument>();
                  //  findOptions.Limit = limit;
                  //  Result = await collection.FindAsync(filter);
                  //  var a = Result.ToList();
                  //  midDate = ((DateTime)a[0].GetValue("Timestamp"));
                }).Wait();
                sayac--;
      }
      else // burda f ve b den başka bir şeye basarsa programdan çıkıyor .
      {
      break;
      }


Bugünkü kazanımlarım
-	Findoptions yapısını öğrendim










 








Tarih : 26/05/ 2023

 
















































 	







 





