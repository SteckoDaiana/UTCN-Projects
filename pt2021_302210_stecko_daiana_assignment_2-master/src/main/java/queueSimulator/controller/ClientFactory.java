package queueSimulator.controller;

import queueSimulator.model.Client;

import java.util.ArrayList;
import java.util.Random;

public class ClientFactory
{
    public static ArrayList<Client> generateClients(int N, int minST, int maxST, int minAT, int maxAT)
    {
        Random r = new Random();
        ArrayList<Client> clients = new ArrayList<>();
        for(int id = 1; id <= N; id++){
            int ST = r.nextInt(maxST - minST) + minST;
            int AT = r.nextInt(maxAT - minAT) + minAT;
            clients.add(new Client(id, ST, AT));
        }
        return clients;
    }
}
