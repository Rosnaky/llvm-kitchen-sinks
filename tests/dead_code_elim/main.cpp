
void solve(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        *arr += arr[i];
    }
}

// Sum elements
int main() {

    // Must be power of 2
    constexpr int NUM_ELEMENTS = 1 << 20;
    // Must be power of 2
    constexpr int BATCH_SIZE = 16;

    int x = NUM_ELEMENTS * 3;
    int y = x + 3;    // dead
    int z = y * 2;    // dead

    if (NUM_ELEMENTS < BATCH_SIZE) while (1);
    
    if (false) {
        while(1);
    }

    int arr[NUM_ELEMENTS] = {0};

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        arr[i] = (i * 1e9+15) / (1e9+7);
    }

    int working_size = NUM_ELEMENTS;
    while (BATCH_SIZE <= NUM_ELEMENTS) {
        for (int i = 0; i < working_size/BATCH_SIZE; i++) {
            solve(arr + i*BATCH_SIZE, BATCH_SIZE);
            arr[i] = arr[i*BATCH_SIZE];
            working_size /= BATCH_SIZE;
        }
    }

    solve(arr, working_size);
}
