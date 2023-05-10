package ro.tuc.ds2020.reciver;

class MultithreadingDemo extends  Thread{
    int noThreads=0;

    public int getNoThreads() {
        return noThreads;
    }

    public void setNoThreads(int noThreads) {
        this.noThreads = noThreads;
    }

    public void run()
    {
        try {
            // Displaying the thread that is running
            System.out.println(
                    "Thread " + Thread.currentThread().getId()
                            + " is running");
            Worker.main(noThreads);
        }
        catch (Exception e) {
            // Throwing an exception
            System.out.println("Exception is caught");
        }
    }

}
public class QueueCreator {
    public static void callMainRecivers()
    {
        int n = 8; // Number of threads
        for (int i = 0; i < n; i++) {
            MultithreadingDemo object
                    = new MultithreadingDemo();
            object.setNoThreads(i);
            object.start();
        }
    }
}
