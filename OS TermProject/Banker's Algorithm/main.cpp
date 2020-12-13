#include <iostream>
using namespace std;

struct process // process 
{
	int num;

	int max_a, max_b, max_c, max_d;
	int allo_a, allo_b, allo_c, allo_d;
	
	int need_a = max_a - allo_a;
	int need_b = max_b - allo_b;
	int need_c = max_c - allo_c;
	int need_d = max_d - allo_d;

	int sequence = 0;
};

struct available // available resource
{
	int av;
	int av_a = av / 1000;
	int av_b = (av % 1000) / 100;
	int av_c = (av % 100) / 10;
	int av_d = av % 10;
};

bool possible(process x, available y) // need를 현재 available로 처리 가능한지
{
	if (x.need_a <= y.av_a && x.need_b <= y.av_b && x.need_c <= y.av_c && x.need_d <= y.av_d)
		return true;
	else
		return false;
}

int main()
{
	while(1)
	{
		int menu;
		cout << "원하는 번호를 입력해주세요!\n 1. Is the System is safe state?\n 2. Request for (?,?,?,?) by P?\n 3. End\n";
		cin >> menu;
		cout << endl;

		process p0{ 0,6,0,1,2,4,0,0,1 };
		process p1{ 1,1,7,5,0,1,1,0,0 };
		process p2{ 2,2,3,5,6,1,2,5,4 };
		process p3{ 3,1,6,5,3,0,6,3,3 };
		process p4{ 4,1,6,5,6,0,2,1,2 };
		available re{ 3211 };

		process arr[5] = { p0,p1,p2,p3,p4 };

		if (menu == 2) // request 처리
		{
			int q, w, e, r, t;
			while (1) // 적당한 값을 넣을때 까지 반복
			{
				cout << "Please Enter (?,?,?,?) and Process Number: ";
				cin >> q >> w >> e >> r >> t;
				cout << "Check that Request Available... \n";
				if (q <= re.av_a && w <= re.av_b && e <= re.av_c && r <= re.av_d)
				{
					cout << "Available\n\n";
					break;
				}
				else
					cout << "Fail\n\n";
			}
			re.av_a -= q;
			re.av_b -= w;
			re.av_c -= e;
			re.av_d -= r;

			arr[t].allo_a += q;
			arr[t].allo_b += w;
			arr[t].allo_c += e;
			arr[t].allo_d += r;

			arr[t].need_a -= q;
			arr[t].need_b -= w;
			arr[t].need_c -= e;
			arr[t].need_d -= r;
		}
		else if (menu == 3) // 프로그램 종료
			break;
		int order = 1; 
		int count = 0;
		bool tr = true;
		
		// 1번, 2번에서 request 적용 이후 safe 판정
		while (tr)
		{
			for (int i = 0; i < 5; i++)
			{
				if (possible(arr[i], re) == true)
				{
					if (arr[i].allo_a != 0 || arr[i].allo_b != 0 || arr[i].allo_c != 0 || arr[i].allo_d != 0)
					{
						
						count++;
						arr[i].sequence = order; //process 처리 순서 기억
						re.av_a = re.av_a + arr[i].allo_a;
						re.av_b = re.av_b + arr[i].allo_b;
						re.av_c = re.av_c + arr[i].allo_c;
						re.av_d = re.av_d + arr[i].allo_d;
						arr[i].allo_a = 0;
						arr[i].allo_b = 0;
						arr[i].allo_c = 0;
						arr[i].allo_d = 0;
						arr[i].need_a = 0;
						arr[i].need_b = 0;
						arr[i].need_c = 0;
						arr[i].need_d = 0; // 작업이 완료된 process의 allo와 need 0으로
						cout << "P" << i << " 작업 완료! \n Available = " << re.av_a << " " << re.av_b << " " << re.av_c << " " << re.av_d << endl;
						//process 완료후 남은 available 출력
						order++;
					}
				}
			}
			if (count == 0) // process들을 한 바퀴 돌렸음에도 처리 가능한 것이 없었다면 탈출
				tr = false;
			else // 더 이상 수행 가능한 process가 없을 때까지 반복
				count = 0;
		}
		cout << endl;

		if (order == 6) // 위 루프를 탈출 했을때 5개 process 모두 처리 했을 경우
		{
			cout << "Safe 하다!\n";
			cout << "Safe Sequence = ";
			process seq[5];
			for (int i = 0; i < 5; i++)
			{
				seq[arr[i].sequence - 1] = arr[i]; // process 처리 순서대로 배열에 저장
			}
			for (int i = 0; i < 5; i++)
			{
				cout << 'P' << seq[i].num << " "; // 배열에 저장된 순서대로 출력
			}
			cout << endl<< endl;
		}
		else // 5개의 process를 모두 처리하지 못한 경우 
			cout << "Unsafe 하다!\n\n";

	}
	return 0;
}
