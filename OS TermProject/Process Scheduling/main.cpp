#include <iostream>
using namespace std;

struct process
{
	string name;
	double arrival;
	double burst;
	double waiting = 0;
};
int main()
{
	bool tr = 1;

	while (tr)
	{	process p1 = { "P1",0, 10 };
		process p2 = { "P2",3, 12 };
		process p3 = { "P3",7, 4 };
		process p4 = { "P4",10, 6 };
		process p5 = { "P5",14, 8 };
		process p6 = {"P6",15, 7};

		process arr[6] = { p1,p2,p3,p4,p5,p6 };

		double sum = 0;
		int next;
		cout << "어떤 것을 원하십니까?" << endl;
		cout << "1. FCFS         2. SJF         3. RR        4. 종료" << endl;
		cout << "원하는 숫자를 입력해주세요: ";
		cin >> next;

		if (next == 1)
		{
			int time = 0;
			
			for (int i = 0; i < 6; i++)
			{	
				bool end = true;
				while (end)
				{
					cout << time << "~" << time + 1 << " " << arr[i].name << endl;
					time++;
					arr[i].burst--;
					for (int j = 0; j < 6; j++) // 대기중인 process의 대기시간 증가
					{
						if (i!= j&& arr[j].burst != 0)
						{
							arr[j].waiting++;
						}
					}
					if (arr[i].burst == 0)
						end = false;
				}
			}
				cout << "FCFS Average Waiting Time = ("; // waiting time 출력
				for (int i = 0; i < 6; i++)
				{
					if (i == 5)
					{
						cout << arr[i].waiting  << ") / 6 = ";
						sum += arr[i].waiting ;
					}
					else
					{
						cout << arr[i].waiting  << " + ";
						sum += arr[i].waiting ;
					}
				}
				cout << sum / 6 << endl << endl;
		}

		else if (next == 2)
		{
			int time = 0;
			sum = 0;
			process *small = &arr[0];
			bool end = true;
			while (end)
			{
				for (int i = 0; i < 6; i++) // 실행될 process 를 찾는 과정
				{
					if (arr[i].arrival <= time)
					{
						if (small->burst > arr[i].burst && arr[i].burst != 0)
						{
							small = &arr[i];
						}
						else if (small->burst == 0)
							small = &arr[i];
					}
				}
				cout << time << "~" <<time+1<<" " << small->name << endl;
				small->burst--; // 실행되었으므로 burst 1 감소
				time++; // 실행되었으므로 시간 1 증가

				for (int i = 0; i < 6; i++) // 대기중인 process의 대기시간 증가
				{
					if (arr[i].arrival != small->arrival && arr[i].burst != 0)
					{
						arr[i].waiting++;
					}
				}

				int count = 0;
				for (int i = 0; i < 6; i++) // 모두 종료되었는지 확인
				{
					if (arr[i].burst == 0)
					{
						count++;
					}
				}
				if (count == 6) // 모두 종료되었다면 waiting time 출력
				{
					cout << "SRTF Average Waiting Time = (";
					for (int i = 0; i < 6; i++)
					{
						if (i == 5)
						{
							cout << arr[i].waiting-arr[i].arrival << ") / 6 = ";
							sum += arr[i].waiting - arr[i].arrival;
						}
						else
						{
							cout << arr[i].waiting - arr[i].arrival << " + ";
							sum += arr[i].waiting - arr[i].arrival;
						}
					}
					cout << sum / 6 << endl << endl;
					end = false;
				}
			}
		}
		else if (next == 3)
		{
			int timeq = 3;
			int time = 0;
			int k = 0;
			process* now;
			bool end = true;

			int btime[6] = { arr[0].burst,arr[1].burst, arr[2].burst, arr[3].burst, arr[4].burst, arr[5].burst }; //초기 burst time 저장

			while (end)
			{
				now = &arr[k];
				if (timeq <= now->burst)
				{
					for (int i = 0; i < timeq; i++)
					{	
						cout << time << "~" << time + 1 << " " << now->name << endl;
						time++;
						now->burst--;
					}
				}
				else
				{
					int br = now->burst;
					for (int i = 0; i < br; i++)
					{
						cout << time << "~" << time + 1 << " " << now->name << endl;
						time++;
						now->burst--;
					}
				}
				if (now->burst == 0 && now->waiting ==0) // 프로세스 종료 시간 저장
					now->waiting = time;

				if (k < 5) // 프로세스 순환
					k++;
				else
					k = 0;

				int count = 0;
				for (int i = 0; i < 6; i++) // 모두 종료되었는지 확인
				{
					if (arr[i].burst == 0)
					{
						count++;
					}
				}
				if (count == 6) // 모두 종료되었다면 waiting time 출력
				{
					cout << "RR Average Waiting Time = (";
					for (int i = 0; i < 6; i++)
					{
						if (i == 5)
						{
							cout << arr[i].waiting - btime[i] << ") / 6 = ";
							sum += arr[i].waiting - btime[i];
						}
						else
						{
							cout << arr[i].waiting - btime[i] << " + ";
							sum += arr[i].waiting - btime[i];
						}
					}
					cout << sum / 6 << endl << endl;
					end = false;
				}
			}
		}
		else if(next == 4)
		tr = false;
	}
	return 0;
}
