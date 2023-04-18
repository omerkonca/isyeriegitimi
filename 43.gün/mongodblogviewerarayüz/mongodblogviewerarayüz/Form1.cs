using MongoDB.Bson;
using MongoDB.Driver;
using System.Text.Json;

namespace mongodblogviewerarayüz
{
    public partial class Form1 : Form
    {
        private int _pageNumber = 1;
        private int _pageSize = 50;
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
            _pageNumber++;
            await DisplayData();
        }
        private async System.Threading.Tasks.Task DisplayData()
        {
            var connectionString = "mongodb://192.168.2.125:27017";
            var client = new MongoClient(connectionString);
            var database = client.GetDatabase("robutel_local_log");
            var collection = database.GetCollection<BsonDocument>("ReportLog");
            var filter = Builders<BsonDocument>.Filter.Empty;
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

            label1.Text = "Sayfa " + _pageNumber;

            button1.Enabled = (_pageNumber > 1);
            button2.Enabled = (documents.Count == _pageSize);
        }
    }
}