package queueSimulator.model;

import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.atomic.AtomicInteger;

public class ParallelQueue extends Thread
{
    public LinkedBlockingDeque<Client> queue;

    public ParallelQueue()
    {
        queue = new LinkedBlockingDeque<>();
        totalWaitTime.getAndSet(0);
    }

    AtomicInteger totalWaitTime = new AtomicInteger();

    @Override
    public void run() {
        try {
            while(true) {
                Client c = queue.take();
                queue.addFirst(c);
                while(c.getServeTime() != 0){
                    totalWaitTime.getAndAdd(queue.size() - 1);
                    Thread.sleep(1000);
                    c.setServeTime(c.getServeTime() - 1);
                }
                queue.take();
            }
        }
        catch (Exception e) {

        }
    }

    public void addClient(Client c) {
        queue.add(c);
    }

    public int getTotalWaitTime() {
        return totalWaitTime.get();
    }
}
