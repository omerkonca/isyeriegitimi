# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Log viewer filtreleme işlemi

Bugün bana yeni görev verildi görevde şu şekilde biz çektiğimiz logların içinde arama yapmak istiyoruz. Ctrl – F mantığı gibi arama yapan kod yazdım .

     arananKelime = textBox1.Text;

            // Önceki aramada bulunan kelimeyi vurgusunu kaldır
            logArea.SelectionBackColor = Color.White;
            logArea.SelectionColor = Color.Black;

            int bulunanIndex = logArea.Find(arananKelime, sonIndex + 1, RichTextBoxFinds.None);
            if (bulunanIndex != -1)
            {
                // Bulunan kelimeyi seç ve renklendir
                logArea.Select(bulunanIndex, arananKelime.Length);
                logArea.SelectionBackColor = Color.Yellow;
                logArea.SelectionColor = Color.Red;

                // Bulunan kelimeyi görüntüle
                logArea.ScrollToCaret();

                sonIndex = bulunanIndex;
            }
            else
            {
                MessageBox.Show("Kelime bulunamadı.");
                sonIndex = -1;
            }
        }
        private int bulunanSayisi = 0;
        private void button5_Click(object sender, EventArgs e)
        {
            bulunanSayisi = 0;

            foreach (string line in logArea.Lines)
            {
                int index = 0;
                while (index < line.Length)
                {
                    index = line.IndexOf(arananKelime, index);
                    if (index == -1)
                    {
                        break;
                    }

                    bulunanSayisi++;
                    index += arananKelime.Length;
                }
            }

            MessageBox.Show("Toplam " + bulunanSayisi + " adet bulundu.");
        }

Kod bu şekilde herhangi bir kelimeyi yazınca o kelimeye eş kelime varsa arayıp ekrana getiriyor ve kaç tane varsa say butonuna basıp bütün eşdeğer kelimeleri sayıyor ekrana yazdırıyor






Bu şekilde 2 buton 1 tane text box

![image](https://user-images.githubusercontent.com/65457096/231780062-bed33bdf-0ee6-4fcf-b9a8-7752d75b2421.png)


![image](https://user-images.githubusercontent.com/65457096/231780076-3471979b-de69-4364-8a16-1abeb05630d0.png)


![image](https://user-images.githubusercontent.com/65457096/231780095-e96ea8a8-5a30-424a-85c1-c6e0d839ccc4.png)


Bugünkü kazanımlarım
-	filtreleme yapmayı öğrendim 



























 	







 





