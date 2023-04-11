


using MongoDB.Driver;
using MongoDB.Bson;
using System.Diagnostics;

class Program
{
    static void Main(string[] args)
    {
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

        //foreach (var document in documents)
        //{
        //    var json = document.ToJson(new JsonWriterSettings { Indent = true }); // BSON belgesini JSON formatına dönüştürülüyor
        //    Console.WriteLine(json);
        //}

        Console.WriteLine($"{documents.Count} adet belge bulundu.");
        Console.WriteLine($"Sorgu {stopwatch.Elapsed.TotalSeconds} saniyede tamamlandı.");

        Console.ReadLine();
    }
}

