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
    int Fx;                       //x konum
    int Fy;                       // y konum
	int Bx;                       //x konum
	int By;                       // y konum
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
	std ::string SSID;                // wifi ismi 
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



class GraphicData {
public:
	float Time;
	float History = 1.0f;
	bool Enabled = true;
};

class WheelGraphicData :public GraphicData
{
public:
	ScrollingBuffer ReadingWheelAngel;
	ScrollingBuffer WritingWheelAngel;

};

class SpeedGraphicData :public GraphicData
{
public:
	ScrollingBuffer ReadingSpeed;        
	ScrollingBuffer WritingSpeed;      
};

class AgvAngleGraphicData : public GraphicData
{
public:
	ScrollingBuffer AgvAngle;
};

class AgvPositionGraphicData : public GraphicData
{
public:
	ScrollingBuffer AgvFrontPosition;
	ScrollingBuffer AgvBackPosition;
	float AgvAngle;
};

class PointGraphicData : public GraphicData
{
public:
	ScrollingBuffer Point;
};

class ROTracer
{   
public:                   //constructor 
	ROTracer();
	~ROTracer();

	void SpeedPage();      // agv fonksiyonlar 
	void LoginPage();
	void AgvPositionPage();
	void WheelPage();
	void AgvAngelPage();

	void ShowAGVWindow(bool* p_open);
	void ShowNETWindow(bool* p_open);

	//----------------
	void WifiSpeedPage();    // net fonksiyonlarý 
	void PingPage();
	void ReceivedRatePage();
	void SignalPingSpeedPage();
	void TransmitededRatePage();


	void StartStreamParser();
	void StopStreamParser();



	AgvData *Agv;          //agv classýna ait  nesne oluþturduk  
	NetData *Net;
	SpeedGraphicData *SpeedGraphic;    // SpeedGraphicData class'ýnýn nesnesini oluþturduk 
	WheelGraphicData *WheelGraphic;
	AgvAngleGraphicData *AgvAngleGraphic;
	AgvPositionGraphicData *AgvPositionGraphic;
	PointGraphicData *AgvRouteGraphic;
	PointGraphicData *AgvCurveGraphic;
	PointGraphicData *AgvSimRouteGraphic;

	char IpAddress[16] = "192.168.2.125";
	bool _isRunning;
	bool page1 = true;


private:
	

	bool _zmqLoopFlag;               //zmq data parse iþlemini yapýp yapmama  
	bool _loginPageVisibility;

	void ZMQDataStreamParser();       // parse iþlemi private onun için burda yoksa yukarý da yazabilirdik
	
};


#endif