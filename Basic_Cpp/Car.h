#ifndef CAR_H_
#define CAR_H_

// Kích thước dãy mã số cá nhân
#define	MSCN_ARRAY_SIZE 8

#include <string>
using namespace std;

class Car
{
public:
	Car();
	// @param dataFile file chứa data
	void run(string dataFile);
private:
	// Dữ liệu riêng class gồm mã số cá nhân 
	// và 3 mức tốc độ cảnh báo khoảng cách an toàn 
	unsigned int mscn_[MSCN_ARRAY_SIZE];
	unsigned int warning_speed_[3];

	enum class Screen
	{
		kPNScreen, kRDScreen
	};
	static unsigned int input_mscn_[];
	static bool power_on_;
	static Screen screen;
	static char gear_;
	static unsigned int speed_;

	bool loginAndSetup(string dataFile);
	void inputMSCN();
	bool checkMSCN();
	void reinstallMSCN();
	void installWarningSpeed();
	void reinstallWarningSpeed();

	void menu();
	void handleSelection();
	unsigned int inputSelection(int num_of_choices);
	void set_gear(char new_gear);
	void speedUp();
	void speedDown();
	void brake();

	bool readData(string dataFile);
	void writeData(string dataFile);
};

#endif // !CAR_H_