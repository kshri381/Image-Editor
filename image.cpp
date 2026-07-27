#include "image.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

// ---------------- construction / memory management ----------------

Image::Image() : data(nullptr), width(0), height(0), channels(3) {}

Image::Image(int w, int h, int ch)
    : data(nullptr), width(w), height(h), channels(ch) {
    data = new unsigned char[width * height * channels];
    memset(data, 0, width * height * channels);
}

Image::Image(const Image& other)
    : data(nullptr), width(other.width), height(other.height), channels(other.channels) {
    int n = width * height * channels;
    data = new unsigned char[n];
    memcpy(data, other.data, n);
}

Image& Image::operator=(const Image& other) {
    if (this == &other) return *this;
    delete[] data;
    width = other.width;
    height = other.height;
    channels = other.channels;
    int n = width * height * channels;
    data = new unsigned char[n];
    memcpy(data, other.data, n);
    return *this;
}

Image::~Image() {
    delete[] data;
}

// ---------------- PPM (P6) file I/O ----------------
// Format:
//   P6\n<width> <height>\n255\n<raw RGB bytes, row-major>

bool Image::load(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Could not open " << filename << "\n";
        return false;
    }

    string magic;
    file >> magic;
    if (magic != "P6") {
        cerr << "Not a P6 PPM file\n";
        return false;
    }

    // skip comments starting with '#'
    auto skipWhitespaceAndComments = [&]() {
        char c;
        while (file.get(c)) {
            if (c == '#') {
                string line;
                getline(file, line);
            } else if (!isspace(c)) {
                file.unget();
                break;
            }
        }
    };

    skipWhitespaceAndComments();
    file >> width;
    skipWhitespaceAndComments();
    file >> height;
    skipWhitespaceAndComments();
    int maxVal;
    file >> maxVal;
    file.get(); // consume single whitespace after maxVal

    channels = 3;
    delete[] data;
    int n = width * height * channels;
    data = new unsigned char[n];
    file.read(reinterpret_cast<char*>(data), n);

    if (!file) {
        cerr << "Unexpected end of file while reading pixel data\n";
        return false;
    }
    return true;
}

bool Image::save(const string& filename) const {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Could not create " << filename << "\n";
        return false;
    }
    file << "P6\n" << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char*>(data), width * height * channels);
    return true;
}

// ---------------- WORKED EXAMPLE 1: invert ----------------
// Simplest possible full traversal of the array: visit every element once,
// apply a pointwise transform. This is O(width * height * channels).
void Image::invert() {
    int n = width * height * channels;
    for (int i = 0; i < n; i++) {
        data[i] = 255 - data[i];
    }
}

// ---------------- WORKED EXAMPLE 2: grayscale ----------------
// Here we must respect the pixel structure (groups of 3 bytes = R,G,B),
// so we traverse row by row, col by col, and compute index() ourselves
// instead of just walking the flat array byte-by-byte like invert() does.
// This is the pattern almost every other operation in this project follows.
void Image::toGrayscale() {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int idxR = index(row, col, 0);
            int idxG = index(row, col, 1);
            int idxB = index(row, col, 2);

            unsigned char r = data[idxR];
            unsigned char g = data[idxG];
            unsigned char b = data[idxB];

            // luminosity formula, standard weights for human eye sensitivity
            unsigned char gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);

            data[idxR] = gray;
            data[idxG] = gray;
            data[idxB] = gray;
        }
    }
}