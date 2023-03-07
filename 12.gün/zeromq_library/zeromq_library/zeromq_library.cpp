#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://localhost:5555");

    zmq::message_t request(5);
    memcpy(request.data(), "Merhaba", 5);
    socket.send(request);

    zmq::message_t response;
    socket.recv(&response);
    std::cout << "Gelen Yanıt: " << std::string(static_cast<char*>(response.data()), response.size()) << std::endl;

    return 0;
}
