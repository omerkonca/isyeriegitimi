# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :Position kısmı revize işlemleri

Bugünkü görevim mouse tıkladığımızda 1.noktayı alıp, 2.tıkladığımızdada 2.noktayı alıp arasına çizgi çizmek ve bunuda ctrl tuşuna basarak yapmaktı ve başarılı bir şekilde yaptım. Ve aynı zamanda bir checkbox ekleyip checkbox a tıklayınca çizgi çizebiliyoruz basmazsak hiçbir işlem yapamıyoruz.

Kodumu aşağıya ekledim

	if (drawLine && ImGui::IsMouseClicked(0) && ImGui::GetIO().KeyCtrl)
	{
		if (point1.x == 0.0f && point1.y == 0.0f)
		{
			point1 = ImPlot::GetPlotMousePos();
		}
		else
		{
			point2 = ImPlot::GetPlotMousePos();
			ImPlot::GetPlotDrawList()->AddLine(
			ImPlot::PlotToPixels(ImPlotPoint(point1)),
			ImPlot::PlotToPixels(ImPlotPoint(point2)),
			IM_COL32(255, 0, 0, 255)
			);
			ImPlot::GetPlotDrawList()->AddLine(ImPlot::PlotToPixels(ImPlot::PlotToPixels(point1)), ImPlot::PlotToPixels(point2), IM_COL32(255, 0, 0, 255));
			point1 = ImVec2(0.0f, 0.0f);
			//point2 = ImVec2(0.0f, 0.0f);
		}
	}



Uzunluk hesaplaması da bu şekilde

	float dx = point1.x - point2.x;
	float dy = point1.y - point2.y;
	float distance = sqrt(dx * dx + dy * dy);





Bugünkü kazanımlarım
-	Mouse değişkenlerini kullanmayı öğrendim
























 














 	







 





