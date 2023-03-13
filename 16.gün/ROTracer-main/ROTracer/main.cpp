#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot/implot.h"
#include "implot/implot_internal.h"
#pragma warning (disable : 4996)
#include <stdio.h>
  
#include <string>
#include "data_for_graphic.h"

#include <string.h>
#include <zmq.h>
#include <thread>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif
#include <iostream>
using namespace std;


void task1()
{
	TakeDatasString dataa, // sayac nesnesi oluþtur
		* dataaPtr = &dataa, // dataya pointer
		& dataRef = dataa; // dataya referans

	void* context = zmq_ctx_new();
	void* subscriber = zmq_socket(context, ZMQ_SUB);
	int rc = zmq_connect(subscriber, "tcp://192.168.2.125:5556");

	rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);


	const int topic_size = 5;
	const int msg_size = 128;

	char topic[topic_size] = { 0 };
	char msg[msg_size] = { 0 };
	std::string new_msg(msg);
	size_t sayac = 0;
	char* pch;

	while (1)
	{
		rc = zmq_recv(subscriber, topic, topic_size, 0);
		if (rc != -1)
			fprintf(stdout, "TOPIC: %s \n", topic);

		rc = zmq_recv(subscriber, msg, msg_size, 0);
		if (rc != -1) {

		if(topic=="real"){
			pch = strtok(msg, ";");
			while (pch != NULL)
			{
				if (sayac == 0) {
					dataa.x = stoi(pch);
					sayac++;
					
				}
				else if (sayac == 1) {
					dataa.y = stoi(pch);
					sayac++;
					
				}
				else if (sayac == 2) {
					dataa.a = std::stof(pch);
					sayac++;
				
				}
				else if (sayac == 3) {
					dataa.ws = stoi(pch);
					sayac++; 
					
				}
				else if (sayac == 4) {
					dataa.rs = stoi(pch);
					sayac++;
					
				}
				else if (sayac == 5) {
					dataa.wwa = std::stof(pch);
					sayac++;
				
				}
				else if (sayac == 6) {
					dataa.rwa = std::stof(pch);
					sayac++;
				
				}



				printf("%s\n", pch);
				pch = strtok(NULL, ";");
			}
			}
			printf("-----------------------");
			fprintf(stdout, "MSG: %s \n", msg);
		}
	}

	zmq_close(subscriber);
	zmq_ctx_destroy(context);

}   

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
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

// Main code
int main(int, char**)
{

	TakeDatasString datasa, //  nesnesi oluþtur
		* dataaPtr = &datasa, // dataya pointer
		& dataRef = datasa; // dataya referans
	

	std::thread t1(task1);
	t1.detach(); 

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
#ifdef __EMSCRIPTEN__
	io.IniFilename = NULL;
	EMSCRIPTEN_MAINLOOP_BEGIN
#else

	while (!glfwWindowShouldClose(window))
#endif
	{
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//-----------------------------------draw graphics------------------------------------------------------- 
	/*
		static RollingBuffer   rdata1, rdata2;

		static float t = 0;
		t += ImGui::GetIO().DeltaTime;

		rdata1.AddPoint(t, datasa.ws * 0.0005f);
		rdata2.AddPoint(t, datasa.rs * 0.0005f);

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
	*/
		//-------------------------------------------------------------------------------------------------------

		ImPlot::ShowDemoWindow();
		
		Demo_RealtimePlots();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}
#ifdef __EMSCRIPTEN__
	EMSCRIPTEN_MAINLOOP_END;
#endif

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

