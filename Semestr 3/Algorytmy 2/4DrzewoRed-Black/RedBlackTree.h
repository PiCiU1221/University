#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#pragma once

#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

template <typename T>
class RedBlackTree {
public:
	// Node class declaration, had to be public in order to retrieve the Node pointer in the main function
	template <typename T>
	class Node {
	public:
		T data;

		Node<T>* parent;
		Node<T>* left;
		Node<T>* right;

		bool isRed;

		int index;

		Node(T value, int index) : data(value), parent(nullptr), left(nullptr), right(nullptr), isRed(true), index(index) {}
	};

private:
	Node<T>* root;
	int size;

	int uniqueIndexIncrement;

	// Used in (b)
	// Recursive function that writes every node in preorder traversal
	void preOrderTraversalRecursive(Node<T>* node, std::vector<T>& result) {
		if (node != nullptr) {
			// If the node is not null add it to the vector
			result.push_back(node->data);

			// Recursively do the same for the left and right children of the node with the priority to the left
			preOrderTraversalRecursive(node->left, result);
			preOrderTraversalRecursive(node->right, result);
		}
	}

	// Used in (c)
	// Recursive function that writes every node in inorder traversal
	void inOrderTraversalRecursive(Node<T>* node, std::vector<T>& result) {
		if (node != nullptr) {
			// Go to the far left node
			inOrderTraversalRecursive(node->left, result);

			// Write this node's data to the vector
			result.push_back(node->data);

			// Go to the right and try to go for the far left if possible
			inOrderTraversalRecursive(node->right, result);
		}
	}

	// Used in (d)
	// Recursive function that deletes every node in postorder traversal
	void postOrderTraversalRecursiveDelete(Node<T>* node) {
		if (node != nullptr) {
			// Go to the far left node
			postOrderTraversalRecursiveDelete(node->left);

			// Go to the right and try to go for the far left if possible
			postOrderTraversalRecursiveDelete(node->right);

			// Delete node
			delete(node);
		}
	}

	// Used in (e)
	// Recursive function that calculated the tree height
	int heightRecursive(Node<T>* node) {
		if (node == nullptr) {
			return 0;
		}

		int leftHeight = heightRecursive(node->left);
		int rightHeight = heightRecursive(node->right);

		return (std::max(leftHeight, rightHeight) + 1);
	}

	// Returns the address of the parent element if there is one for the wanted value
	Node<T>* searchForPossibleParent(Node<T>* current, T value, int (*data_cmp)(T, T)) {
		if (current == nullptr) {
			return nullptr;
		}
		else if (data_cmp(value, current->data) < 0) {
			if (current->left == nullptr) {
				return current;
			}
			else {
				return searchForPossibleParent(current->left, value, data_cmp);
			}
		}
		else if (data_cmp(value, current->data) >= 0) {
			if (current->right == nullptr) {
				return current;
			}
			else {
				return searchForPossibleParent(current->right, value, data_cmp);
			}
		}

		return nullptr;
	}

	// Function that fixes the possible insert violations
	void violationFix(Node<T>* insertedNode) {
		if (insertedNode == root) {
			insertedNode->isRed = false;
			return;
		}

		Node<T>* parent = insertedNode->parent;
		if (parent == nullptr || parent->isRed == false) {
			return;  // No violation, the parent is black
		}

		Node<T>* grandparent = parent->parent;
		if (grandparent == nullptr) {
			return;  // No grandparent; it should not proceed as the parent isn't black
		}

		Node<T>* uncle = nullptr;

		if (grandparent->left == parent) {
			uncle = grandparent->right;
		}
		else {
			uncle = grandparent->left;
		}

		// Uncle is red
		if (uncle != nullptr && uncle->isRed == true) {
			grandparent->isRed = true;
			parent->isRed = false;
			uncle->isRed = false;

			violationFix(grandparent);
		}
		// Uncle is black
		else {
			// LL
			if (grandparent->left == parent && parent->left == insertedNode) {
				rotateRight(parent, grandparent);

				parent->isRed = false;
				grandparent->isRed = true;
			}
			// LR
			else if (grandparent->left == parent && parent->right == insertedNode) {
				rotateLeft(insertedNode, parent);
				rotateRight(insertedNode, grandparent);

				insertedNode->isRed = false;
				grandparent->isRed = true;
			}
			// RR
			else if (grandparent->right == parent && parent->right == insertedNode) {
				rotateLeft(parent, grandparent);

				parent->isRed = false;
				grandparent->isRed = true;
			}
			// RL
			else {
				rotateRight(insertedNode, parent);
				rotateLeft(insertedNode, grandparent);

				insertedNode->isRed = false;
				grandparent->isRed = true;
			}
		}
	}

	// Used in (g)
	// Recursive function to display Red-Black Tree structure
	void displayTreeRecursive(Node<T>* node, std::ostringstream& oss) {
		if (node != nullptr) {
			oss << "\t(" << std::setw(4) << node->index << ": ";

			if (node->parent != nullptr)
				oss << "[p: " << std::setw(4) << node->parent->index << ", ";
			else
				oss << "[p: NULL, ";

			if (node->left != nullptr)
				oss << "l: " << std::setw(4) << node->left->index << ", ";
			else
				oss << "l: NULL, ";

			if (node->right != nullptr)
				oss << "r: " << std::setw(4) << node->right->index << "], ";
			else
				oss << "r: NULL], ";

			oss << (node->isRed ? "Color: Red,   " : "Color: Black, ");
			oss << "Data: " << node->data << ")" << std::endl;

			displayTreeRecursive(node->left, oss); // Recursive call for the left child
			displayTreeRecursive(node->right, oss); // Recursive call for the right child
		}
	}

	// Used in (g) (shortened rbt display)
	// Recursive function that tries to display the first elements in the rbt
	void displayFirstNodesPostorder(Node<T>* node, int& count, std::ostringstream& oss) {
		if (node != nullptr && count > 0) {
			displayFirstNodesPostorder(node->left, count, oss);
			displayFirstNodesPostorder(node->right, count, oss);
			if (count > 0) {
				oss << "\t" << node->data << std::endl;
				count--;
			}
		}
	}

	// Used in (g) (shortened rbt display)
	// Recursive function that tries to display the last elements in the rbt
	void displayFirstNodesReversePreorder(Node<T>* node, int& count, std::ostringstream& oss) {
		if (node != nullptr && count > 0) {
			if (count > 0) {
				oss << "\t" << node->data << std::endl;
				count--;
			}
			displayFirstNodesReversePreorder(node->right, count, oss);
			displayFirstNodesReversePreorder(node->left, count, oss);
		}
	}

	// (h) rotacjê w lewo wskazanej pary dziecko-rodzic (argumenty: wskaŸnik na dziecko, wskaŸnik na
	// rodzica),

	void rotateLeft(Node<T>* child, Node<T>* parent) {
		parent->right = child->left;
		if (parent->right != nullptr) {
			parent->right->parent = parent;
		}

		child->left = parent;

		// Swap parents
		child->parent = parent->parent;
		parent->parent = child;

		// Change the root if the parent was root
		if (root == parent) {
			root = child;
			return;
		}

		if (child->parent->left == parent) {
			child->parent->left = child;
		}
		else {
			child->parent->right = child;
		}
	}

	// (i) rotacjê w prawo wskazanej pary dziecko-rodzic (argumenty: jak wy¿ej).

	void rotateRight(Node<T>* child, Node<T>* parent) {
		// Swap child and parent
		parent->left = child->right;
		if (parent->left != nullptr) {
			parent->left->parent = parent;
		}

		child->right = parent;

		// Swap parents
		child->parent = parent->parent;
		parent->parent = child;

		// Change the root if the parent was root
		if (root == parent) {
			root = child;
			return;
		}

		// Change the child pointer of the parent's parent before the rotation
		if (child->parent->left == parent) {
			child->parent->left = child;
		}
		else {
			child->parent->right = child;
		}
	}

public:
	// Constructor
	RedBlackTree() : root(nullptr), size(0), uniqueIndexIncrement(0) {}

	// Destruktor
	~RedBlackTree() { deleteAll(); }

	// (a) wyszukanie elementu (argumenty: dane wzorcowe oraz informacja lub komparator definiuj¹ce klucz wyszukiwania — np. wskaŸnik na funkcjê; wynik: wskaŸnik na odnaleziony element
	// drzewa lub NULL w przypadku niepowodzenia),

	Node<T>* findNode(T value, int (*data_cmp)(T, T)) {
		Node<T>* current = root;

		while (current != nullptr) {
			if (data_cmp(value, current->data) == 0) {
				return current;
			}
			else if (data_cmp(value, current->data) < 0) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}

		return nullptr;
	}

	// (b) przejœcie pre-order drzewa (argumenty i sposób przekazania wyniku wg uznania programisty,
	// mo¿liwe m.in.zostawienie wyniku — porz¹dku przejœcia — na zewnêtrznej liœcie przekazywanej
	// przez wskaŸnik w ramach rekurencji),

	std::vector<T> preOrderTraversal() {
		std::vector<T> result;
		preOrderTraversalRecursive(root, result);
		return result;
	}

	// (c) przejœcie in - order drzewa(argumenty i sposób przekazania wyniku jak wy¿ej),

	std::vector<T> inOrderTraversal() {
		std::vector<T> result;
		inOrderTraversalRecursive(root, result);
		return result;
	}

	// (d) czyszczenie drzewa tj. usuniêcie wszystkich elementów,

	void deleteAll() {
		postOrderTraversalRecursiveDelete(root);

		// The whole tree is empty so we set the root to nullptr
		root = nullptr;

		size = 0;
		uniqueIndexIncrement = 0;
	}

	// (e) wyznaczenie wysokoœci drzewa,

	int height() {
		return heightRecursive(root);
	}

	// (f) dodanie nowego elementu do drzewa (argumenty: dane i informacja lub komparator definiuj¹ce
	// klucz porz¹dkowania)

	void add(T value, int (*data_cmp)(T, T)) {
		// Insert the node
		Node<T>* newNode = new Node<T>(value, uniqueIndexIncrement++);
		Node<T>* parent = searchForPossibleParent(root, value, data_cmp);

		if (parent == nullptr) {
			root = newNode;
		}
		else if (data_cmp(value, parent->data) < 0) {
			parent->left = newNode;
			newNode->parent = parent;
		}
		else if (data_cmp(value, parent->data) >= 0) {
			parent->right = newNode;
			newNode->parent = parent;
		}

		size++;

		// Check if the tree needs fixing violations
		violationFix(newNode);
	}

	// (g) zwrócenie napisowej reprezentacji drzewa

	std::string to_string(bool displayAll = true) {
		std::ostringstream oss;

		oss << " Red-black tree:" << std::endl;
		oss << "\tSize: " << size << std::endl;
		//oss << "\tHeight: " << height() << std::endl;

		if (displayAll) {
			oss << "\t{" << std::endl;

			displayTreeRecursive(root, oss);

			oss << "\t}" << std::endl << std::endl;
		}
		else {
			// Number of the nodes displayed from the begining and from the end
			int count = 3;

			oss << "\n\tFirst 3 nodes: \n";
			displayFirstNodesPostorder(root, count, oss);
			oss << std::endl;

			// Need to reset the count variable for the recursive function
			count = 3;

			oss << "\tLast 3 nodes: \n";
			displayFirstNodesReversePreorder(root, count, oss);
			oss << std::endl;
		}

		return oss.str();
	}
};

#endif // REDBLACKTREE_H