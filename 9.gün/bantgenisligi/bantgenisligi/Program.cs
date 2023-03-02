using System;
using System.Net.Sockets;

public static void bantgenisligi(string ipAddress, int port, string message)
{
    try
    {
        TcpClient client = new TcpClient(ipAddress, port);

        Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);

        NetworkStream stream = client.GetStream();

        stream.Write(data, 0, data.Length);

        Console.WriteLine("Mesaj gönderildi: {0}", message);

        data = new Byte[256];

        String responseData = String.Empty;

        Int32 bytes = stream.Read(data, 0, data.Length);
        responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
        Console.WriteLine("Sunucudan cevap alındı: {0}", responseData);

        stream.Close();
        client.Close();
    }
    catch (ArgumentNullException e)
    {
        Console.WriteLine("ArgumentNullException: {0}", e);
    }
    catch (SocketException e)
    {
        Console.WriteLine("SocketException: {0}", e);
    }
}