# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Arayüz geliştirilmesi

Bugünkü görevim arayüzde kullanışsız bazı yerler vardı onları daha kullanışlı hale getirme
Grafiklerde yeniden boyutlandırılmaya izin verilmiyor onu düzelttim
Bir checkbox ile hizala görevini yapamadım
3grafiği yanyana gösterme görevinide tamamladım
Birde otomatik fokuslama görevinide kısmen hallettim
Kodlarım şu şekilde

	ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("Agv"))
		{
			ImGui::MenuItem("Wheel Angle", "", &this->WheelGraphic->Visibility);
			ImGui::MenuItem("Speed", "", &this->SpeedGraphic->Visibility);
			ImGui::MenuItem("Angle", "", &this->AgvAngleGraphic->Visibility);
			ImGui::MenuItem("Position", "", &this->AgvPositionGraphic->Visibility);
			ImGui::EndMenu();
		}	
		if (ImGui::BeginMenu("Net"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();

		if (this-> SpeedGraphic->Visibility)
		{
			ImGui::BeginChild("Speed Page", ImVec2(1000, 600), true);
				this->SpeedGraphic->Visibility = true;
				this->SpeedPage();
				ImGui::EndChild();
		}
		
		if (this->WheelGraphic->Visibility)
		{

		
			ImGui::SameLine();

			ImGui::BeginChild("Wheel Angle Page", ImVec2(1000, 600), true);
			
				this->WheelGraphic->Visibility = true;
				this->WheelPage();
				ImGui::EndChild();
			
		}
		
                if (this->AgvAngleGraphic->Visibility)
		{

			ImGui::BeginChild("Agv Angle Page", ImVec2(1000, 600), true);
			
				this->AgvAngleGraphic->Visibility = true;
				this->AgvAngelPage();
				ImGui::EndChild();	
		}

		if (this->AgvPositionGraphic->Visibility)
			{
			ImGui::SameLine();

			ImGui::BeginChild("Agv Position Page", ImVec2(1000, 600), true);

			this->AgvPositionGraphic->Visibility = true;
			this->AgvPositionPage();
			ImGui::EndChild();
			}
![image](https://user-images.githubusercontent.com/65457096/227555571-b60b1d41-b0db-45ef-bfc5-cda28df9d6c4.png)

Bu şekilde normalde alt alta geliyordu açılan grafikler bu şekilde güncelledim

Bugünkü kazanımlarım
-  ImGui::BeginChild("Wheel Angle Page", ImVec2(1000, 600), true);   yapısını öğrendim














 














 	







 





