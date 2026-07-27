#ifndef IMAGE_H
#define IMAGE_H
 
#include <string>
using namespace std;
 
// A PPM (P6) RGB image backed by ONE flat dynamic array.
// Memory layout (row-major): pixel(row, col).channel c lives at:
//   data[row * width * channels + col * channels + c]
//
// We use a flat array on purpose instead of unsigned char img[H][W][3].
// This is the whole point of the exercise: you compute the index yourself,
// so you actually feel how 2D/3D data is really just 1D memory + arithmetic.
class Image {
public:
    unsigned char* data;   // the ONE array that holds everything
    int width;
    int height;
    int channels;          // 3 for RGB
 
    Image();
    Image(int w, int h, int ch = 3);
    Image(const Image& other);            // deep copy constructor
    Image& operator=(const Image& other); // deep copy assignment
    ~Image();
 
    // ---- core index math (the most important function in this whole project) ----
    inline int index(int row, int col, int c) const {
        return row * width * channels + col * channels + c;
    }
 
    // ---- file I/O ----
    bool load(const string& filename);
    bool save(const string& filename) const;
 
    // ---- worked examples (fully implemented, read these first) ----
    void invert();
    void toGrayscale();
 
    // ---- exercises: declared here, YOU implement in operations.cpp ----
    void adjustBrightness(int delta);
    void flipHorizontal();
    void flipVertical();
    Image rotate90() const;
    Image crop(int x, int y, int w, int h) const;
    Image resizeNearestNeighbor(int newW, int newH) const;
    Image boxBlur(int kernelSize) const;
    Image medianFilter(int windowSize) const;
    void threshold(int t);
    void histogramEqualize();
    void hideMessageLSB(const string& message);
    string extractMessageLSB() const;
};
 
#endif
 