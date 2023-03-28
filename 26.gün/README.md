# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Position grafiğinde mouse çizgi çizip uzunluk ölçümü yapma 

Bugün haftanın ilk günü olması sebebiyle toplantı yaptık görev dağılımlarını belirledik ben uzunluk hesabı kısmını aldım ve ayrıca bu hafta demolara başlıyacağımızı söylediler. Benim görevim position grafiğinde herhangi bir yere mouse ile sağ click yapınca oraya kadar olan bir çizgi çizmeyi sağlıyor. İlk görevim buydu ve bunu yaptım. Daha sonraki görevim ise o çizdiğim çizginin uzunluğunu hesaplamaktı ve onu da yaptım aşağıda kodları ve resimleri belirttim.


Aşağıdaki kod mouse sağ tıklamasını verdiğimiz point1 parametresine atama yapıyor.

Ve aşağıdaki fx ve fy ile mouse tıkladığımız yere GetPlotDrawList fonksiyonuyla çizgi çizdirebiliyoruz.

	if (ImGui::IsMouseClicked(0))
   		 point1 = ImPlot::GetPlotMousePos();
				
			// mevcut konum ve tıklanan nokta arasındaki uzaklığı hesapla
			
			//ImGui::Text("Uzunluk: %.2f", distance);
				ImPlot::GetPlotDrawList()->AddLine(ImPlot::PlotToPixels(ImPlotPoint(this->Agv->CellLx, this->Agv->CellLy)), ImPlot::PlotToPixels(ImPlotPoint(this->Agv->CellSx, this->Agv->CellSy)), IM_COL32(255, 127, 0, 255));
				ImPlot::GetPlotDrawList()->AddCircleFilled(ImPlot::PlotToPixels(ImPlotPoint(this->Agv->CellLx, this->Agv->CellLy)), 3, IM_COL32(255, 127, 0, 255));

				ImPlot::GetPlotDrawList()->AddLine(ImPlot::PlotToPixels(ImPlotPoint(this->Agv->Fx, this->Agv->Fy)), ImPlot::PlotToPixels(point1), IM_COL32(255, 0, 0, 255));




#### Burda position grafiğinin çalışma mantığı forklift haraketini bitirdikten sonra gittiği yolu gösteriyor onuda diziye atayarak yaptık.



![image](https://user-images.githubusercontent.com/65457096/228234244-2b697cd3-f93a-4cb8-a74e-85df5762e826.png)



## Bugünkü kazanımlarım
- getplotdrawlist fonksiyonun ne işe yaradığını öğrendim
- çizgi çizmeyi öğrendim ve 2 nokta arasındaki uzunluk nasıl hesaplanır onu öğrendim





























 














 	







 





