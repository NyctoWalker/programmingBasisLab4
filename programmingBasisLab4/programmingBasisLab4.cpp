#include <iostream>
#include <fstream> //Чтение файлов
#include <sstream> //Преобразование string в int при чтении

using namespace std;

/*Произвести чтение массива структур данных. Структура должна иметь не менее 5 полей не менее 2 различных типов.
Должно быть реализовано меню действий пользователя, включающее как минимум следующий набор пунктов: 
загрузка перечня, печать перечня, поиск по значению одного из полей, добавление новой структуры, 
удаление структуры по номеру, сохранение перечня. Должна быть обеспечена корректная работа с динамической памятью.
Чтение данных организовать из файла, диалог с пользователем – в консоли, сохранение изменённых данных – в файл.
Программа должна быть структурирована и разбита на функции.
Предусмотреть форматированный вывод данных в удобном для пользователя виде.

8. 	Вариант структуры: Музыкальный товар (носитель (грампластинка, аудиокассета, лазерный диск), 
название, исполнитель, порядковый номер в каталоге, время звучания, цена).*/

struct product // Стрктура
{
	string type="none";
	string name="none";
	string performer="none";
	int id=-1;
	int price=0;
};

void Add(product Product, product*& productArr, int &length) // Функция добавления нового продукта в массив
{
	{
		length++;
		product* productArrChanged = new product[length];
		for (int i = 0; i < length-1; i++) // Копирование элементов
			productArrChanged[i] = productArr[i];
		productArrChanged[length-1] = Product; // Добавление нового элемента
		delete[] productArr;
		productArr = productArrChanged;
	}
}

void Delete(int number, product*& productArr, int& length) // Функция удаления продукта по номеру 
{
	if (length > 0 && number>0 && (number<=length)) 
	{
		number--;
		length--;
		product* productArrChanged = new product[length];
		for (int i = 0; i < length; i++)
		{
			if (i < number)
			{
				productArrChanged[i] = productArr[i];
			}
			else
			{
				productArrChanged[i] = productArr[i + 1];
			}
		}
		delete[] productArr;
		productArr = productArrChanged;
		cout << "Удалено!" << endl;
	}
	else
	{
		cout << "Удалять пока нечего/некорректный ввод данных" << endl;
	}
}

void AddNewProduct(product*& productArr, int &length) // Добавление новой стркутуры
{
	product newProduct;
	cout << "Введите имя тип носителя(Диск, Флешка, Кассета и т.д.): ";
	cin >> newProduct.type;
	cout << "Введите название товара: ";
	cin >> newProduct.name;
	cout << "Введите название исполнителя: ";
	cin >> newProduct.performer;
	cout << "Введите неповторяющийся целочисленный id: ";
	cin >> newProduct.id;
	cout << "Цена(число): ";
	cin >> newProduct.price;

	Add(newProduct, productArr, length);
}

void Print(int j, product* productArr) // Функция вывода продукта
{
	cout << "Тип носителя: " << productArr[j].type << endl;
	cout << "Название товара: " << productArr[j].name << endl;
	cout << "Исполнитель: " << productArr[j].performer << endl;
	cout << "ID: " << productArr[j].id << endl;
	cout << "Цена: " << productArr[j].price << endl;;
	cout << endl;
}

void Search(int choose, product* productArr, int &length) // Функция поиска по значению поля
{
	string search;
	cout << "Введите значение поля: ";
	cin >> search;
	cout << endl;
	bool flag = false;
	for (int i = 0; i < length; i++)
	{
		switch (choose)
		{
		case 1:
			if (productArr[i].type == search)
			{
				cout << "Товар №" << i + 1 << endl;
				Print(i, productArr);
				flag = true;
			}
			break;
		case 2:
			if (productArr[i].name == search)
			{
				cout << "Товар №" << i + 1 << endl;
				Print(i, productArr);
				flag = true;
			}
			break;
		case 3:
			if (productArr[i].performer == search)
			{
				cout << "Товар №" << i + 1 << endl;
				Print(i, productArr);
				flag = true;
			}
			break;
		case 4:
			if (productArr[i].id == stoi(search))
			{
				cout << "Товар №" << i + 1 << endl;
				Print(i, productArr);
				flag = true;
			}
			break;
		case 5:
			if (productArr[i].price == stoi(search))
			{
				cout << "Товар №" << i + 1 << endl;
				Print(i, productArr);
				flag = true;
			}
			break;
		}
	}
	if (flag == false) cout << "Не найдено ни одного совпадения" << endl;
}

void SaveFile(string FileName, product* productArr, int &length) // Функция сохранения в файл
{
	FileName += ".txt";
	ofstream file;
	file.open(FileName, ios_base::out | ios_base::trunc); //out=записываем(вводим) информацию, trunc = усекаем размер файла до нуля
	for (int i = 0; i < length; i++)
	{
		{
			file << productArr[i].type << endl;
			file << productArr[i].name << endl;
			file << productArr[i].performer << endl;
			file << productArr[i].id << endl;
			file << productArr[i].price << endl;
			if (i!=length-1)
				file << "" << endl;
		}
	}
	file.close();
}

void LoadFile(string FileName, product*& productArr, int &length) // Функция загрузки перечня из файла
{
	FileName += ".txt";
	ifstream file;
	file.open(FileName);
	if (file.is_open())
	{
		cout << "Перечень из файла загружен." << endl;
		string str; // Строка для считывания из файла
		string var;
		product newProduct;
		int count = 0;
		while (getline(file, str))
		{
			if (str != "")
			{
				int len = str.length();
				for (int i = 0; i < len; i++)
				{
					var += str[i];
				}
				if (count == 0)		 newProduct.type = var;
				else if (count == 1) newProduct.name = var;
				else if (count == 2) newProduct.performer = var;
				else if (count == 3) newProduct.id = stoi(var);
				else if (count == 4) newProduct.price = stoi(var);
				count ++;
				var = "";
			}
			else //Если файл не закончил читаться и остались параметры до пустого символа
			{
				count = 0;
				Add(newProduct, productArr, length);
			}
		}
		Add(newProduct, productArr, length);
	}
	else
	{
		cout << "Ошибка при загрузке файла!" << endl;
	}
	file.close();
}

int main()
{
	setlocale(LC_ALL, "ru"); //Работает только на вывод, http://cppstudio.com/post/435/ кириллица на ввод избыточна, 
							//функционал ограничен английским входным текстом названий, исполнителей, носителей.
	int length = 0; // Количество ячееек для сохранения структур
	product* productArr = new product[length];
	int i=0, choose;
	string FileName;

	while (i!=-1)
	{
		switch (i)
		{
			case 0:
			{
				cout << "Нажмите 1 для загрузки файла" << endl;
				cout << "Нажмите 2 для сохранения файла" << endl;
				cout << "Нажмите 3 для добавления нового товара" << endl;
				cout << "Нажмите 4 для удаления товара по его номеру в списке" << endl;
				cout << "Нажмите 5 для поиска по полю" << endl;
				cout << "Нажмите 6 для вывода товаров" << endl;
				cout << "Введите любое другое число для выхода" << endl;
				cout << "Введите число: ";
				cin >> i;
				cout << endl;
				break;
			}
			case 1: //Загрузка дополнительных товаров из перечня
			{
				cout << "Введите название файла(без формата): ";
				cin >> FileName;
				LoadFile(FileName, productArr, length);
				i = 0;

				break;
			}
			case 2: //Сохранение файла
			{
				cout << "Если в директрии присутвует файл такого же названия, то его содержимое заменится на сохраняемое" << endl;
				cout << "Введите название нового файла (без формата): ";
				cin >> FileName;
				SaveFile(FileName, productArr, length);
				cout << "Сохранено!" << endl << endl;
				i = 0;

				break;
			}
			case 3: //Добавление продукта
			{
				AddNewProduct(productArr, length);
				cout << endl;
				i = 0;
	
				break;
			}
			case 4: //Удаление продукта
			{
				cout << "Введите номер продукта: ";
				cin >> choose;
				Delete(choose, productArr, length);
				cout << endl;
				i = 0;

				break;
			}
			case 5: //Поисковик продукта по параметрам
			{
				cout << "Нажмите 1 для поиску по типу(Кассета, Диск)" << endl;
				cout << "Нажмите 2 для поиску по названию" << endl;
				cout << "Нажмите 3 для поиску по исполнителю" << endl;
				cout << "Нажмите 4 для поиску по id" << endl;
				cout << "Нажмите 5 для поиску по цене" << endl;
				cin >> choose;
				Search(choose, productArr, length);
				cout << endl;
				i = 0;

				break;
			}
			case 6: //Вывод всех продуктов
			{
				if (length == 0)
				{
					cout << "Товаров пока что нет!"<<endl<<endl;
				}
				for (int j = 0; j < length; j++)
				{
					cout << "Товар №" << j + 1 << endl;
					Print(j, productArr);
				}
				i = 0;

				break;
			}
			default: //Завершение работы программы
			{
				delete[] productArr;
				i = -1;
			}
		}
	}
}