#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void printM(int** arr, int rows, int columns) { 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << setw(5) << arr[i][j] << " ";
        }
        cout << endl;
    }
}


int* findZero(int** arr, int rows, int columns, int& count0) { 
    int* zerocolumns = (int*)calloc(columns, sizeof(int));
    count0 = 0;

    for (int j = 0; j < columns; j++) {
        bool has0 = false;
        for (int i = 0; i < rows; i++) {
            if (arr[i][j] == 0) {
                has0 = true;
                break;
            }
        }
        if (has0) {
            zerocolumns[count0] = j;
            count0++;
        }
    }

    if (count0 > 0)
        zerocolumns = (int*)realloc(zerocolumns, count0 * sizeof(int));

    return zerocolumns;
}


void removeColumns(int** arr, int rows, int& columns, int* zerocolumns, int count0) { 
    if (count0 == 0) return;

    int newcolumns = columns;
    for (int j = columns - 1; j >= 0; j--) {
        int jdelete = j;
        bool deleted = false;

        for (int q = 0; q < count0; q++)
        {
            if (jdelete == zerocolumns[q])
                deleted = true;
        }

        if (deleted == true) {
            newcolumns--;

            for (int k = j + 1; k < columns; k++)
            {
                for (int t = 0; t < rows; t++)
                {
                    arr[t][k - 1] = arr[t][k];
                }
            }

        }

    }

    printM(arr, rows, columns);
    cout << endl;

    for (int i = 0; i < rows; i++) {

        arr[i] = (int*)realloc(arr[i], newcolumns * sizeof(int));
    }

    columns = newcolumns;

    printM(arr, rows, columns);
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Пункт 1\n";

    int A, B, C, D;

    do {
        cout << "Введите A (кол-во строк снизу): ";
        cin >> A;
        if (A < 0) cout << "А не может быть меньше нуля\n";
    } while (A < 0);

    do {
        cout << "Введите B (кол-во столбцов справа): ";
        cin >> B;
        if (B < 0) cout << "В не может быть меньше нуля\n";
    } while (B < 0);

    cout << "Введите C: ";
    cin >> C;
    cout << "Введите D: ";
    cin >> D;

    int Rows = 2;
    int Columns = 2;

    int** arr = (int**)malloc(Rows * sizeof(int*));
    for (int i = 0; i < Rows; i++) {
        arr[i] = (int*)malloc(Columns * sizeof(int));
    }

    arr[0][0] = A;
    arr[1][0] = C;
    arr[0][1] = B;
    arr[1][1] = D;


    cout << "Исходная матрица:\n";
    printM(arr, Rows, Columns);

    int rows = Rows + A;
    int columns = Columns + B;

    arr = (int**)realloc(arr, rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        if (i < Rows)
            arr[i] = (int*)realloc(arr[i], columns * sizeof(int));
        else
            arr[i] = (int*)malloc(columns * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            arr[i][j] = i * C + j * D - C;
        }
    }
  
    cout << "Итоговая матрица " << rows << "x" << columns << ":\n";
    printM(arr, rows, columns);

    int count0 = 0;
    int* zerocolumns = findZero(arr, rows, columns, count0);


    if (count0 > 0) {
        cout << "Столбцы, содержащие нули: ";
        for (int i = 0; i < count0; i++) {
            cout << zerocolumns[i] << " ";
        }
        cout << endl;
    }
    else {
        cout << "Элементов, равных нулю, нет\n";
    }

    removeColumns(arr, rows, columns, zerocolumns, count0);

    cout << "Матрица после удаления столбцов:\n";
    printM(arr, rows, columns);

    for (int i = 0; i < rows; i++) free(arr[i]);
    free(arr);
    free(zerocolumns);


    cout << "Пункт 2\n";

    double a, b;
    cout << "Введите значение a: ";
    cin >> a;
    cout << "Введите значение b: ";
    cin >> b;

    double* pa = new double(a);
    double* pb = new double(b);

    *pa = *pa * 3;

    double w = *pa;
    *pa = *pb;
    *pb = w;

    cout << "После всех операций:\n";
    cout << "a = " << *pa << ", b = " << *pb << endl;

    delete pa;
    delete pb;

    return 0;
}
