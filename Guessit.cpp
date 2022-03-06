#include <bits/stdc++.h>

using namespace std;

int selectNumber(int low, int high);
char getHostAnswer(int X);

int main()
{
    int X,low(1),high(100);
    cout << "Let's play!\n";

    char answer;
    do
    {
        X=selectNumber(low,high);
        answer = getHostAnswer(X);
        if(answer=='>') high=X-1;
        else if(answer=='<') low=X+1;
        else cout << "Your number is " << X <<"\n";
    }while(answer != '=');

    return 0;
}

char getHostAnswer(int X)
{
    char answer;
    cout << "Is " << X <<" your number? ";
    cin >> answer;
    return answer;
}

int selectNumber(int low, int high)
{
    return (low+high)/2;
}
