public class Main {
    public static void main(String[] args) {
        PrintQueue printQueue = new PrintQueue(10);

        Thread producerThread = new Thread(new Producer(printQueue));

        Thread consumerThread = new Thread(new Consumer(printQueue));

        producerThread.start();
        consumerThread.start();
    }
}
