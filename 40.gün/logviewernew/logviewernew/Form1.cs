using MongoDB.Bson;
using MongoDB.Driver;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace logviewernew
{
    public partial class Form1 : Form
    {

        private List<BsonDocument> veriler;
        public Form1()
        {
            InitializeComponent();

            // MongoDB baðlantýsý oluþturuyoruz
            var client = new MongoClient("mongodb://192.168.2.125:27017");
            var database = client.GetDatabase("robutel_local_log");
            var collection = database.GetCollection<BsonDocument>("ReportLog");

            // Verileri MongoDB'den çekiyoruz
            veriler = collection.Find(new BsonDocument()).ToList();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Ýlk yükleme için ilk sayfayý gösteriyoruz
            SayfaGoster(1);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // Kullanýcýnýn seçtiði sayfayý gösteriyoruz
            SayfaGoster(Convert.ToInt32(textBox1.Text));
        }
        private int pageSize = 50; // Number of documents per page
        private int currentPage = 1; // Current page number

        private void SayfaGoster(int sayfaNo)
        {
            // Update the current page number
            currentPage = sayfaNo;

            // Calculate the index of the first document to be displayed on the current page
            int startIndex = (currentPage - 1) * pageSize;

            // Filter the retrieved documents based on the current page and the page size
            var gosterilecekVeriler = veriler.Skip(startIndex).Take(pageSize);

            // Clear the richTextBox1 control
            richTextBox3.Controls.Clear();

            // Add the documents to the richTextBox1 control
            int satir = 0;
            int sutun = 0;
            int panelGenisligi = richTextBox3.Width - 20; // 20, Label aralýðý için
            foreach (var veri in gosterilecekVeriler)
            {
                Label label = new Label();
                label.Text = veri.ToString();
                label.AutoSize = true;
                if (label.Width > panelGenisligi / 2)
                {
                    label.Width = panelGenisligi / 2;
                    label.Height = (int)label.CreateGraphics().MeasureString(label.Text, label.Font, label.Width).Height + 10;
                }
                label.Top = satir * (label.Height + 10) + 10;
                label.Left = sutun * (label.Width + 10) + 10;
                richTextBox3.Controls.Add(label);

                sutun++;
                if (sutun * (label.Width + 10) + 10 > panelGenisligi)
                {
                    satir++;
                    sutun = 0;
                }
            }

            // Calculate the total number of pages
            int toplamSayfaSayisi = (int)Math.Ceiling((double)veriler.Count / pageSize);

            // Update the label1 control to display the current page number and the total number of pages
            label1.Text = string.Format("Sayfa: {0}/{1}", currentPage, toplamSayfaSayisi);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string arananKelime = textBox2.Text;

            int bulunanIndex = richTextBox3.Find(arananKelime);

            if (bulunanIndex != -1)
            {
                // Bulunan kelimeyi seç ve renklendir
                richTextBox3.Select(bulunanIndex, arananKelime.Length);
                richTextBox3.SelectionBackColor = Color.Yellow;
                richTextBox3.SelectionColor = Color.Red;

                // Bulunan kelimeyi görüntüle
                richTextBox3.ScrollToCaret();
            }
            else
            {
                MessageBox.Show("Kelime bulunamadý.");
            }
        }
    }
}
