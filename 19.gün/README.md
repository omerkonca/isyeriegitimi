# İşyeri Eğitimi

## Yapılan Çalışmanın Konusu : Gelen dataları parse işlemi 

Bugün forkliften gelen verileri parse etmem istendi bende ilk önce araştırma yaptım nasıl parse edilir otarz sayfaları inceledim ve parse işleminin mantığını anladım ve verileri parse ederek ayırmış oldum aşağıdada kodu şu şekilde

    while (this->_zmqLoopFlag)
	  {
		rc = zmq_recv(subscriber, topic, topic_size, 0);
		if (rc != -1)
			fprintf(stdout, "TOPIC: %s \n", topic);

		rc = zmq_recv(subscriber, msg, msg_size, 0);
		if (rc != -1) {
			if (topic == "real")         //gelen veri tipine göre parse iþlemi yapacak 
			{
				if (std::strcmp("real", topic) == 0) {
					pch = strtok(msg, ";");
					while (pch != NULL)
					{
						if (sayac == 0) {
							Agv->X = stoi(pch);
							sayac++;

						}
						else if (sayac == 1) {
							Agv->Y = stoi(pch);
							sayac++;

						}
						else if (sayac == 2) {
							Agv->Angle = std::stof(pch);
							sayac++;

						}
						else if (sayac == 3) {
							Agv->WSpeed = stoi(pch);
							sayac++;

						}
						else if (sayac == 4) {
							Agv->RSpeed = stoi(pch);
							sayac++;

						}

						//printf("%s\n", pch);
						pch = strtok(NULL, ";");
					}	
          
Bugünkü kazanımlarım
- data parse işlemini öğrendim





