#ifndef DFG_H   // bu kütüphaneye birden fazla yerden çagýrmak için  Ýsimlendirmenini kýsaltmasý þeklinde yazdýk burdaki ismi
#define DFG_H    

#include <iostream>
#include <zmq.h>

class TakeDatasString {
public:
    int x;           //x konum
    int y;           // y konum
    float a;           // açý
    int ws;          // yazýlan hýz
    int rs;          // okunan hýz 
    float wwa;         // yazýlan teker açýsý 
    float rwa;         // okunan teker açýsý 

};

void Demo_RealtimePlots();  // cpp dosyasýnda bulunan foksiyonu buraya çagýrýyoruz.  sonrasýnda da main tarafýndan çaðýracagýz 
                           
	

#endif