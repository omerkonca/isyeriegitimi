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

// AgvStreamData
class AgvData {
public:
	int X;                       //x konum
	int Y;                       // y konum
	float Angle;                 // açý
	int WSpeed;                  // yazýlan hýz
	int RSpeed;                  // okunan hýz 
	float WAngle;                // yazýlan teker açýsý 
	float RAngle;                // okunan teker açýsý 
};

class NetData {
public:
	std::string DeviceMacAddress;     //mac adresi    
	int Ping;                         // ping degeri 
	int ReceivedRate;                 // alýnma oraný
	int Signal;                       // wifi sinyal kalitesi
	int Speed;                        // wifi hýzý 
	std::string SSID;                // wifi ismi 
	std::string Status;               // wifi durumu 
	int TransmitededRate;             // iletim oraný


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

class SpeedGraphicData
{
public:
	ScrollingBuffer ReadingSpeed;        // data depolamak için oluþturduðumuz deðiþken 
	ScrollingBuffer WritingSpeed;        // data depolamak için oluþturduðumuz deðiþken 
	ScrollingBuffer ReadingAngel;
	ScrollingBuffer WritingAngel;
	ScrollingBuffer totalAngel;
	static ScrollingBuffer totalX;
	static ScrollingBuffer totalY;

	ScrollingBuffer ping;
	ScrollingBuffer receivedrate;
	ScrollingBuffer signal;


	float Time;                          // geçen zamaný depolamak için oluþturdugumuz deðiþken 
	float History;                       // geçmiþ zamaný depolamak için 
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

	AgvData* Agv;          //agv classýna ait  nesne oluþturduk  
	NetData* Net;
	char IpAddress[16] = "192.168.2.125";
	bool _isRunning;
	bool page1 = true;
	bool position = false;
	bool angle = false;
	bool speed = false;
	bool wheel = false;



	//bool Ping = false;
	//bool ReceivedRate = false;
	//bool Signal = false;
	//bool wifiSpeed = false;


	bool isPause = false;       // grafik durdurma durumunu tutma       
	SpeedGraphicData* SGD;    // SpeedGraphicData class'ýnýn nesnesini oluþturduk  


private:
	bool _loginPageVisibility;        //giriþ sayfa görünürlüðü
	bool _speedPageVisibility;        //hýz grafik sayfasýnýn görünürlüðü
	bool _positionPageVisibility;
	bool _wheelPageVisibility;
	bool _anglePageVisibility;


	bool _PingPageVisibility;
	bool _ReceivedRatePageVisibility;
	bool _SignalPageVisibility;
	bool _wifiSpeedPageVisibility;


	bool _zmqLoopFlag;               //zmq data parse iþlemini yapýp yapmama  

	void ZMQDataStreamParser();       // parse işlemi private onun için burda yoksa yukarý da yazabilirdik
	void PositionPage();
	void WheelPage();
	void AngelPage();
	void Ping();
	void ReceivedRate();
	void Signal();
	void wifiSpeed();
};


#endif
