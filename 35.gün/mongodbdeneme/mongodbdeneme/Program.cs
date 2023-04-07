using MongoDB.Driver;
using MongoDB.Bson;
using MongoDB.Bson.IO;



class Program
{
    static void Main(string[] args)
    {
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
        Console.ReadLine();
    }
}

