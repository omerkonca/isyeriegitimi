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


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#ifndef PI
#define PI 3.14159265358979323846
#endif

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
	ScrollingBuffer StokingPosition;


	ScrollingBuffer ping;
	ScrollingBuffer receivedrate;
	ScrollingBuffer Signal_ping_baundrate;
	ScrollingBuffer speed;


	float Time;                          // geçen zamaný depolamak için oluþturdugumuz deðiþken 
	float wheelTime;                          // geçen zamaný depolamak için oluþturdugumuz deðiþken 
	float angleTime;                          // geçen zamaný depolamak için oluþturdugumuz deðiþken 
	float speedTime;                          // geçen zamaný depolamak için oluþturdugumuz deðiþken 
	float pingTime;                          // geçen zamaný depolamak için oluþturdugumuz deðiþken 
	float receivedrateTime;                          // geçen zamaný depolamak için oluþturdugumuz deðiþken 
	float signalTime;                          // geçen zamaný depolamak için oluþturdugumuz deðiþken 
	 float TimeReceivedRate;

	float TimePosition;
	
	float History= 20.0f;                       // geçmiþ zamaný depolamak için 
	float angleHistory= 20.0f;                       // geçmiþ zamaný depolamak için 
	float speedHistory = 20.0f;                       // geçmiþ zamaný depolamak için 
	float pingHistory=20.0f;                       // geçmiþ zamaný depolamak için 
	float receivedrateHistory;                       // geçmiþ zamaný depolamak için 
	float signalHistory= 20.0f;                       // geçmiþ zamaný depolamak için 
	float wheelHistory= 20.0f;                       // geçmiþ zamaný depolamak için 
	float HistoryPosition = 20.0f;
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
	bool totalangle = false;
	bool Agvspeed = false;
	bool wheel = false;



	//bool Ping = false;
	//bool ReceivedRate = false;
	//bool Signal = false;
	//bool wifiSpeed = false;


	bool isPause = false;       // grafik durdurma durumunu tutma  
	bool anglePause = false;       // grafik durdurma durumunu tutma  
	bool speedPause = false;       // grafik durdurma durumunu tutma  
	bool PingPause = false;       // grafik durdurma durumunu tutma  
	bool ReceivedRatePause = false;       // grafik durdurma durumunu tutma  
	bool SignalPause = false;       // grafik durdurma durumunu tutma  
	bool wheelPause = false;       // grafik durdurma durumunu tutma  

	bool isPausePosition = false;



	SpeedGraphicData* SGD;    // SpeedGraphicData class'ýnýn nesnesini oluþturduk  


private:
	bool _loginPageVisibility;        //giriþ sayfa görünürlüðü
	bool _speedPageVisibility;        //hýz grafik sayfasýnýn görünürlüðü
	bool _positionPageVisibility;
	bool _wheelPageVisibility;
	bool _angleTotalPageVisibility;


	bool _PingPageVisibility;
	bool _ReceivedRatePageVisibility;
	bool _SignalPageVisibility;
	bool _wifiSpeedPageVisibility;


	bool _zmqLoopFlag;               //zmq data parse iþlemini yapýp yapmama  

	void ZMQDataStreamParser();       // parse işlemi private onun için burda yoksa yukarý da yazabilirdik
	void PositionPage();
	void WheelPage();
	void TotalAngelPage();
	void Signal_ping_baundrate();

	void positionjson();

};


#endif
