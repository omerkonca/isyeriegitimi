using MongoDB.Bson;
using MongoDB.Driver;
using System.Text.Json;

namespace mongodblogviewerarayüz
{
    public partial class Form1 : Form
    {
        private int _pageNumber = 1;
        private int _pageSize = 1000;
        private int _totalPages = 1;
        private long _totalDocuments = 0;
        public Form1()
        {
            InitializeComponent();
        }

        private async void Form1_Load(object sender, EventArgs e)
        {
            dateTimePicker1.Value = new DateTime(2022, 1, 1);
            dateTimePicker2.Value = DateTime.Today;

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
            if (int.TryParse(numericUpDown1.Text, out int pageNumber))
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


        private async Task DisplayData()
        {
            DateTime startDate = dateTimePicker1.Value.Date;
            DateTime endDate = dateTimePicker2.Value.Date.AddDays(1);

            var connectionString = "mongodb://192.168.1.105:27017";
            var client = new MongoClient(connectionString);
            var database = client.GetDatabase("robutel_local_log");
            var collection = database.GetCollection<BsonDocument>("GeneralLog");

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

                richTextBox1.AppendText("\n");
            }

            label1.Text = $"Sayfa {_pageNumber} / {_totalPages}";
            label2.Text = $"Toplam belge sayısı: {_totalDocuments}";
            label3.Text = $"Sayfa başına belge sayısı: {_pageSize}";
            numericUpDown1.Text = _pageNumber.ToString();

            button1.Enabled = (_pageNumber > 1);
            button2.Enabled = (_pageNumber < _totalPages);
        }
        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {
            if (dateTimePicker1.Value > dateTimePicker2.Value)
            {
                dateTimePicker1.Value = dateTimePicker2.Value.AddDays(-1);
            }
        }

        private void dateTimePicker2_ValueChanged(object sender, EventArgs e)
        {
            if (dateTimePicker2.Value < dateTimePicker1.Value)
            {
                dateTimePicker2.Value = dateTimePicker1.Value.AddDays(1);
            }
        }



        private async void button4_Click_1(object sender, EventArgs e)
        {
            await DisplayData();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            richTextBox1.Clear();
            label1.Text = "Sayfa";
            label2.Text = "Toplam belge sayısı:";
            label3.Text = "Sayfa başına belge sayısı:";
            numericUpDown1.Value = 0;
        }
    }
}