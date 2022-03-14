package queueSimulator.controller;

import javafx.application.Platform;
import queueSimulator.model.*;
import queueSimulator.view.GUI;

import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class Simulator extends TimerTask
{
    private final Arguments arguments;
    private Results results;
    private ArrayList<Client> clients;
    private ArrayList<ParallelQueue> queues;
    private FileWriter fout;
    private int time = -1;
    private Timer timer;
    private GUI gui;
    private Random r = new Random();

    public Simulator(Arguments arg, Timer t, GUI gui)
    {
        this.gui = gui;
        timer = t;
        results = new Results();
        arguments = arg;
        clients = ClientFactory.generateClients(arg.getN(), arg.getMinST(), arg.getMaxST(), arg.getMinAT(), arg.getMaxAT());
        for(Client c: clients){
            results.setAverageServiceTime(results.getAverageServiceTime() + c.getServeTime());
        }
        results.setAverageServiceTime(results.getAverageServiceTime() / arg.getN());
        queues = new ArrayList<>();
        for(int i = 0; i < arg.getQ(); i++){
            ParallelQueue pq = new ParallelQueue();
            queues.add(pq);
            pq.start();
        }
        try{
            fout =  new FileWriter("result.txt");
        }
        catch (IOException e){
            System.out.println(e.getMessage());
            System.exit(-1);
        }

    }

    @Override
    public String toString()
    {
        String s = "";
        s += "Time " + time + "\n";
        s += "Waiting clients: ";
        for(Client c: clients){
            s += "(" + c.getID() + "," + c.getArriveTime() + "," + c.getServeTime() + ") ";
        }
        s += "\n";
        int i = 1;
        for(ParallelQueue q: queues){
            s += "Queue " + i + ": ";
            i ++;
            if(q.queue.isEmpty())
                s += "empty";
            else
            {
                for(Client c: q.queue){
                    s += "(" + c.getID() + "," + c.getArriveTime() + "," + c.getServeTime() + ") ";
                }
            }
            s += "\n";
        }
        return s;
    }

    @Override
    public void run() {
        time++;
        int nr = 0;
        for(ParallelQueue q: queues){
            for(Client c: q.queue){
                nr++;
            }
        }
        results.setPeakHour(time, nr);
        if(time > arguments.getSimTime() || (nr == 0 && clients.size() == 0)){
            timer.cancel();
            clear();
            return;
        }
        Iterator<Client> it = clients.iterator();
        while(it.hasNext()){
            Client c = it.next();
            if(c.getArriveTime() == time) {
                queues.get(r.nextInt(queues.size())).addClient(c);
                it.remove();
            }
        }
        Platform.runLater(() -> gui.setArea(this.toString()) );
        try{
            fout.write(this.toString());
        }
        catch (IOException e){
            System.out.println("Failed :(");
        }
    }

    public Results getResult()
    {
        int sum = 0;
        for(ParallelQueue q: queues){
            sum += q.getTotalWaitTime();
        }
        results.setAverageWaitingTime( (float) sum / arguments.getN() );
        return results;
    }

    public void clear()
    {
        try{
            fout.write(getResult().toString());
            Platform.runLater(() -> gui.setArea(getResult().toString()) );
            fout.close();
        }
        catch (IOException e){
            System.out.println("It just wouldn't close :(");
        }
    }
}
