# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :  Robo 3t de filtreleme işlemi 
Bugün yavaşlık sorunun çözümü için, bizim loglamaları çektiğimiz robo 3t uygulamasında filtreleme işlemi yapıp, yavaşlık testi yaptık ve sonuç olarak sorun burdada olmadığını gördük 



Filtreleme kodum

     db.getCollection('ReportLog').find({ Timestamp: { $gte: new Date('2022-01-01'), $lt: new Date('2023-02-01') }})


robo3t filtreleme yaptığım yer

 
![image](https://user-images.githubusercontent.com/65457096/231389590-f5d71288-87ab-42d5-b85f-44ed0fb7e6f0.png)





Bugünkü kazanımlarım
-	robo3t filtrelemeyi öğrendim
































 	







 





