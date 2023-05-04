#include "qtcount.h"

bool qtcount::prunable(Node* node, const int tol) const {
    /* Your code here */
    return phelper(node, tol, node->avg);
}

bool qtcount::phelper(Node* node, const int tol, RGBAPixel a) const {

    if (node->NW == NULL && node->NE ==NULL && node->SW == NULL && node->SE == NULL) {
        return (
            (node->avg.r - a.r)*(node->avg.r - a.r) + (node->avg.g - a.g)*(node->avg.g - a.g) + (node->avg.b - a.b)*(node->avg.b - a.b) <= tol
        );
    } else {
        return (
            phelper(node->NW, tol, a) && phelper(node->NE, tol, a) && phelper(node->SW, tol, a) && phelper(node->SE, tol, a)
        );
    }

}
