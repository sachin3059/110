#include <bits/stdc++.h>
using namespace std;

class RW {
private:
    mutex readlock;     // To protect readcount
    mutex writelock;    // To ensure exclusive access for writing
    int readcount = 0;  // Counter to track number of active readers

public:
    // Reader thread function
    void reader(int thread_num) {
        unique_lock<mutex> lock(readlock);
        readcount++;
        if (readcount == 1) {
            writelock.lock();  // First reader blocks writers
        }
        lock.unlock();  // Allow other readers to access the resource

        // Simulate reading
        cout << "Thread " << thread_num << " is reading." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Thread " << thread_num << " finished reading." << endl;

        lock.lock();  // Reacquire lock to update readcount
        readcount--;
        if (readcount == 0) {
            writelock.unlock();  // Last reader releases writer lock
        }
    }

    // Writer thread function
    void writer(int thread_num) {
        unique_lock<mutex> lock(writelock);  // Ensure exclusive access for writing

        // Simulate writing
        cout << "Thread " << thread_num << " is writing." << endl;
        this_thread::sleep_for(chrono::milliseconds(1500));
        cout << "Thread " << thread_num << " finished writing." << endl;
    }

    // Function to manage the reader and writer threads
    void run() {
        int n;
        cout << "Enter the number of processes (1 for read, 0 for write): ";
        cin >> n;

        vector<int> seq(n);
        cout << "Enter the sequence of operations (1 for reading, 0 for writing):\n";
        for (int i = 0; i < n; ++i) {
            cin >> seq[i];
        }

        vector<thread> processes;
        int thread_counter = 1;  // Thread counter starting from 1
        for (int i = 0; i < n; ++i) {
            if (seq[i] == 1) {
                processes.push_back(thread(&RW::reader, this, thread_counter));
            } else {
                processes.push_back(thread(&RW::writer, this, thread_counter));
            }
            thread_counter++;  // Increment thread number for the next thread
        }

        // Wait for all threads to finish
        for (auto& t : processes) {
            t.join();
        }
    }
};

int main() {
    RW rw;
    rw.run();  // Start the reader-writer process
    return 0;
}
