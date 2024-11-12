#include <bits/stdc++.h>
using namespace std;

// Function to simulate sending a frame with a 90% success rate
bool sendFrame(int frame) {
    return rand() % 10 >= 1;  // 90% chance to successfully "send" (acknowledge) the frame
}

// Function to simulate Go-Back-N protocol
void goBackN(int totalFrames, int windowSize) {
    int sentFrames = 0;
    int ackedFrames = 0;

    while (ackedFrames < totalFrames) {
        // Sending frames within the window
        for (int i = 0; i < windowSize && sentFrames < totalFrames; i++) {
            cout << "Sending frame " << sentFrames << endl;
            sentFrames++;
        }

        // Simulate acknowledgment process
        for (int i = 0; i < windowSize && ackedFrames < totalFrames; i++) {
            if (sendFrame(ackedFrames)) {
                cout << "Acknowledgment received for frame " << ackedFrames << endl;
                ackedFrames++;
            } else {
                // If acknowledgment is not received, go back to the first unacknowledged frame
                cout << "Frame " << ackedFrames << " not acknowledged. Go back to frame " << ackedFrames << endl;
                sentFrames = ackedFrames;  // Reset `sentFrames` to `ackedFrames`
                break;
            }
        }
    }

    cout << "All frames have been successfully sent and acknowledged." << endl;
}

int main() {
    srand(time(0));  // Seed the random number generator

    int totalFrames, windowSize;
    cout << "Enter the total number of frames: ";
    cin >> totalFrames;
    cout << "Enter the window size: ";
    cin >> windowSize;

    goBackN(totalFrames, windowSize);

    return 0;
}

