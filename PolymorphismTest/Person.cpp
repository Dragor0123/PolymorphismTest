#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

class Person
{
protected:
	string name;

public:
	Person(string _name) : name(_name) {}
	Person(const Person& Other) : Person(Other.name) {}
	Person& operator=(const Person& Other)
	{
		if (this != &Other) {
			this->name = Other.name;
		}
		return *this;
	}
	virtual ~Person() {}

	// Functions

	virtual Person* clone() = 0;

	virtual void printOut()
	{
		cout << "�̸� : " << name << "\n"
			<< "\n";
	}
	const string& getName() const { return this->name; }
};

class PersonSpawner
{
private:
	Person* prototype;

public:
	PersonSpawner() { prototype = nullptr; }
	PersonSpawner(Person* _prototype) : prototype(_prototype) {}
	Person* makePerson()
	{
		return prototype->clone();
	}

	void setPrototype(Person* _proto)
	{
		prototype = _proto;
	}
};

class Student : public Person
{
private:
	string schoolName;
	int stdNum;
	float gpa;
public:
	Student(string _name, string _schoolName, int _stdNum, float _gpa)
		: Person(_name), schoolName(_schoolName), stdNum(_stdNum), gpa(_gpa) {}

	Student(const Student& Other)
		: Student(Other.name, Other.schoolName, Other.stdNum, Other.gpa) {}

	Student& operator=(const Student& Other)
	{
		if (this != &Other) {
			this->name = Other.name;
			this->schoolName = Other.schoolName;
			this->stdNum = Other.stdNum;
			this->gpa = Other.gpa;
		}
		return *this;
	}
	virtual ~Student() {}

	//Functions
	virtual Person* clone()
	{
		return new Student(name, schoolName, stdNum, gpa);
	}

	virtual void printOut()
	{
		cout << "�̸� : " << name << "\n"
			<< "�б� : " << schoolName << "\n"
			<< "�й� : " << stdNum << "\n"
			<< "���� : " << gpa << "\n"
			<< "\n";
	}

	void setGpa(float val)
	{
		this->gpa = val;
	}

	const float getGpa() const
	{
		return this->gpa;
	}
};

class SalaryMan : public Person
{
private:
	string companyName;
	string position;
	unsigned int salary;
public:
	SalaryMan(string _name, string _companyName, string _position, unsigned int _salary)
		: Person(_name), companyName(_companyName), position(_position), salary(_salary) {}

	SalaryMan(const SalaryMan& Other)
		: SalaryMan(Other.name, Other.companyName, Other.position, Other.salary) {}

	SalaryMan& operator=(const SalaryMan& Other)
	{
		if (this != &Other) {
			this->name = Other.name;
			this->companyName = Other.companyName;
			this->position = Other.position;
			this->salary = Other.salary;
		}
		return *this;
	}
	virtual ~SalaryMan() {}

	//Functions
	virtual Person* clone()
	{
		return new SalaryMan(name, companyName, position, salary);
	}

	virtual void printOut()
	{
		cout << "�̸� : " << name << "\n"
			<< "ȸ�� : " << companyName << "\n"
			<< "���� : " << position << "\n"
			<< "���� : " << salary << "�� ��" << "\n"
			<< "\n";
	}

	void setSalary(unsigned int salary)
	{
		this->salary = salary;
	}

	const unsigned int getSalary() const
	{
		return this->salary;
	}
};




int main()
{
	int num = 5;
	Person** personList = new Person * [num];
	personList[0] = new Student("�ڽ�ȣ", "���հ����б�", 201038036, 3.72);
	personList[1] = new Student("������", "����ø����б�", 201083052, 3.90);
	personList[2] = new SalaryMan("���μ�", "GS retail", "�븮", 340);
	personList[3] = new Student("�ŵ���", "�������б�", 201076035, 4.21);
	personList[4] = new SalaryMan("��ö��", "NHN", "����", 410);

	for (size_t i = 0; i < num; ++i) {
		personList[i]->printOut();
	}
	cout << "-----------------------------------------\n";

	// ���⼭ Shin�� personList[i] �����Ͱ� ������ ����Ű�� �ִ� ��ü�� Ÿ��(���� Ÿ��)�� �޾Ƽ� �� Ÿ���� �÷�
	// �����Ҵ� �ϴ� ����� ã�ƶ�.

	// Solution : Prototype Pattern.
	Person* Kim = PersonSpawner(personList[4]).makePerson();
	Kim->printOut();
	
	delete Kim;

	for (size_t i = 0; i < num; ++i) {
		delete personList[i];
	}

	delete[] personList;

	return 0;
}
