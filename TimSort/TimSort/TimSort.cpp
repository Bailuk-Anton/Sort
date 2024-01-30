#include <conio.h>
#include <iostream>
#include <stack>
#include <ctime>
using namespace std;

class LAB2
{
public:
	int* adres, index, size;
	void CreateArr(int num)
	{
		adres = new int[num];
		size = num;
		for (unsigned int i = 0; i < size; i++) {
			adres[i] = i;
		}
	}
	void PrintArr()
	{
		cout << endl << "Array:\n";
		for (unsigned int i = 0; i < size; i++) {
			cout << i + 1 << ". " << *(adres + i) << "\n";
		}
	}
	void DeleteArr()
	{
		delete[]adres;
		size = 0;
	}
	void AddArr(int value)
	{
		int* adres1 = new int[size + 1];
		for (unsigned int i = 0; i < size; i++) {
			adres1[i] = adres[i];
		}
		size++;
		adres1[size - 1] = value;
		adres = adres1;
	}
	void GetArr(int num) {
		cout << *(adres + num - 1);
	}
	void SetArr(int num, int value) {
		if (num >= size) {
			AddArr(value);
		}
		if (num < size) {
			int* adres1 = new int[size + 1];
			for (unsigned int i = 0; i < num - 1; i++) {
				adres1[i] = adres[i];
			}
			adres1[num - 1] = value;
			size++;
			for (unsigned int i = num; i < size; i++) {
				adres1[i] = adres[i - 1];
			}
			adres = adres1;
		}
	}
	void SetELEMENT(int index, int value) {
		adres[index - 1] = value;
	}
};

class TimSort {
public:
	int* mas, sizeMas;

	int getMinrun()
	{
		int n = sizeMas;
		int r = 0;
		while (n >= 64) {
			r |= (n & 1);
			n >>= 1;
		}
		return n + r;
	};
	void insertionSort(int start, int end) {
		for (int i = start + 1; i < end; i++) {
			for (int j = i; j > start; j--) {
				if (mas[j - 1] > mas[j]) {
					swap(mas[j - 1], mas[j]);

				}
			}
		}
	};
	void reverseMas(int start, int end) {
		for (int i = 0; i < (end - start) / 2; i++) {
			swap(mas[start + i], mas[end - 1 - i]);
		}

	};
	bool timSortFinishPoint(int start, int& end) {
		bool positive = true, negative = true, endPoint = false;
		for (int i = start + 1; i < sizeMas; i++) {
			if (mas[i - 1] < mas[i] && positive) {
				negative = false;
			}
			else if (mas[i - 1] > mas[i] && negative) {
				positive = false;
			}
			else if (mas[i - 1] < mas[i] && !positive) {
				end = i;
				return false;
			}
			else if (mas[i - 1] > mas[i] && !negative) {
				end = i;
				return false;
			}
			if (i == sizeMas - 1) {
				end = sizeMas;
				endPoint = true;
			}

		}
		if (start == end) {
			endPoint = true;
		}
		return endPoint;

	};
	void merge(int firstStartPoint, int firstfinishPoint, int secondStartPoint, int secondFinishPoint) {
		int* temp1 = new int[secondFinishPoint - secondStartPoint];
		for (int i = secondStartPoint, j = 0; i < secondFinishPoint; i++, j++) {
			temp1[j] = mas[i];
		}
		int* temp2 = new int[firstfinishPoint - firstStartPoint];
		for (int i = firstStartPoint, j = 0; i < firstfinishPoint; i++, j++) {
			temp2[j] = mas[i];
		}
		int i = 0, j = 0, k = firstStartPoint;
		while (true) {
			if (temp2[i] > temp1[j]) {
				mas[k] = temp1[j];
				k++;
				j++;
			}
			else {
				mas[k] = temp2[i];
				k++;
				i++;
			}
			if (i == firstfinishPoint - firstStartPoint) {
				while (j != secondFinishPoint - secondStartPoint) {
					mas[k] = temp1[j];
					k++;
					j++;
				}
				delete[] temp1;
				delete[] temp2;
				break;
			}
			if (j == secondFinishPoint - secondStartPoint) {
				while (i != firstfinishPoint - firstStartPoint) {
					mas[k] = temp2[i];
					k++;
					i++;
				}
				delete[] temp1;
				delete[] temp2;
				break;
			}
		}

	};

	void timSort() {
		LAB2 A;
		A.adres = mas;
		stack<pair<int, int>> Stack;
		int start = 0, end = 0, count = 0, minRun = getMinrun();
		bool endPoint = false, ERROR = false;
		while ((!endPoint)) {
			endPoint = timSortFinishPoint(start, end);
			if (mas[start] > mas[end - 1]) {
				reverseMas(start, end);
			}
			if ((end - start) < minRun) {
				if (end + minRun > sizeMas) {
					end = sizeMas;
					insertionSort(start, end);
				}
				else {
					end += minRun - (end - start);
					insertionSort(start, end);
				}
			}
			if (start == end) { endPoint = true; }
			if (!endPoint) {
				Stack.push({ start, end });
				//cout << "\nPush " << start << " " << end << "\n";
				start = end;
			}

			if ((Stack.size() >= 2) && (!endPoint)) {
				pair<int, int> x = Stack.top();
				Stack.pop();
				//cout << "\nPopX  " << x.first << " " << x.second << "\n";
				pair<int, int> y = Stack.top();
				Stack.pop();
				//cout << "\nPopY  " << y.first << " " << y.second << "\n";
				if (!Stack.empty()) {
					pair<int, int> z = Stack.top();
					Stack.pop();
					//cout << "\nPopZ " << z.first << " " << z.second << "\n";
					if (z.second - z.first > x.second - x.first + y.second - y.first) {
						if (x.second - x.first < y.second - y.first) {
							//cout << "\nPUSH XYZ 209\n";
							Stack.push({ z.first,z.second });
							Stack.push({ y.first,y.second });
							Stack.push({ x.first,x.second });
						}
						else if (x.second - x.first >= y.second - y.first) {
							if (z.second - z.first > x.second - x.first) {
								merge(y.first, y.second, x.first, x.second);//cout << "\nMerge212 " << y.first << " " << y.second << " " << x.first << " " << x.second << "\n";
								merge(z.first, z.second, y.first, x.second);//cout << "\nMerge213 " << z.first << " " << z.second << " " << y.first << " " << x.second << "\n";
								//cout << "\nPUSH ZX 218\n";
								Stack.push({ z.first,x.second });
							}
							if (z.second - z.first <= x.second - x.first) {
								merge(z.first, z.second, y.first, y.second);//cout << "\nMerge217 " << z.first << " " << z.second << " " << y.first << " " << y.second << "\n";
								merge(z.first, y.second, x.first, x.second);//cout << "\nMerge218 " << z.first << " " << y.second << " " << x.first << " " << x.second << "\n";
								//	cout << "\nPUSH ZX 224\n";
								Stack.push({ z.first,x.second });
							}
						}
					}
					if (z.second - z.first <= x.second - x.first + y.second - y.first) {
						if (z.second - z.first <= x.second - x.first) {
							merge(z.first, z.second, y.first, y.second);//cout << "\nMerge225 " << z.first << " " << z.second << " " << y.first << " " << y.second << "\n";
							if (x.second - x.first >= y.second - z.first) {
								merge(z.first, y.second, x.first, x.second);//cout << "\nMerge227 " << z.first << " " << y.second << " " << x.first << " " << x.second << "\n";
								//cout << "\nPUSH ZX 234\n";
								Stack.push({ z.first,x.second });
							}
							else if (x.second - x.first < y.second - z.first) {
								//cout << "\nPUSH ZY XX 238\n";
								Stack.push({ z.first,y.second });
								Stack.push({ x.first,x.second });
							}
						}
						else if (z.second - z.first > x.second - x.first) {
							merge(y.first, y.second, x.first, x.second);//cout << "\nMerge " << y.first << " " << y.second << " " << x.first << " " << x.second << "\n";
							merge(z.first, z.second, y.first, x.second);//cout << "\nMerge " << z.first << " " << z.second << " " << y.first << " " << x.second << "\n";
							//cout << "\nPUSH ZX 246\n";
							Stack.push({ z.first,x.second });
						}
					}
				}
				if (Stack.empty()) {
					if (y.first != 0) {
						//cout << "\nPUSH 0Y 253\n";
						Stack.push({ 0,y.first });
					}
					if (x.second - x.first >= y.second - y.first) {
						merge(y.first, y.second, x.first, x.second);
						//cout << "\nMerge245 " << y.first << " " << y.second << " " << x.first << " " << x.second << "\n";
						Stack.push({ y.first,x.second });
						//cout << "\nPushYX " << y.first << " " << x.second << "\n";

					}
					else if ((x.second - x.first < y.second - y.first) && (x.first != x.second) && (y.first != y.second)) {
						Stack.push({ y.first, y.second });
						//cout << "\nPushY " << y.first << " " << y.second << "\n";

						Stack.push({ x.first, x.second });
						//	cout << "\nPushX " << x.first << " " << x.second << "\n";

					}

				}
			}

		}

		if (!Stack.empty()) {
			pair<int, int> x = Stack.top();
			Stack.pop();
			int preMerge = x.first, lastMerge = x.second;
			while (!Stack.empty()) {
				pair<int, int> y = Stack.top();
				Stack.pop();
				if (y.second != preMerge) { preMerge = y.second; }
				merge(y.first, y.second, preMerge, lastMerge);
				//cout << "\n Merge " << y.first << " " << y.second << " " << preMerge << " " << lastMerge;
				preMerge = y.first;
			}
			if ((Stack.empty()) && (preMerge != 0)) {
				merge(0, preMerge, preMerge, lastMerge);
				//cout << "\n Merge " << 0 << " " << preMerge << " " << preMerge << " " << lastMerge;

			}
		}
	}

	void Sort() {
		LAB2 DinArr;
		int size1;
		cin >> size1;
		DinArr.CreateArr(size1);

		mas = DinArr.adres;
		sizeMas = size1;
		for (int i = 0; i < size1; i++) {
			mas[i] = rand() % 10000;
		}
		//DinArr.PrintArr();
		int st = clock();
		timSort();
		cout << "\n\n\nВремя работы TimSort " << double(clock() - st) / 1000 << " с\n\n\n";
		//DinArr.PrintArr();
		DinArr.DeleteArr();
	};
};
int main()
{
	TimSort S;
	setlocale(0, "");
	S.Sort();
	cout << "\n\n\nВремя работы всей программы " << double(clock()) / 1000 << " с";
	return 0;
}