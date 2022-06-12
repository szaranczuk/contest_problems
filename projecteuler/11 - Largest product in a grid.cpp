#include <bits/stdc++.h>

using namespace std;

vector<int> dy = {1, 0, -1, 0, 1, 1, -1, -1};
vector<int> dx = {0, 1, 0, -1, 1, -1, 1, -1};
int n = 20;

inline bool isInBoard(int y, int x) {return y >= 0 && y < n && x >= 0 && x < n;}

int main()
{
    vector<vector<int>> board(n);
    for (int i = 0; i < n; i++)
    {
        board[i].resize(n);
        for (int j = 0; j < n; j++) cin >> board[i][j];
    }
    long long max_res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                long long local_res = board[i][j];
                int y = i + dy[k];
                int x = j + dx[k];
                bool isValid = true;
                for (int l = 0; l < 3; l++)
                {
                    if (!isInBoard(y, x))
                    {
                        isValid = false;
                        break;
                    }
                    local_res *= board[y][x];
                    y += dy[k];
                    x += dx[k];
                }
                if (isValid) max_res = max(max_res, local_res);
            }
        }
    }
    cout << max_res << '\n';
}