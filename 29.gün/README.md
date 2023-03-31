# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : : Mouse hareketi ile daire çizimi 
Bugünkü konumuz mouse tıklanmasıyla daire çizimi. Yani şöyle açıklıyacak olursam bir tıklamayı 1.parametre 2.tıklamayı 2.parametre olarak alıyor onu yarı çapı değişkenine atıyor ve o uzunluk kadar bir daire çizimi yapıyor aşağıda kod ve görseli ekledim.
Aşağıdaki kod radius değişkeni yani yarı çap uzunluğumuz olacak mouse tıklarını atıyoruz oraya sonra plotline çember çizimi yapıyoruz

	radius = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
			static double xs[360], ys[360];
			for (int i = 0; i < 360; ++i)
			{
				double angle = i * 2 * PI / 359.0;
				xs[i] = point2.x + radius * cos(angle);
				ys[i] = point2.y + radius * sin(angle);
			}
			ImPlot::PlotLine("Circle", xs, ys, 360);


### Aşağıda görselde çizilen daire yer alıyor

![image](https://user-images.githubusercontent.com/65457096/229059101-3abde281-7a72-4d6a-a050-1819b8f880aa.png)

Bugünkü kazanmlarım
-	Daire hesaplamasını kod ile nasıl yapcağımı öğrendim










 	







 





