# kWayMergeSort
N uzunluğunda, rastgele üretilen dizilerle çalışmayı içeriyor. 

Bu diziler benzersiz (unique) sayılardan oluşmalı ve farklı k değerlerine göre k-way merging algoritması kullanılarak
sıralanmalıdır. Bu sıralama işlemi, MergeSort algoritması kullanılarak yapılacaktır. Ayrıca,
çözümde farklı N ve k değerleriyle çalışma süresi ölçümleri yapılacaktır.

N: Dizi uzunluğu (10, 100, 1000, 10000, 100000, 1000000, 10000000 gibi değerler alabilir).
k: k-way merging işlemi için birleştirilecek dizilerin sayısı. (2 ≤ k ≤ N)

Kullanılan algoritmalar ve yaklaşımlar şunlardır:
1. Benzersiz Sayıların Rastgele Üretilmesi (Fisher-Yates algoritması): Başlangıçta, N uzunluğunda
diziler oluşturulacaktır. Bu diziler 1..N aralığında benzersiz (unique) rastgele sayılardan
oluşacak ve her bir dizinin elemanları birbirinden farklı olacaktır. Bu sebeple dizilerin unique
olmasının kontrol edilmesinde N için büyük sayılarda sorun yaşanmış bu sebeple Fisher-Yates
algoritması kullanılmıştır

2. MergeSort Algoritması: Dizilerin sıralanması için MergeSort algoritması kullanılacaktır.
MergeSort, Divide and Conquer (Böl ve Yönet) yaklaşımını kullanarak diziyi iki alt diziye böler,
her alt diziyi sıralar ve sonra bu iki sıralı alt diziyi birleştirir. Bu işlem rekürsif olarak devam eder
ve sonunda sıralanmış bir dizi elde edilir.

3. k-Way Merge Algoritması: Sıralanmış diziler daha sonra k-way merging işlemi ile
birleştirilecektir. Burada, k sayısı kadar sıralı diziyi birleştirmek için her dizinin en küçük
elemanı karşılaştırılır ve en küçük olanı sonuç dizisine eklenir. Bu işlem, tüm dizilerdeki
elemanlar tükenene kadar devam eder. Bu sayede k sayıda sıralı dizi tek bir sıralı diziye
dönüştürülür.

4. Deneysel Analiz ve Performans Ölçümü: Farklı N ve k değerleri için çalışma süreleri ölçülüp
karşılaştırılacaktır. Bu ölçümler, dizilerin uzunluğu ve k-way merge işlemi sayısının artmasıyla
algoritmanın performansını gözlemlememize olanak tanıyacaktır.

Genel Karmaşıklık

Time Complexity (Overall): O(N log(N/k) + N log k + maxValue). //Diziyi oluşturma (maxValue),
kWayMergeSort işlemi ve sıralama süreçleri hesaba katılarak oluşturulmuştur.

Space Complexity (Overall): O(N + k + maxValue). Diziyi sıralamak için kullanılan geçici diziler ve
generateRandomArray'deki tempArray dizisi nedeniyle bu bellek karmaşıklığına sahiptir.
