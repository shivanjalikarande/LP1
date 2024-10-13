import java.util.concurrent.Semaphore;
import java.lang.Runnable;
import java.lang.Thread;
import java.util.Vector;

class Container {
    int item;
    Vector<Integer>buffer = new Vector<Integer>(100);
    static Semaphore Con = new Semaphore(0);
    static Semaphore Prod = new Semaphore(1);
    static Semaphore limit = new Semaphore(100);

    void put(int item) {
        try 
        {
            limit.acquire();
            Prod.acquire(); // wait method is like acquire
            this.item = item;
            buffer.add(item);
            System.out.println("Producer produced item no." + item);
            System.out.println("Total items producer produced is : " + buffer.size() + " items");
            System.out.println("Number of items Producer can still produce : " + limit.availablePermits());

            System.out.println();
        } 
        catch (Exception eobj) 
        {
            System.out.println("Exception has occurred" + eobj);
        }
        Prod.release();
        Con.release(); // release method is for signalling
    }

    void get() 
    {
        try 
        {
            Con.acquire();
            Prod.acquire();
            if(buffer.size() > 0)
            {
                System.out.println("Consumer consumed : " + buffer.size() + " products");
                System.out.println("Number of items left : " + Prod.availablePermits());

                System.out.println();
                buffer.clear();
            }
        } 
        catch (Exception eobj) 
        {
            System.out.println("Exception occurred " + eobj);
        }
        Prod.release();
        limit.release();
    }
}

class Consumer implements Runnable {
    Container Pcontain;

    Thread t2;

    Consumer(Container c) {
        this.Pcontain = c;
        t2 = new Thread(this, "Consumer");
        t2.start();
    }

    public void run() {
        try {
            for (int i = 1; i <= 100; i++) {
                Pcontain.get();
                Thread.sleep(30);
            }
        } 
        catch (InterruptedException eobj) {
            System.out.println("Exception caught: " + eobj);
        }
    }
}

class Producer extends Thread {
    Container Ccontain;

    Thread t1;
    Producer(Container c) {
        this.Ccontain = c;
        t1 = new Thread(this, "Producer");
        t1.start();
    }

    public void run() {
        try {
            for (int i = 1; i <= 100; i++) {
                Ccontain.put(i);
                Thread.sleep(5);
            }
        } catch (InterruptedException eobj) {
            System.out.println("Exception caught: " + eobj);
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
