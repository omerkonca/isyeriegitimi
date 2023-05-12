# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :  Logviewer backend kısmındaki sorunların araştırılması

Bugün staj günümde logviewerda daki sayfalar arası geçiş yaptığımızda sürekli aynı veriler geliyordu çözümünü araştırarak geçti günüm ve sorunu çözdüm çözümü ise şu şekilde yapacağım bitane fonksiyon oluşturup ileri geri butonlarında o fonksiyonun sürekli dönmesini sağlayacağım

Bu şekilde 1.sayfadayım veriler

  ![image](https://github.com/omerkonca/isyeriegitimi/assets/65457096/bd3be48d-fa9f-4983-af4f-54688273782f)






Bu şekilde 2.sayfaya geçiyoum veriler yine aynı

 ![image](https://github.com/omerkonca/isyeriegitimi/assets/65457096/fd17a21d-97b0-43e6-8545-f6eb79429da4)



Kodumda bu şekilde

         logArea.Clear();
     

            foreach (var document in logDocuments)
            {

                var fields = document.AsBsonDocument.Elements;

                foreach (var field in fields)
                {
                    logArea.AppendText(field.Name + ": " + field.Value + "\n");
                }

                logArea.AppendText("\n");
            }

            lbl_sayfa.Text = $"Sayfa {_pageNumber} / {_totalPages}";
            lbl_top_veri.Text = $"Toplam veri: {_totalDocuments}";
            lbl_sayfa_veri_adedi.Text = $"Sayfa veri adedi: {_pageSize}";
            numeric_git.Text = _pageNumber.ToString();








































 








Tarih : 05/06/ 2023

 
















































 	







 





