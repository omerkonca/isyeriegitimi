# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Position kısmı revize işlemleri 2 
Bugün position kısmına devam ediyorum. Dün yazdığım kodlarımı tamamen değiştirdim bugün biraz daha clean code yapısına çevirdim ayrıca begintooltip yapısıda ekledim. Begintooltip yapısının amaci fareyle çizginin üzerine geldiği zaman uzunluğu göstermesi. Ek olarak clear line diye bir buton ekledim ona bastığımız zaman çizgiyi siliyor ve bu şekilde daha kullanışlı oldu. Ve daha benden bi görev daha istendi ve istenen görev ise çizgilerin uçları çarpı işareti olmasıydı ve onuda çizginin kordinatlarını alarak başarılı bir şekilde ekledim.



	if (cnt == 2) 
	{

	const float arrowSize = 10.0f;
	const ImVec2 p1 = ImPlot::PlotToPixels(ImPlotPoint(point1));
	const ImVec2 p2 = ImPlot::PlotToPixels(ImPlotPoint(point2));
	const ImVec2 dir = ImVec2(p2.x - p1.x, p2.y - p1.y);
	const float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
	const ImVec2 norm = ImVec2(dir.x / len, dir.y / len);
	const ImVec2 perp = ImVec2(-norm.y, norm.x);

	//ImPlot::GetPlotDrawList()->AddLine(p1, p2, IM_COL32(255, 0, 0, 255), 3.0f);
	ImPlot::GetPlotDrawList()->AddLine(
		ImPlot::PlotToPixels(ImPlotPoint(point1)),
		ImPlot::PlotToPixels(ImPlotPoint(point2)),
		IM_COL32(255, 0, 0, 255), 
		3.0f
	);
			
	const float crossSize = 4.0f;
	ImPlot::GetPlotDrawList()->AddLine(ImVec2(p1.x + perp.x * crossSize, p1.y + perp.y * crossSize), ImVec2(p1.x - perp.x * crossSize, p1.y - perp.y * crossSize), IM_COL32(255, 255, 255, 255), 1.5f);
	ImPlot::GetPlotDrawList()->AddLine(ImVec2(p1.x + perp.x * crossSize, p1.y - perp.y * crossSize), ImVec2(p1.x - perp.x * crossSize, p1.y + perp.y * crossSize), IM_COL32(255, 255, 255, 255), 1.5f);

	ImPlot::GetPlotDrawList()->AddLine(ImVec2(p2.x + perp.x * crossSize, p2.y + perp.y * crossSize), ImVec2(p2.x - perp.x * crossSize, p2.y - perp.y * crossSize), IM_COL32(255, 255, 255, 255), 1.5f);
	ImPlot::GetPlotDrawList()->AddLine(ImVec2(p2.x + perp.x * crossSize, p2.y - perp.y * crossSize), ImVec2(p2.x - perp.x * crossSize, p2.y + perp.y * crossSize), IM_COL32(255, 255, 255, 255), 1.5f);

	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::Text("Line Length: %.2f", distance);
		ImGui::EndTooltip();
	}
	}



![image](https://user-images.githubusercontent.com/65457096/228814796-b85536b4-4a22-4639-a350-49f148d20c2c.png)
 

![image](https://user-images.githubusercontent.com/65457096/228814840-439ab581-e2e4-46b6-a964-ca2520ed61a5.png)


Bugünkü kazanımlarım
-	Begintooltip yapısını öğrendim ve uyguladım











 














 	







 





