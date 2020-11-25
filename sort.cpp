#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <stdio.h> 
#include <time.h> 
#include <random>

using namespace std;
unsigned int start = 0; //Начало массива
unsigned int const size = 50; // Конец массива //Есть файлы для замены с 10/20/50/10000/20000/50000/100000 элементов
unsigned int Array[size] = {}; //Массив

void randomDigits()
{
    unsigned int x = 200000;
    random_device rd;
    mt19937 mersenne(rd());
    unsigned int Array[x];
    unsigned int k = 0;
    bool flag = true;
    srand(time(NULL));
    cout << endl << "Флаг 1";
    for (unsigned int i = 0; i < x; i++)
    {
        k = 1 + mersenne()%x;
        flag = false;
        for (unsigned int n = 0; n <= i; n++)
        {
            if (Array[n] != k)
            {
                flag = false;
            }
            else
            {
                flag = true;
                i--;
                break;
            }
        } 
        if(!flag)
        {
            Array[i]=k;
        }
    } 
    cout << endl << "Флаг 2";
    ofstream outf("array1000000.txt");
    for (unsigned int i=0; i<x; i++)
    {
        if (!outf)
        {
           cout << "Ошибка записи в файл" << "\n";
        }
        else
        {
            outf << Array[i] << endl;
        }
    }  
}

//Функция чтения массива из файла
void readFile() 
{
    string s_size = to_string(size);
    ifstream inf("array"+s_size+".txt");
    if (!inf)
    {
        cout << "Ошибка чтения файла" << endl;
        exit(1);
    }
    while (inf)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            string line;
            getline(inf, line);
            if (inf.eof())
            {
                inf.close();
                break;
            }
            Array[i] = stoi(line);
        }
    }
    inf.close();
}
//закончили чтение

//Функция сортировки (принимает указатель на массив, начальное и конечное значение)
unsigned int Sort(unsigned int *arr, unsigned int begin, unsigned int end)
{
    unsigned int left_size = (end-begin) / 2;                       //Определяем размер левого логического подмассива
    unsigned int right_size = (end-begin) - left_size;              //Определяем размер правого логического подмассива
    if(left_size > 1)                                               //если есть на что разбивать, то...
    {
        Sort(arr, begin, begin+left_size);                          //Применяем функцию сортировки к левому логическому подмассиву
    }
    if(right_size > 1)                                              //если есть на что разбивать, то...
    {
        Sort(arr, begin+left_size, begin+left_size+right_size);     //Применяем функцию сортировки к правому логическому подмассиву
    }
    unsigned int left = 0;                                          //Переменная для перебора элементов левого логического подмассива
    unsigned int right = 0;                                         //Переменная для перебора элементов правого логического подмассива
    unsigned int i = 0;                                             //Переменная для перебора временного физического массива
    unsigned int temp_arr[end-begin];                               //Временный физический массив(принимает размер разбиваемого логического подмассива)
    while (left < left_size || right < right_size )                 //Сортируем в один проход пока левый или правый индекс не закончатся
    {
        if (arr[begin+left] < arr[begin+left_size+right])           //если элемент правой части больше, то...
        {
            temp_arr[i] = arr[begin+left_size+right];               //Записываем его во временны массив
            right++;                                                //Итерируем правую часть
        }
        else                                                        //если элемент левой части больше, то...
        {
            temp_arr[i] = arr[begin+left];                          //Записываем его во временный массив
            left++;                                                 //Итерируем левую часть
        }
        if(left == left_size)                                       //если левый массив закончился, то....
        {
            for(unsigned int k = right; k < right_size; k++)        //
            {                                                       //
                temp_arr[left+k] = arr[begin+left_size+right];      //Добавляем в конец временного массива оставшиеся элементы правой части
                right++;
            }
            break;                                                  //Выходим из цикла сортировки
        }
        if(right == right_size)                                     //если правый массив закончился, то....
        {
            for(unsigned int k=left; k<left_size; k++)              //
            {                                                       //
                temp_arr[right+k]= arr[begin+left];                 //Добавляем в конец временного массива оставшиеся элементы левой части
                left++;
            }
            break;                                                  //Выходим из цикла сортировки
        }
        i++;                                                        //Итерируем временный массив
    }
    for (unsigned int i = 0; i < end-begin; i++)
    {
        arr[begin+i] = temp_arr[i];                                 //Все элементы временного массива вставляем на свои места в исходную строку
    }
    return *arr;                                                    //Возвращаем указатель на исходный массив
}

int main()
{
    //Читаем массив из файла
    //readFile(); 

    //Выводим массив
    /*cout << endl << "Array: " << endl;
    for (unsigned int i = 0; i < size-start; i++)
    {
        cout << Array[i] << " ";
    }*/
    //Сортируем массив
    clock_t begin = clock();//запускаем таймер
    //Sort(Array, start, size);
    cout << endl << "Флаг -1";
    randomDigits();
    clock_t end = clock();
    double seconds = (double)(end - begin) / CLOCKS_PER_SEC;

    //Выводим отсортированный массив
    /*cout << endl << "Sorted array:" << endl;
    for (unsigned int i = start; i < size; i++)
    {
        cout << Array[i] << " ";
    }*/
    //cout << endl << "Время выполнения сортировки: " << seconds << endl;
    cout << endl << "Время наполения массива: " << seconds << endl;
    //cin >> start ;
    return 0;
}
