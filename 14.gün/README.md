# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Verileri görselleştirme

Bugünkü konumuz forkliften gelen verileri almak benim görevim ise görselleştirmek. Forkliften 7 tane veri geliyor şuan için realtime alıp grafikte gösterebiliyorum. Aşağıda kodunu yazdım x, y, a, ws, rs, wwa, rwa veriler ise bunlar 




  	std::string delimiter = ";";
    	size_t pos = 0;
    	std::string token;
   	 while ((pos = msg.find(delimiter)) != std::string::npos) {
       	 token = msg.substr(0, pos);
       	 switch (pos) {
        	case 0:
          	  dataa.x = (int)token;
          	  break;
        case 1:
            dataa.y = token;
            break;

        case 2:
            dataa.a = token;
            break;
        case 3:
            dataa.ws = token;
            break;

        case 4:
            dataa.rs = token;
            break;
        case 5:
            dataa.wwa = token;
            break;

        case 6:
            dataa.rwa = token;
            break;
        }



        msg.erase(0, pos + delimiter.length());
    }
class kısmı


    
	class take_data {
    	public:
      	  int x;
      	  int y;
       	 float a;
       	 int ws;
       	 int rs;
        	float wwa;
       	 float rwa;
       	 void yaz() {
          	  fprintf(stdout, " degerler atandı ");
        	};
   	 };


	if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, 150))) {
       	 ImPlot::SetupAxes(NULL, NULL, flags, flags);
        ImPlot::SetupAxisLimits(ImAxis_X1, t - history, t, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
        ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
        ImPlot::PlotShaded("Mouse X", &sdata1.Data[0].x, &sdata1.Data[0].y, sdata1.Data.size(), -INFINITY, 0, sdata1.Offset, 2 * sizeof(float));
        ImPlot::PlotLine("Mouse Y", &sdata2.Data[0].x, &sdata2.Data[0].y, sdata2.Data.size(), 0, sdata2.Offset, 2 * sizeof(float));
        ImPlot::EndPlot();
  	  }


Bugünkü kazanımlarım
- Veri görselleştirmeyi öğrendim











































 	







 





