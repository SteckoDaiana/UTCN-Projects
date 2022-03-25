package queueSimulator.model;

public class Results
{
    public Results()
    {
        averageServiceTime = 0.0f;
        averageServiceTime = 0.0f;
        peakHour = 0;
        waitingClients = 0;
    }

    @Override
    public String toString()
    {
        String s = "";
        s += "Average Service Time: " + averageServiceTime + "\n";
        s += "Average Waiting Time: " + averageWaitingTime + "\n";
        s += "Peak hour: second " + peakHour + " with " + waitingClients + " clients waiting." + "\n";
        return s;
    }

    private float averageWaitingTime;
    private float averageServiceTime;
    private int peakHour;
    private int waitingClients;

    public float getAverageWaitingTime() {
        return averageWaitingTime;
    }

    public void setAverageWaitingTime(float averageWaitingTime) {
        this.averageWaitingTime = averageWaitingTime;
    }

    public float getAverageServiceTime() {
        return averageServiceTime;
    }

    public void setAverageServiceTime(float averageServiceTime) {
        this.averageServiceTime = averageServiceTime;
    }

    public int getPeakHour() {
        return peakHour;
    }

    public void setPeakHour(int peakHour, int waitingClients) {
        if(waitingClients > this.waitingClients){
            this.waitingClients = waitingClients;
            this.peakHour = peakHour;
        }
    }
}
