# İşyeri Eğitimi


##  Yapılan Çalışmanın Konusu : Position kısmına üçgen çizdirme

Bugünkü yapacağım işler, position kısmına anlık olarak veriler x, y, angle(açı) olarak geliyor. Position kısmı ne diyecek olursanız position kısmı forkliftin teker açısınına nlık olarak gelen verilleri grafikte gösterdiğimiz bir class, tam olarak 3 tane veri geliyor gelen 3 veriden x ve y forkliftin konumunu gösteriyor angle(açı) olanda forkliftin yönünü gösteriyor.  Veriler bu şekilde geliyor ve bende bunu anlık olarak grafikte gösterdim. Ve yapacağım üçgeni hesapladım.

Aşağıda kodlarım ve çalışma şekli 

	if (this->SGD->StokingPosition.Data.size() > 0) {
  	 float xMin = this->SGD->StokingPosition.Data[0].x - 5000; // x ekseninin minimum değeri
  	 float xMax = this->SGD->StokingPosition.Data[0].x + 5000; // x ekseninin maksimum değeri
 	  float yMin = this->SGD->StokingPosition.Data[0].y - 5000; // y ekseninin minimum değeri
 	  float yMax = this->SGD->StokingPosition.Data[0].y + 5000; // y ekseninin maksimum değeri
  	 if (ImPlot::BeginPlot("Scatter Plot", ImVec2(-1,0), ImPlotFlags_Equal)) {
		ImPlot::SetupAxesLimits(xMin, xMax, yMin, yMax);
		ImPlot::PlotScatter("pos", &this->SGD->StokingPosition.Data[0].x, &this->SGD->StokingPosition.Data[0].y, this->SGD->StokingPosition.Data.size(), 0, 0, 2 * sizeof(int));
		int lastIndex = this->SGD->StokingPosition.Data.Size - 1;

		//ImPlot::PopStyleVar();
		float xRange = ImPlot::GetPlotLimits().X.Max - ImPlot::GetPlotLimits().X.Min;
		float yRange = ImPlot::GetPlotLimits().Y.Max - ImPlot::GetPlotLimits().Y.Min;
		float r = fminf(xRange, yRange) / 50.0f; // r değerini grafik boyutuna göre ölçeklendirin

	float x1 = this->SGD->StokingPosition.Data[lastIndex].x;
	float y1 = this->SGD->StokingPosition.Data[lastIndex].y;

	float x_1 = x1 + cos(this->Agv->Angle * PI / 180) * r * 2;
	float y_1 = y1 + sin(this->Agv->Angle * PI / 180) * r * 2;
		
	float x_2 = x1 + cos(fmod(this->Agv->Angle + 120, 360) * PI / 180) * r;
	float y_2 = y1 + sin(fmod(this->Agv->Angle + 120, 360) * PI / 180) * r;

	float x_3 = x1 + cos(fmod(this->Agv->Angle + 240, 360) * PI / 180) * r;
	float y_3 = y1 + sin(fmod(this->Agv->Angle + 240, 360) * PI / 180) * r;


	ImVec2 p1 = ImPlot::PlotToPixels(ImPlotPoint(x_2, y_2));//sol alt 
	ImVec2 p2 = ImPlot::PlotToPixels(ImPlotPoint(x_3, y_3));// sag alt 
	ImVec2 p3 = ImPlot::PlotToPixels(ImPlotPoint(x_1, y_1));// tepe
	ImPlot::GetPlotDrawList()->AddTriangleFilled(p1, p2, p3, IM_COL32(255, 127, 0, 255));
				
	ImPlot::EndPlot();
				
			}
		}



Üçgenin hesaplanmasını tahtada bu şekilde yaptım

![image](https://user-images.githubusercontent.com/65457096/230889634-71f1b790-30be-43cd-affb-0a9bdec82daf.png)

grafiğin yazdırması bu şekilde


![image](https://user-images.githubusercontent.com/65457096/230889666-7d8cd211-ed17-4502-aa21-80739a1ff223.png)


Bugünkü kazanımlarım
-	Matematiksel işlem ile kod yazarak üçgen çizdirmeyi öğrendim


 














 	







 





