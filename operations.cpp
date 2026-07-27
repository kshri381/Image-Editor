// ============================================================
// EXERCISES — implement each function in image.h yourself.
// Ordered from easiest to hardest. Each one teaches a specific
// array pattern used constantly in DSA interviews.
//
// Compile/test each one incrementally by wiring it into main.cpp.
// ============================================================
#include "image.h"
#include <algorithm>
#include <vector>
using namespace std;
 
// ------------------------------------------------------------
// 1) adjustBrightness(delta)
// PATTERN: single flat-array traversal, same as invert().
// HINT: add delta to every byte, but CLAMP to [0, 255] —
//       don't let unsigned char overflow wrap around.
// ------------------------------------------------------------
void Image::adjustBrightness(int delta) {
    // TODO
}
 
// ------------------------------------------------------------
// 2) flipHorizontal()
// PATTERN: two-pointer swap, classic array-reversal — but applied
//          per row, and you must swap all 3 channels together.
// HINT: for each row, left = col 0, right = col (width-1),
//       swap pixel(row,left) with pixel(row,right), left++, right--,
//       stop when left >= right.
// ------------------------------------------------------------
void Image::flipHorizontal() {
    // TODO
}
 
// ------------------------------------------------------------
// 3) flipVertical()
// PATTERN: same two-pointer idea, but swap whole ROWS instead of
//          individual pixels. You can swap width*channels bytes
//          at once with a temporary buffer or swap_ranges.
// ------------------------------------------------------------
void Image::flipVertical() {
    // TODO
}
 
// ------------------------------------------------------------
// 4) rotate90() const
// PATTERN: index-mapping between two DIFFERENT arrays (source and
//          destination have swapped width/height). This is the
//          matrix-transpose-plus-reverse trick.
// HINT: output image has dimensions (height x width) swapped.
//       For 90 deg clockwise: dst(col, height-1-row) = src(row, col)
//       Build a new Image of size (height, width) and fill it —
//       do NOT try to do this in place.
// ------------------------------------------------------------
Image Image::rotate90() const {
    Image result(height, width, channels); // note swapped dims
    // TODO: fill result using the index mapping above
    return result;
}
 
// ------------------------------------------------------------
// 5) crop(x, y, w, h) const
// PATTERN: subarray extraction with an offset — very common in
//          array problems ("subarray starting at index k").
// HINT: create Image result(w, h, channels). For each row/col in
//       the new image, read from src at (y+row, x+col).
//       Add bounds checking so a bad crop doesn't crash.
// ------------------------------------------------------------
Image Image::crop(int x, int y, int w, int h) const {
    Image result(w, h, channels);
    // TODO
    return result;
}
 
// ------------------------------------------------------------
// 6) resizeNearestNeighbor(newW, newH) const
// PATTERN: index scaling / mapping between two arrays of different
//          sizes — you compute a ratio and round to nearest index.
// HINT: for each (row, col) in the NEW image, find the corresponding
//       source pixel: srcRow = row * height / newH,
//                      srcCol = col * width  / newW
//       (integer division intentionally truncates — that's "nearest").
// ------------------------------------------------------------
Image Image::resizeNearestNeighbor(int newW, int newH) const {
    Image result(newW, newH, channels);
    // TODO
    return result;
}
 
// ------------------------------------------------------------
// 7) boxBlur(kernelSize) const
// PATTERN: 2D sliding window / convolution — for EVERY pixel, look
//          at a (kernelSize x kernelSize) neighborhood and average it.
//          This is the array pattern behind almost all image filters.
// HINT: kernelSize should be odd (3, 5, 7...). radius = kernelSize/2.
//       For each output pixel (row,col) and each channel c:
//         sum over dr in [-radius, radius], dc in [-radius, radius]
//         of src(row+dr, col+dc, c), skipping out-of-bounds neighbors,
//         then divide by the count actually summed.
//       Do this on a SEPARATE result image — never blur in place,
//       or you'll blur using already-blurred pixels.
// ------------------------------------------------------------
Image Image::boxBlur(int kernelSize) const {
    Image result(width, height, channels);
    // TODO
    return result;
}
 
// ------------------------------------------------------------
// 8) medianFilter(windowSize) const  — great for removing noise
// PATTERN: same sliding window as boxBlur, but instead of averaging,
//          you SORT the values in the window and take the middle one.
//          This is where sorting algorithms meet image processing.
// HINT: for each pixel/channel, gather the neighborhood values into
//       a small vector<unsigned char>, sort it, take the
//       middle element as the output value.
// ------------------------------------------------------------
Image Image::medianFilter(int windowSize) const {
    Image result(width, height, channels);
    // TODO
    return result;
}
 
// ------------------------------------------------------------
// 9) threshold(t) — binarize the image (black/white only)
// PATTERN: traversal + condition, like "search array and replace
//          values matching a predicate."
// HINT: convert to grayscale logic per pixel (or just compare each
//       channel), set to 255 if >= t else 0.
// ------------------------------------------------------------
void Image::threshold(int t) {
    // TODO
}
 
// ------------------------------------------------------------
// 10) histogramEqualize() — contrast enhancement
// PATTERN: frequency array + prefix sum, a very classic DSA combo.
// HINT:
//   a) Build int hist[256] = {0}; count occurrences of each gray value
//      (convert to grayscale first, or do it per channel).
//   b) Build a prefix-sum (cumulative distribution) array from hist.
//   c) Normalize the prefix sum to [0,255] — this is your lookup table.
//   d) Traverse the image again, replacing each pixel value v with
//      lookupTable[v].
// ------------------------------------------------------------
void Image::histogramEqualize() {
    // TODO
}
 
// ------------------------------------------------------------
// 11) hideMessageLSB(message) / extractMessageLSB()
// PATTERN: bit manipulation across an array — classic steganography.
// HINT for hiding:
//   - Convert message to bits (include a fixed-length header storing
//     the message length, or a terminator sequence).
//   - For each bit, overwrite the LEAST significant bit of successive
//     bytes in `data` with that bit:
//         data[i] = (data[i] & 0xFE) | bit;
//   - This barely changes pixel values (off by at most 1), invisible
//     to the eye, but recoverable.
// HINT for extracting: read the LSBs back in the same order and
//   reassemble bytes/characters.
// ------------------------------------------------------------
void Image::hideMessageLSB(const string& message) {
    // TODO
}
 
string Image::extractMessageLSB() const {
    // TODO
    return "";
}