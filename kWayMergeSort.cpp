#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <memory>
#include <algorithm>

#define ARRAY_COUNT 10 // �retilen dizi say�s�
#define MAX(a, b) ((a) > (b) ? (a) : (b)) // �ki de�erden b�y���n� se�mek i�in kullan�lan makro

using namespace std;

// Rastgele ve unique dizi olu�turma fonksiyonu
// @param array: Rastgele say�larla doldurulacak dizi
// @param N: Dizinin eleman say�s�
// @param maxValue: Rastgele say�lar�n alabilece�i en y�ksek de�er
void generateRandomArray(vector<int>& array, int N, int maxValue) {
    vector<int> tempArray(maxValue);

    // 0'dan maxValue'ye kadar say�lar� tempArray'e ekleyin
    for (int i = 0; i < maxValue; i++) {
        tempArray[i] = i;
    }

    // Fisher-Yates Shuffle algoritmas� ile tempArray kar��t�rma i�lemi
    for (int i = maxValue - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(tempArray[i], tempArray[j]);
    }

    // �lk N eleman� kopyalayarak unique ve rastgele bir dizi elde et
    array.assign(tempArray.begin(), tempArray.begin() + N);
}

// Tek bir dizi �zerinde merge i�lemi
// @param array: Birle�tirilecek ana dizi
// @param left, right: Birle�tirilecek b�l�m�n ba�lang�� ve biti� indeksleri
// @param mid: Dizinin ortas�n� belirleyen indeks
void merge(vector<int>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Sol ve sa� alt diziler i�in bellek ay�rma
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = array[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = array[mid + 1 + i];

    // Birle�tirme i�lemi
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

// K���k par�alar i�in klasik merge sort i�levi
void mergeSort(vector<int>& array, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}

// K-way birle�tirme i�in �zel bir merge sort
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

    cout << "Dizi uzunlu�unu (N) girin: ";
    cin >> N;

    int maxValue = N * 2;
    srand(time(NULL));

    vector<vector<int>> arrays(ARRAY_COUNT, vector<int>(N));

    cout << "\nOlu�turulan 10 adet rastgele dizi:\n";
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
        cout << "\nS�ralamak istedi�iniz diziyi se�in (1-" << ARRAY_COUNT << " aras�nda): ";
        cin >> selectedArray;

        if (selectedArray < 1 || selectedArray > ARRAY_COUNT) {
            cout << "Ge�ersiz se�im. L�tfen 1 ile " << ARRAY_COUNT << " aras�nda bir de�er girin.\n";
            continue;
        }

        cout << "\nk de�erini girin: ";
        cin >> k;

        if (k < 2 || k > N) {
            cout << "Ge�ersiz k de�eri.\n";
            continue;
        }

        vector<int> result(arrays[selectedArray - 1]);

        clock_t startTime = clock();
        kWayMergeSort(result, 0, N - 1, k);
        clock_t endTime = clock();

        double timeTaken = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000;
        cout << "\n" << k << "-way birle�tirme sonucu:\n";

        for (int i = 0; i < N; i++) {
            cout << result[i] << " ";
        }
        cout << "\n�al��ma s�resi: " << timeTaken << " milisaniye\n";

        cout << "Ba�ka bir dizi veya k de�eri denemek istiyor musunuz? (E/e: Evet, H/h: Hay�r): ";
        cin >> continueChoice;

    } while (continueChoice == 'E' || continueChoice == 'e');

    return 0;
}
