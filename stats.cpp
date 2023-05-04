
#include "stats.h"

stats::stats(PNG& im) {
    /* Your code here!! */

    sumRed.resize(im.width(), vector<long>(im.height()));
    sumGreen.resize(im.width(), vector<long>(im.height()));
    sumBlue.resize(im.width(), vector<long>(im.height()));
    sumsqRed.resize(im.width(), vector<long>(im.height()));
    sumsqGreen.resize(im.width(), vector<long>(im.height()));
    sumsqBlue.resize(im.width(), vector<long>(im.height()));

    for (unsigned int x = 0; x < im.width(); x++) {

        for (unsigned int y = 0; y < im.height(); y++) {

            RGBAPixel* p = im.getPixel(x, y);
            long r = p->r;
            long g = p->g;
            long b = p->b;
            long rs = r*r;
            long gs = g*g;
            long bs = b*b;

            if (x==0 && y==0) {
                sumRed[0][0] = r;
                sumGreen[0][0] = g;
                sumBlue[0][0] = b;
                sumsqRed[0][0] = r*r;
                sumsqGreen[0][0] = g*g;
                sumsqBlue[0][0] = b*b;
            }
            else if (x==0 && y != 0) {
                sumRed[0][y] = sumRed[0][y-1] + r;
                sumGreen[0][y] = sumGreen[0][y-1] + g;
                sumBlue[0][y] = sumBlue[0][y-1] + b;
                sumsqRed[0][y] = sumsqRed[0][y-1] + rs;
                sumsqGreen[0][y] = sumsqGreen[0][y-1] + gs;
                sumsqBlue[0][y] = sumsqBlue[0][y-1] + bs;
            }
            else if (x!=0 && y == 0) {
                sumRed[x][y] = sumRed[x-1][y] + r;
                sumGreen[x][y] = sumGreen[x-1][y] + g;
                sumBlue[x][y] = sumBlue[x-1][y] + b;
                sumsqRed[x][y] = sumsqRed[x-1][y] + rs;
                sumsqGreen[x][y] = sumsqGreen[x-1][y] + gs;
                sumsqBlue[x][y] = sumsqBlue[x-1][y] + bs;
            }
            else {
                sumRed[x][y] = sumRed[x][y-1] + sumRed[x-1][y] + r - sumRed[x-1][y-1];
                sumGreen[x][y] = sumGreen[x][y-1] + sumGreen[x-1][y] + g - sumGreen[x-1][y-1];
                sumBlue[x][y] = sumBlue[x][y-1] + sumBlue[x-1][y] + b - sumBlue[x-1][y-1];
                sumsqRed[x][y] = sumsqRed[x][y-1] + sumsqRed[x-1][y] + rs - sumsqRed[x-1][y-1];
                sumsqGreen[x][y] = sumsqGreen[x][y-1] + sumsqGreen[x-1][y] + gs - sumsqGreen[x-1][y-1];
                sumsqBlue[x][y] = sumsqBlue[x][y-1] + sumsqBlue[x-1][y] + bs - sumsqBlue[x-1][y-1];
            }

        }

    }
}

long stats::getSum(char channel, pair<int, int> ul, int dim) {
    /* Your code here!! */

    int sum = 0;
    int i = pow(2,dim)-1;

    if (channel == 'r') {
        if (ul.first == 0 && ul.second == 0) {
            sum = sumRed[i][i];
        } 
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumRed[ul.first+i][ul.second+i] - sumRed[ul.first-1][ul.second+i];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumRed[ul.first+i][ul.second+i] - sumRed[ul.first+i][ul.second-1];
        } 
        else {
            sum = sumRed[ul.first+i][ul.second+i] - sumRed[ul.first-1][ul.second+i] - sumRed[ul.first+i][ul.second-1] + sumRed[ul.first-1][ul.second-1];
        }
    } else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            sum = sumGreen[i][i];
        } 
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumGreen[ul.first+i][ul.second+i] - sumGreen[ul.first-1][ul.second+i];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumGreen[ul.first+i][ul.second+i] - sumGreen[ul.first+i][ul.second-1];
        } 
        else {
            sum = sumGreen[ul.first+i][ul.second+i] - sumGreen[ul.first-1][ul.second+i] - sumGreen[ul.first+i][ul.second-1] + sumGreen[ul.first-1][ul.second-1];
        }
    } else if (channel == 'b') {
        if (ul.first == 0 && ul.second == 0) {
            sum = sumBlue[i][i];
        } 
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumBlue[ul.first+i][ul.second+i] - sumBlue[ul.first-1][ul.second+i];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumBlue[ul.first+i][ul.second+i] - sumBlue[ul.first+i][ul.second-1];
        } 
        else {
            sum = sumBlue[ul.first+i][ul.second+i] - sumBlue[ul.first-1][ul.second+i] - sumBlue[ul.first+i][ul.second-1] + sumBlue[ul.first-1][ul.second-1];
        }
    }

    return sum;
}

long stats::getSumSq(char channel, pair<int, int> ul, int dim) {
    /* Your code here!! */
    int sum = 0;
    int i = pow(2,dim)-1;

    if (channel == 'r') {
        if (ul.first == 0 && ul.second == 0) {
            sum = sumsqRed[i][i];
        } 
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumsqRed[ul.first+i][ul.second+i] - sumsqRed[ul.first-1][ul.second+i];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumsqRed[ul.first+i][ul.second+i] - sumsqRed[ul.first+i][ul.second-1];
        } 
        else {
            sum = sumsqRed[ul.first+i][ul.second+i] - sumsqRed[ul.first-1][ul.second+i] - sumsqRed[ul.first+i][ul.second-1] + sumsqRed[ul.first-1][ul.second-1];
        }
    } else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            sum = sumsqGreen[i][i];
        } 
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumsqGreen[ul.first+i][ul.second+i] - sumsqGreen[ul.first-1][ul.second+i];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumsqGreen[ul.first+i][ul.second+i] - sumsqGreen[ul.first+i][ul.second-1];
        } 
        else {
            sum = sumsqGreen[ul.first+i][ul.second+i] - sumsqGreen[ul.first-1][ul.second+i] - sumsqGreen[ul.first+i][ul.second-1] + sumsqGreen[ul.first-1][ul.second-1];
        }
    } else if (channel == 'b') {
        if (ul.first == 0 && ul.second == 0) {
            sum = sumsqBlue[i][i];
        } 
        else if (ul.first != 0 && ul.second == 0) {
            sum = sumsqBlue[ul.first+i][ul.second+i] - sumsqBlue[ul.first-1][ul.second+i];
        }
        else if (ul.first == 0 && ul.second != 0) {
            sum = sumsqBlue[ul.first+i][ul.second+i] - sumsqBlue[ul.first+i][ul.second-1];
        } 
        else {
            sum = sumsqBlue[ul.first+i][ul.second+i] - sumsqBlue[ul.first-1][ul.second+i] - sumsqBlue[ul.first+i][ul.second-1] + sumsqBlue[ul.first-1][ul.second-1];
        }
    }

    return sum;

}

long stats::rectArea(int dim) {
    /* Your code here!! */
    int i = pow(2,dim);
    int value = i*i;

    return value;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int dim) {
    /* Your code here!! */

    double area = rectArea(dim);
    double sumr = getSum('r', ul, dim);
    double sumg = getSum('g', ul, dim);
    double sumb = getSum('b', ul, dim);

    double sumsqr = getSumSq('r', ul, dim);
    double sumsqg = getSumSq('g', ul, dim);
    double sumsqb = getSumSq('b', ul, dim);

    double r = (sumr*sumr)/area;
    double g = (sumg*sumg)/area;
    double b = (sumb*sumb)/area;

    double v = (sumsqr - r) + (sumsqg - g) + (sumsqb - b);

    return v;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int dim) {
    /* Your code here!! */

    long area = rectArea(dim);
    long sumr = getSum('r', ul, dim);
    long sumg = getSum('g', ul, dim);
    long sumb = getSum('b', ul, dim);

    return RGBAPixel(sumr/area, sumg/area, sumb/area);
}
