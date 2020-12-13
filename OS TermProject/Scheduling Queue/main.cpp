#include <iostream>
using namespace std;

struct pcb
{
	int number;
	string state;
	pcb* pointer;
	int count;
	int jobindex;
	int readyindex;
};

class Queue
{
public:
	Queue(int max, string a);
	~Queue();
	void in(pcb& a);
	void out(int i);
	void print();
	int getlength();
	pcb getpcb(int i);
private:
	int index;
	int maxque;
	int length;
	pcb* items;
	string name;
};

Queue::Queue(int max, string a)
{
	maxque = max;
	items = new pcb[maxque];
	name = a;
	index = -1;
	length = 0;
	if (name == "Running")
		cout << name << "을 위한 cpu가 생성되었습니다." << endl;
	else
	cout << name << " Queue가 생성되었습니다." << endl;
}
Queue::~Queue()
{
	delete[] items;
}

void Queue::in(pcb& a)
{
	items[length] = a;
	index++;
	length++;
	if (name == "Job")
	{
		a.jobindex = length - 1;
	}
	else if (name == "Ready")
		a.readyindex = length - 1;
	a.state = name;

	if (name == "Running")
		a.count++;
}

void Queue::out(int i)
{
	if (length == 1)
	{
		index--;
		length--;
	}
	else
	{
		for (int j = 0; j < length; j++)
		{

			if (j > i)
			{
				items[j - 1] = items[j];
				if (name == "Job")
					items[j-1].jobindex = j - 1;
				else if (name == "Ready")
					items[j-1].readyindex = j - 1;
			}
		}
		index--;
		length--;
	}
}

void Queue::print()
{
	cout << name << ": ";
	for (int i = 0; i < length; i++)
	{
		cout << items[i].number << " " ;
	}
	cout << endl ;
}

int Queue::getlength()
{
	return length;
}
pcb Queue::getpcb(int i)
{
	return items[i];
}

int main()
{
	Queue Job(5, "Job"), Ready(3, "Ready"), Device(1, "Device");
	Queue Running(1, "Running");
	pcb pcb1, pcb2, pcb3, pcb4, pcb5;
	pcb1 = { 1, "대기 상태", &pcb2,0 };
	pcb2 = { 2, "대기 상태",&pcb3,0 };
	pcb3 = { 3, "대기 상태", &pcb4 ,0 };
	pcb4 = { 4, "대기 상태", &pcb5 ,0 };
	pcb5 = { 5, "대기 상태", &pcb1 ,0 };

	pcb imp;

    cout << endl;
	int num;
	while (1)
	{
		
		cout << "진행하려면 1을 입력하세요: ";
		cin >> num;
		cout << endl;
		if (num == 1)
		{
			if (Job.getlength() == 0)
			{
				Job.in(pcb1);
				Job.in(pcb2);
				Job.in(pcb3);
				Job.in(pcb4);
				Job.in(pcb5);
			}
			else if (Job.getlength() != 0 && Ready.getlength() == 0 && Running.getlength() == 0)
			{
				Ready.in(pcb1);
			}
			else if (Job.getlength() != 0 && Ready.getlength() != 0 && Running.getlength() == 0 && Device.getlength() ==0)
			{
				int nnn = Ready.getpcb(0).number;
				imp = Ready.getpcb(0);
				switch (Ready.getpcb(0).number)
				{
				case 1:
					Ready.out(0);
					Running.in(pcb1);
					break;
				case 2:
					Ready.out(0);
					Running.in(pcb2);
					break;
				case 3:
					Ready.out(0);
					Running.in(pcb3);
					break;
				case 4:
					Ready.out(0);
					Running.in(pcb4);
					break;
				case 5:
					Ready.out(0);
					Running.in(pcb5);
					break;
				}
				
				Ready.in(*imp.pointer);
				Ready.in(*(*imp.pointer).pointer);
				Ready.in(*(*(*imp.pointer).pointer).pointer);
			}

			else if (Running.getlength() != 0 && Device.getlength() ==0 &&Job.getlength() >1)
			{
				int nnn = Running.getpcb(0).number;
				imp = Running.getpcb(0);
				switch (Running.getpcb(0).number)
				{
				case 1:
					Running.out(0);
					if (pcb1.count == 2)
					{
						pcb1.state = "End";
						pcb5.pointer = &pcb2;
						Job.out(0);
					}
					else
						Device.in(pcb1);
					break;
				case 2:
					Running.out(0);
					if (pcb2.count == 2)
					{
						pcb2.state = "End";
						pcb1.pointer = &pcb3;
						Job.out(0);
					}
					else
					Device.in(pcb2);
					break;
				case 3:
					Running.out(0);
					if (pcb3.count == 2)
					{
						pcb3.state = "End";
						pcb2.pointer = &pcb4;
						Job.out(0);
					}
					else
					Device.in(pcb3);
					break;
				case 4:
					Running.out(0);
					if (pcb4.count == 2)
					{
						pcb4.state = "End";
						pcb3.pointer = &pcb5;
						Job.out(0);
					}
					else
					Device.in(pcb4);
					break;
				case 5:
					Running.out(0);
					if (pcb5.count == 2)
					{
						pcb5.state = "End";
						pcb4.pointer = &pcb1;
						Job.out(0);
					}
					else
					Device.in(pcb5);
					break;
				}

				nnn = Ready.getpcb(0).number;
				imp = Ready.getpcb(0);
				switch (Ready.getpcb(0).number)
				{
				case 1:
					Ready.out(0);
					Running.in(pcb1);
					break;
				case 2:
					Ready.out(0);
					Running.in(pcb2);
					break;
				case 3:
					Ready.out(0);
					Running.in(pcb3);
					break;
				case 4:
					Ready.out(0);
					Running.in(pcb4);
					break;
				case 5:
					Ready.out(0);
					Running.in(pcb5);
					break;
				}
				if(Job.getlength() >4)
				Ready.in(*(*(*imp.pointer).pointer).pointer);
			}

			else if (Running.getlength() != 0 && Device.getlength() != 0 && Ready.getlength() ==3 )
			{
			switch (Running.getpcb(0).number)
			{
			case 1:
				Running.out(0);
				pcb1.state = "End";
				pcb5.pointer = &pcb2;
				Job.out(pcb1.jobindex);
				break;
			case 2:
				Running.out(0);
				pcb2.state = "End";
				pcb1.pointer = &pcb3;
				Job.out(pcb2.jobindex);
				break;
			case 3:
				Running.out(0);
				pcb3.state = "End";
				pcb2.pointer = &pcb4;
				Job.out(pcb3.jobindex);
				break;
			case 4:
				Running.out(0);
				pcb4.state = "End";
				pcb3.pointer = &pcb5;
				Job.out(pcb4.jobindex);
				break;
			case 5:
				Running.out(0);
				pcb5.state = "End";
				pcb4.pointer = &pcb1;
				Job.out(pcb5.jobindex);
				break;
			}
			}
			else if (Job.getlength() != 0 && Ready.getlength() != 0 && Running.getlength() == 0 && Device.getlength() != 0)
			{
			int nnn = Ready.getpcb(0).number;
			imp = Ready.getpcb(0);
			switch (Ready.getpcb(0).number)
			{
			case 1:
				Ready.out(0);
				Running.in(pcb1);
				break;
			case 2:
				Ready.out(0);
				Running.in(pcb2);
				break;
			case 3:
				Ready.out(0);
				Running.in(pcb3);
				break;
			case 4:
				Ready.out(0);
				Running.in(pcb4);
				break;
			case 5:
				Ready.out(0);
				Running.in(pcb5);
				break;
			}
			Device.out(0);
			Ready.in(*(*(*imp.pointer).pointer).pointer);
 }
			else if (Running.getlength() != 0 && Device.getlength() != 0 && Ready.getlength() < 3)
			{
			Device.out(0);
			Ready.in(*(*(*imp.pointer).pointer).pointer);
 }
			else if (Running.getlength() != 0 && Device.getlength() == 0 && Ready.getlength() == 0 && Job.getlength() == 1)
			{
			
			switch (Running.getpcb(0).number)
			{
			case 1:
				Running.out(0);
				if (pcb1.count == 2)
				{
					pcb1.state = "End";
					Job.out(0);
				}
				else
					Device.in(pcb1);
				break;
			case 2:
				Running.out(0);
				if (pcb2.count == 2)
				{
					pcb2.state = "End";
					Job.out(0);
				}
				else
					Device.in(pcb2);
				break;
			case 3:
				Running.out(0);
				if (pcb3.count == 2)
				{
					pcb3.state = "End";
					Job.out(0);
				}
				else
					Device.in(pcb3);
				break;
			case 4:
				Running.out(0);
				if (pcb4.count == 2)
				{
					pcb4.state = "End";
					Job.out(0);
				}
				else
					Device.in(pcb4);
				break;
			case 5:
				
				if (pcb5.count == 2)
				{
					pcb5.state = "End";
					Running.out(0);
					Job.out(0);
				}
				else
					Device.in(pcb5);
				break;
			}

			cout << "모든 PCB가 종료되어 프로그램이 종료됩니다." << endl;
			Running.print();
			Ready.print();
			Device.print();
			Job.print();
			cout << endl;

			cout << 1 << " " << pcb1.state << " " << pcb1.count << endl;
			cout << 2 << " " << pcb2.state << " " << pcb2.count << endl;
			cout << 3 << " " << pcb3.state << " " << pcb3.count << endl;
			cout << 4 << " " << pcb4.state << " " << pcb4.count << endl;
			cout << 5 << " " << pcb5.state << " " << pcb5.count << endl;

			break;
 }
			
			Running.print();
			Ready.print();
			Device.print();
			Job.print();
			cout << endl;
			
				cout << 1 << " " << pcb1.state << " " << pcb1.count << endl;
				cout << 2 << " " << pcb2.state << " " << pcb2.count << endl;
				cout <<3 << " " << pcb3.state << " " << pcb3.count << endl;
				cout << 4 << " " << pcb4.state << " " << pcb4.count << endl;
				cout << 5 << " " << pcb5.state << " " << pcb5.count << endl;
		}
	}
	return 0;
}
