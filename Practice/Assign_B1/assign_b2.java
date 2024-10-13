import java.util.Vector;
import java.util.concurrent.Semaphore;
import java.lang.Runnable;
import java.lang.Thread;

class Container
{
    int item;
    Vector<Integer>buffer = new Vector(100); 
    static Semaphore con = new Semaphore(0);
    static Semaphore prod = new Semaphore(1);
    static Semaphore limit = new Semaphore(100);

    void put(int item)
    {
        try
        {
            prod.acquire();
            limit.acquire();
            this.item = item;
            buffer.add(item);
            System.out.println("Producer produced item "+item+" item");
            System.out.println("No. of items producer produced "+ buffer.size()+" items");
            System.out.println("No of items producer can still produce: "+limit.availablePermits());
            System.out.println();

        }
        catch(Exception e)
        {
            System.out.println("Error "+e);
        }
        prod.release();
        con.release();
    }

    void get()
    {
        try
        {
            prod.acquire();
            con.acquire();
            if(buffer.size() > 0)
            {
                System.out.println("No. of items consumer consumed "+ buffer.size()+" items");
                System.out.println("No of items left: "+prod.availablePermits());
            }
            System.out.println();
            buffer.clear();
        }
        catch(Exception e)
        {
            System.out.println("Error "+e);
        }
        prod.release();
        limit.release();
    }

}

class Producer implements Runnable
{
    Container PContain;
    Thread t1;
    Producer(Container c)
    {
        this.PContain = c;
        t1 = new Thread(this,"Producer");
        t1.start();
    }
    public void run()
    {
        try
        {
            for(int i=0;i<100;i++)
            {
                PContain.put(i);
                t1.sleep(5);
            }
        }
        catch(InterruptedException e)
        {
            System.out.println("Error "+e);
        }
    }
}

class Consumer implements Runnable
{
    Container CContain;
    Thread t2;
    Consumer(Container c)
    {
        this.CContain = c;
        t2 = new Thread(this,"Container");
        t2.start();
    }
    public void run()
    {
        try
        {
            for(int i=0;i<100;i++)
            {
                CContain.get();
                t2.sleep(30);
            }
        }
        catch(InterruptedException e)
        {
            System.out.println("Error "+e);
        }
    }
}

class Producer_Consumer
{
    public static void main(String [] args)
    {
        Container contain = new Container();
        Producer produce = new Producer(contain);
        Consumer consume = new Consumer(contain);
    }
}