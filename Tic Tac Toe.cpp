#include<bits/stdc++.h>
using namespace std;
int win[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
				 {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
				 {0, 4, 8}, {2, 4, 6}};
int player[2] = {0};
int rec[9] = {0};
int place[3][3] = {0};
int end = 0;

int com()
{
	int o = 0, x = 0;
	for(int a = 0; 8 > a; a++)
	{
		int w = 0;
		for(int b = 0; 3 > b; b++)
		{
			if(rec[win[a][b]] == 2){break;}
			if(rec[win[a][b]] == 1){w++;}
			if(b == 2){o++;}
		}
		int w1 = 0;
		for(int b = 0; 3 > b; b++)
		{
			if(rec[win[a][b]] == 1){break;}
			if(rec[win[a][b]] == 2){w++;}
			if(b == 2){x++;}
		}
		if(player[1] == 1&&w ==3){return -10000;}
		if(player[1] == 2&&w1 ==3){return -10000;}
	}
	if(player[2] == 1){return o-x;}
	else{return x-o;}
}

int ai(){
	int min = 10, t = 0;
	for(int a = 0; 3 > a; a++)
	{
		for(int b = 0; 3 > b; b++)
		{
			if(place[b][a] == 0){
				rec[a*3+b] = player[2];
				t = com();
				if(min > t){min = t;}
				rec[a*3+b] = 0;
			}
		}
	}
	return min;
}

int main()
{
	int num;
	cout << "叉叉請輸入1，圈圈請輸入2" << endl;
	cin >> num;
	player[1] = num;
	if(num == 1){player[2] = 2;}
	else{player[2] = 1;}
		for(int a = 0; 3 > a; a++) //輸出目前情況 
		{
			if(a == 0){cout << "     1   2   3 " << endl << "   -------------" << endl;}
			cout << " " << a+1 << " |";
			for(int b = 0; 3 > b; b++)
			{
				if(place[b][a] == 1){cout << " X ";}
				if(place[b][a] == 2){cout << " O ";}
				if(place[b][a] == 0){cout << "   ";}
				cout << "|";
			}
			cout << endl;
			cout << "   -------------" << endl;
		}
	while(1)
	{
		int x, y, xx = 0, yy = 0, max = -10;
		cout << endl << "    請輸入座標" << endl << endl; 
		cin >> x >> y; //玩家優先出手
		while(place[x-1][y-1] > 0){cout << endl << "已有物體請重新輸入" << endl << endl; cin >> x >> y;}
		rec[(y-1)*3+(x-1)] = player[1];
		place[x-1][y-1] = player[1];
		cout << endl << "    玩家的回合" << endl << endl;;
		for(int a = 0; 3 > a; a++) //輸出目前情況 
		{
			if(a == 0){cout << "     1   2   3 " << endl << "   -------------" << endl;}
			cout << " " << a+1 << " |";
			for(int b = 0; 3 > b; b++)
			{
				if(place[b][a] == 1){cout << " X ";}
				if(place[b][a] == 2){cout << " O ";}
				if(place[b][a] == 0){cout << "   ";}
				cout << "|";
			}
			cout << endl;
			cout << "   -------------" << endl;
		}
		for(int a = 0; 8 > a; a++) //判斷是否贏了 
		{
			for(int b = 0; 3 > b; b++)
			{
				if(rec[win[a][b]] != player[1]){break;}
				if(b == 2){cout << "You win." << endl; end = 1;}
			}
		}
		
		if(end == 1){break;} //遊戲結束 
		
		for(int a = 0; 3 > a; a++)
		{
			for(int b = 0; 3 > b; b++)
			{
				if(place[b][a] == 0){
					rec[a*3+b] = player[2];
					for(int c = 0; 7 >= c; c++) //判斷玩家是否輸了 
					{
						for(int d = 0; 3 > d; d++)
						{
							if(rec[win[c][d]] != player[2]){break;}
							if(d == 2){
								place[b][a] = player[2];
									for(int a = 0; 3 > a; a++) //輸出目前情況 
										{
										if(a == 0){cout << "     1   2   3 " << endl << "   -------------" << endl;}
										cout << " " << a+1 << " |";
										for(int b = 0; 3 > b; b++)
										{
											if(place[b][a] == 1){cout << " X ";}
											if(place[b][a] == 2){cout << " O ";}
											if(place[b][a] == 0){cout << "   ";}
											cout << "|";
										}
										cout << endl;
										cout << "   -------------" << endl;
									}
								cout << "You lose." << endl; end = 1; break;}
						}
						if(end == 1){break;} //遊戲結束 
					}
					rec[a*3+b] = 0;
					if(end == 1){break;} //遊戲結束
					
					for(int y = 0; 3 > y; y++) //判斷玩家是否快贏了 
					{
						for(int x = 0; 3 > x; x++)
						{
							if(rec[y*3+x] == 0){
								rec[y*3+x] = player[1];
								for(int c = 0; 8 > c; c++)
								{
									int n = 0;
									for(int d = 0; 3 > d; d++)
									{
										if(rec[win[c][d]] == player[1]){n++;}
										else{break;}
									}
									if(n == 3){xx = x; yy = y; end = 1; break;}
								}
								rec[y*3+x] = 0;
							}
							if(end == 1){break;} //回合結束 
						}
						if(end == 1){break;} //回合結束 
					}
					if(end == 0){int t = ai(); if(t > max){max = t; xx = b; yy = a;}rec[a*3+b] = 0;}
					else{end = 0;}
						
				}
				if(end == 1){break;} //遊戲結束 
			}
			if(end == 1){break;} //遊戲結束 
		}
		if(end == 1){break;} //遊戲結束 
		
		place[xx][yy] = player[2];
		rec[yy*3+xx] = player[2];
		cout << endl << "    電腦的回合" << endl << endl;
		for(int a = 0; 3 > a; a++) //輸出目前情況 
		{
			if(a == 0){cout << "     1   2   3 " << endl << "   -------------" << endl;}
			cout << " " << a+1 << " |";
			for(int b = 0; 3 > b; b++)
			{
				if(place[b][a] == 1){cout << " X ";}
				if(place[b][a] == 2){cout << " O ";}
				if(place[b][a] == 0){cout << "   ";}
				cout << "|";
			}
			cout << endl;
			cout << "   -------------" << endl;
		}
		if(num == 1){num = 0;}
		else{num = 1;}
		for(int a = 0; 9 > a; a++)
			{
				if(rec[a] == 0){break;}
				if(a == 8){cout << "Tie." << endl; end = 1;}
			}
			if(end == 1){break;}
		}
	}
