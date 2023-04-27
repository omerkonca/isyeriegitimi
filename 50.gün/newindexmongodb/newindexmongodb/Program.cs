using MongoDB.Bson;
using MongoDB.Driver;

var client = new MongoClient("mongodb://192.168.1.107:27017");
var database = client.GetDatabase("robutel_local_log");
var collection = database.GetCollection<BsonDocument>("BatteryLog");


Console.WriteLine((DateTime.Now.ToString("HH:m:s:fff")));
var indexModel = new CreateIndexModel<BsonDocument>(Builders<BsonDocument>.IndexKeys.Ascending("Timestamp"));
Console.WriteLine("--------");


await collection.Indexes.CreateOneAsync(indexModel);


Console.WriteLine((DateTime.Now.ToString("HH:m:s:fff")));