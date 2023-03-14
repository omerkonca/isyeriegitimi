#ifndef ROTRACER_H   // bu kütüphaneye birden fazla yerden çagýrmak için  Ýsimlendirmenini kýsaltmasý þeklinde yazdýk burdaki ismi
#define ROTRACER_H    
// ----------------------------BÜTÜN TANIMLAMA ÝÞLEMLERÝNÝ BURDA YAPIYORUZ --------------------------
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)

#include <iostream>
#include <imgui.h>               // imgui bileþenlerini kullnmak için 
#include <implot/implot.h>       // implot bileþenleri için 
#include <regex>
#include <string.h>
#include <zmq.h>
#include <thread>
#include <stdio.h>

class AgvData {
public:
	int x;           //x konum
	int y;           // y konum
	float a;           // açý
	int ws;          // yazýlan hýz
	int rs;          // okunan hýz 
	float wwa;         // yazýlan teker açýsý 
	float rwa;         // okunan teker açýsý 
};


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

struct ScrollingBuffer {
	int MaxSize;
	int Offset;
	ImVector<ImVec2> Data;
	ScrollingBuffer(int max_size = 2000000) {
		MaxSize = max_size;
		Offset = 0;
		Data.reserve(MaxSize);
	}
	void AddPoint(float x, float y) {
		if (Data.size() < MaxSize)
			Data.push_back(ImVec2(x, y));
		else {
			Data[Offset] = ImVec2(x, y);
			Offset = (Offset + 1) % MaxSize;
		}
	}
	void Erase() {
		if (Data.size() > 0) {
			Data.shrink(0);
			Offset = 0;
		}
	}
};

class ROTracer
{
public:                   //constructor 
	ROTracer();
	~ROTracer();

	void SpeedPage();      //fonksiyonlar 
	void LoginPage();

	void StartStreamParser();
	void StopStreamParser();

	AgvData* Agv;          // nesne oluþturduk

	char IpAddress[16] = "192.168.2.125";
	bool _isRunning;


private:
	bool _loginPageVisibility;        //giriþ sayfa görünürlüðü
	bool _speedPageVisibility;        //hýz grafik sayfasýnýn görünürlüðü

	bool _zmqLoopFlag;               //zmq data parse iþlemini yapýp yapmama  

	void ZMQDataStreamParser();       // parse iþlemi private onun için burda yoksa yukarý da yazabilirdik
};


#endif