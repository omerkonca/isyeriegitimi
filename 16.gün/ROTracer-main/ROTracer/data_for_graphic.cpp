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

//--------------------------------grafik çizme alanı---------------------------------------------------------------

void ROTracer::SpeedPage() {
	_zmqLoopFlag = true;
	if (this->_speedPageVisibility == true) {

		if (this->Agv == NULL) {
			return;
		}

		ImGui::BulletText("Move your speed to change the data!");

		ImGui::Checkbox("Pause", &speedPause);     // duraklatma seçenegi 

		if (!speedPause)      // eger checkbox'a tıklanmazsa (false)  güncel zamanı alıyor  
		{
			/*this->SGD->speedHistory = 20.0f;*/
			this->SGD->speedTime += ImGui::GetIO().DeltaTime;

			this->SGD->ReadingSpeed.AddPoint(this->SGD->speedTime, this->Agv->RSpeed);
			this->SGD->WritingSpeed.AddPoint(this->SGD->speedTime, this->Agv->WSpeed);

		}
		else     // eger checkbox'a tıklanırsa en son zamanı alıyor 
			this->SGD->speedTime;



		ImGui::SliderFloat("History", &this->SGD->speedHistory, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanıyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->speedTime - this->SGD->speedHistory, this->SGD->speedTime, ImGuiCond_Always);
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

		ImGui::Checkbox("Pause", &wheelPause);     // duraklatma seçenegi 

		if (!wheelPause)      // eger checkbox'a tıklanmazsa (false)  güncel zamanı alıyor  
		{
			/*this->SGD->wheelHistory = 20.0f;*/
			this->SGD->wheelTime += ImGui::GetIO().DeltaTime;

			this->SGD->ReadingAngel.AddPoint(this->SGD->wheelTime, this->Agv->RAngle);
			this->SGD->WritingAngel.AddPoint(this->SGD->wheelTime, this->Agv->WAngle);

		}
		else     // eger checkbox'a tıklanırsa en son zamanı alıyor 
			this->SGD->wheelTime;



		ImGui::SliderFloat("History", &this->SGD->wheelHistory, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanıyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Wheel °");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->wheelTime - this->SGD->wheelHistory, this->SGD->wheelTime, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("READ WHEEL ANGLE ", &this->SGD->ReadingAngel.Data[0].x, &this->SGD->ReadingAngel.Data[0].y, this->SGD->ReadingAngel.Data.size(), 0, this->SGD->ReadingAngel.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("WRITE WHEEL ANGLE", &this->SGD->WritingAngel.Data[0].x, &this->SGD->WritingAngel.Data[0].y, this->SGD->WritingAngel.Data.size(), 0, this->SGD->WritingAngel.Offset, 2 * sizeof(float));
			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}

}

void ROTracer::TotalAngelPage() {
	_zmqLoopFlag = true;
	if (this->_angleTotalPageVisibility == true) {

		if (this->Agv == NULL) {
			return;
		}

		ImGui::BulletText("Move your Angel to change the data!");

		ImGui::Checkbox("Pause", &anglePause);     // duraklatma seçenegi 

		if (!anglePause)      // eger checkbox'a tıklanmazsa (false)  güncel zamanı alıyor  
		{
			/*this->SGD->angleHistory = 20.0f;*/
			this->SGD->angleTime += ImGui::GetIO().DeltaTime;

			this->SGD->ReadingAngel.AddPoint(this->SGD->angleTime, this->Agv->RAngle);
			this->SGD->WritingAngel.AddPoint(this->SGD->angleTime, this->Agv->WAngle);
		}
		else     // eger checkbox'a tıklanırsa en son zamanı alıyor 
			this->SGD->angleTime;



		ImGui::SliderFloat("History", &this->SGD->angleHistory, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanıyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Angle ");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->angleTime - this->SGD->angleHistory, this->SGD->angleTime, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -100, 100);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("W ANGLE ", &this->SGD->ReadingAngel.Data[0].x, &this->SGD->ReadingAngel.Data[0].y, this->SGD->ReadingAngel.Data.size(), 0, this->SGD->ReadingAngel.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("R ANGLE ", &this->SGD->WritingAngel.Data[0].x, &this->SGD->WritingAngel.Data[0].y, this->SGD->WritingAngel.Data.size(), 0, this->SGD->WritingAngel.Offset, 2 * sizeof(float));

			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}

}

void ROTracer::PositionPage() {
	_zmqLoopFlag = true;
	if (this->_positionPageVisibility == true) {


		//if (ImPlot::BeginPlot("##EqualAxes", ImVec2(-1, 0), ImPlotFlags_Equal)) {
		//	int x1 = 4;
		//	int y1 = 2;
		//	int r = 5;

		//	float angle = 45;

		//	float x_1 = x1 + cos(angle * PI / 180) * r;   //üst 
		//	float y_1 = y1 + sin(angle * PI / 180) * r;

		//	float x_2 = x1 + cos((angle + 120) * PI / 180) * r;  // sol alt 
		//	float y_2 = y1 + sin((angle + 120) * PI / 180) * r;

		//	float x_3 = x1 + cos((angle + 240) * PI / 180) * r;    //sağ alt 
		//	float y_3 = y1 + sin((angle + 240) * PI / 180) * r;


		//	ImVec2 p1 = ImPlot::PlotToPixels(ImPlotPoint(x_2, y_2));    //sol alt 
		//	ImVec2 p2 = ImPlot::PlotToPixels(ImPlotPoint(x_3, y_3));     // sag alt 
		//	ImVec2 p3 = ImPlot::PlotToPixels(ImPlotPoint(x_1, y_1));     // tepe


		//	//ImPlot::SetupAxis(ImAxis_X2, NULL, ImPlotAxisFlags_AuxDefault);
		//	//ImPlot::SetupAxis(ImAxis_Y2, NULL, ImPlotAxisFlags_AuxDefault);
		//	//ImPlot::SetAxes(ImAxis_X2, ImAxis_Y2);

		//	ImPlot::GetPlotDrawList()->AddTriangleFilled(p1, p2, p3, IM_COL32(128, 0, 255, 255));
		//	ImPlot::EndPlot();
		//}

		if (this->Agv == NULL) {
			return;
		}

		float xMin = 10000, xMax = 30000, yMin = 30000, yMax = 80000;
		if (this->SGD->StokingPosition.Data.size() > 0) {
			if (ImPlot::BeginPlot("Scatter Plot", ImVec2(-1, 0), ImPlotFlags_Equal)) {
			
				ImPlot::PlotScatter("pos", &this->SGD->StokingPosition.Data[0].x, &this->SGD->StokingPosition.Data[0].y, this->SGD->StokingPosition.Data.size(), 0, 0, 2 * sizeof(int));


				//ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
				//ImPlot::SetNextMarkerStyle(ImPlotMarker_Up, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(1));
				//ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, 6);
				int lastIndex = this->SGD->StokingPosition.Data.Size - 1;

				//ImPlot::PlotScatter("p2 ", &this->SGD->StokingPosition.Data[lastIndex].x, &this->SGD->StokingPosition.Data[lastIndex].y, 1);

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
		/*
		static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
		{
			return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
		}
		static inline ImVec2 ImRotate(const ImVec2& v, float cos_a, float sin_a)
		{
			return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a);
		}
		void ImageRotated(ImTextureID tex_id, ImVec2 center, ImVec2 size, float angle)
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			float cos_a = cosf(angle);
			float sin_a = sinf(angle);
			ImVec2 pos[4] =
			{
				center + ImRotate(ImVec2(-size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
				center + ImRotate(ImVec2(+size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
				center + ImRotate(ImVec2(+size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a),
				center + ImRotate(ImVec2(-size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a)
			};
			ImVec2 uvs[4] =
			{
				ImVec2(0.0f, 0.0f),
				ImVec2(1.0f, 0.0f),
				ImVec2(1.0f, 1.0f),
				ImVec2(0.0f, 1.0f)
			};
			draw_list->AddImageQuad(tex_id, pos[0], pos[1], pos[2], pos[3], uvs[0], uvs[1], uvs[2], uvs[3], IM_COL32_WHITE);
		}
		*/


		//------------------------------------------------------------------------------------
		/*void Demo_CustomRendering() {
			if (ImPlot::BeginPlot("##CustomRend")) {
				ImVec2 cntr = ImPlot::PlotToPixels(ImPlotPoint(0.5f, 0.5f));
				ImVec2 rmin = ImPlot::PlotToPixels(ImPlotPoint(0.25f, 0.75f));
				ImVec2 rmax = ImPlot::PlotToPixels(ImPlotPoint(0.75f, 0.25f));
				ImPlot::PushPlotClipRect();
				ImPlot::GetPlotDrawList()->AddCircleFilled(cntr, 20, IM_COL32(255, 255, 0, 255), 20);
				ImPlot::GetPlotDrawList()->AddRect(rmin, rmax, IM_COL32(128, 0, 255, 255));
				 srand(359);
				 int angle = rand();
				ImVec2 p1 = ImPlot::PlotToPixels(ImPlotPoint(0.0f, 1.f));
				ImVec2 p2 = ImPlot::PlotToPixels(ImPlotPoint(2.f, 1.f));
				ImVec2 p3 = ImPlot::PlotToPixels(ImPlotPoint(1.f, 7.f));
				 ImPlot::GetPlotDrawList()->AddTriangleFilled(p1, p2, p3, IM_COL32(128, 0, 255, 255));
				 ImPlot::PopPlotClipRect();
				ImPlot::EndPlot();
			}
		}*/



	}
}


float x = 10.f;
float y = 15.f;
void ROTracer::positionjson() {

	if (ImPlot::BeginPlot("##CustomRend")) {
		float base = x;   // taban uzunluğu
		float height = y; // yükseklik
		ImVec2 center = ImPlot::PlotToPixels(ImPlotPoint(x, y));

		float half_base = base * 0.5f;
		float half_height = height * 0.5f;

		ImVec2 p1 = ImVec2(center.x - half_base, center.y + half_height);
		ImVec2 p2 = ImVec2(center.x + half_base, center.y + half_height);
		ImVec2 p3 = ImVec2(center.x, center.y - half_height);

		ImPlot::PushPlotClipRect();
		ImPlot::GetPlotDrawList()->AddTriangleFilled(p1, p2, p3, IM_COL32(128, 0, 255, 255));
		ImPlot::PopPlotClipRect();
		ImPlot::EndPlot();
	}


	//if (ImPlot::BeginPlot("##CustomRend")) {
	//	float base = x;    // taban uzunluğu
	//	float height = y;  // yükseklik
	//	ImVec2 center = ImPlot::PlotToPixels(ImPlotPoint(x, y));

	//	float half_base = base * 0.5f;
	//	float half_height = height * 0.5f;

	//	// Calculate the four corners of the triangle
	//	ImVec2 p1 = ImVec2(center.x - half_base, center.y + half_height);
	//	ImVec2 p2 = ImVec2(center.x + half_base, center.y + half_height);
	//	ImVec2 p3 = ImVec2(center.x, center.y - half_height);

	//	// Define the rotation angle in degrees
	//	float angle_degrees = 45.0f; // Change this to your desired angle

	//	// Convert the angle from degrees to radians
	//	float angle_radians = angle_degrees * (PI / 180.0f);

	//	// Calculate the cosine and sine of the angle
	//	float cos_a = cosf(angle_radians);
	//	float sin_a = sinf(angle_radians);

	//	// Rotate each corner of the triangle around the center point
	//	ImVec2 delta1 = p1 - center;
	//	ImVec2 delta2 = p2 - center;
	//	ImVec2 delta3 = p3 - center;
	//	p1.x = center.x + delta1.x * cos_a - delta1.y * sin_a;
	//	p1.y = center.y + delta1.x * sin_a + delta1.y * cos_a;
	//	p2.x = center.x + delta2.x * cos_a - delta2.y * sin_a;
	//	p2.y = center.y + delta2.x * sin_a + delta2.y * cos_a;
	//	p3.x = center.x + delta3.x * cos_a - delta3.y * sin_a;
	//	p3.y = center.y + delta3.x * sin_a + delta3.y * cos_a;

	//	// Add the rotated triangle to the plot draw list
	//	ImPlot::PushPlotClipRect();
	//	ImPlot::GetPlotDrawList()->AddTriangleFilled(p1, p2, p3, IM_COL32(128, 0, 255, 255));
	//	ImPlot::PopPlotClipRect();

	//	ImPlot::EndPlot();
	//}
}



//void ROTracer::Ping() {
//	_zmqLoopFlag = true;
//	if (this->_PingPageVisibility == true) {
//
//		if (this->Net == NULL) {
//			return;
//		}
//
//		ImGui::BulletText("Move your speed to change the data!");
//
//		ImGui::Checkbox("Pause", &PingPause);     // duraklatma seçenegi 
//
//		if (!PingPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
//		{
//			this->SGD->pingHistory = 20.0f;
//			this->SGD->pingTime += ImGui::GetIO().DeltaTime;
//
//			this->SGD->ping.AddPoint(this->SGD->pingTime, this->Net->Ping);
//
//
//		}
//		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
//			this->SGD->pingTime;
//
//
//
//		ImGui::SliderFloat("History", &this->SGD->pingHistory, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 
//
//
//		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;
//
//		if (ImPlot::BeginPlot("##Scrolling", ImVec2(400, 150))) {     // grafik ölçeklendirme 
//			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");
//
//			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->pingTime - this->SGD->pingHistory, this->SGD->pingTime, ImGuiCond_Always);
//			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);
//
//			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
//			ImPlot::PlotLine("rs X", &this->SGD->ping.Data[0].x, &this->SGD->ping.Data[0].y, this->SGD->ping.Data.size(), 0, this->SGD->ping.Offset, 2 * sizeof(float));
//			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
//			ImPlot::EndPlot();
//		}
//	}
//}
//
//void ROTracer::ReceivedRate() {
//	_zmqLoopFlag = true;
//	if (this->_ReceivedRatePageVisibility == true) {
//
//		if (this->Net == NULL) {
//			return;
//		}
//
//		ImGui::BulletText("Move your speed to change the data!");
//
//		ImGui::Checkbox("Pause", &ReceivedRatePause);     // duraklatma seçenegi 
//
//		if (!ReceivedRatePause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
//		{
//			this->SGD->receivedrateHistory = 20.0f;
//			this->SGD->receivedrateTime += ImGui::GetIO().DeltaTime;
//
//			this->SGD->receivedrate.AddPoint(this->SGD->receivedrateTime, this->Net->ReceivedRate);
//
//
//		}
//		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 
//			this->SGD->receivedrateTime;
//
//
//
//		ImGui::SliderFloat("History", &this->SGD->receivedrateHistory, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 
//
//
//		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;
//
//		if (ImPlot::BeginPlot("##Scrolling", ImVec2(400, 150))) {     // grafik ölçeklendirme 
//			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");
//
//			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->receivedrateTime - this->SGD->receivedrateHistory, this->SGD->receivedrateTime, ImGuiCond_Always);
//			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);
//
//			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
//			ImPlot::PlotLine("rs X", &this->SGD->receivedrate.Data[0].x, &this->SGD->receivedrate.Data[0].y, this->SGD->receivedrate.Data.size(), 0, this->SGD->receivedrate.Offset, 2 * sizeof(float));
//			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
//			ImPlot::EndPlot();
//		}
//	}
//
//}

void ROTracer::Signal_ping_baundrate() {

	_zmqLoopFlag = true;

	if (this->_SignalPageVisibility == true) {

		if (this->Net == NULL) {

			return;
		}

		ImGui::BulletText("Move your signal,Ping, Speed to change the data!");

		ImGui::Checkbox("Pause", &SignalPause);     // duraklatma seçenegi 


		if (!SignalPause)      // eger checkbox'a týklanmazsa (false)  güncel zamaný alýyor  
		{

			this->SGD->signalTime += ImGui::GetIO().DeltaTime;

			this->SGD->Signal_ping_baundrate.AddPoint(this->SGD->signalTime, this->Net->Signal);
			this->SGD->ping.AddPoint(this->SGD->signalTime, this->Net->Ping);
			this->SGD->speed.AddPoint(this->SGD->signalTime, this->Net->Speed);


		}
		else     // eger checkbox'a týklanýrsa en son zamaný alýyor 


			this->SGD->signalTime;






		ImGui::SliderFloat("History", &this->SGD->signalHistory, 1, 300, "% 1.f saniye");  // .1f yaparsak milisaniye olarak ayarlanýyor 


		static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

		if (ImPlot::BeginPlot("##Scrolling", ImVec2(800, 350))) {     // grafik ölçeklendirme 
			ImPlot::SetupAxes("Time [s]", "Speed [mm/s]");

			ImPlot::SetupAxisLimits(ImAxis_X1, this->SGD->signalTime - this->SGD->signalHistory, this->SGD->signalTime, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -500, 1900);

			//ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 1.f);
			ImPlot::PlotLine("Signal", &this->SGD->Signal_ping_baundrate.Data[0].x, &this->SGD->Signal_ping_baundrate.Data[0].y, this->SGD->Signal_ping_baundrate.Data.size(), 0, this->SGD->Signal_ping_baundrate.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("Ping", &this->SGD->ping.Data[0].x, &this->SGD->ping.Data[0].y, this->SGD->ping.Data.size(), 0, this->SGD->ping.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("Speed", &this->SGD->speed.Data[0].x, &this->SGD->speed.Data[0].y, this->SGD->speed.Data.size(), 0, this->SGD->speed.Offset, 2 * sizeof(float));
			// plotline düz cizgili grafik <=> PlotShaded gölgeli grafik  
			ImPlot::EndPlot();
		}
	}


}








//--------------------------------giriş sayfası--------------------------------------------------------------------

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


			ImGui::Begin("New Page ");
			ImGui::SetNextWindowSize(ImVec2(1700, 900));
			// Yeni sayfa içeriði ve IP adresi bilgisi


			if (ImGui::CollapsingHeader("NET"))
			{

				ImGui::TableNextColumn();
				ImGui::Text("DeviceMacAddress: %s", this->Net->DeviceMacAddress.c_str());

				ImGui::TableNextColumn();
				ImGui::Text("SSID: %s", this->Net->SSID.c_str());
				ImGui::TableNextColumn();
				ImGui::Text("Status: %s", this->Net->Status.c_str());

				// İlk iki grafiği yan yana sırala
				ImGui::BeginChild("Ping", ImVec2(900, 500), true);
				_SignalPageVisibility = true;
				this->Signal_ping_baundrate();
				ImGui::EndChild();

				//ImGui::SameLine();

				//ImGui::BeginChild("ReceivedRate", ImVec2(600, 300), true);
				//_ReceivedRatePageVisibility = true;
				//this->ReceivedRate();
				//ImGui::EndChild();

				//// Son grafiği hemen altına sırala
				//ImGui::BeginChild("Signal", ImVec2(600, 300), true);
				//_SignalPageVisibility = true;
				//this->Signal();
				//ImGui::EndChild();
			}

			if (ImGui::CollapsingHeader("AGV"))
			{
				ImGui::Checkbox("Wheel", &wheel);
				ImGui::SameLine();
				ImGui::Checkbox("Speed", &Agvspeed);
				ImGui::SameLine();
				ImGui::Checkbox("Angle", &totalangle);
				ImGui::SameLine();
				ImGui::Checkbox("Position", &position);


				if (Agvspeed) {
					ImGui::BeginChild("speed", ImVec2(900, 500), true);
					_speedPageVisibility = true;
					this->positionjson();
					ImGui::EndChild();

				}

				if (wheel) {
					ImGui::BeginChild("Ping", ImVec2(900, 500), true);
					_wheelPageVisibility = true;
					this->WheelPage();
					ImGui::EndChild();

				}

				if (totalangle) {
					ImGui::BeginChild("Total Angle", ImVec2(900, 500), true);
					_angleTotalPageVisibility = true;
					this->TotalAngelPage();
					ImGui::EndChild();

				}

				if (position) {
					ImGui::BeginChild("Postion", ImVec2(900, 500), true);
					_positionPageVisibility = true;
					this->PositionPage();
					ImGui::EndChild();
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
	//std::string b = ("tcp://%s:%d", take_ip,take_port);    // opsiyonel kullanım 

	int rc = zmq_connect(subscriber, a.c_str());  //"tcp://192.168.2.125:5556"
	rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);

	//const int topic_size = 5;
	//const int msg_size = 128;

	//char topic[topic_size] = { 0 };
	//char msg[msg_size] = { 0 };
	//std::string new_msg(msg);
	size_t sayac = 0;
	char* pch;
	_isRunning = true;

	fprintf(stdout, "start");

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

		//rc = zmq_recv(subscriber, topic, topic_size, 0);
		/*if (rc != -1) {
			fprintf(stdout, "TOPIC: %s \n", zmq_topic_data);
			fprintf(stdout, "MSG: %s \n", zmq_message_data);
		}*/

		//rc = zmq_recv(subscriber, msg, msg_size, 0);
		if (rc != -1) {

			if (std::strcmp("real", zmq_topic_data) == 0) {
				pch = strtok(zmq_message_data, ";");
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

				this->SGD->StokingPosition.AddPoint(this->Agv->X, this->Agv->Y);
			}
			else if (std::strcmp("net", zmq_topic_data) == 0) {
				pch = strtok(zmq_message_data, ";");
				while (pch != NULL)
				{
					if (sayac == 0) {
						Net->DeviceMacAddress = std::string(pch);
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
						Net->SSID = std::string(pch);;
						sayac++;

					}
					else if (sayac == 6) {
						Net->Status = std::string(pch);
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
			
			else if (std::strcmp("route", zmq_topic_data) == 0) {

				try {
					rapidjson::Document doc;
					doc.Parse(zmq_message_data);

					if (doc.HasParseError()) {
						std::cerr << "Error parsing JSON: "
							<< doc.GetParseError() << std::endl;
						continue;
					}

					rapidjson::Value::ConstValueIterator itr;

					for (itr = doc.Begin(); itr != doc.End(); ++itr) {
						// Access the data in the object
						std::cout << "X: "
							<< itr->GetObject()["X"].GetFloat()
							<< std::endl;
						std::cout << "Y: "
							<< itr->GetObject()["Y"].GetFloat()
							<< std::endl;
						this->SGD->StokingPosition.Data.push_back(ImVec2(x, y));
					}

				}
				catch (...)
				{

				}
			}/*
			else if (std::strcmp("sim", topic) == 0) {
			}
			else if (std::strcmp("curve", topic) == 0) {
			}*/


			//fprintf(stdout, "----------------------- \n");

		}


		//  serbest bırakma 
		free(zmq_topic_data);
		free(zmq_message_data);
	}
	
	zmq_close(subscriber);
	zmq_ctx_destroy(context);

	_isRunning = false;

}