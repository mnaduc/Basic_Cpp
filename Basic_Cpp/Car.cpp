#include "Car.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#include "MyLibrary.h"

using namespace std;

unsigned int Car::input_mscn_[MSCN_ARRAY_SIZE] = { 0,0,0,0,0,0,0,0 }; // Lưu mscn người dùng nhập
bool Car::power_on_ = true; // true khi xe còn chạy, false nếu tắt máy
Car::Screen Car::screen = Screen::kPNScreen; // Lưu id screen
char Car::gear_ = 'N';
unsigned int Car::speed_ = 0;

Car::Car()
{
	for (int i = 0; i < MSCN_ARRAY_SIZE; i++) mscn_[i] = 0;
	for (int i = 0; i < 3; i++) warning_speed_[i] = 0;
}

void Car::run(string dataFile)
{
	if (loginAndSetup(dataFile))
		menu();
	else
	{
		system("cls");
		cout << "*DANG NHAP THAT BAI! DA TAT MAY!\nHen gap lai ban sau\n" << endl;
	}
}

/*
	Hàm thực hiện đăng nhập và cài đặt
	@param dataFile file chứa dữ liệu
	@return true nếu đăng nhập thành công, false nếu thất bại
*/
bool Car::loginAndSetup(string dataFile)
{
	if (readData(dataFile))
	{
		// Xe đã có dữ liệu
		system("cls");
		inputMSCN();
		if (checkMSCN())
		{
			// Đăng nhập thành công
			system("cls");
			cout << "*DANG NHAP THANH CONG!\n" << endl;
			cout << "Mang nhap vao truoc khi sap xep: ";
			printArray(input_mscn_, MSCN_ARRAY_SIZE);
			cout << "Ma so ca nhan truoc khi sap xep: ";
			printArray(mscn_, MSCN_ARRAY_SIZE);

			cout << "--> Mang nhap vao sau khi sap xep: ";
			unsigned int input_mscn_clone[MSCN_ARRAY_SIZE];
			copy_n(input_mscn_, MSCN_ARRAY_SIZE, input_mscn_clone);
			selectionSort(input_mscn_clone, MSCN_ARRAY_SIZE);
			printArray(input_mscn_clone, MSCN_ARRAY_SIZE);

			cout << "--> Ma so ca nhan sau khi sap xep: ";
			unsigned int mscn_clone[MSCN_ARRAY_SIZE];
			copy_n(mscn_, MSCN_ARRAY_SIZE, mscn_clone);
			bubbleSort(mscn_clone, MSCN_ARRAY_SIZE);
			printArray(mscn_clone, MSCN_ARRAY_SIZE);

			cout << endl;
			system("pause");

			reinstallMSCN();
			reinstallWarningSpeed();
			// Cập nhật dữ liệu
			writeData(dataFile);
			return true;
		}
	}
	else
	{
		// Không thể đọc dữ liệu (Không tìm thấy file)
		// Đăng ký lần đầu
		system("cls");
		cout << "*MA SO CA NHAN CHUA DUOC CAI DAT!" << endl;
		inputMSCN();
		copy_n(input_mscn_, MSCN_ARRAY_SIZE, mscn_);
		reinstallMSCN();
		system("cls");
		cout << "*TOC DO CANH BAO KHOANG CACH AN TOAN CHUA DUOC CAI DAT!" << endl;
		installWarningSpeed();
		reinstallWarningSpeed();
		writeData(dataFile);
		return true;
	}
	return false;
}

/*
	Yêu cầu nhập mã số cá nhân và lưu vào mảng input_mscn_
*/
void Car::inputMSCN()
{
	cout << "Nhap ma so ca nhan, mang " << setfill('0') << setw(2) << MSCN_ARRAY_SIZE << " so: " << endl;
	for (int i = 0; i < MSCN_ARRAY_SIZE; i++)
	{
		cout << "so thu " << i + 1 << ": ";
		string str = "";
		getline(cin, str);
		while (!isUnsignedInteger(str))
		{
			cout << "--> Nhap khong hop le, vui long nhap lai: ";
			getline(cin, str);
		}
		input_mscn_[i] = stoi(str);
	}
}

/*
	Thực hiện kiểm tra mã số cá nhân
	So sánh mảng input_mscn_ và mscn_
*/
bool Car::checkMSCN()
{
	unsigned int mscn_clone[MSCN_ARRAY_SIZE];
	unsigned int input_mscn_clone[MSCN_ARRAY_SIZE];
	copy_n(mscn_, MSCN_ARRAY_SIZE, mscn_clone);
	copy_n(input_mscn_, MSCN_ARRAY_SIZE, input_mscn_clone);
	selectionSort(mscn_clone, MSCN_ARRAY_SIZE);
	bubbleSort(input_mscn_clone, MSCN_ARRAY_SIZE);
	for (size_t i = 0; i < MSCN_ARRAY_SIZE; i++)
	{
		if (mscn_clone[i] != input_mscn_clone[i])
			return false;
	}
	return true;
}

/*
	Thông báo mscn đã cài đặt và đưa yêu cầu có cài đặt lại không?
*/
void Car::reinstallMSCN()
{
	system("cls");
	cout << "Ma so ca nhan da cai dat: ";
	printArray(mscn_, MSCN_ARRAY_SIZE);
	cout << endl;
	cout << "Ban co muon cai dat lai ma so ca nhan khong? (y/n)" << endl;
	if (YNQuestion()) {
		system("cls");
		inputMSCN();
		copy_n(input_mscn_, MSCN_ARRAY_SIZE, mscn_);
		reinstallMSCN();
	}
}

/*
	Yêu cầu nhập tốc độ cảnh báo khoảng cách an toàn và lưu vào mảng warning_speed_
*/
void Car::installWarningSpeed()
{
	cout << "*Nhap toc do canh bao khoang cach an toan voi 03 muc toc do!" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "Toc do muc " << i + 1 << ": ";
		string str = "";
		getline(cin, str);
		while (!isUnsignedInteger(str))
		{
			cout << "--> Nhap khong hop le, vui long nhap lai: ";
			getline(cin, str);
		}
		warning_speed_[i] = stoi(str);
	}
	bubbleSort(warning_speed_, 3);
}

/*
	Thông báo tốc độ cảnh báo khoảng cách an toàn đã cài đặt
	và đưa yêu cầu có cài đặt lại không?
*/
void Car::reinstallWarningSpeed()
{
	system("cls");
	cout << "03 muc toc do canh bao an toan: ";
	printArray(warning_speed_, 3);
	cout << endl;
	cout << "Ban co muon cai dat lai toc do canh bao khoang cach an toan khong? (y/n)" << endl;
	if (YNQuestion()) {
		system("cls");
		installWarningSpeed();
		reinstallWarningSpeed();
	}
}

/*
	Xử lý menu
*/
void Car::menu()
{
	system("cls");
	cout << "XIN CHAO!" << endl;
	cout << "Ma so ca nhan: ";
	printArray(mscn_, MSCN_ARRAY_SIZE);
	cout << endl;
	while (power_on_)
	{
		switch (screen)
		{
		case Screen::kPNScreen:
			cout << "Ban dang o tay so: " << gear_ << " - Toc do: " << speed_ << " km/h" << endl;
			cout << "XIN MOI LUA CHON:\n1. P\n2. R\n3. N\n4. D\n0. POWER OFF\n" << endl;
			break;
		case Screen::kRDScreen:
			if (gear_ == 'D')
			{
				if (speed_ < warning_speed_[0])
				{
					cout << "*BAN CHU Y GIU KHOANG CACH TOI THIEU LA 20m\n";
				}
				else if (speed_ < warning_speed_[1])
				{
					cout << "*BAN CHU Y GIU KHOANG CACH TOI THIEU LA 55m\n";
				}
				else if (speed_ < warning_speed_[2])
				{
					cout << "*BAN CHU Y GIU KHOANG CACH TOI THIEU LA 70m\n";
				}
				else
				{
					cout << "*BAN CHU Y GIU KHOANG CACH TOI THIEU LA 100m\n";
				}
				if (speed_ > 60) cout << "*TOC DO NGUY HIEM, BAN NEN GIAM TOC!";
				cout << endl;
			}
			else
			{
				if (speed_ > 20) cout << "*TOC DO NGUY HIEM, BAN NEN GIAM TOC!";
				cout << "\n" << endl;
			}
			cout << "Ban dang o tay so: " << gear_ << " - Toc do: " << speed_ << " km/h" << endl;
			cout << "XIN MOI LUA CHON:\n1. TANG TOC\n2. GIAM TOC\n3. PHANH\n0. TRO VE MENU\n\n" << endl;
			break;
		}
		handleSelection();
	}
	cout << "*DA TAT MAY\nHEN GAP LAI BAN SAU!" << endl;
}

/*
	Hàm yêu cầu lựa chọn và xử lý lựa chọn menu người dùng
*/
void Car::handleSelection()
{
	switch (screen)
	{
	case Car::Screen::kPNScreen:
		switch (inputSelection(5))
		{
		case 1:
			// 'P'
			set_gear('P');
			screen = Screen::kPNScreen;
			break;
		case 2:
			// 'R'
			set_gear('R');
			screen = Screen::kRDScreen;
			break;
		case 3:
			// 'N'
			set_gear('N');
			screen = Screen::kPNScreen;
			break;
		case 4:
			// 'D'
			set_gear('D');
			screen = Screen::kRDScreen;
			break;
		case 0:
			// "POWER OFF"
			power_on_ = false;
			break;
		}
		break;
	case Car::Screen::kRDScreen:
		switch (inputSelection(4))
		{
		case 1:
			//"TANG TOC"
			speedUp();
			break;
		case 2:
			//"GIAM TOC"
			speedDown();
			break;
		case 3:
			//"PHANH"
			brake();
			break;
		case 0:
			// "TRO VE MENU"
			cout << "XIN CHAO!" << endl;
			cout << "Ma so ca nhan: ";
			printArray(mscn_, MSCN_ARRAY_SIZE);
			screen = Screen::kPNScreen;
			break;
		}
		cout << endl;
		break;
	}
}

/*
	Yêu cầu lựa chọn mục
	@param num_of_choices số lượng lựa chọn
	@return index (0~num_of_choices) vị trí được lựa chọn
*/
unsigned int Car::inputSelection(int num_of_choices)
{
	cout << "--> Lua chon cua ban: ";
	string temp = "";
	getline(cin, temp);
	while (!isUnsignedInteger(temp) || stoi(temp) > num_of_choices - 1)
	{
		cout << "*Lua chon khong hop le! Vui long lua chon lai: ";
		getline(cin, temp);
	}
	system("cls");
	return stoi(temp);
}

/*
	Cài đặt tay số
*/
void Car::set_gear(char new_gear)
{
	switch (new_gear)
	{
	case 'P':
		if (speed_ == 0) {
			gear_ = 'P';
			cout << "\n*DA VE SO P\n*CHU Y SU DUNG PHANH TAY DE DAM BAO AN TOAN!";
		}
		else
		{
			cout << "\n*HAY CHAC CHAN XE DA DUNG (TOC DO 0 KM/H)!\n";
		}
		break;
	case 'N':
		if (speed_ == 0) {
			gear_ = 'N';
			cout << "\n*DA VE SO N\n";
		}
		else
		{
			cout << "\n*HAY CHAC CHAN XE DA DUNG (TOC DO 0 KM/H)!\n";
		}
		break;
	case 'D':
		if (gear_ != 'D')
		{
			if (speed_ == 0)
			{
				gear_ = 'D';
				speed_ = 7;
			}
			else
			{
				cout << "*KHONG THE CHUYEN DOI SO R->D KHI XE CHUA DUNG!";
			}
		}
		break;
	case 'R':
		if (gear_ != 'R')
		{
			if (speed_ == 0)
			{
				gear_ = 'R';
				speed_ = 7;
			}
			else
			{
				cout << "*KHONG THE CHUYEN DOI SO D->R KHI XE CHUA DUNG!";
			}
		}
		break;
	}
	cout << endl;
}

void Car::speedUp()
{
	speed_ += 5;
}

void Car::speedDown()
{
	speed_ = (speed_ > 5) ? (speed_ - 5) : 0;
}

void Car::brake()
{
	speed_ = 0;
}

bool Car::readData(string filename)
{
	ifstream file;
	file.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		file.open(filename, ios::binary);
		file.read((char*)this, sizeof(Car));
		return true;
	}
	catch (const ifstream::failure& e)
	{
		/*system("cls");
		cout << "--> Failed to read data from the file" << endl;
		cout << e.what() << endl;
		system("pause");
		system("cls");*/
	}
	catch (...)
	{
		/*system("cls");
		cout << "--> Failed to read data from the file" << endl;
		system("pause");
		system("cls");*/
	}
	return false;
}

void Car::writeData(string filename)
{
	ofstream file;
	file.exceptions(ofstream::failbit | ofstream::badbit);
	try
	{
		file.open(filename, ios::binary);
		file.write((char*)this, sizeof(Car));
	}
	catch (...)
	{
		/*system("cls");
		cout << "--> Failed to write data to the file" << endl;
		system("pause");
		system("cls");*/
	}
}


