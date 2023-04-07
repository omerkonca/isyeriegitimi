# İşyeri Eğitimi

## Yapılan Çalışmanın Konusu : Arayüz tasarımı Grafik oluşturma 


Bugünkü çalışmam grafik oluşturma. Önce araştırma yaptım ve daha sonra yaptığım araştırmalar sonucu nasıl yapılacağını öğrendim. Ve daha sonra gereksinimleri gözden geçirdim daha sonra grafik yapmak için işe koyuldum. Grafiğe dökeceğim değerler ise şunlar ; [Angle][g], [Speed][g], [Wheel][g] şimdilik bu 3 değer. Ilerde gereksinimlere göre artabilir.
Buda yazmış olduğum angle grafiğinin kodu

         _zmqLoopFlag = true;
	        if (this->_ anglePageVisibility == true) {

		if (this->Net == NULL) {
			return;
		}

		ImGui::BulletText("Move your speed to change the data!");

		ImGui::Checkbox("Pause", &isPause);     // duraklatma seçenegi 

		if (!isPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		{
			this->SGD->History = 20.0f;
			this->SGD->Time += ImGui::GetIO().DeltaTime;

			this->SGD-> angle.AddPoint(this->SGD->Time, this->Net->Signal);


		}
		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
			this->SGD->Time;



		ImGui::SliderFloat("History", &this->SGD->History, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(200, 150))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->Time - this->SGD->History, this->SGD->Time, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("rs X", &this->SGD->angle.Data[0].x, &this->SGD-> angle.Data[0].y, this->SGD-> angle.Data.size(), 0, this->SGD-> angle.Offset, 2 * sizeof(float));
			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	    }
    }


Tasarladığım arayüz ise şu şekilde

![image](https://user-images.githubusercontent.com/65457096/230601369-91ff6d8e-3b91-44c3-a4ca-e0a4198ebe83.png)

![image](https://user-images.githubusercontent.com/65457096/230601378-e0358a6c-3747-4c9b-9f74-fde41189a02a.png)



 
Bugünkü kazanımlarım
- Grafik yapmayı öğrendim




