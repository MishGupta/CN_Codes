#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10
#define OUTGOING_RATE 3

void leaky_bucket(int packets[], int n) {
    int bucket = 0; 
    int i;

    printf("Time\tIncoming\tBucket\t\tOutgoing\n");
    printf("--------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t", i + 1, packets[i]);
        
        // Check for overflow
        if (packets[i] + bucket > BUCKET_SIZE) {
            printf("Overflow: %d dropped\t", packets[i] + bucket - BUCKET_SIZE);
            bucket = BUCKET_SIZE; // Bucket fills to max capacity
        } else {
            bucket += packets[i];
            printf("%d\t\t", bucket);
        }

        // Outgoing process
        if (bucket >= OUTGOING_RATE) {
            bucket -= OUTGOING_RATE;
            printf("%d\n", OUTGOING_RATE); // Print outgoing rate
        } else {
            printf("%d\n", bucket); // Print remaining if less than outgoing rate
            bucket = 0; // Empty the bucket
        }
    }

    // Drain any remaining packets in the bucket
    while (bucket > 0) {
        printf("%d\t0\t\t%d\t\t", ++i, bucket);
        if (bucket >= OUTGOING_RATE) {
            bucket -= OUTGOING_RATE;
            printf("%d\n", OUTGOING_RATE);
        } else {
            printf("%d\n", bucket);
            bucket = 0;
        }
    }
}

int main() {
    int n, i;

    printf("Enter the number of packet intervals: ");
    scanf("%d", &n);

    int packets[n];
    printf("Enter the incoming packets for each interval:\n");
    for (i = 0; i < n; i++) {
        printf("Interval %d: ", i + 1);
        scanf("%d", &packets[i]);
    }

    leaky_bucket(packets, n);

    return 0;
}

