# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Position verilerinin Parse işlemi 

Bugün position kısmından gelen veriler sayısal tipte geldiği için önce json formatına çevirmek için araştırma yaptım daha sonra öğrendiğim kadarıyla birazda benle ilgilenen yazılımcı abiyle gelen verileri jsona çevirdik ve daha sonra bütün verileri parse ettik 
bu şekilde

	else if (std::strcmp("route", zmq_topic_data) == 0)
	{
	doc.Parse(zmq_message_data);

	if (doc.HasParseError()) {
		continue;
	}
	this->AgvPositionGraphic->Erase();

	for (itr = doc.Begin(); itr != doc.End(); ++itr)
				{
   	this->AgvPositionGraphic->Route.AddPoint(itr->GetObject()["X"].GetFloat(), itr->GetObject()["Y"].GetFloat());
				}
			}
	else if (std::strcmp("sim", zmq_topic_data) == 0) {

	doc.Parse(zmq_message_data);

	if (doc.HasParseError()) {
			continue;
		}
	for (itr = doc.Begin(); itr != doc.End(); ++itr)
	{
    this->AgvPositionGraphic->Simu.AddPoint(itr->GetObject()["X"].GetFloat(), itr->GetObject()["Y"].GetFloat());
				}
			}
	else if (std::strcmp("curve", zmq_topic_data) == 0) {

	doc.Parse(zmq_message_data);

	if (doc.HasParseError()) {
	continue;
			}

	for (itr = doc.Begin(); itr != doc.End(); ++itr)
		{
	this->AgvPositionGraphic->Curve.AddPoint(itr->GetObject()["X"].GetFloat(), itr->GetObject()["Y"].GetFloat());
				}
	}
	else if (std::strcmp("cell", zmq_topic_data) == 0) {
			doc.Parse(zmq_message_data);

	if (doc.HasParseError()) {
					continue;
		}









 














 	







 





