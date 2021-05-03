#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    int B, S;
    scanf("%d %d", &B, &S);
    int cases_iterator = 1;
    while (B != 0 || S != 0)
    {
        std::vector<int> bachelors_ages;
        bachelors_ages.reserve(B);
        for (int i = 0; i < B; i++)
        {
            int bachelor_age;
            scanf("%d", &bachelor_age);
            bachelors_ages.push_back(bachelor_age);
        }
        std::vector<int> spinsters_ages;
        spinsters_ages.reserve(S);
        for (int i = 0; i < S; i++)
        {
            int spinster_age;
            scanf("%d", &spinster_age);
            spinsters_ages.push_back(spinster_age);
        }
        int not_matched_bachelors = std::max(0, B - S);
        if (not_matched_bachelors != 0)
        {
            int youngest_not_matched_bachelor = bachelors_ages[0];
            for (int bachelor_age : bachelors_ages)
                youngest_not_matched_bachelor = std::min(youngest_not_matched_bachelor, bachelor_age);
            printf("Case %d: %d %d\n", cases_iterator, not_matched_bachelors, youngest_not_matched_bachelor);
        }
        else
            printf("Case %d: 0\n", cases_iterator);
        cases_iterator++;
        scanf("%d %d", &B, &S);
    }
    return 0;
}
