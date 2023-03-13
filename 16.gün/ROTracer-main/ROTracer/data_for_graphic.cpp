#include <iostream>
#include <imgui.h>               // imgui bileþenlerini kullnmak için 
#include <implot/implot.h>       // implot bileþenleri için 

#include <data_for_graphic.h>    //data_for_graphic deki veriler için çagýrýyoruz 



struct RollingBuffer {  //grafik için eklendi 
	float Span;
	ImVector<ImVec2> Data;
	RollingBuffer() {
		Span = 10.0f;
		Data.reserve(2000);
	}
	void AddPoint(float x, float y) {
		float xmod = fmodf(x, Span);
		if (!Data.empty() && xmod < Data.back().x)
			Data.shrink(0);
		Data.push_back(ImVec2(xmod, y));
	}
};



//--------------------------------grafik çizme alaný-------------
void Demo_RealtimePlots() {
	TakeDatasString d, //  nesnesi oluþtur
		* dataaPtr = &d, // dataya pointer
		& dataRef = d; // dataya referans



	static RollingBuffer   rdata1, rdata2;

	static float t = 0;
	t += ImGui::GetIO().DeltaTime;

	rdata1.AddPoint(t, d.ws * 0.005f);
	rdata2.AddPoint(t, d.rs * 0.005f);

	static float history = 10.0f;
	ImGui::SliderFloat("History", &history, 1, 30, "%.1f s");
	rdata1.Span = history;
	rdata2.Span = history;



	static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

	if (ImPlot::BeginPlot("##Rolling", ImVec2(-1, 150))) {
		ImPlot::SetupAxes(NULL, NULL, flags, flags);
		ImPlot::SetupAxisLimits(ImAxis_X1, 0, history, ImGuiCond_Always);
		ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
		ImPlot::PlotLine("Write speed", &rdata1.Data[0].x, &rdata1.Data[0].y, rdata1.Data.size(), 0, 0, 2 * sizeof(float));
		ImPlot::PlotLine("Read speed", &rdata2.Data[0].x, &rdata2.Data[0].y, rdata2.Data.size(), 0, 0, 2 * sizeof(float));
		ImPlot::EndPlot();
	}

}

//-----------------------------------------------------------------------------

