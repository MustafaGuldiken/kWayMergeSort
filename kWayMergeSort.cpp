#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <memory>
#include <algorithm>

#define ARRAY_COUNT 10 // Üretilen dizi sayýsý
#define MAX(a, b) ((a) > (b) ? (a) : (b)) // Ýki deðerden büyüðünü seçmek için kullanýlan makro

using namespace std;

// Rastgele ve unique dizi oluþturma fonksiyonu
// @param array: Rastgele sayýlarla doldurulacak dizi
// @param N: Dizinin eleman sayýsý
// @param maxValue: Rastgele sayýlarýn alabileceði en yüksek deðer
void generateRandomArray(vector<int>& array, int N, int maxValue) {
    vector<int> tempArray(maxValue);

    // 0'dan maxValue'ye kadar sayýlarý tempArray'e ekleyin
    for (int i = 0; i < maxValue; i++) {
        tempArray[i] = i;
    }

    // Fisher-Yates Shuffle algoritmasý ile tempArray karýþtýrma iþlemi
    for (int i = maxValue - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(tempArray[i], tempArray[j]);
    }

    // Ýlk N elemaný kopyalayarak unique ve rastgele bir dizi elde et
    array.assign(tempArray.begin(), tempArray.begin() + N);
}

// Tek bir dizi üzerinde merge iþlemi
// @param array: Birleþtirilecek ana dizi
// @param left, right: Birleþtirilecek bölümün baþlangýç ve bitiþ indeksleri
// @param mid: Dizinin ortasýný belirleyen indeks
void merge(vector<int>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Sol ve sað alt diziler için bellek ayýrma
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = array[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = array[mid + 1 + i];

    // Birleþtirme iþlemi
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            array[k++] = leftArr[i++];
        }
        else {
            array[k++] = rightArr[j++];
        }
    }

    while (i < n1) array[k++] = leftArr[i++];
    while (j < n2) array[k++] = rightArr[j++];
}

// Küçük parçalar için klasik merge sort iþlevi
void mergeSort(vector<int>& array, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}

// K-way birleþtirme için özel bir merge sort
void kWayMergeSort(vector<int>& array, int left, int right, int k) {
    if (left >= right) return;

    if (right - left + 1 <= k) {
        mergeSort(array, left, right);
        return;
    }

    int segmentSize = (right - left + 1) / k;
    int remainder = (right - left + 1) % k;
    int start = left;

    vector<int> segmentEnds(k);

    for (int i = 0; i < k; i++) {
        segmentEnds[i] = start + segmentSize - 1 + (i < remainder ? 1 : 0);
        kWayMergeSort(array, start, segmentEnds[i], k);
        start = segmentEnds[i] + 1;
    }

    vector<int> temp(right - left + 1);
    vector<int> indices(k);

    for (int i = 0; i < k; i++) indices[i] = (i == 0 ? left : segmentEnds[i - 1] + 1);

    for (int i = left; i <= right; i++) {
        int minIndex = -1;
        for (int j = 0; j < k; j++) {
            if (indices[j] <= segmentEnds[j] && (minIndex == -1 || array[indices[j]] < array[indices[minIndex]])) {
                minIndex = j;
            }
        }
        temp[i - left] = array[indices[minIndex]];
        indices[minIndex]++;
    }

    for (int i = left; i <= right; i++) array[i] = temp[i - left];
}

// Ana fonksiyon
int main() {
    setlocale(LC_ALL, "Turkish");
    int N, k;

    cout << "Dizi uzunluðunu (N) girin: ";
    cin >> N;

    int maxValue = N * 2;
    srand(time(NULL));

    vector<vector<int>> arrays(ARRAY_COUNT, vector<int>(N));

    cout << "\nOluþturulan 10 adet rastgele dizi:\n";
    for (int i = 0; i < ARRAY_COUNT; i++) {
        generateRandomArray(arrays[i], N, maxValue);

        cout << "Dizi " << i + 1 << ": ";
        if (N > 100) {
            for (int j = 0; j < 5; j++) {
                cout << arrays[i][j] << " ";
            }
            cout << "... ";
            for (int j = N - 5; j < N; j++) {
                cout << arrays[i][j] << " ";
            }
        }
        else {
            for (int j = 0; j < N; j++) {
                cout << arrays[i][j] << " ";
            }
        }
        cout << "\n";
    }

    char continueChoice;
    do {
        int selectedArray;
        cout << "\nSýralamak istediðiniz diziyi seçin (1-" << ARRAY_COUNT << " arasýnda): ";
        cin >> selectedArray;

        if (selectedArray < 1 || selectedArray > ARRAY_COUNT) {
            cout << "Geçersiz seçim. Lütfen 1 ile " << ARRAY_COUNT << " arasýnda bir deðer girin.\n";
            continue;
        }

        cout << "\nk deðerini girin: ";
        cin >> k;

        if (k < 2 || k > N) {
            cout << "Geçersiz k deðeri.\n";
            continue;
        }

        vector<int> result(arrays[selectedArray - 1]);

        clock_t startTime = clock();
        kWayMergeSort(result, 0, N - 1, k);
        clock_t endTime = clock();

        double timeTaken = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000;
        cout << "\n" << k << "-way birleþtirme sonucu:\n";

        for (int i = 0; i < N; i++) {
            cout << result[i] << " ";
        }
        cout << "\nÇalýþma süresi: " << timeTaken << " milisaniye\n";

        cout << "Baþka bir dizi veya k deðeri denemek istiyor musunuz? (E/e: Evet, H/h: Hayýr): ";
        cin >> continueChoice;

    } while (continueChoice == 'E' || continueChoice == 'e');

    return 0;
}
