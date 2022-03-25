package queueSimulator.model;

public class Arguments
{
    public Arguments(int N, int Q, int minST, int maxST, int minAT, int maxAT, int simTime)
    {
        this.N = N;
        this.Q = Q;
        this.minST = minST;
        this.maxST = maxST;
        this.minAT = minAT;
        this.maxAT = maxAT;
        this.simTime = simTime;
    }

    private int N;
    private int Q;
    private int minST;
    private int maxST;
    private int minAT;
    private int maxAT;

    private int simTime;


    public int getN() {
        return N;
    }

    public void setN(int n) {
        N = n;
    }

    public int getQ() {
        return Q;
    }

    public void setQ(int q) {
        Q = q;
    }

    public int getMinST() {
        return minST;
    }

    public void setMinST(int minST) {
        this.minST = minST;
    }

    public int getMaxST() {
        return maxST;
    }

    public void setMaxST(int maxST) {
        this.maxST = maxST;
    }

    public int getMinAT() {
        return minAT;
    }

    public void setMinAT(int minAT) {
        this.minAT = minAT;
    }

    public int getMaxAT() {
        return maxAT;
    }

    public void setMaxAT(int maxAT) {
        this.maxAT = maxAT;
    }

    public int getSimTime() {
        return simTime;
    }

    public void setSimTime(int simTime) {
        this.simTime = simTime;
    }
}
