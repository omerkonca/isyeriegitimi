using MongoDB.Bson;
using MongoDB.Driver;
using System;
using System.Text.Json;
using System.Threading;

namespace mongodbindex
{
    class Program
    {
        static void Main(string[] args)
        {
            var mongoClient = new MongoClient("mongodb://192.168.1.107:27017");
            var database = mongoClient.GetDatabase("robutel_local_log");
            var collection = database.GetCollection<BsonDocument>("CurrentSpeedLog");

            var options = new ChangeStreamOptions
            {
                FullDocument =
                           ChangeStreamFullDocumentOption.UpdateLookup
            };
            var pipeline = new EmptyPipelineDefinition<ChangeStreamDocument
                          <BsonDocument>>().Match(change => change.OperationType ==
                          ChangeStreamOperationType.Insert);

            var changeStream = collection.Watch(pipeline, options);

            var timer = new Timer(async (state) =>
            {
                var indexKeys = Builders<BsonDocument>.IndexKeys.Text("logMessage");
                collection.Indexes.CreateOne(new
                                   CreateIndexModel<BsonDocument>(indexKeys));

                Console.WriteLine($"Logs indexed at {DateTime.Now}");
            }, null, GetDueTime(), TimeSpan.FromDays(1)); // Her gün 11:00-12:00   
           // arasında indeksleme işlemini gerçekleştirir.
            changeStream.ForEachAsync(async change =>
            {
                var newLog = change.FullDocument;
                Console.WriteLine($"New log indexed: {newLog}");
            });
            Console.ReadLine();
        }

        static TimeSpan GetDueTime()
        {
            var now = DateTime.Now;
            var dueTime = new DateTime(now.Year, now.Month, now.Day, 23, 0, 0, DateTimeKind.Local);
            if (dueTime <= now)
            {
                dueTime = dueTime.AddDays(1);
            }
            return dueTime - now;
        }
    }
}
