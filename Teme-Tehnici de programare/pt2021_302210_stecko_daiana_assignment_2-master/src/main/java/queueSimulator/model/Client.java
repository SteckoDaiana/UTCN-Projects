package queueSimulator.model;

public class Client
{
    private int ID;
    private int serveTime;
    private int arriveTime;

    public Client(int ID, int serveTime, int arriveTime)
    {
        this.ID = ID;
        this.serveTime = serveTime;
        this.arriveTime = arriveTime;
    }

    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public int getServeTime() {
        return serveTime;
    }

    public void setServeTime(int serveTime) {
        this.serveTime = serveTime;
    }

    public int getArriveTime() {
        return arriveTime;
    }

    public void setArriveTime(int arriveTime) {
        this.arriveTime = arriveTime;
    }
}
