# İşyeri Eğitimi


## Yapılan Çalışmanın Konusu :    Logviewer limit işlemindeki hataların çözümü 

Bugünkü staj konum logviewrdaki hataların çözümüydü. Bugünkü hatamız limit kısmının çalışmamasıydı limit değerini aktif hale getirip gelen değerleri de ona göre düzenledim.

Bu kodu ekleyerek sorunun önüne geçtim

   _totalDocuments = await collection.CountDocumentsAsync(filter);
                _totalPages = (int)Math.Ceiling((double)_totalDocuments / _pageSize);

                // lastpagedatacount => son sayfadaki veri adedi
                if (limit > 0)
                {
                    var lastpagedatacount = limit % _pageSize;
                    if (lastpagedatacount != 0)
                    {
                        _totalPages = (limit / _pageSize) + 1;
                    }
                    _totalDocuments = limit;

                    if (_pageNumber == _totalPages)
                    {
                        _pageSize = lastpagedatacount;
                    }
                }

Burda limit değerini giriyoruz

 ![image](https://github.com/omerkonca/isyeriegitimi/assets/65457096/617c0704-108a-4c26-8cc7-dc48bfac0f8c)



Burda da girilen limit değerine göre bize sayfalama yapıyor
 
![image](https://github.com/omerkonca/isyeriegitimi/assets/65457096/25058c9a-cf12-45b0-9244-881967cf6724)




Bugünkü kazanımlarım
-	Algoritmik düşünmemi geliştridim

















































 








Tarih : 06/06/ 2023

 
















































 	







 





