# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu : Arayüz tasarımı

Bugünün çalışmasını planladık bana düşen iş ise dün yarım kalan arayüz tasarımı idi ben de ona devam etmeye başladım ve günüm o şekilde geçti
 aşağıda yazdığım kodlar göstereceğim

	ImGui::Begin("PAGE", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);  //, &no_collapse
   
            // Pencere başlığı ve IP adresi giriş kutusu
            ImGui::Text("                                                       Enter IP Address");
            ImGui::Spacing();

            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(" ", NULL, true).x) / (1, 5));
            ImGui::InputText(" ", ipAddress, 32, ImGuiInputTextFlags_CharsNoBlank);

            ImGui::Spacing();

            // IP adresi girişi ve "Login" düğmesi
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Login", NULL, true).x) / 2);

            // IP adresi girişi ve "Login" düğmesi
            if (ImGui::Button("Login")) {
                // IP adresi doğrulama
                std::regex ip_regex("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
                if (!std::regex_match(ipAddress, ip_regex)) {
                    ImGui::OpenPopup("Uyari");
                }
                else {
                    // Login düğmesine tıklandığında, saklanan IP adresi ile diğer sayfaya geçme
                    std::cout << "Entered IP Address:" << ipAddress << std::endl;
                    ImGui::OpenPopup("New Page");
                    page1 = false;
                }
            }

Yazdığım kod bu şekilde bu kodda kullanıcı bi rip adres giriyor ve ip adres kontrol ediliyor yazımı uygunmu diye, uygunsa diğer sayfaya geçiş yapıyor o şekilde çalışıyor.

Bugünkü kazanımlarım
- Arayüz tasarımında kendimi geliştirdim























 	







 





