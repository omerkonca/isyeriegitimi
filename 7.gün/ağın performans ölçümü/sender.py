import socket

# Gönderici ve alıcı IP adresleri ve port numaraları
sender_ip = "192.168.1.10"
receiver_ip = "192.168.1.20"
port = 12345

# Soket oluşturma ve bağlantıyı ayarlama
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((sender_ip, port))
s.listen(1)
conn, addr = s.accept()

# Bağlantı başarılı oldu
print("Connected by", addr)

# Veri gönderme
data = "Hello, world!"
conn.sendall(data.encode())

# Bağlantıyı kapatma
conn.close()
s.close()