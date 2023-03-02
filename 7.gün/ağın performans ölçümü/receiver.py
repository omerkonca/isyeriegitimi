import socket

# Gönderici ve alıcı IP adresleri ve port numaraları
sender_ip = "192.168.1.10"
receiver_ip = "192.168.1.20"
port = 12345

# Soket oluşturma ve bağlantıyı ayarlama
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((sender_ip, port))

# Veri alma
data = s.recv(1024)

# Veriyi ekrana yazdırma
print("Received", repr(data.decode()))

# Bağlantıyı kapatma
s.close()