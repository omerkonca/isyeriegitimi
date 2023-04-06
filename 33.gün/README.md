# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :  Network kısmının grafikleştirilmesi

Bugün net kısmına geçtik agv kısmı tamamıyla bitti. Bugünkü görevler tam olarak Transmiteded Rate (İletim Oranı), Signal, Ping, Speed , Received Rate (Alınan Oran) bu verileri grafikleştirme işlmeini yaptım.

Aşağıdaki kod received rate nin grafiği diğer grafik kodları da bu şekilde benzer kodlar

	ImGui::Checkbox("Enabled", &this->ReceivedRateGraphic->Enabled);
	ImGui::SameLine();
	ImGui::SliderFloat("History", &this->ReceivedRateGraphic->History, 1, 30, "%.1f s");  // .1f yaparsak milisaniye olarak ayarlanıyor 

	static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

	if (ImPlot::BeginPlot("##Scrollinga")) {     // grafik ölçeklendirme 
	ImPlot::SetupAxes("Time [s]", "Received rate  [ ]");

	ImPlot::SetupAxisLimits(ImAxis_X1, this->ReceivedRateGraphic->Time - this->ReceivedRateGraphic->History, this->ReceivedRateGraphic->Time, ImGuiCond_Always);
	ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 2000);
	if (this->ReceivedRateGraphic->StokingReceivedRate.Data.Size > 0) {
		//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
		ImPlot::PlotLine("received rate", &this->ReceivedRateGraphic->StokingReceivedRate.Data[0].x, &this->ReceivedRateGraphic->StokingReceivedRate.Data[0].y, this->ReceivedRateGraphic->StokingReceivedRate.Data.size(), 0, this->ReceivedRateGraphic->StokingReceivedRate.Offset, 2 * sizeof(float));
	}
	ImPlot::EndPlot();
	}
              
![image](https://user-images.githubusercontent.com/65457096/230352000-deed5a0e-9359-4d09-a8d3-aaf881876b90.png)
![image](https://user-images.githubusercontent.com/65457096/230351919-9604d782-5a43-4012-bb4b-b3b104c9885d.png)


Bugünkü kazanımlarım
-	Gelen datayı grafikleştirmeyi öğrendim
















 














 	







 





