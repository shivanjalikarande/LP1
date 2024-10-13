
import java.concurrent.Semaphore;
import java.lang.Runnable;
import java.lang.Vector;
import java.util.Vector;


class Container
{
    int item = 0;
    Vector<Integer>buffer = new Vector<Integer>buffer;
    static Semaphore con = new Semaphore(0);
    static Semaphore prod = new Semaphore(1);

    void get()
    {
        try
        {
            con.acquire();
            prod.acquire();
            System.out.println("Consumer consumed : "+buffer.size()+" items");
            System.out.println("No of items left: "+limit.availablePermits());
            buffer.clear();
        }
        catch(Exception exp)
        {
            cout<<"Exception: "+exp<<endl;
        }
        prod.release();
        limit.release();
    }

    void put(int item)
    {
        try
        {
            limit.acquire();
            prod.acquire();
            buffer.add(item);
            System.out.println("Producer produced item: "+item);
            System.out.println("Total no of items produced: "+buffer.size()<<" items");
            System.out.println("No of items producer can produce: "+limit.availablePermits());
        }
        catch(Exception exp)
        {
            System.out.println("Exception: "+exp);
        }
        prod.release();
        con.release();
    }
    

}


class Consumer implements Runnable
{
    Container Ccontain;
    Consumer(Container c)
    {
        Ccontain = c;
        Thread t1 = new Thread(this,"Consumer");
        t1.start();
    }
    public void run()
    {
        try
        {
            for(int i=0;i<100;i++)
            {
                Ccontain.get();
                Thread.sleep(30);
            }
        }
        catch(InterruptedException excp)
        {
            System.out.println("Exception occurred: "+excp);
        }
    }
}


class Producer implements Runnable
{
    Container Pconatin;
    Producer(Container c)
    {
        PContain = c;
        Thread t2 = new Thread(this,"Producer");
    }
    public void run()
    {
        try
        {
            for(int i=0;i<100;i++)
            {
                Pconatin.put(i);
                Thread.sleep(5);
            }
        }
        catch(InterruptedException excp)
        {
            System.out.println("Exception occurred: "+excp);
        }
    }
}

class Producer_Consumer
{
    public static void main(String [] args)
    {
        Container contain = new Container();
        Producer p = new Producer(contain);
        Consumer c = new Comsumer(contain);
    }

}