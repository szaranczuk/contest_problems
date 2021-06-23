#include <iostream>
#include <vector>
#include <queue>

int rows, columns;

std::vector<int> dy = {1, 0, -1, 0};
std::vector<int> dx = {0, 1, 0, -1};

std::vector<std::vector<int>> distance;
std::vector<std::vector<bool>> canStandHere;

void BFS(int y_source, int x_source)
{
	distance[y_source][x_source] = 0;
	canStandHere[y_source][x_source] = false;
	std::queue<std::pair<int, int>> BFS_queue;
	BFS_queue.push({y_source, x_source});
	while (!BFS_queue.empty())
	{
		auto vertex = BFS_queue.front();
		BFS_queue.pop();
		for (int i = 0; i < 4; i++)
		{
			int new_y = vertex.first + dy[i];
			int new_x = vertex.second + dx[i];
			if (new_y < rows && new_y >= 0)
			{
				if (new_x < columns && new_x >= 0)
				{
					if (canStandHere[new_y][new_x])
					{
						distance[new_y][new_x] = distance[vertex.first][vertex.second] + 1;
						canStandHere[new_y][new_x] = false;
						BFS_queue.push({new_y, new_x});
					}
				}
			}
		}
	}
}

int main()
{
	scanf("%d %d", &rows, &columns);
	while (rows != 0 || columns != 0)
	{
		distance.resize(rows);
		canStandHere.clear();
		canStandHere.resize(rows);
		for (int i = 0; i < rows; i++)
		{
			distance[i].resize(columns);
			canStandHere[i].assign(columns, true);
		}
		int rows_containing_bombs;
		scanf("%d", &rows_containing_bombs);
		for (int i = 0; i < rows_containing_bombs; i++)
		{
			int row_index, number_of_bombs;
			scanf("%d %d", &row_index, &number_of_bombs);
			for (int j = 0; j < number_of_bombs; j++)
			{
				int column_index;
				scanf("%d", &column_index);
				canStandHere[row_index][column_index] = false;
			}
		}
		int source_row, source_column;
		scanf("%d %d", &source_row, &source_column);
		BFS(source_row, source_column);
		int destination_row, destination_column;
		scanf("%d %d", &destination_row, &destination_column);
		printf("%d\n", distance[destination_row][destination_column]);
		scanf("%d %d", &rows, &columns);
	}
}