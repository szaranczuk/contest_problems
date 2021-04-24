#include <iostream>
#include <vector>

bool isSolved = false;

int n, m;

void backtrack(int index, int prev_piece, int spaces, const std::vector<std::pair<int, int>>& pieces, int was_piece_used_bitmask, int last_piece)
{
    if (isSolved)
        return;
    if (index == spaces)
    {
        if (prev_piece == last_piece)
            isSolved = true;
        return;
    }
    for (int i = 0; i < m; i++)
    {
        if (!(was_piece_used_bitmask & (1 << i)))
        {
            if (pieces[i].first == prev_piece)
            {
                was_piece_used_bitmask ^= 1 << i;
                backtrack(index + 1, pieces[i].second, spaces, pieces, was_piece_used_bitmask, last_piece);
                was_piece_used_bitmask ^= 1 << i;
            }
            else if (pieces[i].second == prev_piece)
            {
                was_piece_used_bitmask ^= 1 << i;
                backtrack(index + 1, pieces[i].first, spaces, pieces, was_piece_used_bitmask, last_piece);
                was_piece_used_bitmask ^= 1 << i;
            }
        }
    }
}

int main()
{
    //int n;
    scanf("%d", &n);
    while (n != 0)
    {
        isSolved = false;
        //int m;
        scanf("%d", &m);
        int first_piece;
        int null;
        scanf("%d %d", &null, &first_piece);
        int last_piece;
        scanf("%d %d", &last_piece, &null);
        std::vector<std::pair<int, int>> pieces;
        pieces.reserve(m);
        for (int i = 0; i < m; i++)
        {
            int piece_front, piece_back;
            scanf("%d %d", &piece_front, &piece_back);
            pieces.push_back({piece_front, piece_back});
        }
        backtrack(0, first_piece, n, pieces, 0, last_piece);
        if(isSolved)
            printf("YES\n");
        else
            printf("NO\n");
        scanf("%d", &n);
    }
    return 0;
}
