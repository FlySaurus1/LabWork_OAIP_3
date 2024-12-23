#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Product {
    string name;
    int quantity;
    double price;
};

void addProductToFile(const Product& product) {
    ofstream file("orders.txt", ios::app);
    if (file.is_open()) {
        file << product.name << "|" << product.quantity << "|" << product.price << endl;
        file.close();
    }
    else {
        cout << "Ошибка при открытии файла для добавления.\n";
    }
}

void addProduct() {
    Product product;
    while (true) {
        cout << "\nВведите название товара (или нажмите Enter для завершения): ";
        getline(cin, product.name);

        if (product.name.empty()) {
            break; // Завершаем добавление, если введена пустая строка
        }

        cout << "Введите количество единиц товара: ";
        cin >> product.quantity;
        cout << "Введите цену за единицу товара: ";
        cin >> product.price;
        cin.ignore(); // Очищаем буфер ввода

        addProductToFile(product);
        cout << "Товар добавлен в файл.\n";
    }
}

void searchProductByName() {
    string name;
    cout << "\nВведите название товара для поиска: ";
    getline(cin, name);

    ifstream file("orders.txt");
    if (file.is_open()) {
        string line;
        bool found = false;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            string productName = line.substr(0, pos);
            if (productName == name) {
                cout << "Товар найден: " << line << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Товар с таким названием не найден.\n";
        }
        file.close();
    }
    else {
        cout << "Ошибка при открытии файла для поиска.\n";
    }
}

bool compareByName(const Product& a, const Product& b) {
    return a.name < b.name;
}

bool compareByQuantity(const Product& a, const Product& b) {
    return a.quantity < b.quantity;
}

bool compareByPrice(const Product& a, const Product& b) {
    return a.price < b.price;
}

void sortProducts() {
    vector<Product> products;
    ifstream file("orders.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);

            Product product;
            product.name = line.substr(0, pos1);
            product.quantity = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            product.price = stod(line.substr(pos2 + 1));

            products.push_back(product);
        }
        file.close();

        int choice;
        cout << "\nВыберите критерий сортировки:\n";
        cout << "1. По названию товара\n";
        cout << "2. По количеству товара\n";
        cout << "3. По цене за единицу\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore(); // Очищаем буфер ввода

        switch (choice) {
        case 1:
            sort(products.begin(), products.end(), compareByName);
            break;
        case 2:
            sort(products.begin(), products.end(), compareByQuantity);
            break;
        case 3:
            sort(products.begin(), products.end(), compareByPrice);
            break;
        default:
            cout << "Неверный выбор.\n";
            return;
        }

        ofstream fileOut("orders.txt");
        if (fileOut.is_open()) {
            for (const auto& product : products) {
                fileOut << product.name << "|" << product.quantity << "|" << product.price << endl;
            }
            fileOut.close();
            cout << "Товары отсортированы.\n";
        }
        else {
            cout << "Ошибка при открытии файла для записи отсортированных данных.\n";
        }
    }
    else {
        cout << "Ошибка при открытии файла для сортировки.\n";
    }
}

void displayProducts() {
    ifstream file("orders.txt");
    if (file.is_open()) {
        string line;
        cout << "\nСписок товаров:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Ошибка при открытии файла для вывода данных.\n";
    }
}

void filterProductsByPrice() {
    double maxPrice;
    cout << "\nВведите максимальную цену для фильтрации товаров: ";
    cin >> maxPrice;
    cin.ignore(); // Очищаем буфер ввода

    ifstream file("orders.txt");
    if (file.is_open()) {
        string line;
        cout << "\nТовары с ценой до " << maxPrice << ":\n";
        while (getline(file, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            double price = stod(line.substr(pos2 + 1));
            if (price <= maxPrice) {
                cout << line << endl;
            }
        }
        file.close();
    }
    else {
        cout << "Ошибка при открытии файла для фильтрации.\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить товар\n";
        cout << "2. Поиск товара по названию\n";
        cout << "3. Сортировка товаров\n";
        cout << "4. Вывод всех товаров\n";
        cout << "5. Фильтрация товаров по цене\n";
        cout << "0. Завершить программу\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore(); // Очищаем буфер ввода

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            searchProductByName();
            break;
        case 3:
            sortProducts();
            break;
        case 4:
            displayProducts();
            break;
        case 5:
            filterProductsByPrice();
            break;
        case 0:
            cout << "Программа завершена.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}