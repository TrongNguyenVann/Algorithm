/*
 * LevelOrderTraversal.cpp
 *
 *  Created on: Jan 14, 2020
 *      Author: fading
 */

#include <bits/stdc++.h>
#include <list>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
      Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }

      /**
       * Traverse node with DFS algorithm
       * @param root
       */
    void levelOrderDFS(Node * root) {
      if (root == nullptr) {
        return;
      }
      std::cout << root->data << " ";
      if (root->left == nullptr && root->right == nullptr) {
        return;
      }
      if (root->left) {
        levelOrder(root->left);
      }
      if (root->right) {
        levelOrder(root->right);
      }
    }

    void levelOrder(Node * root) {
      if (root == nullptr) {
        return;
      }
      std::cout << root->data << " ";
      std::list<Node*> iterating_nodes{root};
      while(!iterating_nodes.empty()) {
        Node* curr_node = iterating_nodes.front();
        iterating_nodes.pop_front();
        if (curr_node->left) {
          std::cout << curr_node->left->data << " ";
          iterating_nodes.push_back(curr_node->left);
        }
        if (curr_node->right) {
          std::cout << curr_node->right->data << " ";
          iterating_nodes.push_back(curr_node->right);
        }
      }
    }

}; //End of Solution

int main() {
  Solution solution;

  // Root node
  Node* root_node = solution.insert(nullptr, 1);
  Node* next_node = solution.insert(root_node, 2);
  next_node = solution.insert(next_node, 5);
  solution.insert(next_node, 6);
  next_node = solution.insert(next_node, 3);
  next_node = solution.insert(root_node, 4);

  solution.levelOrder(root_node);
}


