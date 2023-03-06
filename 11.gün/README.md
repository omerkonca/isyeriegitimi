# GG Computer Kullanıcı Testi

## İlk test  “crystal disk mark” kullanaraktan yapılmıştır . CrystalDiskMark sonuçları megabayt / saniye (MB/s) ve saniye başına girdi çıktı (IOPS) cinsinden görüntülenir.  CrystalDiskMark sonuçlarındaki Seq Q32T1 sıralı okuma yazma sonuçlarını, 4KiB Q8T8 ise rastgele okuma yazma sonuçlarını gösterir. 4KiB Q8T8, disk performansını test etmek için 4K dosya boyutunu kullanır.
![image](https://user-images.githubusercontent.com/65457096/223126487-8d18c3af-f28a-4cab-b3ef-f4eb2865e958.png)


 

## Bu sonuçlara bakıldığında Bilgisayarın okuma-yazma işleminde gayet memnun edici bir performans ortaya koymuştur.



## İkinci test olarak intellij ,anaconda gibi yüksek bellek tüketen idelerin kurulup ,kullanılması ve sonuç olarak çok memnun edici bir kullanım sunulduğu görülmektedir.  



## Özellikle alınan bu performanslardan sonra batarya tüketimine bakıldığında kabul edilebilir bir tüketim mevcut .Şarj olarak %100 iken sarjdan çıkartılıp batarya düzeyinde 2-2,5 saat arası kullanım vermektetir  (pil kullanımı orta bir şekilde kullanılmıştır .ne exrta performans ne de extra pil kullanımda kullanılmamıştır.)
## Üçüncü test olarak yapay zeka modeli eğittik .Yapay zeka da bir model eğitmek gerçekten cok zaman alan ve aynı şekilde çokta bellek isteyen bir alan . normalde i7 9.nesil 8 gb ram 512 ssd 6 çekirdekli bir monster pc ile kıyaslama yaptığımızda.epoch(model eğitimi tur sayısı) monster bilgisayarda ortlama 900 sn de bir tur atmakta .ancak bu bilgisayarda 450 sn gibi ortalama bir değer de cıktı vermekte bu açıdan her bir turda ortalama 7 dk fark yaratıyor ve bu ciddi bir zaman kazancı . 

## Tabi bu testi bilgisayar şarjda iken yapmaktayız. Bundan dolayı CPU Hızı maximum seviyede çalışmasına rağmen ortalama 3.00 GHz  de 30 dk gibi bir sürede  çalıştı .bu model eğitimini yaparken dışardan hiçbir müdahale yapmadan bilgisayarın ısısı 61 °C  cıktı ,özellikle klavyenin üst kısımlarında yüksek denebilecek isi oluştu.
 ![image](https://user-images.githubusercontent.com/65457096/223126574-7da126df-9b88-4672-9af9-73226ca5f732.png)



## Bu oluşan sıcaklıktan sonra fn+yukarı yön tuşuyla extra fan kısmını açtık ve onla beraber 8 dk gibi bir sürede sıcaklık 48 °C kadar indi ve klavyenin üst kısımlarında yüksek sıcaklık baya azaltı.

## Pc şarjda değilken ve Pil düzeyi %20 altında iken performansa düşmeler olmakta CPU kullanımı %37 civarlarında hız olarakta 1.07 GHz hızında idi .

## ÖZETLE ;
## Performans olarak ,kullanım olarak gayet kullanışlı ve hızlı bir bilgisayar .ancak kendi sistem insiyatifine bırakırsak yüksek  devirde fan çalıştırmadığı için ısınma problemi var .manuel olarak fan aktif edilirse ısınma probleminin de önüne geçilebilecegini düşünmekteyiz .


