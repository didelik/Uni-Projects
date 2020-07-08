import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class KDServer {

    private ServerSocket serverSocket;
    public static int COUNTERID;
    private static ArrayList<ClientHandler> clients = new ArrayList<>();
    private static ExecutorService pool = Executors.newFixedThreadPool(20);

    public static synchronized int increaseCounterID() {
        return ++COUNTERID;
    }

    public void listener() {
        try {

            serverSocket = new ServerSocket(5600);
            while (true) {
                System.out.println("Server is waiting for client connection....");
                Socket client = serverSocket.accept();
                System.out.println("A connection is established");
                ClientHandler clientThread = new ClientHandler(client);
                clients.add(clientThread);
                pool.execute(clientThread);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void init() {
        try {
            File myObj = new File("ClientsInfo.txt");
            if (myObj.createNewFile()) {
                System.out.println("File created: " + myObj.getName());
            } else {
                System.out.println("File already exists.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }


        try {
            File SG = new File("SocialGraph.txt");
            if (SG.createNewFile()) {
                System.out.println("File created: " + SG.getName());
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }


        File directory = new File("ImagesServer");
        if (!directory.isDirectory()) {
            new File("ImagesServer").mkdir();
        }

        File clientsprofile = new File("ClientsProfile");
        if(!clientsprofile.isDirectory()){
            new File("ClientsProfile").mkdir();
        }
    }

    public static void main(String args[]){
        KDServer server = new KDServer();
        server.init();
        server.listener();
    }

}



