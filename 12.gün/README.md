# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Zeromq kütüphanesinin araştırılması

Ben bu kütüphaneyi otonom forkliftimize veri aktarımı yaparken kullanmak için araştırıyorum. Öğrenip gerçek zamanlı uygulayacağım ve aşağıda kütüphaneni ne işe yaradığını hangi amaçla kullanıldığını yazdım.

Zeromq kütüphanesi
ZeroMQ (ZMQ), dağıtık ve paralel programlama için kullanılan bir mesajlaşma kütüphanesidir. ZMQ, TCP/IP, InfiniBand, multicast, Inter-Process Communication (IPC) ve diğer iletişim protokollerini destekler ve farklı programlama dillerinde kullanılabilir. Kullanıcıların farklı cihazlar arasında veri alışverişinde bulunmasını sağlar. ZeroMQ, hafif, hızlı ve ölçeklenebilir bir yapıya sahiptir. Ayrıca, ZMQ'nun özellikleri arasında güvenlik, yüksek kullanılabilirlik, esneklik ve farklı topolojilerde çalışabilme kabiliyeti bulunur. ZMQ, dağıtık sistemler, bulut hesaplama, Big Data işleme, oyun yazılımı ve diğer alanlarda kullanılmaktadır.

Aşağıda şekilde kullanımı vardır server ve client şeklinde bi taraf mesaj gönderiyor diğer taraf dinliyor.

Server

	#include <zmqpp/zmqpp.hpp>
	#include <string>
	#include <iostream>
	#include <chrono>
	#include <thread>

	using namespace std;

	int main(int argc, char *argv[]) {
  	const string endpoint = "tcp://*:5555";

  	// initialize the 0MQ context
  	zmqpp::context context;

  	// generate a pull socket
  	zmqpp::socket_type type = zmqpp::socket_type::reply;
  	zmqpp::socket socket (context, type);

  	// bind to the socket
  	socket.bind(endpoint);
  	while (1) {
   	 // receive the message
   	 zmqpp::message message;
   	 // decompose the message 
   	 socket.receive(message);
   	 string text;
   	 message >> text;

   	 //Do some 'work'
   	 std::this_thread::sleep_for(std::chrono::seconds(1));
   	 cout << "Received Hello" << endl;
   	 socket.send("World");
 	 }

	}
	
Client 

	#include <zmqpp/zmqpp.hpp>
	#include <string>
	#include <iostream>

	using namespace std;

	int main(int argc, char *argv[]) {
 	 const string endpoint = "tcp://localhost:5555";

 	 // initialize the 0MQ context
  	zmqpp::context context;

  	// generate a push socket
 	 zmqpp::socket_type type = zmqpp::socket_type::req;
 	 zmqpp::socket socket (context, type);

 	 // open the connection
 	 cout << "Connecting to hello world server…" << endl;
 	 socket.connect(endpoint);
 	 int request_nbr;
 	 for (request_nbr = 0; request_nbr != 10; request_nbr++) {
   	 // send a message
   	 cout << "Sending Hello " << request_nbr <<"…" << endl;
   	 zmqpp::message message;
   	 // compose a message from a string and a number
  	  message << "Hello";
   	 socket.send(message);
	    string buffer;
    	socket.receive(buffer);
    
   	 cout << "Received World " << request_nbr << endl;
 	 }
	}

Kodu c++ bu şekilde yazılmaktadır. Ve daha birçok dil desteklemektedir zeromq kütüphanesini

Bugünkü kazanımlarım
- Zeromq kütüphanesini araştırdım, ne işe yaradığını ve nasıl kullanıldığını öğrendim.














 














 	







 





