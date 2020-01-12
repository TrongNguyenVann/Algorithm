#include <iostream>
#include <vector>


class Neighbour {
  int node_name;  // Index of the node
  int distance;  // Distance of this node to node with index neighbour_name
  int neighbour_name;  // Index of the node that measure distance to this node

public:
	Neighbour(int node_name, int distance, int neighbour_name) {
		this->node_name = node_name;
		this->distance = distance;
		this->neighbour_name = neighbour_name;
	}

  int getDistance() const {
    return distance;
  }

  void setDistance(int distance) {
    this->distance = distance;
  }

  int getNeighbourName() const {
    return neighbour_name;
  }

  void setNeighbourName(int neighbourName) {
    neighbour_name = neighbourName;
  }

  int getNodeName() const {
    return node_name;
  }

  void setNodeName(int nodeName) {
    node_name = nodeName;
  }
};

class DistanceLabel {
  int value_;  // Store the temporary distance to source node
  bool is_visited_;  // Store the status whether this node is visited or not

public:
	DistanceLabel(int value, bool is_visited = false) {
		this->value_ = value;
		this->is_visited_ = is_visited;
	}

	int getValue() const {
	  return value_;
	}

	void setValue(int value) {
	  value_ = value;
	}

	bool isVisited() const {
	  return is_visited_;
	}

	void setIsVisited(bool is_visited) {
	  is_visited_ = is_visited;
	}

	friend std::ostream& operator<<(
	    std::ostream& out, const DistanceLabel& label) {
	  out << "DistanceLabel(" << label.value_ << " "
	      << std::boolalpha << label.is_visited_ << ")";
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
		if (distance_values[i].isVisited() == true ||
		    distance_values[i].getValue() == -1) {
			continue;
		}

		// Initialize
		if (min_distance == 0 || distance_values[i].getValue() < min_distance) {
			min_distance = distance_values[i].getValue();
			added_node = i;
		}
	}
	visited_nodes.push_back(added_node);
	distance_values[added_node].setIsVisited(true);
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
		int distance_value =
		    distance_values[last_visited_node].getValue() + neighbour.getDistance();
			if (distance_values[neighbour.getNodeName()].getValue() == -1 ||
				  distance_values[neighbour.getNodeName()].getValue() > distance_value) {
				distance_values[neighbour.getNodeName()].setValue(distance_value);
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
