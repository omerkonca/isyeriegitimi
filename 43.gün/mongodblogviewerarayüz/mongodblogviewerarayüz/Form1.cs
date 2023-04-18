using MongoDB.Bson;
using MongoDB.Driver;
using System.Text.Json;

namespace mongodblogviewerarayüz
{
    public partial class Form1 : Form
    {
        private int _pageNumber = 1;
        private int _pageSize = 50;
        private int _totalPages = 1;
        private long _totalDocuments = 0;
        public Form1()
        {
            InitializeComponent();
        }

        private async void Form1_Load(object sender, EventArgs e)
        {
            await DisplayData();
        }

        private async void button1_Click(object sender, EventArgs e)
        {
            if (_pageNumber > 1)
            {
                _pageNumber--;
                await DisplayData();
            }
        }

        private async void button2_Click(object sender, EventArgs e)
        {
            if (_pageNumber < _totalPages)
            {
                _pageNumber++;
                await DisplayData();
            }
        }



        private async void button3_Click(object sender, EventArgs e)
        {
            if (int.TryParse(textBox1.Text, out int pageNumber))
            {
                if (pageNumber > 0 && pageNumber <= _totalPages)
                {
                    _pageNumber = pageNumber;
                    await DisplayData();
                }
                else
                {
                    MessageBox.Show($"Geçerli bir sayfa numarası giriniz (1 - {_totalPages})");
                }
            }
            else
            {
                MessageBox.Show("Geçerli bir sayfa numarası giriniz");
            }
        }


        private async System.Threading.Tasks.Task DisplayData()
        {
            var connectionString = "mongodb://192.168.2.125:27017";
            var client = new MongoClient(connectionString);
            var database = client.GetDatabase("robutel_local_log");
            var collection = database.GetCollection<BsonDocument>("GeneralLog");
            var filter = Builders<BsonDocument>.Filter.Empty;

            

            _totalDocuments = await collection.CountDocumentsAsync(filter);
            _totalPages = (int)Math.Ceiling((double)_totalDocuments / _pageSize);

            var documents = await collection.Find(filter).Skip((_pageNumber - 1) * _pageSize).Limit(_pageSize).ToListAsync();

            richTextBox1.Clear();

            foreach (var document in documents)
            {
                richTextBox1.AppendText("Belge ID: " + document["_id"] + "\n");

                var fields = document.AsBsonDocument.Elements;

                foreach (var field in fields)
                {
                    richTextBox1.AppendText(field.Name + ": " + field.Value + "\n");
                }

                richTextBox1.AppendText("\n");
            }

            label1.Text = $"Sayfa {_pageNumber} / {_totalPages}";
            label2.Text = $"Toplam belge sayısı: {_totalDocuments}";
            label3.Text = $"Sayfa başına belge sayısı: {_pageSize}";
            textBox1.Text = _pageNumber.ToString();

            button1.Enabled = (_pageNumber > 1);
            button2.Enabled = (_pageNumber < _totalPages);
        }
    }
}