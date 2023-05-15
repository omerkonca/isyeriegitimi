# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :    Mongodb veritabanını c++ entegre işlemi

Öncelikle CMake'i kuruyoruz. Sonra Python 3'ü kuruyoruz
C++ Sürücüsü, C sürücüsüne bağımlıdır. Bu nedenle, önce C Sürücüsünü kurmamız gerekiyor.
C Sürücüsünü İndiriyoruz
Windows - mongocxx sürücüsünü yüklüyoruz
Sürücünün indirilmesi için.
Sürüm tarball'ını indiriyoruz
Sürümler · mongodb/mongo-c-driver ve onu C:\Repos\mongo-c-driver-1.23.0 konumuna çıkarıyoruz.
Kurulumu CMake aracılığıyla yapıyoruz.
powershell/terminal'i yönetici olarak başlatıp. C:\Repos\mongo-c-driver-1.23.0 konumuna gidip ve derleme dosyaları için cmake-build adlı yeni bir klasör oluşturuyoruz.
C: \Repos\mongo-c-driver-1.23.0\cmake-build konumuna gidiyoruz.
Yapı dosyalarını CMake kullanarak yapılandırmak ve oluşturmak için aşağıdaki komutu çalıştırıyoruz.
cmake -G "Visual Studio 17 2022" -A x64 -S "C:\Repos\mongo-c-driver-1.23.0" -B "C:\Repos\mongo-c-driver-1.23.0\cmake-build"
 

![image](https://github.com/omerkonca/isyeriegitimi/assets/65457096/219a8bb2-8c28-40c2-937c-4a58f97da0a7)


Sürücüyü oluşturmak ve yüklemek için aşağıdaki komutu çalıştırıyoruz
cmake --build . --config RelWithDebInfo --target install
ve bu şekilde derleniyor

 
![image](https://github.com/omerkonca/isyeriegitimi/assets/65457096/54ce6ae1-4980-4888-8cfd-8f7f5ba76099)


Bugünkü kazanımlarım
-	Mongodb yi c++ a derlemeyi öğrendim



























































 








Tarih : 09 /03/ 2023

 
















































 	







 





