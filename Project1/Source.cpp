//Реализуйте с использованием паттернов проектирования простейшую систему планирования задач.
//Должна быть возможность создания списка дел, установки приоритетов, 
//установки дат выполнения, удаление и изменения дел.
//Каждому делу можно установить тег.Список дел можно загружать и сохранять в файл.
//Необходимо реализовать возможность поиска конкретного дела.
//Критерии поиска : по датам, по тегам, по приоритету и так далее.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

enum Status
{
	READY,
	NOTREADY
};

enum Priority
{
	IMPORTANT,
	UNIMPORTANT
};

enum Color
{
	RED,
	WHITE,
	BLACK,
	GREEN
};

class Date
{
private:
	int dd;
	int mm;
	int yy;
public:
	Date() {};
	Date(int dd, int mm, int yy)
	{
		this->dd = dd;
		this->mm = mm;
		this->yy = yy;
	}
	void PrintDate()
	{
		cout << "  " << dd << "." << mm << "." << yy;
	}
	bool operator==(Date date)
	{
		if (dd == date.dd && mm == date.mm && yy == date.yy) return true;
		else return false;
	}
	~Date() {}
};

class Tag
{
private:
	string name;
	Color color;
public:
	Tag() {}
	Tag(string name, Color color)
	{
		this->name = name;
		this->color = color;
	}
	void printTag()
	{
		cout << "  " << color << " " << name;
	}
	bool operator == (Tag tag)
	{
		if (name == tag.name) return true;
		else return false;
	}
	~Tag() {}
};

class Task
{
protected:
	Priority priority;
	Date deadline;
	Tag tag;
	int id;
	Status status;
public:
	Task() {}
	Task(Priority priority, Date deadline, Tag tag, int id, Status status)
	{
		this->priority = priority;
		this->deadline = deadline;
		this->tag = tag;
		this->id = id;
		this->status = status;
	}
	void Print(int cnt)
	{
		cout << cnt << ") ID: " << id << endl;
		deadline.PrintDate();
		cout << endl;
		tag.printTag();
		cout << endl;
		cout << "  " << status << endl;
		cout << "  " << priority << endl;
		cnt++;
	}
	void Edit(Task newTask)
	{
		priority = newTask.priority;
		deadline = newTask.deadline;
		tag = newTask.tag;
		id = newTask.id;
		status = newTask.status;
	}
	void setTag(Tag newTag)
	{
		tag = newTag;
	}
	void setPriority(Priority newPriority)
	{
		priority = newPriority;
	}
	void setDate(Date newDate)
	{
		deadline = newDate;
	}
	Tag getTag()
	{
		return tag;
	}
	const int getId()
	{
		return id;
	}
	Date getDate()
	{
		return deadline;
	}
	~Task() {}
};

class taskListProcessor
{
public:
	taskListProcessor() {}
	virtual void Add(Task task){}
	virtual void readFromFile(){}
	virtual void saveToFile(){}
	virtual void Remove(int num){}
	virtual void Sort(){}
	virtual void Edit(){}
	virtual void edit(int num, Task newTask) {}
	virtual void showList(){}
	virtual void searchId(Task task){}
	virtual void searchTag(Task task){}
	virtual void searchDate(Task task){}
	~taskListProcessor() {}
};

class TaskList :public taskListProcessor
{
private:
	vector<Task>tasks;
	int num = 0;
public:
	TaskList() {}
	void Add(Task task)
	{
		tasks.push_back(task);
		num++;
		cout << "added!" << endl;
	}
	void showList()
	{
		for (int i = 0; i < tasks.size(); i++) 
		{
			tasks[i].Print(i+1);
		}
	}
	void edit(int num, Task newTask)
	{
		for (int i = 0; i < tasks.size(); i++)
		{
			if (i == num)
			{
				tasks[i].Edit(newTask);
			}
		}
	}
	void Remove(int num)
	{
		for (int i = 0; i < tasks.size(); i++) 
		{
			if (i == num)
			{
				tasks.erase(tasks.begin() + i);
				cout << "deleted!" << endl;
			}
		}
	}
	void Sort()
	{
		sort(tasks.begin(), tasks.end());
		cout << "sorted by id!" << endl;
	}
	void searchId(Task task)
	{
		for (int i = 0; i < tasks.size(); i++) 
		{
			if (tasks[i].getId() == task.getId())
			{
				tasks[i].Print(i+1);
			}
		}
	}
	void searchTag(Task task)
	{
		for (int i = 0; i < tasks.size(); i++) 
		{
			if (tasks[i].getTag() == task.getTag())
			{
				tasks[i].Print(i+1);
			}
		}
	}
	void searchDate(Task task)
	{
		for (int i = 0; i < tasks.size(); i++)
		{
			if (tasks[i].getDate() == task.getDate())
			{
				tasks[i].Print(i+1);
			}
		}
	}
	~TaskList() {}
};

bool operator <(Task& lhs, Task& rhs)
{
	return lhs.getId() < rhs.getId();
}

class FileLoader :public taskListProcessor
{
public:
	FileLoader() {}
	virtual void readFromFile() {}
	~FileLoader() {}
};

class TxtFileLoader :public FileLoader
{
public:
	TxtFileLoader() {}
	virtual void readFromFile()
	{
		taskListProcessor* a;
		TaskList list;
		a = &list;
		ifstream file("file1.txt");
		string prio;
		file >> prio;
		int dd, mm, yy;
		file >> dd;
		file >> mm;
		file >> yy;
		string name;
		int clr;
		file >> name;
		file >> clr;
		int num;
		file >> num;
		int st;
		file >> st;
		Date date(dd, mm, yy);
		string tag;
		file >> tag;
		file >> prio;
		if (clr == 0)
		{
			tag = RED;
		}
		if (clr == 1)
		{
			tag = WHITE;
		}
		if (clr == 2)
		{
			tag = BLACK;
		}
		if (clr == 3)
		{
			tag = GREEN;
		}
		file >> prio;
		file >> dd >> mm >> yy;
		file >> name >> tag;
		file >> num;
		file >> st;
		//Task task(prio, date, tag, num, st);
		//a->Add(task);
		cout << "readed from txt file!" << endl;
	}
	~TxtFileLoader() {}
};

class ConsoleFileLoader :public FileLoader
{
public:
	ConsoleFileLoader() {}
	virtual void readFromFile()
	{
		cout << "readed from console file!" << endl;
	}
	~ConsoleFileLoader() {}
};

class CsvFileLoader :public FileLoader
{
public:
	CsvFileLoader() {}
	virtual void readFromFile()
	{
		cout << "readed from csv file!" << endl;
	}
	~CsvFileLoader() {}
};

class FileSaver :public taskListProcessor
{
public:
	FileSaver() {}
	virtual void saveToFile() {}
	~FileSaver() {}
};

class TxtFileSaver :public FileSaver
{
public:
	TxtFileSaver() {}
	virtual void saveToFile()
	{
		ofstream file("file.txt");
		cout << "Введите Приоритет 0 - IMPORTANT, 1 - UNIMPORTANT" << endl;
		int prio;
		cin >> prio;
		cout << "Введите дэдлайн" << endl;
		cout << "Day, Month, Year: ";
		int dd, mm, yy;
		cin >> dd;
		cout << ".";
		cin >> mm;
		cout << ".";
		cin >> yy;
		cout << "." << endl;
		cout << "Введите тэг" << endl;
		cout << "name, color(0 - 3): ";
		string name;
		int clr;
		cin >> name;
		cin >> clr;
		cout << "Введите ID" << endl;
		int num;
		cin >> num;
		cout << "Введите статус 0 - READY, 1 - NOT READY" << endl;
		int st;
		cin >> st;
		Date date(dd, mm, yy);
		int tag;
		if (clr == 0)
		{
			tag = RED;
		}
		if (clr == 1)
		{
			tag = WHITE;
		}
		if (clr == 2)
		{
			tag = BLACK;
		}
		if (clr == 3)
		{
			tag = GREEN;
		}
		if (prio == 0 && st == 0)
		{
			file << IMPORTANT;
			file << dd << mm << yy;
			file << name << tag;
			file << num;
			file << READY;
		}
		if (prio == 1 && st == 0)
		{
			file << UNIMPORTANT;
			file << dd << mm << yy;
			file << name << tag;
			file << num;
			file << READY;
		}
		if (prio == 1 && st == 1)
		{
			file << UNIMPORTANT;
			file << dd << mm << yy;
			file << name << tag;
			file << num;
			file << NOTREADY;
		}
		if (prio == 0 && st == 1)
		{
			file << IMPORTANT;
			file << dd << mm << yy;
			file << name << tag;
			file << num;
			file << NOTREADY;
		}
		cout << "saved to txt file!" << endl;
	}
	~TxtFileSaver() {}
};

class CsvFileSaver :public FileSaver
{
public:
	CsvFileSaver() {}
	virtual void saveToFile()
	{
		cout << "saved to csv file!" << endl;
	}
	~CsvFileSaver() {}
};

class ConsoleFileSaver :public FileSaver
{
public:
	ConsoleFileSaver() {}
	virtual void saveToFile()
	{
		cout << "saved to console file!" << endl;
	}
	~ConsoleFileSaver() {}
};

int main()
{
	setlocale(LC_ALL, "rus");
	taskListProcessor* a;
	TaskList list;
	a = &list;
	int m = 0;
	while (m < 10)
	{
		system("cls");
		cout << "1 - Добавить дело" << endl;
		cout << "2 - Удалить дело" << endl;
		cout << "3 - Найти дело" << endl;
		cout << "4 - Показать все дела" << endl;
		cout << "5 - Редактировать дело" << endl;
		cout << "6 - Записать в файл" << endl;
		cout << "7 - Считать с файла" << endl;
		cout << "8 - Сортировать дела по ID" << endl;
		cout << "9 - Выйти" << endl;
		cin >> m;
		if (m == 1)
		{
			cout << "Введите Приоритет 0 - IMPORTANT, 1 - UNIMPORTANT" << endl;
			int prio;
			cin >> prio;
			cout << "Введите дэдлайн" << endl;
			cout << "Day, Month, Year: ";
			int dd, mm, yy;
			cin >> dd;
			cout << ".";
			cin >> mm;
			cout << ".";
			cin >> yy;
			cout << "." << endl;
			cout << "Введите тэг" << endl;
			cout << "name, color(0 - 3): ";
			string name;
			int clr;
			cin >> name;
			cin >> clr;
			cout << "Введите ID" << endl;
			int num;
			cin >> num;
			cout << "Введите статус 0 - READY, 1 - NOT READY" << endl;
			int st;
			cin >> st;
			Date date(dd, mm, yy);
			Tag tag;
			if (clr == 0)
			{
				Tag tag1(name, RED);
				tag = tag1;
			}
			if (clr == 1)
			{
				Tag tag1(name, WHITE);
				tag = tag1;
			}
			if (clr == 2)
			{
				Tag tag1(name, BLACK);
				tag = tag1;
			}
			if (clr == 3)
			{
				Tag tag1(name, GREEN);
				tag = tag1;
			}
			if (prio == 0 && st == 0)
			{
				Task task(IMPORTANT, date, tag, num, READY);
				a->Add(task);
			}
			if (prio == 1 && st == 0)
			{
				Task task(UNIMPORTANT, date, tag, num, READY);
				a->Add(task);
			}
			if (prio == 1 && st == 1)
			{
				Task task(UNIMPORTANT, date, tag, num, NOTREADY);
				a->Add(task);
			}
			if (prio == 0 && st == 1)
			{
				Task task(IMPORTANT, date, tag, num, NOTREADY);
				a->Add(task);
			}
			system("pause");
		}
		if (m == 2)
		{
			cout << "Введите индекс дела(начиная с 0)" << endl;
			int num;
			cin >> num;
			a->Remove(num);
			system("pause");
		}
		if (m == 3)
		{
			cout << "1 - Найти по ID" << endl;
			cout << "2 - Найти по тэгу" << endl;
			cout << "3 - Найти по дэдлайну" << endl;
			int er;
			cin >> er;
			if (er == 1)
			{
				cout << "Введите ID" << endl;
				int trg;
				cin >> trg;
				Date date(0, 0, 0);
				Tag tag("sds", WHITE);
				Task task(IMPORTANT, date, tag, trg, NOTREADY);
				a->searchId(task);
			}
			if (er == 2)
			{
				cout << "Введите тэш" << endl;
				string name;
				int clr;
				cin >> name;
				cin >> clr;
				Tag tag;
				if (clr == 0)
				{
					Tag tag1(name, RED);
					tag = tag1;
				}
				if (clr == 1)
				{
					Tag tag1(name, WHITE);
					tag = tag1;
				}
				if (clr == 2)
				{
					Tag tag1(name, BLACK);
					tag = tag1;
				}
				if (clr == 3)
				{
					Tag tag1(name, GREEN);
					tag = tag1;
				}
				Date date(0, 0, 0);
				Task task(IMPORTANT, date, tag, 0, NOTREADY);
				a->searchTag(task);
			}
			if (er == 3)
			{
				cout << "Введите дэдлайн" << endl;
				int dd, mm, yy;
				cout << "Days, Month, Year: ";
				cin >> dd;
				cout << ".";
				cin >> mm;
				cout << ".";
				cin >> yy;
				Date date(dd, mm, yy);
				Tag tag("sds", WHITE);
				Task task(IMPORTANT, date, tag, 0, NOTREADY);
				a->searchDate(task);
			}
			system("pause");
		}
		if (m == 4)
		{
			a->showList();
			system("pause");
		}
		if (m == 5)
		{
			cout << "Введите индекс дела которое хотите изменить: ";
			int ind;
			cin >> ind;
			cout << "Введите Приоритет 0 - IMPORTANT, 1 - UNIMPORTANT" << endl;
			int prio;
			cin >> prio;
			cout << "Введите дэдлайн" << endl;
			cout << "Day, Month, Year: ";
			int dd, mm, yy;
			cin >> dd;
			cout << ".";
			cin >> mm;
			cout << ".";
			cin >> yy;
			cout << "." << endl;
			cout << "Введите тэг" << endl;
			cout << "name, color(0 - 3): ";
			string name;
			int clr;
			cin >> name;
			cin >> clr;
			cout << "Введите ID" << endl;
			int num;
			cin >> num;
			cout << "Введите статус 0 - READY, 1 - NOT READY" << endl;
			int st;
			cin >> st;
			Date date(dd, mm, yy);
			Tag tag;
			if (clr == 0)
			{
				Tag tag1(name, RED);
				tag = tag1;
			}
			if (clr == 1)
			{
				Tag tag1(name, WHITE);
				tag = tag1;
			}
			if (clr == 2)
			{
				Tag tag1(name, BLACK);
				tag = tag1;
			}
			if (clr == 3)
			{
				Tag tag1(name, GREEN);
				tag = tag1;
			}
			if (prio == 0 && st == 0)
			{
				Task task(IMPORTANT, date, tag, num, READY);
				a->edit(ind, task);
			}
			if (prio == 1 && st == 0)
			{
				Task task(UNIMPORTANT, date, tag, num, READY);
				a->edit(ind, task);
			}
			if (prio == 1 && st == 1)
			{
				Task task(UNIMPORTANT, date, tag, num, NOTREADY);
				a->edit(ind, task);
			}
			if (prio == 0 && st == 1)
			{
				Task task(IMPORTANT, date, tag, num, NOTREADY);
				a->edit(ind, task);
			}
			system("pause");
		}
		if (m == 6)
		{
			cout << "Введите данные дела которые нужно записать в файл (TXT): " << endl;
			FileSaver* y;
			TxtFileSaver l;
			y = &l;
			a = y;
			a->saveToFile();
			system("pause");
		}
		if (m == 7)
		{
			FileLoader* g;
			TxtFileLoader j;
			g = &j;
			a = g;
			a->readFromFile();
			system("pause");
		}
		if (m == 8)
		{
			a->Sort();
			system("pause");
		}
		if (m == 9)
		{
			return 0;
		}
	}
	return 0;
}