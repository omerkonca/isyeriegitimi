# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Mongodb veritabanı filtreleme 

Bugün veri tabanı filtreleme işlemi yaptım ve filtreleme işlemi ise bir tarihten diğer bir tarihe kadar olan aralıktaki loglama kayıtlarını consola yazdırmasıydı

      var client = new MongoClient("mongodb://192.168.2.107:27017");
      var database = client.GetDatabase("Master_1071");
      var collection = database.GetCollection<BsonDocument>("GeneralLog");

      var startDate = new DateTime(2023, 4, 1);
      var endDate = new DateTime(2023, 4, 5);

      var filter = Builders<BsonDocument>.Filter.And(
            Builders<BsonDocument>.Filter.Gte("Timestamp", startDate),
            Builders<BsonDocument>.Filter.Lte("Timestamp", endDate)
         );

       var documents = collection.Find(filter).ToList();

       foreach (var document in documents)
         {
       var json = document.ToJson(new JsonWriterSettings { Indent = true }); // BSON belgesini JSON formatına dönüştürülüyor
            Console.WriteLine(json);
         }
        
Bu şekilde filtreleme işlemi yaptırıyorum


 ![image](https://user-images.githubusercontent.com/65457096/230888805-6ba1e032-4863-48ff-93a3-ac5226ab120a.png)



Bugünkü kazanımlarım
-	mongodb filtrelemeyi öğrendim












 	







 





