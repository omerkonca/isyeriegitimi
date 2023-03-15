#include "data_for_graphic.h"   //data_for_graphic deki veriler için çagýrýyoruz 
using namespace std;


ROTracer::ROTracer() {
	this->Agv = new AgvData();
	this->Net = new NetData();

	this->SGD = new SpeedGraphicData();

	_loginPageVisibility = true;
}

ROTracer::~ROTracer() {
	delete this->Agv;
	delete this->Net;

}

void ROTracer::StartStreamParser() {
	if (!_isRunning)
	{
		this->_zmqLoopFlag = true;
		std::thread lth(&ROTracer::ZMQDataStreamParser, this);
		lth.detach();
	}
}

void ROTracer::StopStreamParser() {
	this->_zmqLoopFlag = false;
}

//--------------------------------grafik çizme alaný---------------------------------------------------------------

void ROTracer::SpeedPage() {
	_zmqLoopFlag = true;
	if (this->_speedPageVisibility == true) {

		if (this->Agv == NULL) {
			return;
		}

		ImGui::BulletText("Move your speed to change the data!");

		ImGui::Checkbox("Pause", &isPause);     // duraklatma seçenegi 

		if (!isPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		{
			this->SGD->History = 20.0f;
			this->SGD->Time += ImGui::GetIO().DeltaTime;

			this->SGD->ReadingSpeed.AddPoint(this->SGD->Time, this->Agv->RSpeed);
			this->SGD->WritingSpeed.AddPoint(this->SGD->Time, this->Agv->WSpeed);

		}
		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
			this->SGD->Time;



		ImGui::SliderFloat("History", &this->SGD->History, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->Time - this->SGD->History, this->SGD->Time, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("rs X", &this->SGD->ReadingSpeed.Data[0].x, &this->SGD->ReadingSpeed.Data[0].y, this->SGD->ReadingSpeed.Data.size(), 0, this->SGD->ReadingSpeed.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("ws Y", &this->SGD->WritingSpeed.Data[0].x, &this->SGD->WritingSpeed.Data[0].y, this->SGD->WritingSpeed.Data.size(), 0, this->SGD->WritingSpeed.Offset, 2 * sizeof(float));
			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}
}

void ROTracer::WheelPage() {
	_zmqLoopFlag = true;
	if (this->_wheelPageVisibility == true) {

		if (this->Agv == NULL) {
			return;
		}

		ImGui::BulletText("Move your whell to change the data!");

		ImGui::Checkbox("Pause", &isPause);     // duraklatma seçenegi 

		if (!isPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		{
			this->SGD->History = 20.0f;
			this->SGD->Time += ImGui::GetIO().DeltaTime;

			this->SGD->ReadingAngel.AddPoint(this->SGD->Time, this->Agv->RAngle);
			this->SGD->WritingAngel.AddPoint(this->SGD->Time, this->Agv->WAngle);

		}
		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
		{
			this->SGD->Time;
		}


		ImGui::SliderFloat("History", &this->SGD->History, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("WHEEL ANGLES", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->Time - this->SGD->History, this->SGD->Time, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("READ WHEEL ANGLE ", &this->SGD->ReadingAngel.Data[0].x, &this->SGD->ReadingAngel.Data[0].y, this->SGD->ReadingAngel.Data.size(), 0, this->SGD->ReadingAngel.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("WRITE WHEEL ANGLE", &this->SGD->WritingAngel.Data[0].x, &this->SGD->WritingAngel.Data[0].y, this->SGD->WritingAngel.Data.size(), 0, this->SGD->WritingAngel.Offset, 2 * sizeof(float));
			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}

}

void ROTracer::AngelPage() {
	_zmqLoopFlag = true;
	if (this->_anglePageVisibility == true) {

		if (this->Agv == NULL) {
			return;
		}

		ImGui::BulletText("Move your Angel to change the data!");

		ImGui::Checkbox("Pause", &isPause);     // duraklatma seçenegi 

		if (!isPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		{
			this->SGD->History = 20.0f;
			this->SGD->Time += ImGui::GetIO().DeltaTime;

			this->SGD->totalAngel.AddPoint(this->SGD->Time, this->Agv->Angle);
		}
		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
			this->SGD->Time;



		ImGui::SliderFloat("History", &this->SGD->History, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("ANGLE", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->Time - this->SGD->History, this->SGD->Time, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("TOTAL ANGLE ", &this->SGD->totalAngel.Data[0].x, &this->SGD->totalAngel.Data[0].y, this->SGD->totalAngel.Data.size(), 0, this->SGD->totalAngel.Offset, 2 * sizeof(float));

			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}

}

void ROTracer::PositionPage() {


}



void ROTracer::Ping() {
	_zmqLoopFlag = true;
	if (this->_PingPageVisibility == true) {

		if (this->Net == NULL) {
			return;
		}

		ImGui::BulletText("Move your speed to change the data!");

		ImGui::Checkbox("Pause", &isPause);     // duraklatma seçenegi 

		if (!isPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		{
			this->SGD->History = 20.0f;
			this->SGD->Time += ImGui::GetIO().DeltaTime;

			this->SGD->ping.AddPoint(this->SGD->Time, this->Net->Ping);
			

		}
		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
			this->SGD->Time;



		ImGui::SliderFloat("History", &this->SGD->History, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(400, 150))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->Time - this->SGD->History, this->SGD->Time, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("rs X", &this->SGD->ping.Data[0].x, &this->SGD->ping.Data[0].y, this->SGD->ping.Data.size(), 0, this->SGD->ping.Offset, 2 * sizeof(float));
			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}
}

void ROTracer::ReceivedRate() {
	_zmqLoopFlag = true;
	if (this->_ReceivedRatePageVisibility == true) {

		if (this->Net == NULL) {
			return;
		}

		ImGui::BulletText("Move your speed to change the data!");

		ImGui::Checkbox("Pause", &isPause);     // duraklatma seçenegi 

		if (!isPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		{
			this->SGD->History = 20.0f;
			this->SGD->Time += ImGui::GetIO().DeltaTime;

			this->SGD->receivedrate.AddPoint(this->SGD->Time, this->Net->ReceivedRate);


		}
		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
			this->SGD->Time;



		ImGui::SliderFloat("History", &this->SGD->History, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(400, 150))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->Time - this->SGD->History, this->SGD->Time, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("rs X", &this->SGD->receivedrate.Data[0].x, &this->SGD->receivedrate.Data[0].y, this->SGD->receivedrate.Data.size(), 0, this->SGD->receivedrate.Offset, 2 * sizeof(float));
			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}

}

void ROTracer::Signal() {

	_zmqLoopFlag = true;
	if (this->_SignalPageVisibility == true) {

		if (this->Net == NULL) {
			return;
		}

		ImGui::BulletText("Move your speed to change the data!");

		ImGui::Checkbox("Pause", &isPause);     // duraklatma seçenegi 

		if (!isPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		{
			this->SGD->History = 20.0f;
			this->SGD->Time += ImGui::GetIO().DeltaTime;

			this->SGD->signal.AddPoint(this->SGD->Time, this->Net->Signal);


		}
		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
			this->SGD->Time;



		ImGui::SliderFloat("History", &this->SGD->History, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(400, 150))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->Time - this->SGD->History, this->SGD->Time, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("rs X", &this->SGD->signal.Data[0].x, &this->SGD->signal.Data[0].y, this->SGD->signal.Data.size(), 0, this->SGD->signal.Offset, 2 * sizeof(float));
			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}
}

void ROTracer::wifiSpeed() {


}





//--------------------------------giriþ sayfasý--------------------------------------------------------------------

void ROTracer::LoginPage() {
	//_zmqLoopFlag = false;
	if (this->_loginPageVisibility == true)
	{
		ImGui::SetNextWindowSize(ImVec2(920, 520));

		// GÝRÝÞ SAYFA
		if (page1 == true)
		{
			ImGui::Begin("PAGE", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);  //, &no_collapse
			ImGui::StyleColorsDark();
			ImGuiStyle& style = ImGui::GetStyle();
			ImVec4* colors = style.Colors;
			style.WindowRounding = 0.9f; // Pencere köþelerinin yuvarlanma miktarý
			colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.95f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
			colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
			ImGui::Text(" ");
			ImGui::Text(" ");
			ImGui::Text(" ");
			ImGui::Text(" ");
			ImGui::Text(" ");
			// Pencere baþlýðý ve IP adresi giriþ kutusu
			ImGui::Text("                                                       Enter IP Address");
			ImGui::Spacing();

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(" ", NULL, true).x) / (1, 5));
			ImGui::InputText(" ", IpAddress, 32, ImGuiInputTextFlags_CharsNoBlank);

			ImGui::Spacing();

			// IP adresi giriþi ve "Login" düðmesi
			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Login", NULL, true).x) / 2);

			// IP adresi giriþi ve "Login" düðmesi
			if (ImGui::Button("Login")) {
				// IP adresi doðrulama
				std::regex ip_regex("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
				if (!std::regex_match(IpAddress, ip_regex)) {
					ImGui::OpenPopup("Uyari");
				}
				else {
					// Login düðmesine týklandýðýnda, saklanan IP adresi ile diðer sayfaya geçme
					std::cout << "Entered IP Address:" << IpAddress << std::endl;
					ImGui::OpenPopup("New Page");
					page1 = false;
					this->_loginPageVisibility = false;
					this->StartStreamParser();

				}
			}


			// IP adresi uyarý mesajý
			if (ImGui::BeginPopupModal("Uyari", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
				ImGui::Text("Please enter a valid IP address.");
				if (ImGui::Button("Ok")) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			ImGui::End();
		}

	}
	
	// Yeni acýlacak grafiklerin sayfasý penceresi 
	if (!this->_loginPageVisibility) {
		
		if (!page1) {
			ImGui::Begin("New Page");
			ImGui::SetNextWindowSize(ImVec2(920, 520));
			// Yeni sayfa içeriði ve IP adresi bilgisi
		   //--------------------------------------------------
			if (ImGui::CollapsingHeader("NET",2))
			{
				static ImPlotSubplotFlags flags = ImPlotSubplotFlags_None;
				static int rows = 3;
				static int cols = 3;
				ImGui::SliderInt("Rows", &rows, 1, 5);
				ImGui::SliderInt("Cols", &cols, 1, 5);
				if (ImPlot::BeginSubplots("split", rows, cols, ImVec2(-1, 400), flags))
				{
					ImGui::TableNextColumn();
					ImGui::Text("DeviceMacAddress: ");
					ImGui::TableNextColumn();
					ImGui::Text("SSID: ");
					ImGui::TableNextColumn();
					ImGui::Text("Status: ");

					ImGui::TableNextColumn();
					_PingPageVisibility = true;
					this->Ping();

					ImGui::TableNextColumn();
				_ReceivedRatePageVisibility = true;
				this->ReceivedRate();

				ImGui::TableNextColumn();
				_SignalPageVisibility = true;
				this->Signal();

				/*_wifiSpeedPageVisibility = true;
				this->wifiSpeed();*/

				ImPlot::EndSubplots();
				
				
				
			}
				
			}
			if (ImGui::CollapsingHeader("AGV"))
			{
				if (ImGui::BeginTable("split",2))
				{
					ImGui::TableNextColumn(); ImGui::Checkbox("Position", &position);
					ImGui::TableNextColumn(); ImGui::Checkbox("Angle", &angle);
					ImGui::TableNextColumn(); ImGui::Checkbox("Speed", &speed);
					ImGui::TableNextColumn(); ImGui::Checkbox("Wheel", &wheel);

					// pozisyon grafiði 
					if (position == true)//position checkbox ýna týklanýnca
					{
						ImGui::Begin("Position Chart");
						_positionPageVisibility = true;
						this->PositionPage();

						// x ve y kordinatý alýnnan grafik  ücgen ve daireli 
						ImGui::End();
					}

					// açý grafiði
					if (angle == true) //angle checkbox ýna týklanýnca
					{

						ImGui::Begin("Angle Chart");
						_anglePageVisibility = true;
						this->AngelPage();
						ImGui::End();

					}

					// hýz grafiði
					if (speed == true)//speed checkbox ýna týklanýnca
					{
						ImGui::Begin("Speed Chart");
						_speedPageVisibility = true;
						this->SpeedPage();
						ImGui::End();
					}

					// tekerlek açý grafiði
					if (wheel == true)//wheel checkbox ýna týklanýnca
					{
						ImGui::Begin("Wheel Chart");
						_wheelPageVisibility = true;
						this->WheelPage();
						ImGui::End();

					}
					ImGui::EndTable();
				}
			}
			ImGui::End();

		}
	}

}
//-------------------------------DATA  PARSER BLOCK----------------------------------------------------------

void ROTracer::ZMQDataStreamParser()
{

	void* context = zmq_ctx_new();
	void* subscriber = zmq_socket(context, ZMQ_SUB);
	std::string take_ip = this->IpAddress;
	std::string  a = "tcp://" + take_ip + ":5556";
	//std::string b = ("tcp://%s:%d", take_ip,take_port);    // opsiyonel kullaným 

	int rc = zmq_connect(subscriber, a.c_str());  //"tcp://192.168.2.125:5556"
	rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);

	const int topic_size = 5;
	const int msg_size = 128;

	char topic[topic_size] = { 0 };
	char msg[msg_size] = { 0 };
	std::string new_msg(msg);
	size_t sayac = 0;
	char* pch;
	_isRunning = true;

	printf("start");

	while (this->_zmqLoopFlag)
	{
		rc = zmq_recv(subscriber, topic, topic_size, 0);
		if (rc != -1)
			fprintf(stdout, "TOPIC: %s \n", topic);

		rc = zmq_recv(subscriber, msg, msg_size, 0);
		if (rc != -1) {
			if (topic == "real")         //gelen veri tipine göre parse iþlemi yapacak 
			{
				if (std::strcmp("real", topic) == 0) {
					pch = strtok(msg, ";");
					while (pch != NULL)
					{
						if (sayac == 0) {
							Agv->X = stoi(pch);
							sayac++;

						}
						else if (sayac == 1) {
							Agv->Y = stoi(pch);
							sayac++;

						}
						else if (sayac == 2) {
							Agv->Angle = std::stof(pch);
							sayac++;

						}
						else if (sayac == 3) {
							Agv->WSpeed = stoi(pch);
							sayac++;

						}
						else if (sayac == 4) {
							Agv->RSpeed = stoi(pch);
							sayac++;

						}
						else if (sayac == 5) {
							Agv->WAngle = std::stof(pch);
							sayac++;

						}
						else if (sayac == 6) {
							Agv->RAngle = std::stof(pch);
							sayac++;

						}

						//printf("%s\n", pch);
						pch = strtok(NULL, ";");
					}
					sayac = 0;
				}
				//printf("-----------------------");
				//fprintf(stdout, "MSG: %s \n", msg);
			}
			else {
				if (std::strcmp("net", topic) == 0) {
					pch = strtok(msg, ";");
					while (pch != NULL)
					{
						if (sayac == 0) {
							Net->DeviceMacAddress = std::string(msg);
							sayac++;

						}
						else if (sayac == 1) {
							Net->Ping = stoi(pch);
							sayac++;

						}
						else if (sayac == 2) {
							Net->ReceivedRate = stoi(pch);
							sayac++;

						}
						else if (sayac == 3) {
							Net->Signal = stoi(pch);
							sayac++;

						}
						else if (sayac == 4) {
							Net->Speed = stoi(pch);
							sayac++;

						}
						else if (sayac == 5) {
							Net->SSID = std::string(msg);;
							sayac++;

						}
						else if (sayac == 6) {
							Net->Status = std::string(msg);
							sayac++;
						}
						else if (sayac == 7) {
							Net->TransmitededRate = stoi(pch);
							sayac++;

						}

						//	printf("%s\n", pch);
						pch = strtok(NULL, ";");
					}
					sayac = 0;
				}
				//printf("-----------------------");
				//fprintf(stdout, "MSG: %s \n", msg);

			}
		}
	}
	zmq_close(subscriber);
	zmq_ctx_destroy(context);

	_isRunning = false;

}