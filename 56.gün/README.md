# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :   Veritabanından log kayıtları çekme 

Bugünkü stajımda, C# programlama dilinde Windows Forms kullanarak bir MongoDB veritabanına bağlanan ve belirli bir tarih aralığındaki belgeleri görüntüleyen bir uygulama geliştirdim. Uygulamayı tasarlamak için Microsoft Visual Studio IDE'sini kullandım.

Uygulamanın kullanıcı arayüzü, bir tarih aralığı seçmek için iki adet DateTimePicker kontrolü içeriyordu. Kullanıcının belge sayısını ve sayfa numarasını takip etmesi için iki adet Label kontrolü ve bir NumericUpDown kontrolü de eklendi. Belgelerin görüntülenmesi için de bir RichTextBox kontrolü kullanıldı. Ayrıca, sayfalama işlevselliğini sağlamak için "Önceki Sayfa" ve "Sonraki Sayfa" düğmeleri de eklendi.

Veritabanı işlemleri için MongoDB.Driver ve MongoDB.Bson kütüphaneleri kullanıldı. Bu kütüphaneler, MongoDB veritabanına bağlanmak, belgeleri sorgulamak ve sonuçları işlemek için gerekli araçları sağladı.

Verilerin işlenmesi için ise System.Text.Json kütüphanesi kullanıldı. Bu kütüphane, belgeleri JSON formatına dönüştürmek ve JSON formatındaki verileri işlemek için kullanıldı.

Uygulama, belirli bir tarih aralığındaki belgeleri veritabanından almak, sayfalama işlevselliğini sağlamak, belgeleri JSON formatına dönüştürmek ve son olarak RichTextBox kontrolünde görüntülemek için bir dizi metot kullandı.

Bu uygulama sayesinde, C# programlama dili ve MongoDB veritabanı yönetimi konusundaki deneyimimi daha da geliştirdim. Ayrıca, Windows Forms uygulamalarının nasıl oluşturulacağına dair daha fazla bilgi edinerek bu alandaki becerilerimi de geliştirdim.

Yazdığım kod bu şekilde

            DateTime startDate = dateTimePicker1.Value.Date;
            DateTime endDate = dateTimePicker2.Value.Date.AddDays(1);

            var connectionString = "mongodb://192.168.1.109:27017";
            var client = new MongoClient(connectionString);
            var database = client.GetDatabase("robutel_local_log");
            var collection = database.GetCollection<BsonDocument>("Traffic");

            var filter = Builders<BsonDocument>.Filter.And(
                Builders<BsonDocument>.Filter.Gte("Timestamp", startDate),
                Builders<BsonDocument>.Filter.Lte("Timestamp", endDate));

            _totalDocuments = await collection.CountDocumentsAsync(filter);
            _totalPages = (int)Math.Ceiling((double)_totalDocuments / _pageSize);

            var findOptions = new FindOptions<BsonDocument>();
            findOptions.Limit = _pageSize;
            findOptions.Skip = (_pageNumber - 1) * _pageSize;

            var result = await collection.FindAsync(filter, findOptions);
            var documents = result.ToList();
            richTextBox1.Clear();
            foreach (var document in documents)
            {
                richTextBox1.AppendText("Belge ID: " + document["_id"] + "\n");
                var fields = document.AsBsonDocument.Elements;
                foreach (var field in fields)
                {
                    richTextBox1.AppendText(field.Name + ": " + field.Value + "\n");
                }
            }




            label1.Text = $"Sayfa {_pageNumber} / {_totalPages}";
            label2.Text = $"Toplam belge sayısı: {_totalDocuments}";
            label3.Text = $"Sayfa başına belge sayısı: {_pageSize}";
            numericUpDown1.Text = _pageNumber.ToString();

            button1.Enabled = (_pageNumber > 1);
            button2.Enabled = (_pageNumber < _totalPages);


Uygulama bu şekilde

![image](https://user-images.githubusercontent.com/65457096/235841325-996c3857-1fd4-465d-ba7c-7313f9a1a027.png)

 


Bugünkü stajımda MongoDB kullanarak verileri filtreleyebilme ve sayfalama özellikleri eklediğiniz bir arayüz geliştirdim. Kodumda C# programlama dilini kullanarak MongoDB.Driver ve System.Text.Json kütüphanelerini kullandım. Bunun yanı sıra Windows Form Application arayüzü oluşturdum ve arayüzdeki kontrolleri kullanarak kullanıcıların verileri filtrelemesine, sayfalama özelliklerini kullanmasına ve arama yapmasına olanak sağladım.

Bugünkü kazanımlarım
-	MongoDB ile veri filtreleme ve sayfalama işlemlerini gerçekleştirebilme becerisi
-	C# programlama dilini kullanarak veritabanı işlemleri yapabilme yeteneği
-	Windows Form Application arayüzü oluşturma becerisi
-	Kontrol bileşenleri (DateTimePicker, NumericUpDown, Button, Label ve RichTextBox gibi) kullanarak kullanıcı arayüzü oluşturma becerisi
-	Asenkron programlama konusunda tecrübe edinme fırsatı.












Tarih : 22/05/ 2023

 
















































 	







 





