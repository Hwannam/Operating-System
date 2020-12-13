#include <iostream>
using namespace std;

int LRU(int ary[],int len)
{
	int frame[4];
	fill_n(frame, 4, -1);
	int length = len;
	int check[4];
	int index;
	int pfault = 0;
	
	for (int i = 0; i < length; i++)
	{
		bool more = true;
		bool exist = false;
		for (int j = 0; j < 4; j++)
		{
			if (frame[j] == ary[i])
				exist = true;
		}

		if (exist == false)
		{
			for (int j = 0; j < 4; j++)
			{
				if (frame[j] == -1)
				{
					frame[j] = ary[i];
					more = false;
					pfault++;
					break;
				}
			}

			if (more == true)
			{
				fill_n(check, 4, 0);

				for (int j = i + 1; j < length; j++)
				{
					int count = 0;
					for (int k = 0; k < 4; k++)
					{
						if (frame[k] == ary[j])
							check[k] = 1;
					}
					for (int k = 0; k < 4; k++)
					{
						if (check[k] == 0)
							index = k;
						else
							count++;
					}
					if (count == 3)
						break;
				}
				frame[index] = ary[i];
				pfault++;
			}
			for (int j = 0; j < 4; j++)
				cout << frame[j];
			cout << endl;
		}
	}	
	return pfault;
}

int Optimal(int ary[],int len)
{
	int frame[4];
	fill_n(frame, 4, -1);
	int length = len;
	int check[4];
	int index;
	int pfault = 0;

	for (int i = 0; i < length; i++)
	{
		bool more = true;
		bool exist = false;
		for (int j = 0; j < 4; j++)
		{
			if (frame[j] == ary[i])
				exist = true;
		}

		if (exist == false)
		{
			for (int j = 0; j < 4; j++)
			{
				if (frame[j] == -1)
				{
					frame[j] = ary[i];
					more = false;
					pfault++;
					break;
				}
			}

			if (more == true)
			{
				fill_n(check, 4, 0);

				for (int j = i - 1; j >=0; j--)
				{
					int count = 0;
					for (int k = 0; k < 4; k++)
					{
						if (frame[k] == ary[j])
							check[k] = 1;
					}
					for (int k = 0; k < 4; k++)
					{
						if (check[k] == 0)
							index = k;
						else
							count++;
					}
					if (count == 3)
						break;
				}
				frame[index] = ary[i];
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
	int ary[] = { 1,2,3,2,5,6,3,4,6,3,7,3,1,5,3,6,3,4,2,4,3,4,5,1};
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
			cout << endl << "LRU replacement의 page fault는 " << LRU(ary,24) << "개 입니다." << endl << endl;
			break;
		case 2:
			cout << endl <<"Optimal replacement의 page fault는 " << Optimal(ary,24) << "개 입니다."<< endl << endl;
			break;
		case 3:
			tr = false;
			break;
		}
	}
	return 0;
}
