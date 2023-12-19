#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#pragma once

#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
class BinarySearchTree {
public:
	// Node class declaration, had to be public in order to retrieve the Node pointer in the main function
	template <typename T>
	class Node {
	public:
		T data;

		Node<T>* parent;
		Node<T>* left;
		Node<T>* right;

		int index;

		Node(T value, int index) : data(value), parent(nullptr), left(nullptr), right(nullptr), index(index) {}
	};

private:
	Node<T>* root;

	int size;
	int uniqueIndexIncrement;

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

	// Iterates through the whole tree and displays its components
	void displayTreeRecursive(Node<T>* node, std::ostringstream& oss) {
		if (node != nullptr) {
			oss << "\t(" << node->index << ": ";
			if (node->parent != nullptr)
				oss << "[p: " << node->parent->index << ", ";
			else
				oss << "[p: NULL, ";

			if (node->left != nullptr)
				oss << "l: " << node->left->index << ", ";
			else
				oss << "l: NULL, ";

			if (node->right != nullptr)
				oss << "r: " << node->right->index << "], data: " << node->data << "), " << std::endl;
			else
				oss << "r: NULL], data: " << node->data << "), " << std::endl;

			displayTreeRecursive(node->left, oss);
			displayTreeRecursive(node->right, oss);
		}
	}

	// Used in (c)
	// Returns the smallest Node on the right subtree
	Node<T>* findSmallestOnRightSubtree(Node<T>* toDelete) {
		Node<T>* current = toDelete->right;

		while (current->left != nullptr) {
			current = current->left;
		}

		return current;
	}

	// Used in (d)
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

	// Used in (e)
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

	// Used in (f)
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

	// Used in (g)
	// Recursive function that calculated the tree height
	int heightRecursive(Node<T>* node) {
		if (node == nullptr) {
			return 0;
		}

		int leftHeight = heightRecursive(node->left);
		int rightHeight = heightRecursive(node->right);

		return (std::max(leftHeight, rightHeight) + 1);
	}

	// Used in (h) (full bst display)
	// Additional function that could help in visualizing the BST
	void displayTreeVisual(Node<T>* node, std::ostringstream& oss, std::string prefix, bool isLeft) {
		if (node != nullptr) {
			oss << prefix;
			oss << (isLeft ? "+-- " : "\\-- ");
			oss << node->data << std::endl;

			// Recursively display the right child
			displayTreeVisual(node->right, oss, prefix + (isLeft ? "|   " : "    "), false);
			// Recursively display the left child
			displayTreeVisual(node->left, oss, prefix + (isLeft ? "    " : "|   "), true);
		}
	}

	// Used in (h) (shortened bst display)
	// Recursive function that tries to display the first elements in the bst
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

	// Used in (h) (shortened bst display)
	// Recursive function that tries to display the last elements in the bst
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

public:
	// Constructor
	BinarySearchTree() : root(nullptr), size(0), uniqueIndexIncrement(0) {}

	// Destruktor
	~BinarySearchTree() { deleteAll(); }

	// (a) dodanie nowego elementu do drzewa (argumenty: dane i informacja lub komparator definiujące
	// klucz porządkowania / wyszukiwania — np.wskaźnik na funkcję),

	void add(T value, int (*data_cmp)(T, T)) {
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
	}

	// (b) wyszukanie elementu (argumenty: dane wzorcowe oraz informacja lub komparator definiujące
	// klucz wyszukiwania; wynik: wskaźnik na odnaleziony element drzewa lub NULL w przypadku
	// niepowodzenia),

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

		return NULL;
	}

	// (c) usuwanie znalezionego wcześniej węzła drzewa (argumenty: wskaźnik na węzeł do usunięcia),

	void deleteNode(Node<T>* toDelete, int (*data_cmp)(T, T)) {
		Node<T>* parent = toDelete->parent;

		// No children (leaf)
		if (toDelete->left == nullptr && toDelete->right == nullptr) {
			// toDelete node doesnt have a parent
			if (parent == nullptr) {
				root = nullptr;
			}
			// toDelete node is the left child of their parent
			else if (parent->left == toDelete) {
				parent->left = nullptr;
			}
			// toDelte node is the right parent of their parent
			else {
				parent->right = nullptr;
			}
		}

		// Only left child
		else if (toDelete->left != nullptr && toDelete->right == nullptr) {
			// toDelete node doesnt have a parent
			if (parent == nullptr) {
				root = toDelete->left;
			}
			// toDelete node is the left child of their parent
			else if (parent->left == toDelete) {
				parent->left = toDelete->left;
				toDelete->left->parent = parent;
			}
			// toDelete node is the right child of their parent
			else {
				parent->right = toDelete->left;
				toDelete->left->parent = parent;
			}
		}

		// Only right child
		else if (toDelete->left == nullptr && toDelete->right != nullptr) {
			// toDelete node doesnt have a parent
			if (parent == nullptr) {
				root = toDelete->right;
			}
			// toDelete node is the left child of their parent
			else if (parent->left == toDelete) {
				parent->left = toDelete->right;
				toDelete->right->parent = parent;
			}
			// toDelete node is the right child of their parent
			else {
				parent->right = toDelete->right;
				toDelete->right->parent = parent;
			}
		}

		// Both childen
		else if (toDelete->left != nullptr && toDelete->right != nullptr) {
			Node<T>* smallestOnRightSubtree = findSmallestOnRightSubtree(toDelete);
			Node<T>* parentOfSmallest = smallestOnRightSubtree->parent;

			// Parent of the smallest node is the one we want to delete
			if (parentOfSmallest == toDelete) {
				// Assign the right subtree of toDelete to the smallest element, so that we keep other elements
				smallestOnRightSubtree->right = toDelete->right;
				smallestOnRightSubtree->right->parent = smallestOnRightSubtree;

				// toDelete node doesnt have a parent
				if (parent == nullptr) {
					root = smallestOnRightSubtree;
				}
				// toDelete node is the left child of their parent
				else if (parent->left == toDelete) {
					parent->left = smallestOnRightSubtree;
				}
				// toDelete node is the right child of their parent
				else if (parent->right == toDelete) {
					parent->right = smallestOnRightSubtree;
				}

				delete toDelete;
				size--;
				return;
			}

			// Not the parent of the smallest note is to delete
			// If the smallest element has a right child, we asign it to its parent as a left child
			if (smallestOnRightSubtree->right != nullptr) {
				parentOfSmallest->left = smallestOnRightSubtree->right;
				smallestOnRightSubtree->right->parent = parentOfSmallest;
			}
			// If it doesnt have a right child we just tell its parent that it doesnt have a children anymore
			else {
				parentOfSmallest->left = nullptr;
			}
			// It cant have a left child if its the smallest element so we dont have to consider this

			// Here we swap the smallest element onto the toDelete node
			smallestOnRightSubtree->parent = toDelete->parent;

			// Assign the right subtree of the toDelete element to the smallest element, so that we keep other elements
			smallestOnRightSubtree->right = toDelete->right;
			smallestOnRightSubtree->right->parent = smallestOnRightSubtree;

			// Assign the left subtree of the toDelete elements that is now without the smallest element
			smallestOnRightSubtree->left = toDelete->left;
			smallestOnRightSubtree->left->parent = smallestOnRightSubtree;

			// toDelete node doesnt have a parent
			if (parent == nullptr) {
				root = smallestOnRightSubtree;
			}
			// toDelete node is the left child of their parent
			else if (parent->left == toDelete) {
				parent->left = smallestOnRightSubtree;
			}
			// toDelete node is the right child of their parent
			else if (parent->right == toDelete) {
				parent->right = smallestOnRightSubtree;
			}
		}

		// The actual delete action
		delete toDelete;
		size--;
	}

	// (d) przejście pre-order drzewa

	std::vector<T> preOrderTraversal() {
		std::vector<T> result;
		preOrderTraversalRecursive(root, result);
		return result;
	}

	// (e) przejście in-order drzewa

	std::vector<T> inOrderTraversal() {
		std::vector<T> result;
		inOrderTraversalRecursive(root, result);
		return result;
	}

	// (f) czyszczenie drzewa tj. usunięcie wszystkich elementów

	void deleteAll() {
		postOrderTraversalRecursiveDelete(root);

		// The whole tree is empty so we set the root to nullptr
		root = nullptr;

		size = 0;
		uniqueIndexIncrement = 0;
	}

	// (g) wyznaczenie wysokości drzewa

	int height() {
		return heightRecursive(root);
	}

	// (h) zwrócenie napisowej reprezentacji drzewa

	std::string to_string(bool displayAll = true) {
		std::ostringstream oss;

		oss << " Binary search tree:" << std::endl;
		oss << "\tSize: " << size << std::endl;
		oss << "\tHeight: " << height() << std::endl;

		if (displayAll) {
			oss << "\t{" << std::endl;

			displayTreeRecursive(root, oss);

			oss << "\t}" << std::endl << std::endl;

			if (root != nullptr) {
				displayTreeVisual(root, oss, "", true);
			}
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

#endif // BINARYSEARCHTREE_H