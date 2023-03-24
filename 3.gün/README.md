# İşyeri Eğitimi

## Yapılan Çalışmanın Konusu: Opengl kütüphanesinin araştırılması ve öğrenilmesi 

Bugünkü çalışmam opengl hakkındaydı. İnternetten yapmış olduğum araştırmalar sonucunda opengl: gelişmiş donanım desteğini kullanarak hem iki hem de üç boyutlu grafikleri ekrana çizmek için kullanılan ücretsiz bir grafik uygulama geliştirme arabirimidir. Windows, Linux, MacOS ve Solaris gibi birçok işletim sisteminde yaygın olarak ve Playstation 3 başta olmak üzere bazı oyun konsollarınca destekleniyormuş.

Platform bağımsızdır
OpenGL kullanan bir programı işletim sisteminizde çalıştırmanız için öncelikle işletim sisteminizde programın çalışırken kullanacağı işlevleri içeren kitaplığın bulunması gerekir, bu kitaplıkların genel adı "runtime-library", türkçesi çalışma anı kitaplığıdır.

OpenGL çalışma anı kitaplığı Linux, Unix, Mac OS, OS/2, Windows 95/98/NT/2000, OPENStep ve BeOS işletim sistemlerinde halihazırda mevcuttur. Windows işletim sistemi ailesinde standart olarak gelir. Yani OpenGL kullanan bir programı çalıştırmak için bir çaba harcamazsınız.

Pencere yöneticisinden bağımsızdır
OpenGL kullanılarak yazılmış programlar, Win32, MacOS ve X-Window pencere yöneticilerinde sorunsuz çalışırlar.

Birçok programlama dilinde kullanılabilir
Ada, C, C++, C# (SharpGL adı verilen sınıflar sayesinde), Fortran, Python, Perl ve Java programlama dilleri kullanılarak OpenGL kitaplığından faydalanılabilir.

Aynı zamanda cmake kavramınıda araştırdım oda şu şekilde: CMake yazılım inşa sürecinin derleyiciden bağımsız olarak otomasyonu için kullanılan çapraz-platform ve açık kaynak kodlu yazılım. Çoklu kütüphane kullanan uygulamaları ve dizin hiyerarşisini destekler. Make, Apple Xcode ve Microsoft Visual Studio gibi yerli inşa ortamlarıyla birlikte kullanılır.



Yazmış olduğum cmake komutları

cmake_minimum_required(VERSION 2.8)

project(OpenGLDers)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
			${PROJECT_SOURCE_DIR}/kutuphane.cpp
			${PROJECT_SOURCE_DIR}/main.cpp)

set(PROJECT_HEADERS
			${PROJECT_INCLUDE_DIR}/kutuphane.hpp)

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

Bugünkü kazanımlarım
-Opengl kütüphanesi öğrenildi




