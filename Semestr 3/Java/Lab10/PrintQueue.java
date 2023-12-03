import java.util.LinkedList;
import java.util.Queue;

class PrintQueue {
    private final Queue<String> buffer;
    private final int capacity;
    private boolean valueSet;
    private int count;

    public PrintQueue(int capacity) {
        this.buffer = new LinkedList<>();
        this.capacity = capacity;
        this.valueSet = false;
        this.count = 1;
    }

    public synchronized void put(String data) throws InterruptedException {
        while (valueSet || buffer.size() >= capacity) {
            wait();
        }

        String dataToAdd = data + "-" + count++;

        buffer.add(dataToAdd);
        System.out.println("Produced by " + Thread.currentThread().getName() + ": " + dataToAdd);

        valueSet = true;
        notifyAll();
    }

    public synchronized void get() throws InterruptedException {
        while (!valueSet || buffer.isEmpty()) {
            wait();
        }

        String data = buffer.poll();
        System.out.println("Consumed by " + Thread.currentThread().getName() + ": " + data + "\n");

        valueSet = false;
        notifyAll();
    }
}

class Producer implements Runnable {
    private final PrintQueue printQueue;

    public Producer(PrintQueue printQueue) {
        this.printQueue = printQueue;
    }

    @Override
    public void run() {
        try {
            while (true) {
                String data = "Data";
                printQueue.put(data);
                Thread.sleep(500); // Simulating production time
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Consumer implements Runnable {
    private final PrintQueue printQueue;

    public Consumer(PrintQueue printQueue) {
        this.printQueue = printQueue;
    }

    @Override
    public void run() {
        try {
            while (true) {
                printQueue.get();
                Thread.sleep(1000); // Simulating consumption time
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}