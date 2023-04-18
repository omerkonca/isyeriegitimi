# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :  Agv kısmının düzenlenmesi 
Bugün haftanın ilk günü olduğu için toplantı yaptık. Haftalık neler yapacağımızı planladık. Bugün için görev belirledim kendime. Bugünkü görevim ise şu şekilde agv kısmında 5 tane grafik var mesela hepsini açtığım zaman dağınık gözüküyor onların hepsini düzenli olması lazım ve bir tane hizala diye buton yaparak o butona tıklayınca bütün grafiklerin hizalanmasını sağladım ve daha düzenli gözüktü.

kod bu şekilde

	ImVec2 ROTracer::GetLocation(int index) {
	int x = 50;
	int y = 20;
	int column = 3;

	//ImGuiContext& g = *GImGui;    --> bu'da yine pencere bilgisi almak için    
                                           oluşturabilecegimiz nesne 

	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	int cW = viewport->Size.x / column;
	DefaultWidth = cW;
	DefaultHeight = cW / 2;

	int pColumn = (index % column);
	x =  (cW * pColumn);
	y = 20 + DefaultHeight * (index / column);

	return ImVec2(x, y);
  	 }



Görüntü bu şekilde

 ![image](https://user-images.githubusercontent.com/65457096/232812233-8b25145a-5158-4d78-afe4-2f87ed21ce60.png)



Bugünkü kazanımlarım
-	Grafik hizalamayı öğrendim












 














 	







 





