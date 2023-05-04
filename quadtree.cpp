
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
using namespace std;

// Node constructor, given.
quadtree::Node::Node(pair<int, int> ul, int d, RGBAPixel a, double v)
    : upLeft(ul), dim(d), avg(a), var(v), NW(nullptr), NE(nullptr), SE(nullptr), SW(nullptr) {}

// quadtree destructor, given.
quadtree::~quadtree() {
    clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree& other) {
    copy(other);
}
// quadtree assignment operator, given.
quadtree& quadtree::operator=(const quadtree& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

quadtree::quadtree(PNG& imIn) {
    /* Your code here! */

    stats s = stats(imIn);

    pair<int, int> start = {0,0};

    int limit = min(imIn.height(), imIn.width());

    int size = 1;
    int tracker = 0;

    while (size < limit) {
        size = size*2;
        tracker++;
    }
    if (size > limit) {
        tracker--;
    }
    
    root = buildTree(s, start, tracker);
}

quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    /* Your code here! */

    RGBAPixel average = s.getAvg(ul, dim);
    double var = s.getVar(ul, dim);
    
    Node* newnode = new Node(ul, dim, average, var);

    if (dim == 0) {
        return newnode;
    }

    pair<int, int> nw = ul;
    pair<int, int> ne = {ul.first + pow(2,dim-1), ul.second};
    pair<int, int> sw = {ul.first, ul.second + pow(2,dim-1)};
    pair<int, int> se = {ul.first + pow(2,dim-1), ul.second + pow(2,dim-1)};

    newnode->NW = buildTree(s, nw, dim-1);
    newnode->NE = buildTree(s, ne, dim-1);
    newnode->SW = buildTree(s, sw, dim-1);
    newnode->SE = buildTree(s, se, dim-1);

    return newnode;
}

PNG quadtree::render() const {
    /* Your code here! */

    int size = pow(2, this->root->dim);

    PNG p = PNG(size,size);

    renderhelper(p, root);

    return p;
}

void quadtree::renderhelper(PNG& imIn, Node* n) const {

    Node* curr = n; 

    if (curr->NW == NULL) {

        for (int x = curr->upLeft.first; x < curr->upLeft.first + pow(2, curr->dim); x++) {

            for (int y = curr->upLeft.second; y < curr->upLeft.second + pow(2, curr->dim); y++) {

                *imIn.getPixel(x,y) = curr->avg;

            }
        }

    } else {

        renderhelper(imIn, curr->NW);
        renderhelper(imIn, curr->NE);
        renderhelper(imIn, curr->SW);
        renderhelper(imIn, curr->SE);

    }

}



int quadtree::idealPrune(const int leaves) const {
    /* Your code here! */
    int t = ihelper(leaves, 0, 10000000);

    while (t > 0 && pruneSize(t-1) == leaves) {
        t--;
    }


    return t;
}

int quadtree::ihelper(const int leaves, int min, int max) const {

    if (min == max) {
        return min;
    }

    int mid = (min+max)/2;

    if (pruneSize(mid) == leaves) {
        return mid;
    } else if (pruneSize(mid) < leaves) {
        return ihelper(leaves, min, mid-1);
    } else {
        return ihelper(leaves, mid+1, max);
    }

}



int quadtree::pruneSize(const int tol) const {
    /* Your code here! */
    return shelper(root, tol);
}

int quadtree::shelper(Node* n, const int tol) const {

    if (n == NULL || n->NW == NULL) {
        return 1;
    }

    if (prunable(n, tol)) {
        return 1;
    } else {

        return (
            shelper(n->NW, tol) + shelper(n->NE, tol) + shelper(n->SW, tol) + shelper(n->SE, tol)
        );

    }

}


void quadtree::prune(const int tol) {
    /* Your code here! */

    prunehelper(root, tol);
}

void quadtree::prunehelper(Node* n, const int tol) {

    if (n == NULL || n->NW == NULL) {
        return;
    }

    if (prunable(n, tol)) {
        clearhelper(n->NW);
        clearhelper(n->NE);
        clearhelper(n->SW);
        clearhelper(n->SE);

        n->NW = NULL;
        n->NE = NULL;
        n->SE = NULL;
        n->SW = NULL;
    } else {
        prunehelper(n->NW, tol);
        prunehelper(n->NE, tol);
        prunehelper(n->SW, tol);
        prunehelper(n->SE, tol);
    }

}





void quadtree::clear() {
    /* your code here */
    clearhelper(root);

}

void quadtree::clearhelper(Node* curr) {

    if (curr == NULL) {
        return;
    }

    clearhelper(curr->NW);
    clearhelper(curr->NE);
    clearhelper(curr->SE);
    clearhelper(curr->SW);

    delete curr;

}

void quadtree::copy(const quadtree& orig) {
    /* your code here */

    root = copyhelper(orig.root);
}

quadtree::Node* quadtree::copyhelper(Node* curr) {

    if (curr == NULL) {
        return NULL;
    }

    Node* newnode = new Node({curr->upLeft.first, curr->upLeft.second}, curr->dim, curr->avg, curr->var);

    newnode->NW = copyhelper(curr->NW);
    newnode->NE = copyhelper(curr->NE);
    newnode->SW = copyhelper(curr->SW);
    newnode->SE = copyhelper(curr->SE);

    return newnode;

}
