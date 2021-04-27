/*********************************************************************************************
*                         I was writing this for about 4 hours                               *
*                            max 1h was for problem solving                                  *
*           the rest was for IO, and for fixing bugs created by rewriting code for IO        *
**********************************************************************************************/

#include <iostream>
#include <vector>

std::vector<std::string> compute_for_d(std::string representation, int& index, int rows, int columns);

std::string compute_for_b(std::vector<std::vector<bool>>& representation, int min_row, int max_row, int min_column, int max_column);

int main()
{
    char format;
    std::cin >> format;
    int rows, columns;
    std::cin >> rows >> columns;
    while (true)
    {
        std::string full_input;
        std::string input;
        std::getline(std::cin, input);
        if (input[0] == '#')
            goto hash_char;
        while (input[1] != ' ')
        {
            full_input += input;
            std::getline(std::cin, input);
            if (input[0] == '#')
                goto hash_char;
        }
        hash_char:
        if (format == 'D')
        {
            std::string representation;
            representation += full_input;
            std::cout << "B ";
            if (rows - 99 > 0)
            {

            }
            else if (rows - 9 > 0)
                std::cout << " ";
            else
                std::cout << "  ";
            std::cout << rows << " ";
            if (columns - 99 > 0)
            {

            }
            else if (columns - 9 > 0)
                std::cout << " ";
            else
                std::cout << "  ";
            std::cout << columns << '\n';
            int index = 0;
            std::vector<std::string> vector_result = compute_for_d(representation, index, rows, columns);
            std::string result;
            for (auto row : vector_result)
                result += row;
            for(int i = 0; i < result.size(); i++)
            {
                if (i % 50 == 0 && i != 0)
                    std::cout << '\n';
                std::cout << result[i];
            }
            std::cout << '\n';
        }
        else
        {
            //std::cout << full_input << '\n';
            std::vector<std::vector<bool>> representation;
            for (int i = 0; i < rows; i++)
            {
                std::vector<bool> row;
                for (int j = 0; j < columns; j++)
                {
                    row.push_back((bool) (full_input[i * columns + j] - '0'));
                    //std::cout << (bool) (full_input[i * columns + j] - '0');
                   // std::cout << row[j];
                }
                //std::cout << '\n';
                representation.push_back(row);
            }
            std::cout << "D ";
            if (rows - 99 > 0)
            {

            }
            else if (rows - 9 > 0)
                std::cout << " ";
            else
                std::cout << "  ";
            std::cout << rows << " ";
            if (columns - 99 > 0)
            {

            }
            else if (columns - 9 > 0)
                std::cout << " ";
            else
                std::cout << "  ";
            std::cout << columns << '\n';
            //std::cout << representation[1][3];
            std::string result = compute_for_b(representation, 0, rows, 0, columns);
            for(int i = 0; i < result.size(); i++)
            {
                if (i % 50 == 0 && i != 0)
                    std::cout << '\n';
                std::cout << result[i];
            }
            std::cout << '\n';
        }
        if (input[0] == '#')
            break;
        format = input[0];
        bool wasRows = false;
        bool isCurrentlyDimension = false;
        //std::cout << "\n\n" << input;
        std::string s_rows;
        std::string s_columns;
        for (int i = 1; i < input.size(); i++)
        {
            char dimension = input[i];
            if (dimension != ' ')
            {
                isCurrentlyDimension = true;
                if (wasRows)
                {
                    //std::cout << "dupa";
                    s_columns += dimension;
                }
                else
                {
                    //std::cout << "dupa2";
                    s_rows += dimension;
                }
            }
            else
            {
                //std::cout << "dupa1";
                if (isCurrentlyDimension)
                {
                    isCurrentlyDimension = false;
                    wasRows = true;
                }
            }
        }
        rows = std::stoi(s_rows);
        columns = std::stoi(s_columns);

    }
    return 0;
}

std::vector<std::string> compute_for_d(std::string representation, int& index, int rows, int columns)
{
    if (index >= representation.size())
        return {};
    if  (rows * columns <= 0)
    {
        return {};
    }
    std::vector<std::string> result (rows);
    if (representation[index] == 'D')
    {
        index++;
        std::vector<std::string> q1;
        std::vector<std::string> q2;
        std::vector<std::string> q3;
        std::vector<std::string> q4;
        q1 = compute_for_d(representation, index, (rows + 1) / 2, (columns + 1) / 2);
        q2 = compute_for_d(representation, index, (rows + 1) / 2, columns / 2);
        q3 = compute_for_d(representation, index, rows / 2, (columns + 1) / 2);
        q4 = compute_for_d(representation, index, rows / 2, columns / 2);
        for (int i = 0; i < (rows + 1) / 2; i++)
        {
            if (i < q1.size())
                result[i] += q1[i];
            if (i < q2.size())
                result[i] += q2[i];
        }
        int res_index = 0;
        for (int i = (rows + 1) / 2; i < rows; i++)
        {
            if (res_index < q3.size())
                result[i] += q3[res_index];
            if (res_index < q4.size())
                result[i] += q4[res_index];
            res_index++;
        }
     }
    else if (representation[index] == '1')
    {
        index++;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                result[i].push_back('1');
            }
        }
    }
    else if (representation[index] == '0')
    {
        index++;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                result[i].push_back('0');
            }
        }
    }
    return result;
}

std::string compute_for_b(std::vector<std::vector<bool>>& representation, int min_row, int max_row, int min_column, int max_column)
{
    std::string result;
    bool first_field = representation[min_row][min_column];
    for (int i = min_row; i < max_row; i++)
    {
        for (int j = min_column; j < max_column; j++)
        {
            bool dupa = representation[i][j];
            if (representation[i][j] != first_field)
            {
                result += 'D';
                result += compute_for_b(representation, min_row, (min_row + max_row + 1) / 2, min_column, (min_column + max_column + 1) / 2);
                if ((min_column + max_column + 1) / 2 < max_column)
                    result += compute_for_b(representation, min_row, (min_row + max_row + 1) / 2, (min_column + max_column + 1) / 2, max_column);
                if ((min_row + max_row + 1) / 2 < max_row)
                    result += compute_for_b(representation, (min_row + max_row + 1) / 2, max_row, min_column, (min_column + max_column + 1) / 2);
                if ((min_row + max_row + 1) / 2 < max_row && (min_column + max_column + 1) / 2 < max_column)
                    result += compute_for_b(representation, (min_row + max_row + 1) / 2, max_row, (min_column + max_column + 1) / 2, max_column);
                return result;
            }
        }
    }
    result += std::to_string(first_field);
    return result;
}

