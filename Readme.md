Array-Only Image Editor (C++)

A pure-C++ image editor that stores every pixel in one flat 1D dynamic array (unsigned char* data), with all higher-dimensional structure (rows, cols, channels) computed manually via index math. No image libraries — the point is to feel arrays, not hide behind an API.

Why PPM?

.ppm (P6) is just a tiny text header (P6\nwidth height\n255\n) followed by raw RGB bytes. That means file I/O is a few lines, and 100% of your effort goes into array algorithms instead of decoding a compressed format.

Viewing PPM files: most image viewers (GIMP, IrfanView, VLC, even feh on Linux) open .ppm directly. You can also convert with ffmpeg -i output.ppm output.png if you want a PNG to view/share.

Build
bash
g++ -std=c++17 -Wall -O2 image.cpp operations.cpp main.cpp -o editor
./editor
Files
image.h / image.cpp — the Image class: memory management, PPM load/save, and two fully worked examples (invert, toGrayscale) showing the two core traversal patterns you'll reuse everywhere.
operations.cpp — 11 stubbed exercises, ordered easy → hard, each with a hint comment explaining the DSA pattern it teaches. This is where you do the actual learning.
main.cpp — bare menu to test whatever you've implemented.
sample.ppm — a small generated gradient test image (64x64) to test with.
The learning path (do these in order)
adjustBrightness — flat traversal + clamping. Warm-up.
flipHorizontal — two-pointer array reversal, applied per row.
flipVertical — same idea, swap whole rows.
rotate90 — index-mapping between two arrays of swapped dimensions.
crop — subarray extraction with offset.
resizeNearestNeighbor — index scaling between differently-sized arrays.
boxBlur — 2D sliding window / convolution (the big one — this pattern underlies almost every real image filter).
medianFilter — sliding window + sorting (sort the window, take the middle element). Connects sorting algorithms to a real use case.
threshold — traversal + conditional replace.
histogramEqualize — frequency array + prefix sum (very common interview pattern, applied visually here).
hideMessageLSB / extractMessageLSB — bit manipulation across an array (steganography). Good capstone: combines everything.
Stretch goals once the list is done
Sobel edge detection (two convolution kernels, combine via magnitude)
Merge/blend two images (element-wise combination, needs same dimensions)
Quad-tree based compression (recursion over 2D regions)
A simple "undo" stack storing previous array states