#include "image.h"
#include <iostream>
using namespace std;

void printMenu() {
    cout << "\n===================== MENU =====================\n"
         << " 1) Invert\n"
         << " 2) Grayscale\n"
         << " 3) Adjust brightness\n"
         << " 4) Flip horizontal\n"
         << " 5) Flip vertical\n"
         << " 6) Rotate 90\n"
         << " 7) Crop\n"
         << " 8) Resize (nearest neighbor)\n"
         << " 9) Box blur\n"
         << "10) Median filter\n"
         << "11) Threshold (binarize)\n"
         << "12) Histogram equalize\n"
         << "13) Hide message (LSB steganography)\n"
         << "14) Extract hidden message (LSB)\n"
         << " 0) Load a different image\n"
         << "-1) Quit\n"
         << "==================================================\n"
         << "Choice: ";
}

int main() {
    Image img;
    string filename;

    cout << "Enter input PPM file path: ";
    cin >> filename;
    if (!img.load(filename)) {
        cerr << "Failed to load image. Check the path and try again.\n";
        return 1;
    }
    cout << "Loaded " << img.width << "x" << img.height << " image.\n";

    while (true) {
        printMenu();
        int choice;
        cin >> choice;

        if (choice == -1) {
            cout << "Bye.\n";
            break;
        }

        if (choice == 0) {
            cout << "Enter PPM file path: ";
            cin >> filename;
            if (!img.load(filename)) {
                cerr << "Failed to load image.\n";
                continue;
            }
            cout << "Loaded " << img.width << "x" << img.height << " image.\n";
            continue;
        }

        // result holds the output for operations that return a NEW image
        // (crop, resize, rotate, blur, median filter) instead of modifying
        // the current one in place.
        Image result;
        bool producedNewImage = false;

        switch (choice) {
            case 1:
                img.invert();
                break;

            case 2:
                img.toGrayscale();
                break;

            case 3: {
                int delta;
                cout << "Brightness delta (e.g. 40 or -40): ";
                cin >> delta;
                img.adjustBrightness(delta);
                break;
            }

            case 4:
                img.flipHorizontal();
                break;

            case 5:
                img.flipVertical();
                break;

            case 6:
                result = img.rotate90();
                producedNewImage = true;
                break;

            case 7: {
                int x, y, w, h;
                cout << "Crop x y width height (current size is "
                     << img.width << "x" << img.height << "): ";
                cin >> x >> y >> w >> h;
                result = img.crop(x, y, w, h);
                producedNewImage = true;
                break;
            }

            case 8: {
                int newW, newH;
                cout << "New width height: ";
                cin >> newW >> newH;
                result = img.resizeNearestNeighbor(newW, newH);
                producedNewImage = true;
                break;
            }

            case 9: {
                int k;
                cout << "Kernel size (odd number, e.g. 3, 5, 7): ";
                cin >> k;
                result = img.boxBlur(k);
                producedNewImage = true;
                break;
            }

            case 10: {
                int w;
                cout << "Window size (odd number, e.g. 3, 5): ";
                cin >> w;
                result = img.medianFilter(w);
                producedNewImage = true;
                break;
            }

            case 11: {
                int t;
                cout << "Threshold value (0-255, e.g. 128): ";
                cin >> t;
                img.threshold(t);
                break;
            }

            case 12:
                img.histogramEqualize();
                break;

            case 13: {
                cin.ignore(); // flush leftover newline before getline
                string message;
                cout << "Message to hide: ";
                getline(cin, message);
                img.hideMessageLSB(message);
                break;
            }

            case 14: {
                string hidden = img.extractMessageLSB();
                cout << "Extracted message: " << hidden << "\n";
                break;
            }

            default:
                cout << "Unknown choice.\n";
                continue;
        }

        // For in-place ops, save the current image.
        // For ops that produce a new image, save THAT instead and
        // also make it the current image so you can chain operations.
        string outName;
        cout << "Save output as (e.g. output.ppm): ";
        cin >> outName;

        if (producedNewImage) {
            result.save(outName);
            img = result; // chain: further ops apply to this new image
            cout << "Saved " << outName << " (" << img.width << "x" << img.height << ")\n";
            if (choice == 6 || choice == 7 || choice == 8 || choice == 9 || choice == 10) {
                cout << "Note: if you haven't implemented this function yet in "
                        "operations.cpp, the output will just be a blank black "
                        "image of the right size.\n";
            }
        } else {
            img.save(outName);
            cout << "Saved " << outName << " (" << img.width << "x" << img.height << ")\n";
        }
    }

    return 0;
}