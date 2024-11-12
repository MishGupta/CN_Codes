#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WINDOW_SIZE = 4;
const int TOTAL_FRAMES = 8;

struct Frame {
    int id;
    bool ack;
};

void sendFrame(Frame &frame) {
    cout << "Sending Frame: " << frame.id << endl;
}

bool receiveAck() {
    // Simulate random ACK/NACK (Acknowledgment/Negative Acknowledgment)
    return rand() % 2;
}

int main() {
    // Seed the random number generator
    srand(time(0));

    vector<Frame> window;
    int nextFrameToSend = 0;

    // Initialize frames with IDs
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        window.push_back({i, false});
    }

    while (nextFrameToSend < TOTAL_FRAMES) {
        // Send frames within the window
        for (int i = nextFrameToSend; i < nextFrameToSend + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!window[i].ack) {
                sendFrame(window[i]);
            }
        }

        // Receive ACKs for frames
        for (int i = nextFrameToSend; i < nextFrameToSend + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!window[i].ack) {
                bool ackReceived = receiveAck();
                if (ackReceived) {
                    cout << "ACK received for Frame: " << window[i].id << endl;
                    window[i].ack = true;
                } else {
                    cout << "NACK received for Frame: " << window[i].id << ". Resending..." << endl;
                }
            }
        }

        // Slide the window forward
        while (nextFrameToSend < TOTAL_FRAMES && window[nextFrameToSend].ack) {
            nextFrameToSend++;
        }
    }

    cout << "All frames sent and acknowledged." << endl;
    return 0;
}

