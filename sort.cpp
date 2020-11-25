#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <stdio.h> 
#include <time.h> 
#include <random>

using namespace std;                                //Пространстов имен
unsigned int start = 0;                             //Начало массива
unsigned int const size = 10000;                       //Конец массива //Есть файлы для замены с 20/50/10k/20k/50k/100k/200k элементов
unsigned int Array[size] = {};                      //Массив

void randomDigits()                                 //Создание массива с случайными числами и его запись в файл
{
    unsigned int x = 200000;                        //Изменить размер массива!
    random_device rd;
    mt19937 mersenne(rd());
    unsigned int Array[x];
    unsigned int k = 0;
    bool flag = true;
    srand(time(NULL));
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
    string s_size = to_string(size);
    ofstream outf("array"+s_size+".txt");
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

void readFile()                                     //Чтение массива из файла
{
    string s_size = to_string(size);                //Принимает число из ряда выше для выбора файла массива!
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

void writeFile()
{
    string s_size = to_string(size);
    ofstream outf("sortingarray"+s_size+".txt");
    for (unsigned int i=0; i<size; i++)
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
    readFile(); 
    //Выводим массив
    cout << endl << "Array: " << endl;
    for (unsigned int i = 0; i < size-start; i++)
    {
        cout << Array[i] << " ";
    }

    //Сортируем массив
    clock_t begin = clock();                                        //Запускаем таймер времени
    Sort(Array, start, size);
    //randomDigits();                                               //Набиваем массив числами
    clock_t end = clock();                                          //Останавливаем таймер времени
    double seconds = (double)(end - begin) / CLOCKS_PER_SEC;        //Считаем время выполнения сортировки
    
    //Выводим отсортированный массив
    cout << endl << "Sorted array:" << endl;
    for (unsigned int i = start; i < size; i++)
    {
        cout << Array[i] << " ";
    }

    cout << endl << "Sort execution time: " << seconds << " c" << endl;
    writeFile();
    //cout << endl << "Время наполения массива: " << seconds << endl;
    //cin >> start ;
    return 0;
}
