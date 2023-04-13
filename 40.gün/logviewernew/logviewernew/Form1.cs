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
            var collection = database.GetCollection<BsonDocument>("CurrentSpeedLog");

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
        private void SayfaGoster(int sayfaNo)
        {
            // Verileri sayfaya göre filtreliyoruz
            var gosterilecekVeriler = veriler.Skip((sayfaNo - 1) * 300).Take(300);

            // Panel'i temizliyoruz
            richTextBox1.Controls.Clear();

            // Verileri Panel'e ekliyoruz
            int satir = 0;
            int sutun = 0;
            int panelGenisligi = richTextBox1.Width - 20; // 20, Label aralýðý için
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
                richTextBox1.Controls.Add(label);

                sutun++;
                if (sutun * (label.Width + 10) + 10 > panelGenisligi)
                {
                    satir++;
                    sutun = 0;
                }
            }

            // Toplam sayfa sayýsýný hesaplýyoruz ve sayfa sayýsý metnini güncelliyoruz
            int toplamSayfaSayisi = (int)Math.Ceiling((double)veriler.Count / 300);
            label1.Text = string.Format("Sayfa: {0}/{1}", sayfaNo, toplamSayfaSayisi);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string arananKelime = textBox2.Text;

            int bulunanIndex = richTextBox1.Find(arananKelime);

            if (bulunanIndex != -1)
            {
                // Bulunan kelimeyi seç ve renklendir
                richTextBox1.Select(bulunanIndex, arananKelime.Length);
                richTextBox1.SelectionBackColor = Color.Yellow;
                richTextBox1.SelectionColor = Color.Red;

                // Bulunan kelimeyi görüntüle
                richTextBox1.ScrollToCaret();
            }
            else
            {
                MessageBox.Show("Kelime bulunamadý.");
            }
        }
    }
}
