# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :  Veritabanı hız testi

Bugün veri tabanının yavaş filtrelemesine sebeb olabilecek sebebleri inceledik. Bir tanesi yanlış dil seçimimi acaba diye kendi kendimize sorduk ve mongodb den veri çeken hem python ve c# kodunu yazdık ve hız testi yaptık ve sonuç pekte absürt farkın olmadığını göstermiş oldu bize

 
      Python # ile yazılmış kod örneği ve hızı

         start_time = time.time()
 
      for i in range(1000000):
      random.randint(1, 100)
 
      end_time = time.time()

     # MongoDB'ye bağlan
     client = pymongo.MongoClient("mongodb://192.168.2.107:27017/")

     # "test" veritabanına eriş
     db = client["robutel_local_log"]

     # "orders" koleksiyonuna eriş
     collection = db["CurrentSpeedLog"]

     # Filtreleme sorgusu
     query = {
    "Timestamp": {
        "$gte": datetime(2023, 3, 1),
        "$lte": datetime(2023, 4, 10)
      }
    }

    # Filtrelenmiş verileri getir
    results = collection.find(query)
    # Veri sayısını al

    # Her bir sonucu ekrana yazdır
    for result in results:
    print(result)
    
    print("Kodun çalışma süresi: ", end_time - start_time, " saniye") 

hızıda bu şekilde

 ![image](https://user-images.githubusercontent.com/65457096/231151065-50b0316d-61d7-4960-94f1-766f041c7467.png)



C# ile yazılmış kod 

        var client = new MongoClient("mongodb://192.168.2.107:27017");
        var database = client.GetDatabase("robutel_local_log");
        var collection = database.GetCollection<BsonDocument>("CurrentSpeedLog");

        var startDate = new DateTime(2023, 4, 1);
        var endDate = new DateTime(2023, 4, 10);

        var filter = Builders<BsonDocument>.Filter.And(
            Builders<BsonDocument>.Filter.Gte("Timestamp", startDate),
            Builders<BsonDocument>.Filter.Lte("Timestamp", endDate)
        );

        var stopwatch = new Stopwatch();
        stopwatch.Start();

        var documents = collection.Find(filter).ToList();

        stopwatch.Stop();

        Console.WriteLine($"{documents.Count} adet belge bulundu.");
        Console.WriteLine($"Sorgu {stopwatch.Elapsed.TotalSeconds} saniyede tamamlandı.");

        Console.ReadLine();
    } 
    


![image](https://user-images.githubusercontent.com/65457096/231151095-a6ce0bb5-c383-43a2-bb2b-539105059188.png)

 




Bugünkü kazanımlarım
-	veritabanı loglamada programlama dilinin etkisinin nasıl değiştiğini öğrendim





















 	







 





