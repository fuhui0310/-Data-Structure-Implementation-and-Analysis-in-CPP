// AVLSet.hpp
//
// ICS 46 Winter 2019
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.  The balancing is actually optional,
// with a bool parameter able to be passed to the constructor to explicitly
// turn the balancing on or off (on is default).  If the balancing is off,
// the AVL tree acts like a binary search tree (e.g., it will become
// degenerate if elements are added in ascending order).
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to implement your AVL tree
// using your own dynamically-allocated nodes, with pointers connecting them,
// and with your own balancing algorithms used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <functional>
#include "Set.hpp"



template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet() noexcept;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;


private:
    // You'll no doubt want to add member variables and "helper" member
    // functions here.
    struct Node{
    	ElementType data;
    	int height;
    	Node* left;
    	Node* right;
    };
    bool sbalance = true;
    Node* root;
    int treeSize;
    bool findNode(const ElementType& element, Node* node) const;
    Node* copyAll(const Node* origin);
    void destroyAll(Node* node);
    Node* insert(const ElementType& element, Node* node);
    Node* LLRotation(Node* &node);
    Node* RRRotation(Node* &node);
    Node* LRRotation(Node* &node);
    Node* RLRotation(Node* &node);
    int findHeight(Node* node);
    void inorderCall(VisitFunction visit, Node* node) const;
    void preorderCall(VisitFunction visit, Node* node) const;
    void postorderCall(VisitFunction visit, Node* node) const;
};


template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{
	root = nullptr;
	sbalance = shouldBalance;
}


template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
	destroyAll(root);
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
	root = copyAll(s.root);
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
	:root{nullptr}
{
	std::swap(root,s.root);
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    if (this != &s)
    {
        destroyAll(root);
        root = nullptr;
        root = copyAll(s.root);
    }

    return *this;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
    std::swap(root,s.root);
    return *this;
}


template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{
	if(root == nullptr){
		root = new Node{element,0,nullptr,nullptr};
		treeSize++;
	}else{
		root = insert(element, root);
	}
}


template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
	bool isFound = false;
    if(root == nullptr){
    	return isFound;
    }else{
    	isFound = findNode(element, root);
    	return isFound;
    }
}


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return treeSize;
}


template <typename ElementType>
int AVLSet<ElementType>::height() const
{
    if(root == nullptr){
    	return -1;
    }else{
    	return root->height;
    }
}


template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
	preorderCall(visit, root);
}

template <typename ElementType>
void AVLSet<ElementType>::preorderCall(VisitFunction visit, Node* node) const{
	if(node != nullptr){
		visit(node->data);
		preorderCall(visit, node->left);
		preorderCall(visit, node->right);
	}
}

template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
	inorderCall(visit, root);
}

template <typename ElementType>
void AVLSet<ElementType>::inorderCall(VisitFunction visit, Node* node) const{
	if(node != nullptr){
		inorderCall(visit, node->left);
		visit(node->data);
		inorderCall(visit, node->right);
	}
}


template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
	postorderCall(visit, root);
}

template <typename ElementType>
void AVLSet<ElementType>::postorderCall(VisitFunction visit, Node* node) const{
	if(node != nullptr){
		postorderCall(visit, node->left);
		postorderCall(visit, node->right);
		visit(node->data);
	}
}

template <typename ElementType>
typename AVLSet<ElementType>::Node* AVLSet<ElementType>::copyAll(const Node* origin){
	Node* node;
	if(origin == nullptr){
		node = nullptr;
	}else{
		treeSize++;
		node = new Node{origin->data, origin->height};
		if(origin->left != nullptr || origin->right != nullptr){
			node->left = copyAll(origin->left);
			node->right = copyAll(origin->right);
		}
	}
	return node;
}

template <typename ElementType>
void AVLSet<ElementType>::destroyAll(Node* node){
	if(node != nullptr){
		destroyAll(node->left);
		destroyAll(node->right);
		delete node;
	}
}

//insert
template <typename ElementType>
typename AVLSet<ElementType>::Node* AVLSet<ElementType>::insert(const ElementType& element, Node* node){
	if(node == nullptr){
		node = new Node{element,0,nullptr,nullptr};
		treeSize++;
		return node;
	}else{
		if(sbalance == true){
			if(element < node->data){
				node->left = insert(element, node->left);
				int rHeight;
				int lHeight;
				if(node->left != nullptr){
					lHeight = node->left->height;
				}else{
					lHeight = -1;
				}
				if(node->right != nullptr){
					rHeight = node->right->height;
				}else{
					rHeight = -1;
				}
				if((lHeight) - (rHeight) == 2){
					if(element < node->left->data){
						node = LLRotation(node);
					}else{
						node = LRRotation(node);
					}
				}
			}else{
				node->right = insert(element, node->right);
				int rHeight;
				int lHeight;
				if(node->left != nullptr){
					lHeight = node->left->height;
				}else{
					lHeight = -1;
				}
				if(node->right != nullptr){
					rHeight = node->right->height;
				}else{
					rHeight = -1;
				}
				if((rHeight) - (lHeight) == 2){
					if(element > node->right->data){
						node = RRRotation(node);
					}else{
						node = RLRotation(node);
					}
				}
			}
		}else{
			if(element < node->data){
				node->left = insert(element, node->left);
			}else{
				node->right = insert(element, node->right);
			}
		}
		int r;
		int l;
		if(node->left != nullptr){
			l = node->left->height;
		}else{
			l = -1;
		}
		if(node->right != nullptr){
			r = node->right->height;
		}else{
			r = -1;
		}
		//if(node->left == nullptr && node->right == nullptr){
		//	node->height = 0;
		//}
		//if(node->left == nullptr && node->right != nullptr){
		//	node->height = node->right->height + 1;
		//}
		//if(node->left != nullptr && node->right == nullptr){
		//	node->height = node->left->height + 1;
		//}
		//if(node->left != nullptr && node->right != nullptr){
		node->height = std::max(l, r) + 1;
		//}
		return node;
	}
	//if(node->left != nullptr || node->right != nullptr){
	//	node->height = findHeight(node);
	//node->height = std::max(node->left->height, node->right->height) + 1;
	//return node;
	//}
	//treeSize++;
}

template <typename ElementType>
bool AVLSet<ElementType>::findNode(const ElementType& element, Node* node) const{
	bool isFound = false;
	if(node == nullptr){
		return isFound;
	}else{
		if(node->data == element){
			isFound = true;
			return isFound;
		}else{
			if(element < node->data){
				isFound = findNode(element, node->left);
			}
			if(element > node->data){
				isFound = findNode(element, node->right);
			}
			return isFound;
		}
	}
}

template <typename ElementType>
typename AVLSet<ElementType>::Node* AVLSet<ElementType>::RRRotation(Node* &node){
	Node* tmp = node->right;
	//tmp->height = findHeight(node->right);
	node->right = tmp->left;
	tmp->left = node;
	int lnode;
	int rnode;
	int tRnode;
	if(node->left != nullptr){
		lnode = node->left->height;
	}else{
		lnode = -1;
	}
	if(node->right != nullptr){
		rnode = node->right->height;
	}else{
		rnode = -1;
	}
	if(node->left == nullptr && node->right == nullptr){
		node->height = 0;
	}else{
		node->height = std::max(lnode, rnode) + 1;
	}
	if(tmp->right != nullptr){
		tRnode = tmp->right->height;
	}else{
		tRnode = -1;
	}
	if(tmp->left == nullptr && tmp->right == nullptr){
		tmp->height = 0;
	}else{
		tmp->height = std::max(tRnode, node->height) + 1;
	}
	return tmp;
}

template <typename ElementType>
typename AVLSet<ElementType>::Node* AVLSet<ElementType>::LLRotation(Node* &node){
	Node* tmp = node->left;
	//tmp->height = findHeight(node->left);
	node->left = tmp->right;
	tmp->right = node;
	int lnode;
	int rnode;
	int tLnode;
	if(node->left != nullptr){
		lnode = node->left->height;
	}else{
		lnode = -1;
	}
	if(node->right != nullptr){
		rnode = node->right->height;
	}else{
		rnode = -1;
	}
	if(node->left == nullptr && node->right == nullptr){
		node->height = 0;
	}else{
		node->height = std::max(lnode, rnode) + 1;
	}
	if(tmp->left != nullptr){
		tLnode = tmp->left->height;
	}else{
		tLnode = -1;
	}
	if(tmp->left == nullptr && tmp->right == nullptr){
		tmp->height = 0;
	}else{
		tmp->height = std::max(tLnode, node->height) + 1;
	}
	return tmp;
}

template <typename ElementType>
typename AVLSet<ElementType>::Node* AVLSet<ElementType>::RLRotation(Node* &node){
	node->right = LLRotation(node->right);
	return RRRotation(node);
}

template <typename ElementType>
typename AVLSet<ElementType>::Node* AVLSet<ElementType>::LRRotation(Node* &node){
	node->left = RRRotation(node->left);
	return LLRotation(node);
}
/**
template <typename ElementType>
int AVLSet<ElementType>::findHeight(Node* node){
	if(node == nullptr){
		return 0;
	}
	if(node->left == nullptr && node->right == nullptr){
		return 0;
	}
	if(node->left == nullptr && node->right != nullptr){
		return node->right->height + 1;
	}
	if(node->right == nullptr && node->left != nullptr){
		return node->left->height + 1;
	}
	if(findHeight(node->left) > findHeight(node->right)){
		return node->left->height + 1;
	}else{
		return node->right->height + 1;
	}

}
**/




#endif // AVLSET_HPP

