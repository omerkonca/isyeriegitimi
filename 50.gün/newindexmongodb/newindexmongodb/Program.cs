using Quartz;
using Quartz.Impl;
using MongoDB.Driver;

// Quartz.NET zamanlayıcıyı oluşturun
var schedulerFactory = new StdSchedulerFactory();
var scheduler = await schedulerFactory.GetScheduler();

// Indeks oluşturmak için görev oluşturun
var indexJob = JobBuilder.Create<CreateIndexJob>()
    .Build();

// Görevi belirli saatlerde çalıştırmak için tetikleyici (trigger) oluşturun
var indexTrigger = TriggerBuilder.Create()
    .WithDailyTimeIntervalSchedule(x => x
        .OnMondayThroughFriday()
        .StartingDailyAt(TimeOfDay.HourAndMinuteOfDay(8, 0)) // 8:00'da başla
        .EndingDailyAt(TimeOfDay.HourAndMinuteOfDay(17, 0)) // 17:00'da bitir
        .WithIntervalInSeconds(60)) // Her dakika çalıştır
    .Build();

// Indeks oluşturma görevini zamanlayıcıya ekleyin
await scheduler.ScheduleJob(indexJob, indexTrigger);

// Quartz.NET zamanlayıcıyı başlatın
await scheduler.Start();

// Indeks oluşturma görevi
public class CreateIndexJob : IJob
{
    public async Task Execute(IJobExecutionContext context)
    {
        var client = new MongoClient("mongodb://192.168.1.107:27017"); // MongoDB bağlantısını oluşturun
        var database = client.GetDatabase("robutel_local_log"); // Veritabanını seçin
        var collection = database.GetCollection<MyClass>("CurrentSpeedLog"); // Koleksiyonu seçin

        var keys = Builders<MyClass>.IndexKeys.Ascending(x => x.id); // Indeks anahtarlarını belirtin

        var options = new CreateIndexOptions { Unique = true }; // Indeks seçeneklerini belirtin

        await collection.Indexes.CreateOneAsync(new CreateIndexModel<MyClass>(keys, options)); // Indeks oluştur
    }
}
