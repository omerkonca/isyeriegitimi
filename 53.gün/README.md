# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :   Mongodb manuel indexleme 

Bugün mongodb de manuel şekilde nasıl index yapılır onu öğrendim ve uyguladım



Kodum bu şekilde


            using MongoDB.Bson;
            using MongoDB.Driver;

            var client = new MongoClient("mongodb://192.168.1.107:27017");
            var database = client.GetDatabase("robutel_local_log");
            var collection = database.GetCollection<BsonDocument>("NavigationLog");

            var indexModel = new CreateIndexModel<BsonDocument>(Builders<BsonDocument>.IndexKeys.Ascending("Timestamp"));

            await collection.Indexes.CreateOneAsync(indexModel);



veri tabanına bağlanıp daha sonra timestamp adında index oluşturuyor



 ![image](https://user-images.githubusercontent.com/65457096/234785066-b4f4b99e-59ff-4ad6-9d1c-139e9f5e578f.png)




Bugünkü kazanımlarım
-	Manuel indexleme yapmayı öğrendim
















































 	







 





