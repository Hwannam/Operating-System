#include <iostream>
using namespace std;

int LRU(int ary[], int len)
{
	int frame[4]; //frame 행렬
	fill_n(frame, 4, -1); // 비어있는 것을 -1로 설정
	int length = len;
	int check[4];// frame안의 원소들이 이전에 등장했는지 체크
	int index;
	int pfault = 0; // page fault의 수

	for (int i = 0; i < length; i++)
	{
		bool more = true;
		bool exist = false;
		for (int j = 0; j < 4; j++) // frame안에 이미 들어있다면 page fault 발생 X
		{
			if (frame[j] == ary[i])
				exist = true;
		}

		if (exist == false) // frame안에 없을때만 page fault 발생
		{
			for (int j = 0; j < 4; j++)
			{
				if (frame[j] == -1) // frame이 비어있다면 비어있는 곳에 추가
				{
					frame[j] = ary[i];
					more = false;
					pfault++;
					break;
				}
			}

			if (more == true) // frame이 가득 차있을때
			{
				fill_n(check, 4, 0);

				for (int j = i - 1; j >= 0; j--) // 앞의 원소를 탐색
				{
					int count = 0;
					for (int k = 0; k < 4; k++) //frame에 있는 것과 동일한 것을 찾으면 check에서 해당 index를 1로
					{
						if (frame[k] == ary[j])
							check[k] = 1;
					}
					for (int k = 0; k < 4; k++) //check안에 0 값을 갖는 index를 새 값을 추가할 index로. 현재 원소로 부터 가장 먼 원소가 삭제될 것
					{
						if (check[k] == 0)
							index = k;
						else
							count++;
					}
					if (count == 3)// frame안의 4개 원소중 3개가 이미 등장했다면 탐색 종료
						break;
				}
				frame[index] = ary[i];
				pfault++;
			}
			for (int j = 0; j < 4; j++) //등장하지 않은 원소값의 index에 새 원소 추가
				cout << frame[j];
			cout << endl;
		}
	}
	return pfault;
}

int Optimal(int ary[], int len)
{
	int frame[4]; // frame 행렬
	fill_n(frame, 4, -1); // 비어있는 것을 -1로 설정
	int length = len;
	int check[4]; // frame안의 원소들이 뒤에 등장하는 것을 체크
	int index;
	int pfault = 0; // page fault의 수

	for (int i = 0; i < length; i++)
	{
		bool more = true;
		bool exist = false;
		for (int j = 0; j < 4; j++) // frame안에 이미 들어있다면 page fault 발생 X
		{
			if (frame[j] == ary[i])
				exist = true; 
		}

		if (exist == false) // frame안에 없을때만 page fault 발생
		{
			for (int j = 0; j < 4; j++)
			{
				if (frame[j] == -1) // frame이 비어있다면 비어있는 곳에 추가
				{
					frame[j] = ary[i];
					more = false;
					pfault++;
					break;
				}
			}

			if (more == true) // frame이 가득 차있을때
			{
				fill_n(check, 4, 0);

				for (int j = i + 1; j < length; j++) // 뒤의 원소를 탐색
				{
					int count = 0;
					for (int k = 0; k < 4; k++) //frame에 있는 것과 동일한 것을 찾으면 check에서 해당 index를 1로
					{
						if (frame[k] == ary[j])
							check[k] = 1;
					}
					for (int k = 0; k < 4; k++) //check안에 0 값을 갖는 index를 새 값을 추가할 index로. 현재 원소로 부터 가장 먼 원소가 삭제될 것
					{
						if (check[k] == 0)
							index = k;
						else
							count++;
					}
					if (count == 3) // frame안의 4개 원소중 3개가 이미 등장했다면 탐색 종료
						break;
				}
				frame[index] = ary[i]; //등장하지 않은 원소값의 index에 새 원소 추가
				pfault++;
			}
			for (int j = 0; j < 4; j++)
				cout << frame[j];
			cout << endl;
		}
	}
	return pfault;
}


int main()
{
	int num;
	int ary[] = { 1,2,3,2,5,6,3,4,6,3,7,3,1,5,3,6,3,4,2,4,3,4,5,1 };
	bool tr = true;
	while (tr)
	{
		cout << "How many page faults would occur?" << endl;
		cout << "1) LRU replacement     2) Optimal replacement     3)End:  ";
		cin >> num;
		cout << endl;

		switch (num)
		{
		case 1:
			cout << endl << "LRU replacement의 page fault는 " << LRU(ary, 24) << "개 입니다." << endl << endl;
			break;
		case 2:
			cout << endl << "Optimal replacement의 page fault는 " << Optimal(ary, 24) << "개 입니다." << endl << endl;
			break;
		case 3:
			tr = false;
			break;
		}
	}
	return 0;
}
