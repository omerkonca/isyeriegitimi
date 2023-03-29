#include "data_for_graphic.h"   //data_for_graphic deki veriler için çagırıyoruz 
using namespace std;


ROTracer::ROTracer() {
	this->Agv = new AgvData();
	this->Net = new NetData();

	this->SpeedGraphic = new SpeedGraphicData();
	this->WheelGraphic = new WheelGraphicData();
	this->AgvAngleGraphic = new AgvAngleGraphicData();

	this->AgvPositionGraphic = new AgvPositionGraphicData();

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




/*
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
{
	return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}


static inline ImVec2 ImRotate(const ImVec2& v, float cos_a, float sin_a)
{
	return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a);
}*/
static ImPlotPoint point1, point2;
static bool drawLine = false;

void ROTracer::LoginPage() {


	if (this->_loginPageVisibility == true)
	{
		ImGui::SetNextWindowSize(ImVec2(920, 300));

		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_::ImGuiCond_Always, ImVec2(0.5f, 0.5f));

		ImGui::Begin("PAGE", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);  //, &no_collapse
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;
		style.WindowRounding = 0.9f; // Pencere köşelerinin yuvarlanma miktarı
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
		// Pencere başlığı ve IP adresi giriş kutusu
		ImGui::SetCursorPosX(300);
		ImGui::Text("Enter IP Address");
		ImGui::SameLine();
		ImGui::SetCursorPosX(510);
		ImGui::Text("Port Address");
		ImGui::Spacing();

		ImGui::SetCursorPosX(300);
		ImGui::PushItemWidth(200);
		ImGui::InputText("##Ip", IpAddress, 24, ImGuiInputTextFlags_CharsNoBlank);
		ImGui::SameLine();


		ImGui::PushItemWidth(100);
		ImGui::InputText("##Port", PortAddress, 8, ImGuiInputTextFlags_CharsNoBlank);
		ImGui::Spacing();
		ImGui::Spacing();

		// IP adresi girişi ve "Login" düğmesi
		ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Login", NULL, true).x) / 2);

		// IP adresi girişi ve "Login" düğmesi
		if (ImGui::Button("Login")) {
			// IP adresi doğrulama
			std::regex ip_regex("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
			if (!std::regex_match(IpAddress, ip_regex)) {
				ImGui::OpenPopup("Uyari");
			}
			else {

				this->_loginPageVisibility = false;
				this->StartStreamParser();
			}
		}

		// IP adresi uyarı mesajı
		if (ImGui::BeginPopupModal("Uyari", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
			ImGui::Text("Please enter a valid IP address.");
			if (ImGui::Button("Ok")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::End();


	}
	else {

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

		if (this->SpeedGraphic->Visibility)
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

		// END MENU

		//// Arrange the visibility flags in a vector for easier manipulation
		//std::vector<bool*> visibilityFlags = { &this->WheelGraphic->Visibility, &this->SpeedGraphic->Visibility,
		//									   &this->AgvAngleGraphic->Visibility, &this->AgvPositionGraphic->Visibility };

		//// Calculate the number of columns
		//const int columns = 3;
		//int visibleItemCount = 0;
		//for (const bool* flag : visibilityFlags) {
		//	if (*flag) visibleItemCount++;
		//}
		//const int rows = std::max(1, (visibleItemCount + columns - 1) / columns);

		//// Calculate the item width and height
		//const float itemWidth = ImGui::GetWindowWidth() / columns;
		//const float itemHeight = 30;
		//bool visibilityFlagNames[] = {};
		//// Draw the visible items
		//int itemIndex = 0;
		//for (int row = 0; row < rows; row++) {
		//	ImGui::Columns(columns, nullptr, false);
		//	for (int col = 0; col < columns; col++) {
		//		if (itemIndex >= visibilityFlags.size()) break;
		//		if (*visibilityFlags[itemIndex]) {
		//			ImGui::SetColumnWidth(col, itemWidth);
		//			ImGui::SetCursorPosX(col * itemWidth);
		//			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemHeight * row);
		//			if (itemIndex == visibleItemCount - 1 && rows > 1) {
		//				ImGui::SetNextWindowContentSize(ImVec2(itemWidth, itemHeight));
		//				ImGui::SetNextWindowPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + itemHeight));
		//			}
		//			if (itemIndex == 0) ImGui::BeginChild("##child", ImVec2(0, 0), false);
		//			ImGui::Text("%s", visibilityFlagNames[itemIndex].c_str());
		//			if (itemIndex == visibilityFlags.size() - 1) ImGui::EndChild();
		//			itemIndex++;
		//		}
		//	}
		//	ImGui::Columns(1);
		//}
		// END MENU

		//if (ImGui::CollapsingHeader("NET"))
		//{
		//	ImGui::TableNextColumn();
		//	ImGui::Text("DeviceMacAddress: %s", this->Net->DeviceMacAddress.c_str());

		//	ImGui::TableNextColumn();
		//	ImGui::Text("SSID: %s", this->Net->SSID.c_str());
		//	ImGui::TableNextColumn();
		//	ImGui::Text("Status: %s", this->Net->Status.c_str());

		//	// İlk iki grafiği yan yana sırala
		//	ImGui::BeginChild("Ping", ImVec2(600, 400), true);

		//	this->SignalPingSpeedPage();
		//	ImGui::EndChild();
		//}


		//ImGui::SetNextWindowSize(ImVec2(920, 520));


		/*if (this->SpeedGraphic->Visibility) {
			this->SpeedPage();
		}

		if (this->WheelGraphic->Visibility) {
			this->WheelPage();
		}

		if (this->AgvAngleGraphic->Visibility) {
			this->AgvAngelPage();
		}

		if (this->AgvPositionGraphic->Visibility) {
			this->AgvPositionPage();
		} */

	}

}


//şimdi ben ekranın boyutunu parametre olarak almak istiyorum ve ben açtığım menü item leri ekrana sığdırmak istiyorum mesela 3 tane açtıysam ona göre sığsın yada 5 tane açtıysam ona göre sığsın dinamik bir şekilde

void ROTracer::ZMQDataStreamParser()
{
	void* context = zmq_ctx_new();
	void* subscriber = zmq_socket(context, ZMQ_SUB);

	char ip[100];
	sprintf(ip, "tcp://%s:%s", this->IpAddress, this->PortAddress);

	int rc = zmq_connect(subscriber, ip);  //"tcp://192.168.2.125:5556"
	rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);

	size_t index = 0;
	char* pch;
	_isRunning = true;
	rapidjson::Document doc;
	rapidjson::Value::ConstValueIterator itr;

	while (this->_zmqLoopFlag)
	{
		zmq_msg_t zmq_topic;
		zmq_msg_t zmq_message;



		zmq_msg_init(&zmq_topic);
		rc = zmq_msg_recv(&zmq_topic, subscriber, 0);

		zmq_msg_init(&zmq_message);
		rc = zmq_msg_recv(&zmq_message, subscriber, 0);

		int zmq_topic_size = zmq_msg_size(&zmq_topic);
		int zmq_message_size = zmq_msg_size(&zmq_message);

		char* zmq_topic_data = (char*)malloc(zmq_topic_size + 1);
		memcpy(zmq_topic_data, zmq_msg_data(&zmq_topic), zmq_topic_size);
		zmq_msg_close(&zmq_topic);
		zmq_topic_data[zmq_topic_size] = 0;

		char* zmq_message_data = (char*)malloc(zmq_message_size + 1);
		memcpy(zmq_message_data, zmq_msg_data(&zmq_message), zmq_message_size);
		zmq_msg_close(&zmq_message);
		zmq_message_data[zmq_message_size] = 0;

		if (rc != -1) {
			fprintf(stdout, "TOPIC: %s \n", zmq_topic_data);
			fprintf(stdout, "MSG: %s \n", zmq_message_data);
		}

		if (rc != -1) {
			index = 0;
			if (std::strcmp("real", zmq_topic_data) == 0) {
				pch = strtok(zmq_message_data, ";");
				while (pch != NULL)
				{
					if (index == 0) {
						Agv->Fx = stoi(pch);
					}
					else if (index == 1) {
						Agv->Fy = stoi(pch);
					}
					else if (index == 2) {
						Agv->Bx = stoi(pch);
					}
					else if (index == 3) {
						Agv->By = stoi(pch);
					}
					else if (index == 4) {
						Agv->Angle = std::stof(pch);
					}
					else if (index == 5) {
						Agv->WSpeed = stoi(pch);
					}
					else if (index == 6) {
						Agv->RSpeed = stoi(pch);
					}
					else if (index == 7) {
						Agv->WAngle = std::stof(pch);
					}
					else if (index == 8) {
						Agv->RAngle = std::stof(pch);
					}

					index++;
					pch = strtok(NULL, ";");
				}


				if (this->SpeedGraphic->Enabled == true)
				{
					this->SpeedGraphic->Time += ImGui::GetIO().DeltaTime;
					this->SpeedGraphic->ReadingSpeed.AddPoint(this->SpeedGraphic->Time, this->Agv->RSpeed);
					this->SpeedGraphic->WritingSpeed.AddPoint(this->SpeedGraphic->Time, this->Agv->WSpeed);
				}

				if (this->WheelGraphic->Enabled == true)
				{
					this->WheelGraphic->Time += ImGui::GetIO().DeltaTime;
					this->WheelGraphic->ReadingWheelAngel.AddPoint(this->WheelGraphic->Time, this->Agv->RAngle);
					this->WheelGraphic->WritingWheelAngel.AddPoint(this->WheelGraphic->Time, this->Agv->WAngle);
				}

				if (this->AgvAngleGraphic->Enabled == true)
				{
					this->AgvAngleGraphic->Time += ImGui::GetIO().DeltaTime;
					this->AgvAngleGraphic->AgvAngle.AddPoint(this->AgvAngleGraphic->Time, this->Agv->Angle);
				}

				if (this->AgvPositionGraphic->Enabled == true)
				{
					this->AgvPositionGraphic->Time += ImGui::GetIO().DeltaTime;
					this->AgvPositionGraphic->AgvFrontPosition.AddPoint(Agv->Fx, Agv->Fy);
					this->AgvPositionGraphic->AgvBackPosition.AddPoint(Agv->Bx, Agv->By);
					this->AgvPositionGraphic->AgvAngle = Agv->Angle;
				}

			}
			else if (std::strcmp("net", zmq_topic_data) == 0) {
				pch = strtok(zmq_message_data, ";");
				while (pch != NULL)
				{
					if (index == 0) {
						Net->DeviceMacAddress = std::string(pch);
					}
					else if (index == 1) {
						Net->Ping = stoi(pch);
					}
					else if (index == 2) {
						Net->ReceivedRate = stoi(pch);
					}
					else if (index == 3) {
						Net->Signal = stoi(pch);
					}
					else if (index == 4) {
						Net->Speed = stoi(pch);
					}
					else if (index == 5) {
						Net->SSID = std::string(pch);;
					}
					else if (index == 6) {
						Net->Status = std::string(pch);
					}
					else if (index == 7) {
						Net->TransmitededRate = stoi(pch);
					}

					//	printf("%s\n", pch);
					pch = strtok(NULL, ";");
				}
			}
			else if (std::strcmp("route", zmq_topic_data) == 0)
			{
				doc.Parse(zmq_message_data);

				if (doc.HasParseError()) {
					continue;
				}

				this->AgvPositionGraphic->Erase();

				for (itr = doc.Begin(); itr != doc.End(); ++itr)
				{
					this->AgvPositionGraphic->Route.AddPoint(itr->GetObject()["X"].GetFloat(), itr->GetObject()["Y"].GetFloat());
				}
			}
			else if (std::strcmp("sim", zmq_topic_data) == 0) {

				doc.Parse(zmq_message_data);

				if (doc.HasParseError()) {
					continue;
				}

				for (itr = doc.Begin(); itr != doc.End(); ++itr)
				{
					this->AgvPositionGraphic->Simu.AddPoint(itr->GetObject()["X"].GetFloat(), itr->GetObject()["Y"].GetFloat());
				}
			}
			else if (std::strcmp("curve", zmq_topic_data) == 0) {

				doc.Parse(zmq_message_data);

				if (doc.HasParseError()) {
					continue;
				}

				for (itr = doc.Begin(); itr != doc.End(); ++itr)
				{
					this->AgvPositionGraphic->Curve.AddPoint(itr->GetObject()["X"].GetFloat(), itr->GetObject()["Y"].GetFloat());
				}
			}
			else if (std::strcmp("cell", zmq_topic_data) == 0) {

				doc.Parse(zmq_message_data);

				if (doc.HasParseError()) {
					continue;
				}

				this->Agv->CellLx = doc[0].GetObject()["X"].GetFloat();
				this->Agv->CellLy = doc[0].GetObject()["Y"].GetFloat();

				this->Agv->CellSx = doc[1].GetObject()["X"].GetFloat();
				this->Agv->CellSy = doc[1].GetObject()["Y"].GetFloat();

			}

		}


		//  serbest bırakma 
		free(zmq_topic_data);
		free(zmq_message_data);
	}

	zmq_close(subscriber);
	zmq_ctx_destroy(context);

	_isRunning = false;

}
//ben bezier eğrisi çizmek istiyorum fareyle bir noktadan bir noktaya çektiğim eğrinin uzunluğunu hesaplamak istiyorum nasıl yaparım
//void Demo_DragBezier() {
//	static ImVec2 point1, point2, point3; // İki kontrol noktası ve bitiş noktası
//
//	if (ImGui::IsMouseClicked(0)) {
//		point1 = point2 = point3 = ImGui::GetMousePos();
//	}
//
//	if (ImGui::IsMouseDragging(0)) {
//		point2 = ImGui::GetMousePos();
//	}
//
//	if (ImGui::IsMouseReleased(0)) {
//		point3 = ImGui::GetMousePos();
//		ImPlot::GetPlotDrawList()->AddBezierCurve(
//			ImPlot::PlotToPixels(point1),
//			ImPlot::PlotToPixels(point2),
//			ImPlot::PlotToPixels(point3),
//			ImVec2(0, 0), // kontrol noktası çizmek için bu değerlere sıfır veriyoruz
//			IM_COL32(255, 0, 0, 255),
//			2.0f // çizgi kalınlığı
//		);
//	}
//}


void ROTracer::SpeedPage() {

	ImGui::SetNextWindowSize(ImVec2(920, 520));

	/*ImGui::Begin("Agv Speed Graphic",&this->SpeedGraphic->Visibility);*/

	if (this->Agv == NULL) {
		return;
	}

	ImGui::Checkbox("Enabled", &this->SpeedGraphic->Enabled);
	ImGui::SameLine();
	ImGui::SliderFloat("History", &this->SpeedGraphic->History, 1, 30, "%.1f s");  // .1f yaparsak milisaniye olarak ayarlanıyor 

	static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

	if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, -1))) {     // grafik ölçeklendirme 
		ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

		ImPlot::SetupAxisLimits(ImAxis_X1, this->SpeedGraphic->Time - this->SpeedGraphic->History, this->SpeedGraphic->Time, ImGuiCond_Always);
		ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 2000);

		if (this->SpeedGraphic->ReadingSpeed.Data.Size > 0) {
			ImPlot::PlotLine("Reading Speed", &this->SpeedGraphic->ReadingSpeed.Data[0].x, &this->SpeedGraphic->ReadingSpeed.Data[0].y, this->SpeedGraphic->ReadingSpeed.Data.size(), 0, this->SpeedGraphic->ReadingSpeed.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("Writing Speed", &this->SpeedGraphic->WritingSpeed.Data[0].x, &this->SpeedGraphic->WritingSpeed.Data[0].y, this->SpeedGraphic->WritingSpeed.Data.size(), 0, this->SpeedGraphic->WritingSpeed.Offset, 2 * sizeof(float));
		}

		ImPlot::EndPlot();
	}

	//ImGui::End();
}

void ROTracer::WheelPage() {

	ImGui::SetNextWindowSize(ImVec2(920, 520));
	//ImGui::Begin("Agv Wheel Graphic", &this->WheelGraphic->Visibility);


	if (this->Agv == NULL) {
		return;
	}

	ImGui::Checkbox("Enabled", &this->WheelGraphic->Enabled);
	ImGui::SameLine();
	ImGui::SliderFloat("History", &this->WheelGraphic->History, 1, 30, "%.1f s");  // .1f yaparsak milisaniye olarak ayarlanıyor 

	static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

	if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, -1))) {     // grafik ölçeklendirme 
		ImPlot::SetupAxes("Time [s]", "Wheel Angle [deg]");

		ImPlot::SetupAxisLimits(ImAxis_X1, this->WheelGraphic->Time - this->WheelGraphic->History, this->WheelGraphic->Time, ImGuiCond_Always);
		ImPlot::SetupAxisLimits(ImAxis_Y1, -100, 100);

		if (this->WheelGraphic->ReadingWheelAngel.Data.Size > 0) {
			ImPlot::PlotLine("Reading Wheel", &this->WheelGraphic->ReadingWheelAngel.Data[0].x, &this->WheelGraphic->ReadingWheelAngel.Data[0].y, this->WheelGraphic->ReadingWheelAngel.Data.size(), 0, this->WheelGraphic->ReadingWheelAngel.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("Writing Wheel", &this->WheelGraphic->WritingWheelAngel.Data[0].x, &this->WheelGraphic->WritingWheelAngel.Data[0].y, this->WheelGraphic->WritingWheelAngel.Data.size(), 0, this->WheelGraphic->WritingWheelAngel.Offset, 2 * sizeof(float));
		}

		ImPlot::EndPlot();
	}

	//ImGui::End();
}


void ROTracer::AgvAngelPage() {

	ImGui::SetNextWindowSize(ImVec2(920, 520));
	//ImGui::Begin("Agv Angle Graphic", &this->AgvAngleGraphic->Visibility);

	if (this->Agv == NULL) {
		return;
	}

	ImGui::Checkbox("Enabled", &this->AgvAngleGraphic->Enabled);
	ImGui::SameLine();
	ImGui::SliderFloat("History", &this->AgvAngleGraphic->History, 1, 30, "%.1f s");

	static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

	if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, -1))) {
		ImPlot::SetupAxes("Time [s]", "Angle [deg]");

		ImPlot::SetupAxisLimits(ImAxis_X1, this->AgvAngleGraphic->Time - this->AgvAngleGraphic->History, this->AgvAngleGraphic->Time, ImGuiCond_Always);
		ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 359);

		if (this->WheelGraphic->ReadingWheelAngel.Data.Size > 0) {
			ImPlot::PlotLine("Agv Angle", &this->AgvAngleGraphic->AgvAngle.Data[0].x, &this->AgvAngleGraphic->AgvAngle.Data[0].y, this->AgvAngleGraphic->AgvAngle.Data.size(), 0, this->AgvAngleGraphic->AgvAngle.Offset, 2 * sizeof(float));
		}

		ImPlot::EndPlot();
	}

	//ImGui::End();
}
void ROTracer::AgvPositionPage() {

	ImGui::SetNextWindowSize(ImVec2(920, 520));
	//ImGui::Begin("Agv Position Graphic", &this->AgvPositionGraphic->Visibility);
	if (this->Agv == NULL) {
		return;
	}
	/*float dx = point1.x - point2.x;
	float dy = point1.y - point2.y;
	float distance = sqrt(dx * dx + dy * dy);*/

	//float distance = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
	double dx = point2.x - point1.x;
	double dy = point2.y - point1.y;
	double distance = sqrt(dx * dx + dy * dy);
	/*Demo_DragBezier();*/
	//ImGui::Text("Uzunluk: %.2f", distance);
	ImGui::InputFloat2("Mouse", new float[2] {(float)point1.x, (float)point1.y});
	ImGui::InputFloat("Length ", new float[1] {(float)distance});
	ImGui::Checkbox("Draw Line", &drawLine);

	static int cnt = 0;

	if (ImPlot::BeginPlot("Scatter Plot", ImVec2(-1, -1), ImPlotFlags_Equal)) {
		if (drawLine && ImGui::IsMouseClicked(0) && ImGui::GetIO().KeyCtrl)
		{
			if (cnt==0)
			{
				point1 = ImPlot::GetPlotMousePos();
				cnt = 1;
			}
			else if(cnt==1)
			{
				point2 = ImPlot::GetPlotMousePos();
				cnt = 2;
				
				//point2 = ImVec2(0.0f, 0.0f);
			}
			
		}
		else if(drawLine==false)
		{
			point1 = ImVec2(0.0f, 0.0f);
			point2 = ImVec2(0.0f, 0.0f);
			cnt = 0;
		}

		if (cnt == 2) {

			ImPlot::GetPlotDrawList()->AddLine(
				ImPlot::PlotToPixels(ImPlotPoint(point1)),
				ImPlot::PlotToPixels(ImPlotPoint(point2)),
				IM_COL32(255, 0, 0, 255)
			);

		}

		//ImPlot::SetupAxisLimits(ImAxis_X1, this->Agv->X - 500, this->Agv->X + 1000, ImGuiCond_Always);
		//ImPlot::SetupAxisLimits(ImAxis_Y1, this->Agv->Y - 500, this->Agv->Y + 1000, ImGuiCond_Always);

		//ImPlot::SetupAxesLimits(10000, 30000, 30000, 80000);

		if (this->AgvPositionGraphic->AgvFrontPosition.Data.size() > 0) {

			ImPlot::PlotScatter("AgvFPosition",
				&this->AgvPositionGraphic->AgvFrontPosition.Data[0].x,
				&this->AgvPositionGraphic->AgvFrontPosition.Data[0].y,
				this->AgvPositionGraphic->AgvFrontPosition.Data.size(), 0, 0, 2 * sizeof(int));

			ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
			ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4, ImPlot::GetColormapColor(5), IMPLOT_AUTO, ImPlot::GetColormapColor(5));
			ImPlot::PlotScatter("AgvBPosition",
				&this->AgvPositionGraphic->AgvBackPosition.Data[0].x,
				&this->AgvPositionGraphic->AgvBackPosition.Data[0].y,
				this->AgvPositionGraphic->AgvBackPosition.Data.size(), 0, 0, 2 * sizeof(int));
			ImPlot::PopStyleVar();

			if (this->AgvPositionGraphic->Route.Data.size() > 0) {
				ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
				ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 2, ImPlot::GetColormapColor(2), IMPLOT_AUTO, ImPlot::GetColormapColor(2));
				ImPlot::PlotScatter("AgvRoute",
					&this->AgvPositionGraphic->Route.Data[0].x,
					&this->AgvPositionGraphic->Route.Data[0].y,
					this->AgvPositionGraphic->Route.Data.size(), 0, 0, 2 * sizeof(int));

				ImPlot::PopStyleVar();
			}

			if (this->AgvPositionGraphic->Curve.Data.size() > 0) {
				ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
				ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 2, ImPlot::GetColormapColor(4), IMPLOT_AUTO, ImPlot::GetColormapColor(4));
				ImPlot::PlotScatter("AgvCurve",
					&this->AgvPositionGraphic->Curve.Data[0].x,
					&this->AgvPositionGraphic->Curve.Data[0].y,
					this->AgvPositionGraphic->Curve.Data.size(), 0, 0, 2 * sizeof(int));

				ImPlot::PopStyleVar();
			}

			if (this->AgvPositionGraphic->Simu.Data.size() > 0) {
				ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
				ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 2, ImPlot::GetColormapColor(5), IMPLOT_AUTO, ImPlot::GetColormapColor(5));
				ImPlot::PlotScatter("AgvSim",
					&this->AgvPositionGraphic->Simu.Data[0].x,
					&this->AgvPositionGraphic->Simu.Data[0].y,
					this->AgvPositionGraphic->Simu.Data.size(), 0, 0, 2 * sizeof(int));

				ImPlot::PopStyleVar();
			}

			int lastIndex = this->AgvPositionGraphic->AgvFrontPosition.Data.Size - 1;

			float xRange = ImPlot::GetPlotLimits().X.Max - ImPlot::GetPlotLimits().X.Min;
			float yRange = ImPlot::GetPlotLimits().Y.Max - ImPlot::GetPlotLimits().Y.Min;
			float r = fminf(xRange, yRange) / 50.0f; // r değerini grafik boyutuna göre ölçeklendirin

			float x1 = this->AgvPositionGraphic->AgvFrontPosition.Data[lastIndex].x;
			float y1 = this->AgvPositionGraphic->AgvFrontPosition.Data[lastIndex].y;

			float x_1 = x1 + cos(this->Agv->Angle * PI / 180) * r * 2;
			float y_1 = y1 + sin(this->Agv->Angle * PI / 180) * r * 2;

			float x_2 = x1 + cos(fmod(this->Agv->Angle + 120, 360) * PI / 180) * r;
			float y_2 = y1 + sin(fmod(this->Agv->Angle + 120, 360) * PI / 180) * r;

			float x_3 = x1 + cos(fmod(this->Agv->Angle + 240, 360) * PI / 180) * r;
			float y_3 = y1 + sin(fmod(this->Agv->Angle + 240, 360) * PI / 180) * r;


			ImVec2 p1 = ImPlot::PlotToPixels(ImPlotPoint(x_2, y_2));//sol alt 
			ImVec2 p2 = ImPlot::PlotToPixels(ImPlotPoint(x_3, y_3));// sag alt 
			ImVec2 p3 = ImPlot::PlotToPixels(ImPlotPoint(x_1, y_1));// tepe
			ImPlot::PushPlotClipRect();
			ImPlot::GetPlotDrawList()->AddTriangleFilled(p1, p2, p3, IM_COL32(255, 127, 0, 255));

	
			//if (this->AgvPositionGraphic->Route.Data.size() > 0) {
			/*
			if (ImGui::IsMouseReleased(0)) {
				if (point1.x == 0 && point1.y == 0) {
					point1 = ImPlot::GetPlotMousePos();
				}
				else {
					point2 = ImPlot::GetPlotMousePos();
					float length = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
					ImGui::Text("Uzunluk: %.2f", length);
				}
			}*/

			

			if (drawLine && ImGui::IsMouseClicked(0) && ImGui::GetIO().KeyCtrl)
			{
				if (point1.x == 0.0f && point1.y == 0.0f)
				{
					point1 = ImPlot::GetPlotMousePos();
				}
				else
				{
					point2 = ImPlot::GetPlotMousePos();
					ImPlot::GetPlotDrawList()->AddLine(
						ImPlot::PlotToPixels(ImPlotPoint(point1)),
						ImPlot::PlotToPixels(ImPlotPoint(point2)),
						IM_COL32(255, 0, 0, 255)
					);
					point1 = ImVec2(0.0f, 0.0f);
					//point2 = ImVec2(0.0f, 0.0f);
				}
			}
			
			 //mevcut konum ve tıklanan nokta arasındaki uzaklığı hesapla
			if (ImGui::IsItemHovered()) // Eğer fare imleci üzerindeyse
			{
				ImGui::BeginTooltip();
				ImGui::Text("Length: %f", distance);
				ImGui::EndTooltip();
			}
			//ImGui::Text("Uzunluk: %.2f", distance);

				ImPlot::GetPlotDrawList()->AddLine(ImPlot::PlotToPixels(ImPlotPoint(this->Agv->CellLx, this->Agv->CellLy)), ImPlot::PlotToPixels(ImPlotPoint(this->Agv->CellSx, this->Agv->CellSy)), IM_COL32(255, 127, 0, 255));
				ImPlot::GetPlotDrawList()->AddCircleFilled(ImPlot::PlotToPixels(ImPlotPoint(this->Agv->CellLx, this->Agv->CellLy)), 3, IM_COL32(255, 127, 0, 255));
				//ImPlot::GetPlotDrawList()->AddLine(ImPlot::PlotToPixels(ImPlot::PlotToPixels(point2)), ImPlot::PlotToPixels(point1), IM_COL32(255, 0, 0, 255)); //mouse ile çizgi çizdirme

				//ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, 6.0f, ImVec4(1, 0, 0, 1), 2.0f);
				
			//}

		}
		ImPlot::EndPlot();
	}

	//ImGui::End();
		
}

void ROTracer::ReceivedRatePage() {

	if (false) {

		if (this->Net == NULL) {
			return;
		}

		//ImGui::BulletText("Move your Received Rate to change the data!");

		//ImGui::Checkbox("Pause", &isPauseReceivedRate);     // duraklatma seçenegi 

		//if (!isPauseReceivedRate)      // eger checkbox'a tıklanmazsa (false)  güncel zamanı alıyor  
		//{
		//	this->SGD->HistoryReceivedRate = 20.0f;
		//	this->SGD->TimeReceivedRate += ImGui::GetIO().DeltaTime;

		//	this->SGD->StokingReceivedRate.AddPoint(this->SGD->TimeReceivedRate, this->Net->ReceivedRate);


		//}
		//else     // eger checkbox'a tıklanırsa en son zamanı alıyor 
		//	this->SGD->TimeReceivedRate;

		//ImGui::SliderFloat("History", &this->SGD->HistoryReceivedRate, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanıyor 


		//static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		//if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
		//	ImPlot::SetupAxes("Time [s]", "Received rate  [ ]");

		//	ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->TimeReceivedRate - this->SGD->HistoryReceivedRate, this->SGD->TimeReceivedRate, ImGuiCond_Always);
		//	ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 3000000);

		//	//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
		//	ImPlot::PlotLine("received rate", &this->SGD->StokingReceivedRate.Data[0].x, &this->SGD->StokingReceivedRate.Data[0].y, this->SGD->StokingReceivedRate.Data.size(), 0, this->SGD->StokingReceivedRate.Offset, 2 * sizeof(float));

		//	ImPlot::EndPlot();
		//}
	}



}

void ROTracer::SignalPingSpeedPage() {

	if (false) {

		if (this->Net == NULL) {
			return;
		}

		//ImGui::BulletText("Move your signal,Ping, Speed to change the data!");

		//ImGui::Checkbox("Pause", &isPauseSignalSpeedPing);     // duraklatma seçenegi 

		//if (!isPauseSignalSpeedPing)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		//{
		//	this->SGD->HistorySignal = 20.0f;
		//	this->SGD->TimeSignalSpeedPing += ImGui::GetIO().DeltaTime;

		//	this->SGD->StokingSignal.AddPoint(this->SGD->TimeSignalSpeedPing, this->Net->Signal);
		//	this->SGD->StokingPing.AddPoint(this->SGD->TimeSignalSpeedPing, this->Net->Ping);
		//	this->SGD->StokingWifiSpeed.AddPoint(this->SGD->TimeSignalSpeedPing, this->Net->Speed);


		//}
		//else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
		//	this->SGD->TimeSignalSpeedPing;



		//ImGui::SliderFloat("History", &this->SGD->HistorySignal, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		//static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		//if (ImPlot::BeginPlot("##Scrolling", ImVec2(500, 250))) {     // grafik ölçeklendirme 
		//	ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

		//	ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->TimeSignalSpeedPing - this->SGD->HistorySignal, this->SGD->TimeSignalSpeedPing, ImGuiCond_Always);
		//	ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

		//	//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
		//	ImPlot::PlotLine("Signal", &this->SGD->StokingSignal.Data[0].x, &this->SGD->StokingSignal.Data[0].y, this->SGD->StokingSignal.Data.size(), 0, this->SGD->StokingSignal.Offset, 2 * sizeof(float));
		//	ImPlot::PlotLine("Ping", &this->SGD->StokingPing.Data[0].x, &this->SGD->StokingPing.Data[0].y, this->SGD->StokingPing.Data.size(), 0, this->SGD->StokingPing.Offset, 2 * sizeof(float));
		//	ImPlot::PlotLine("Speed", &this->SGD->StokingWifiSpeed.Data[0].x, &this->SGD->StokingWifiSpeed.Data[0].y, this->SGD->StokingWifiSpeed.Data.size(), 0, this->SGD->StokingWifiSpeed.Offset, 2 * sizeof(float));
		//	// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
		//	ImPlot::EndPlot();
		//}
	}





}

void ROTracer::TransmitededRatePage() {

	if (false) {

		if (this->Net == NULL) {
			return;
		}

		//ImGui::BulletText("Move your signal to change the data!");

		//ImGui::Checkbox("Pause", &isPauseTransmitededRate);     // duraklatma seçenegi 

		//if (!isPauseTransmitededRate)      // eger checkbox'a tıklanmazsa (false)  güncel zamanı alıyor  
		//{
		//	this->SGD->HistoryTransmittededRate = 20.0f;
		//	this->SGD->TimeTransmittededRate += ImGui::GetIO().DeltaTime;

		//	this->SGD->StokingTransmitededRate.AddPoint(this->SGD->TimeTransmittededRate, this->Net->TransmitededRate);


		//}
		//else     // eger checkbox'a tıklanırsa en son zamanı alıyor 
		//	this->SGD->TimeTransmittededRate;

		//ImGui::SliderFloat("History", &this->SGD->HistoryTransmittededRate, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanıyor 


		//static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		//if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
		//	ImPlot::SetupAxes("Time [s]", "transmiteded rate  [ ]");

		//	ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->TimeTransmittededRate - this->SGD->HistoryTransmittededRate, this->SGD->TimeTransmittededRate, ImGuiCond_Always);
		//	ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 30000000);

		//	//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
		//	ImPlot::PlotLine("transmiteded rate ", &this->SGD->StokingTransmitededRate.Data[0].x, &this->SGD->StokingTransmitededRate.Data[0].y, this->SGD->StokingTransmitededRate.Data.size(), 0, this->SGD->StokingTransmitededRate.Offset, 2 * sizeof(float));

		//	ImPlot::EndPlot();
		//}
	}


}

