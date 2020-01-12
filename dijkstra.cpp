#include <iostream>
#include <vector>


class Neighbour {
public:
	Neighbour(int node_name, int distance, int neighbour_name) {
		this->node_name = node_name;
		this->distance = distance;
		this->neighbour_name = neighbour_name;
	}

	int node_name;
	int distance;
	int neighbour_name;
};

class DistanceLabel {
public:
	int value;
	bool is_visited;

	DistanceLabel(int value, bool is_visited = false) {
		this->value = value;
		this->is_visited = is_visited;
	}

	friend std::ostream& operator<<(std::ostream& out, const DistanceLabel& label) {
	  out << "DistanceLabel(" << label.value << " " << std::boolalpha << label.is_visited << ")";
	  return out;
	}
};

std::vector<Neighbour> FindNeighbourNodes(
	int input_node, const std::vector<std::vector<int>>& weight_matrix) {
	std::vector<Neighbour> results;
	for (int i = 0; i < weight_matrix[input_node].size(); ++i) {
		int weight = weight_matrix[input_node][i];
		if (weight > 0) {
			results.push_back(Neighbour(i, weight, input_node));
		}
	}
	return results;
}


void AddShortestPathNode(
	std::vector<DistanceLabel>& distance_values,
	std::vector<int>& visited_nodes) {

	int added_node(0);
	int min_distance(0);
	for (int i = 0; i < distance_values.size(); ++i) {
		if (distance_values[i].is_visited == true || distance_values[i].value == -1) {
			continue;
		}

		// Initialize
		if (min_distance == 0 || min_distance > distance_values[i].value) {
			min_distance = distance_values[i].value;
			added_node = i;
		}
	}
	visited_nodes.push_back(added_node);
	distance_values[added_node].is_visited = true;
}

template <class T>
void PrintVector(const std::vector<T> input) {
  std::cout << "[";
  for (int i = 0; i < input.size(); ++i) {
    std::cout << input[i];
    if (i != input.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

int main() {

	std::vector<std::vector<int>> weight_matrix = {
		{0, 4, 0, 0, 0, 0, 0, 8, 0},   // 0
		{4, 0, 8, 0, 0, 0, 0, 11, 0},  // 1
		{0, 8, 0, 7, 0, 4, 0, 0, 2},   // 2
		{0, 0, 7, 0, 9, 14, 0, 0, 0},  // 3
		{0, 0, 0, 9, 0, 10, 0, 0, 0},  // 4
		{0, 0, 4, 14, 10, 0, 2, 0, 0}, // 5
		{0, 0, 0, 0, 0, 2, 0, 1, 6},   // 6
		{8, 11, 0, 0, 0, 0, 1, 0, 7},  // 7
		{0, 0, 2, 0, 0, 0, 6, 7, 0},   // 8
	};

	// Get the number of vertex
	const int kNumberVertex = weight_matrix.front().size();

	// List of visited node
	std::vector<int> visited_nodes = {0};

	// List of temporary distance value of other nodes to source node
	std::vector<DistanceLabel> distance_values = {
		DistanceLabel{0, true},
		DistanceLabel{-1},
		DistanceLabel{-1},
		DistanceLabel{-1},
		DistanceLabel{-1},
		DistanceLabel{-1},
		DistanceLabel{-1},
		DistanceLabel{-1},
		DistanceLabel{-1}};

	while (visited_nodes.size() < kNumberVertex) {
		int last_visited_node = visited_nodes.back();
		std::vector<Neighbour> neighbours = FindNeighbourNodes(
			last_visited_node,
			weight_matrix);

		// Update distance value
		for (const auto& neighbour : neighbours) {
			int distance_value = distance_values[last_visited_node].value + neighbour.distance;
			if (distance_values[neighbour.node_name].value == -1 ||
				  distance_values[neighbour.node_name].value > distance_value) {
				distance_values[neighbour.node_name].value = distance_value;
			}
		}

		// Add one node to visited_node list
		AddShortestPathNode(distance_values, visited_nodes);

		// Debug
		static int iterator_number(0);
		std::cout << "Iterator number: " << iterator_number++ << ":\n";
		std::cout << "Visited node:\n";
		PrintVector(visited_nodes);
		std::cout << std::endl;

		std::cout << "Distance values:\n";
		PrintVector(distance_values);
		std::cout << std::endl;
	}
	return 0;
}
