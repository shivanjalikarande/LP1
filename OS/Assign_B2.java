import java.util.concurrent.Semaphore;
import java.lang.Runnable;

class Container {
    int item;
    static Semaphore Con = new Semaphore(0);
    static Semaphore Prod = new Semaphore(1);
    static Semaphore limit = new Semaphore(100);

    void put(int item) {
        try {
            limit.acquire();
            Prod.acquire(); // wait method is like acquire
        } catch (Exception eobj) {
            System.out.println("Exception has occured" + eobj);
        }
        this.item = item;
        System.out.println("Producer produced an item " + item);

        Prod.release();
        Con.release(); // release method is for signalling
    }

    void get() {
        try {
            Prod.acquire();
            Con.acquire();
        } catch (Exception eobj) {
            System.out.println("Exception occured " + eobj);
        }
        System.out.println("Consumer consumed an item " + item);
        Prod.release();
        limit.release();
    }
}

class Consumer implements Runnable {
    Container Pcontain;

    Consumer(Container c) {
        this.Pcontain = c;
        new Thread(this, "Consumer").start();
    }

    public void run() {
        for (int i = 0; i < 100; i++) {
            Pcontain.get();
        }
    }
}

class Producer implements Runnable {
    Container Ccontain;

    Producer(Container c) {
        this.Ccontain = c;
        new Thread(this, "Producer").start();
    }

    public void run() {
        for (int i = 0; i < 100; i++) {
            Ccontain.put(i);
        }
    }
}

class Producer_Consumer {
    public static void main(String args[]) {
        Container contain = new Container();
        new Producer(contain);
        new Consumer(contain);
    }

}