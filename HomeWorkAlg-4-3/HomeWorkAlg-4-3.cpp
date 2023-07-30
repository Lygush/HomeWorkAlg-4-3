#include <iostream>
#include <Windows.h>

class DynamicArray {
private:
    int actual_size{};
    int logical_size{};
    int* arr{};

public:
    DynamicArray(int atual_size, int logical_size) {
        this->arr = new int[atual_size];
        this->actual_size = atual_size;
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void print_dynamic_array() {
        for (int i{}; i < logical_size; ++i) {
            std::cout << arr[i] << " ";
        }
        for (int i{ logical_size }; i < actual_size; ++i) {
            std::cout << "_ ";
        }
    }

    bool remove_dynamic_array_head() {
        if (logical_size == 0) {
            return false;
        }
        if ((logical_size - 1) > (actual_size / 3)) {
            for (int i{ 1 }; i < logical_size; ++i) {
                arr[i - 1] = arr[i];
            }
            logical_size--;
        }
        else {
            int* temp_arr = new int[actual_size / 3];
            for (int i{}; i < actual_size / 3; ++i) {
                temp_arr[i] = arr[i + 1];
            }
            logical_size--;
            actual_size /= 3;
            delete[] arr;
            arr = temp_arr;
        }
        return true;
    }

    void append_to_dynamic_array(int number) {
        if (logical_size == actual_size) {
            int* temp_arr = new int[actual_size * 2];
            for (int i{}; i < logical_size; ++i) {
                temp_arr[i] = arr[i];
            }
            actual_size *= 2;
            delete[] arr;
            arr = temp_arr;
            arr[logical_size] = number;
            logical_size++;
        }
        else {
            arr[logical_size] = number;
            logical_size++;
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int actual_size{}, logical_size{};
    while (true) {
        std::cout << "Введите фактический размер массива: ";
        std::cin >> actual_size;
        std::cout << "Введите логический размер массива: ";
        std::cin >> logical_size;
        if (actual_size < logical_size) {
            std::cout << "Ошибка! Логический размер массива не может превышать фактический!" << "\n" << std::endl;
        }
        else break;
    }
    DynamicArray arr(actual_size, logical_size);
    int temp{};
    for (int i{}; i < logical_size; ++i) {
        std::cout << "Введите arr[" << i << "]: ";
        std::cin >> temp;
        arr.append_to_dynamic_array(temp);
    }
    arr.print_dynamic_array();
    std::string answer{};
    while (true) {
        std::cout << std::endl;
        std::cout << "Удалить первый элемент? ";
        std::cin >> answer;
        if (answer == "нет") {
            std::cout << "Спасибо! Ваш массив: ";
            arr.print_dynamic_array();
            break;
        }
        else if (answer == "да") {
            if (arr.remove_dynamic_array_head()) {
                std::cout << "Динамический массив: ";
                arr.print_dynamic_array();
            }
            else {
                std::cout << "Невозможно удалить первый элемент, так как массив пустой. До свидания!";
                break;
            }
        }
    }
    //arr.~DynamicArray();
    return 0;
}