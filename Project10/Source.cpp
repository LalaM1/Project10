#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class Person {
	string id;
	string name;
	int age;

	void setId(string id) {
		if (id.length() == 7) {
			this->id = id;
		}
		else {
			throw string("Invalid id...");
		}
	}
public:
	Person(string id, string name, int age) {
		setId(id);
		setName(name);
		setAge(age);
	}

	string getId() const noexcept {
		return id;
	}

	void setName(string name) {
		if (name.length() > 2) {
			this->name = name;
		}
		else {
			throw string("Invalid name...");
		}
	}

	string getName() const noexcept {
		return name;
	}

	void setAge(int age) {
		if (age > 0) {
			this->age = age;
		}
		else {
			throw string("Invalid age...");
		}
	}

	int getAge() const noexcept {
		return age;
	}

	virtual void Display() = 0 {
		cout << "Id: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
	}
};

class Doctor : public Person {
	string speciality;
public:
	Doctor(string id, string name, int age, string speciality) :Person(id, name, age) {
		setSpeciality(speciality);
	}

	void setSpeciality(string speciality) {
		if (speciality.length() > 5) {
			this->speciality = speciality;
		}
		else {
			throw string("Invalid speciality...");
		}
	}

	string getSpeciality() const noexcept {
		return speciality;
	}

	void Display() override {
		Person::Display();
		cout << "Speciality: " << speciality << endl;
	}
};

class Patient :public Person {
	string disease; //shikayet (xesteliyi)
public:
	Patient(string id, string name, int age, string disease) :Person(id, name, age) {
		setDisease(disease);
	}

	void setDisease(string disease) {
		if (disease.length() > 7) {
			this->disease = disease;
		}
		else {
			throw string("Invalid disease length...");
		}
	}

	string getDisease() const noexcept {
		return disease;
	}

	void Display() override {
		Person::Display();
		cout << "Disease: " << disease << endl;
	}
};

class Hospital {
	vector<Doctor> doctors;
	vector<Patient> patients;
public:
	Hospital() {
		try
		{

			loadData();
		}
		catch (string ex)
		{
			cout << ex << endl;
			Doctor doctor("34FG8JA", "Mahmud", 47, "Dermatolog");
			AddDoctor(doctor);
		}
	}

	void saveData() { //butun hospitalda olan vectorlari ayri-ayri fayllara yazacaq
		ofstream fs("doctors.txt");
		if (fs.is_open()) {
			for (size_t i = 0; i < doctors.size(); i++)
			{
				if (i == doctors.size() - 1) //sonuncu doctor
				{
					fs << doctors[i].getId() << "#" << doctors[i].getName() << "#" << doctors[i].getAge() << "#" << doctors[i].getSpeciality();
					continue;
				}
				fs << doctors[i].getId() << "#" << doctors[i].getName() << "#" << doctors[i].getAge() << "#" << doctors[i].getSpeciality() << "\n";
			}
		}
		else {
			throw string("File couldn't open...");
		}
		fs.close();
	}

	void loadData() { //butun hospitalda olan vectorlarin melumatlarini fayldan oxuyacaq

		ifstream fs("doctors.txt");

		if (fs.is_open()) {
			while (!fs.eof()) {
				string row;
				getline(fs, row);
				if (row.length() == 0) {
					throw string("File is emtpty...");
				}
				int counter = 0;
				string id, name, speciality, age_str;

				for (auto ch : row)
				{
					if (ch != '#' && counter == 0) {
						id += ch;
					}
					else if (ch != '#' && counter == 1) {
						name += ch;
					}
					else if (ch != '#' && counter == 2) {
						age_str += ch;
					}
					else if (ch != '#' && counter == 3) {
						speciality += ch;
					}
					else {
						counter++;
					}
				}
				int age = stoi(age_str);
				Doctor doctor(id, name, age, speciality);
				doctors.push_back(doctor);
			}
		}
		else {
			throw string("File not found...");
		}
		fs.close();

	}

	void AddDoctor(Doctor doctor) {
		int index = SearchDoctorById(doctor.getId());
		if (index == -1) {
			doctors.push_back(doctor);
			saveData();
		}
		else {
			throw string("Doctor id already used...");
		}
	};
	void ShowAllDoctors() {
		cout << "__________________Doctors_____________________\n";
		for (size_t i = 0; i < doctors.size(); i++)
		{
			doctors[i].Display();
			cout << "_____________________________________________________" << endl;
		}
	};
	void ChangeAgeDoctor(string id, int newAge) {
		int index = SearchDoctorById(id);
		if (index != -1) {
			doctors[index].setAge(newAge);
			saveData();
		}
		else {
			throw string("Id not found...");
		}
	};
	void DeleteDoctor(string id) {
		int index = SearchDoctorById(id);
		if (index != -1) {
			doctors.erase(doctors.begin() + index);
			saveData();
		}
		else {
			throw string("Id not found...");
		}
	};

	int SearchDoctorById(string id) {
		for (size_t i = 0; i < doctors.size(); i++)
		{
			if (doctors[i].getId() == id) {
				return i;
			}
		}
		return -1;
	};

};


void main() {

	//MEN BURDAKI KOMMENTI SILDIM

	Hospital hospital;
	int ch;
	while (true)
	{

		string id, name, speciality;
		int age;
		cout << "1. Add Doctor \n2.Show all doctors \n3. Change doctor's age \n4. Delete doctor by id \n5. Exit \nChoose: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			try
			{
				cin.ignore();
				cout << "ID: ";
				getline(cin, id);

				cout << "Name: ";
				getline(cin, name);

				cout << "Age: ";
				cin >> age;
				cin.ignore();

				cout << "Speciality: ";
				getline(cin, speciality);

				Doctor doctor(id, name, age, speciality);
				hospital.AddDoctor(doctor);
				system("cls");
			}
			catch (string ex)
			{
				cout << ex << endl;
			}

			break;
		case 2:
			hospital.ShowAllDoctors();
			break;
		case 3:
			try
			{
				cin.ignore();
				cout << "ID: ";
				getline(cin, id);

				cout << "Age: ";
				cin >> age;
				hospital.ChangeAgeDoctor(id, age);
				system("cls");
			}
			catch (string ex)
			{
				cout << ex << endl;
			}
			break;
		case 4:
			try
			{
				cin.ignore();
				cout << "ID: ";
				getline(cin, id);
				hospital.DeleteDoctor(id);
				system("cls");
			}
			catch (string ex)
			{
				cout << ex << endl;
			}
			break;
		default:
			if (ch != 5) {
				cout << "Wrong choice..." << endl;
			}
			break;
		}

		if (ch == 5) {
			break;
		}

	}

}



