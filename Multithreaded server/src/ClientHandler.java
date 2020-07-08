import java.io.*;
import java.net.Socket;
import java.net.SocketException;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;
import java.nio.channels.OverlappingFileLockException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.awt.Desktop;

public class ClientHandler implements Runnable ,java.io.Serializable {

    public Socket client;
    private ObjectInputStream in;
    private ObjectOutputStream out;
    private int max_file_data_packet_size = 255;

    int counter = 0;




    public ClientHandler(Socket clientSocket) {
        this.client = clientSocket;
        try {
            in = new ObjectInputStream(client.getInputStream());
            out = new ObjectOutputStream(client.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendFile(String file) {
        try {
            int sequence = 0;
            String ack = null;
            byte b[] = new byte[max_file_data_packet_size + 1];
            boolean resend = false;
            FileInputStream image = new FileInputStream(new File(file));
            while (image.available() > 0) {
                if (resend) {
                    out.write(b, 0, b.length);
                    out.flush();
                    System.out.println("Re sending the packet successfully");
                    resend = false;
                } else {
                    //System.out.println("Sending packet with ACK SEQUENCE "+sequence);
                    image.read(b, 0, b.length - 1);
                    b[b.length - 1] = (byte) sequence;
                    out.write(b, 0, b.length);
                    out.flush();
                }
                try {
                    // System.out.println("Waiting for ack....");
                    Thread.sleep(10);
                    ack = (String) in.readObject();
                } catch (Exception e) {
                    System.out.println("Exception in getting ack");
                }
                if (ack != null && sequence==Integer.parseInt(ack)) {
                    //System.out.println("Properly ACK received.");
                    //System.out.println("ACK NUMBER RECEIVED :"+ack);
                    sequence = (sequence == 0) ? 1 : 0;
                } else {
                    System.out.println("Server did not receive ACK or the Sync failed");
                    System.out.println("Resend the packet");
                    resend = true;
                }

            }

            b[b.length - 1] = (byte) 2;
            out.write(b, 0, b.length);
            out.flush();
            System.out.println("The transmission is completed");
            image.close();
        } catch (IOException e) {
            System.out.println(e);
        }
    }

    public void receiveFile(String name, String clientId) {
        try {
            int sequence = 0;
            byte[] b = new byte[max_file_data_packet_size + 1];

            FileOutputStream fr = new FileOutputStream("ImagesServer\\" + clientId + "\\" + name + ".jpg");
            while (true) {
                in.read(b, 0, b.length);
                if ((int) b[b.length - 1] == (sequence)) {
                    fr.write(b, 0, b.length - 1);
                    out.writeObject(String.valueOf(sequence));
                    out.flush();
                    sequence = (sequence == 0) ? 1 : 0;
                } else if (b[b.length - 1] == (byte) 2) {
                    break;
                } else {
                    System.out.println("Error in data packet.Deleted!");
                }

            }
            System.out.println("File received");
            fr.close();
        } catch (IOException e) {
            e.printStackTrace();

        }
    }

    @Override
    public void run() {
        // TODO Auto-generated method stub
        String[] clientInfo = null;
        try {
            while(true) {
                String entry = (String) in.readObject();
                if (entry.equals("signin")) {
                    if ((clientInfo = checkForAccount()) != null) {
                        out.writeObject("Welcome sir " + clientInfo[4].toUpperCase());
                        out.writeObject(Integer.parseInt(clientInfo[4]));
                        while (!entry.equals("Disconnect")) {
                            entry = (String) in.readObject();
                            System.out.println(entry);
                            if (entry.equals("Upload")) {
                                // Receive the name of the image.
                                entry = (String) in.readObject();
                                // make a directory for him to store his images.
                                makeDirectory(clientInfo[4]);
                                //Receive the image
                                receiveFile(entry, clientInfo[4]);
                                //Write the client made an upload
                                writeToClientProfile(clientInfo[4], entry);

                            }
                            if (entry.equals("Download")) {
                                String requester = (String) in.readObject();
                                String owner = (String) in.readObject();
                                String photo = (String) in.readObject();

                                BufferedReader reader = new BufferedReader(new FileReader("ClientsProfile\\PhotoReqs_1050_" + owner + ".txt"));
                                String line;
                                while ((line = reader.readLine()) != null) {
                                    if(line.contains(requester) && line.contains("download") && line.contains("granted") && line.contains(photo)){
                                        // Send the image to client
                                        sendFile("ImagesServer\\" + owner + "\\" + photo);
                                        // make a directory for him to store his images.
                                        makeDirectory(clientInfo[4]);
                                        // Copy the image to client directory.
                                        copyImageTo(owner, photo, clientInfo[4]);
                                    }
                                    if(line.contains(requester) && line.contains("download") && line.contains("denied") && line.contains(photo)){
                                        out.writeObject("Owner denied your access.You cannot download the photo");
                                    }
                                }

                            }
                            if (entry.equals("Access_Profile")) {

                                String id = (String) in.readObject();

                                boolean follows = checkFollowers(clientInfo[4], id);
                                out.writeObject(follows);
                                if (follows) {

                                    String name = "profile_1050" + id + ".txt";
                                    File file = new File("ClientsProfile");
                                    File[] list = file.listFiles();
                                    if (list != null)
                                        for (File fil : list) {
                                            if (name.equalsIgnoreCase(fil.getName())) {
                                                lockTheFile(name);

                                            }
                                        }
                                }
                            }

                            if (entry.equals("Search_Image")) {
                                String imageName = (String) in.readObject();
                                ArrayList<String> clientswithcertainimage = clientWithCertainImage(imageName, clientInfo[4]);
                                out.writeObject(clientswithcertainimage);
                            }

                            if (entry.equals("Follow")) {
                                entry = (String) in.readObject();  //Receive ID that client typed
                                String[] IDS = entry.split(" ", 2);
                                String sender = IDS[0];
                                String receiver = IDS[1];
                                String info = detectSocketInfo(receiver);
                                boolean check = checkFollowers(sender, receiver);
                                if (info != null && !check) {
                                    out.writeObject("Follow request sent successfully! Waiting for response");

                                    //New version of follow part***************************************.
                                    try {
                                        File file = new File("ClientsProfile\\Requests_1050"+receiver+".txt");
                                        if (file.createNewFile()) {
                                            System.out.println("File created: " + file.getName());
                                        }
                                        BufferedWriter writer = new BufferedWriter(new FileWriter(file,true));
                                        System.out.println("write to 13033 brooooo");
                                        writer.write("Account with ID: " + sender + " wants to follow you." +
                                                "Accept the request?[Y/N]");
                                        writer.newLine();
                                        writer.close();


                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    }



                                }
                                if (info == null)
                                    out.writeObject("The account with ID: " + receiver + " does not exist");
                                if (check)
                                    out.writeObject("You are already following this account");
                            }
                            if (entry.equals("Unfollow")) {
                                entry = (String) in.readObject();
                                String[] IDS = entry.split(" ", 2);
                                String sender = IDS[0];
                                String receiver = IDS[1];
                                String info = detectSocketInfo(receiver);
                                boolean check = checkFollowers(sender,receiver);
                                if (info != null && check) {
                                    updateSocialGraph(sender, receiver, false);
                                    out.writeObject("You have unfollowed the account " + sender);
                                }
                                if (info == null)
                                    out.writeObject("The account with ID: " + sender + "does not exist");
                                if (!check)
                                    out.writeObject("You don't follow this account");
                            }

                            if(entry.equals("View_Request")){
                                BufferedReader reader = new BufferedReader(new FileReader(new File("ClientsProfile\\Requests_1050"+clientInfo[4])+".txt"));
                                String line;
                                int lineCounter = 1;
                                while((line=reader.readLine())!=null){
                                    out.writeObject(lineCounter+"."+line);
                                    lineCounter++;
                                }
                                reader.close();
                                out.writeObject(null);

                                String input = (String) in.readObject();

                                String[] response = input.split(" ");
                                if (response[1].equals("Y")) {
                                    updateSocialGraph(response[2], clientInfo[4], true);
                                    updateRequests(response[0],clientInfo[4]);
                                }else{
                                    System.out.println(true);
                                    updateRequests(response[0],clientInfo[4]);
                                }
                            }

                            if(entry.equals("Comment")){
                                String info =(String) in.readObject();
                                String comment = (String)in.readObject();
                                try {
                                    File file = new File("ClientsProfile\\CommentRequests_1050"+info.split(" ")[0]+".txt");
                                    if (file.createNewFile()) {
                                        System.out.println("File created: " + file.getName());
                                    }
                                    BufferedWriter writer = new BufferedWriter(new FileWriter(file,true));
                                    writer.write("Client "+clientInfo[4]+" on image "+info.split(" ")[1]+" of "+info.split(" ")[0]+" comment , do you want the client to publish it in his/her profile?[Y/N]");
                                    writer.newLine();
                                    writer.write("Comment: "+comment);
                                    writer.newLine();
                                    writer.close();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                writeComment(info,comment,clientInfo[4]);
                            }
                            if(entry.equals("View_Comment_Requests")){
                                ArrayList<String> lines = new ArrayList<String>();
                                BufferedReader reader = new BufferedReader(new FileReader(new File("ClientsProfile\\CommentRequests_1050"+clientInfo[4])+".txt"));
                                String line=null;
                                int lineCounter = 1;
                                while((line=reader.readLine())!=null){
                                    out.writeObject(lineCounter+"."+line);
                                    lines.add(line);
                                    line= reader.readLine();
                                    out.writeObject(line);
                                    lines.add(line);
                                    lineCounter++;
                                }
                                reader.close();
                                out.writeObject(null);

                                String input = (String) in.readObject();
                                String[] response = input.split(" ");
                                int num1 =  2*(Integer.parseInt(response[0])-1);
                                int num2 = 2*(Integer.parseInt(response[0])-1)+1;
                                if (response[1].equals("Y")) {
                                    updateClientProfile(lines.get(num1),lines.get(num2));
                                    BufferedWriter writer = new BufferedWriter(new FileWriter(new File("ClientsProfile\\CommentRequests_1050"+clientInfo[4])+".txt"));
                                    for(int i =0; i<lines.size();i++){
                                        if(i==num1 || i==num2)continue;
                                        writer.write(lines.get(i));
                                        writer.newLine();
                                    }
                                    lines.clear();
                                    writer.close();
                                }
                            }
                            if(entry.equals("Others_Profile")){
                                BufferedWriter writer=null;
                                try {
                                    File file = new File("ClientsProfile\\Others_1050"+clientInfo[4]+".txt");
                                    if (file.createNewFile()) {
                                        System.out.println("File created: " + file.getName());

                                    } else {
                                        System.out.println("File already exists.");
                                    }
                                    writer  = new BufferedWriter(new FileWriter(file));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }

                                BufferedReader reader = new BufferedReader(new FileReader(new File("SocialGraph.txt")));
                                String line = null;
                                while((line=reader.readLine())!=null){
                                    String [] clients = line.split(" ");
                                    if(!clients[0].equals(clientInfo[4])){
                                        if(line.contains(clientInfo[4])){
                                            try {
                                                File file = new File("ClientsProfile\\profile_1050"+clients[0]+".txt");
                                                if (file.createNewFile()) {
                                                    System.out.println("File created: " + file.getName());

                                                } else {
                                                    System.out.println("File already exists.");
                                                }
                                            } catch (IOException e) {
                                                e.printStackTrace();
                                            }
                                            BufferedReader readerProfile = new BufferedReader(new FileReader(new File("ClientsProfile\\profile_1050"+clients[0]+".txt")));
                                            String infoProfile =null;
                                            out.writeObject("***************************************************");
                                            out.flush();
                                            writer.write("***************************************************");
                                            writer.newLine();
                                            out.writeObject("Profile of "+clients[0]);
                                            out.flush();
                                            writer.write("Profile of"+clients[0]);
                                            writer.newLine();
                                            while((infoProfile=readerProfile.readLine())!=null){
                                                out.writeObject(infoProfile);
                                                out.flush();
                                                writer.write(infoProfile);
                                                writer.newLine();
                                            }
                                            out.writeObject("End profile of "+clients[0]);
                                            out.flush();
                                            writer.write("End profile of "+clients[0]);
                                            writer.newLine();
                                            out.writeObject("***************************************************");
                                            out.flush();
                                            writer.write("***************************************************");
                                            writer.newLine();
                                        }
                                    }
                                }
                                out.writeObject(null);
                                out.flush();
                                writer.close();
                            }

                            if(entry.equals("viewPhoto")) {
                                String requester = (String) in.readObject();
                                String owner = (String) in.readObject();
                                String photo = (String) in.readObject();
                                BufferedReader reader = new BufferedReader(new FileReader("ClientsProfile\\PhotoReqs_1050_" + owner + ".txt"));
                                String line;
                                while ((line = reader.readLine()) != null) {
                                    if(line.contains(requester) && line.contains("view") && line.contains("granted") && line.contains(photo)){
                                        File image = new File("ImagesServer\\" + owner + "\\" + photo);
                                        if (image.createNewFile()) {
                                            System.out.println("File created: " + image.getName());
                                        }
                                        Desktop d = Desktop.getDesktop();
                                        d.open(image);

                                    }
                                    if(line.contains(owner) && line.contains("view") && line.contains("denied") && line.contains(photo)){
                                        out.writeObject("Owner denied your access.You cannot view the photo");
                                    }
                                }
                            }

                            if(entry.equals("askPerm")) {
                                String sender = (String) in.readObject();
                                String receiver = (String) in.readObject();
                                String photo = (String) in.readObject();
                                String answer = (String) in.readObject();
                                try {
                                    File file = new File("ClientsProfile\\PhotoAsks_1050_" + receiver + ".txt");
                                    if (file.createNewFile()) {
                                        System.out.println("File created: " + file.getName());
                                    }
                                    BufferedWriter writer = new BufferedWriter(new FileWriter(file,true));
                                    if (answer.equals("V")) {
                                        writer.write(counter + "." + " Client " + sender + " wants to view photo: " + photo);
                                        writer.newLine();
                                    } else if (answer.equals("D")) {
                                        writer.write(counter + "." + " Client " + sender + " wants to download photo: " + photo);
                                        writer.newLine();
                                    }
                                    counter++;
                                    writer.close();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }


                            if(entry.equals("viewPerm")){
                                String id = (String) in.readObject();
                                String ans = (String) in.readObject();
                                String[] info = ans.split(" ", 2);
                                String lineNumb = info[0];
                                String answer = info[1];

                                String request = updatePhotoAsks(lineNumb,id);
                                updatePhotoRequests(id,answer,request);
                            }

                        }
                        break;
                    } else {
                        out.writeObject("Wrong email or password.");
                    }
                } else if (entry.equals("signup")) {
                    boolean registration = writeToRegistrationFile();
                    if (registration) {
                        out.writeObject("Your account has been created successfully!");
                    } else {
                        out.writeObject("Error occurred please try again.");
                    }
                    continue;
                } else {
                    System.out.println("Not valid answer.");
                }
            }
            disconnect();

        } catch (SocketException e) {
            System.out.println("Client Disconnect");
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }


    public boolean checkFollowers(String sender,String receiver)  {
        BufferedReader sc = null;
        try {
            sc = new BufferedReader(new FileReader(new File("SocialGraph.txt")));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        String line;
        try{
            while ((line = sc.readLine()) != null){
                if(line.split(" ")[0].equals(receiver)){
                    if(line.contains(sender)){
                        return true;
                    }
                }
            }
        }catch(IOException e) {
            e.printStackTrace();
        }
        return false;
    }



    public void updateSocialGraph(String sender,String receiver,boolean add) throws IOException {
        int counter = -1;
        File sgf = new File("SocialGraph.txt");

        String lineData = null;
        BufferedReader reader = new BufferedReader(new FileReader(sgf));
        String line = null;

        if (add) {
            while ((line = reader.readLine()) != null ) {
                counter++;
                if ((line.split(" ")[0]).equals(receiver)){
                    lineData = line;
                    List<String> lines = Files.readAllLines(sgf.toPath());
                    lines.set(counter, lineData + " " + sender);
                    Files.write(sgf.toPath(), lines);
                    break;
                }
            }

        } else{
            while ((line = reader.readLine()) != null) {
                counter++;
                if ((line.split(" ")[0]).equals(receiver)) {
                    if (line.contains(sender)) {
                        line = line.replace( " "+sender, "");
                        List<String> lines = Files.readAllLines(sgf.toPath());
                        lines.set(counter, line);
                        Files.write(sgf.toPath(), lines);
                        break;
                    }
                }
            }
        }
    }



    public String detectSocketInfo(String clientID){
        String SocketInfo = null;
        boolean found = false;
        String ip,PORT,IPFinal;
        BufferedReader input = null;
        try {
            input = new BufferedReader(new FileReader("ClientsInfo.txt"));
            String line = null;
            while ( (line=input.readLine()) != null ) {
                line = line.trim();
                if(clientID.equals(line.split(" ")[4])) {
                    found = true;
                    ip = line.split(" ")[5];
                    PORT = clientID;
                    IPFinal = ip.substring(1);
                    SocketInfo = IPFinal + " " + PORT;
                    break;
                }
            }
            if(found == false){
                System.out.println("ID NOT FOUND");
                return null;
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
        return SocketInfo;
    }


    public void makeDirectory(String id) {
        File directory = new File("ImagesServer\\" + id);
        if (!directory.isDirectory()) {
            new File("ImagesServer\\" + id).mkdir();
        }
    }

    public void copyImageTo(String fromId, String imageName, String toId) {
        try {
            Files.copy(Paths.get("ImagesServer\\" + fromId + "\\" + imageName),
                    Paths.get("ImagesServer\\" + toId + "\\" + imageName));
        } catch (IOException e) {
            // TODO Auto-generated catch block
            System.err.println("Problem coping image.Check the file :" + toId);
            e.printStackTrace();
        }
    }

    public boolean writeToRegistrationFile() {
        String entry = null;
        try {
            out.writeObject(
                    "Enter name: \nEnter lastname : \nEnter email :\nEnter password\nInput form [name lastname email password].");
            entry = (String) in.readObject();
        } catch (ClassNotFoundException e1) {
            System.err.println("Error on casting to string writeToRegistrationFile method");
            return false;
        } catch (IOException e1) {
            System.err.println("Error on reading or writing to socket writeToRegistrationFile method");
            return false;
        }
        String clientID = getNextId();

        if(clientID==null){
            clientID = "13033";
        }else{
            clientID = String.valueOf(Integer.parseInt(clientID)+1);
        }

        String registration = (entry + " " + clientID + " " + client.getInetAddress() + " "
                + client.getPort() + "\n");
        BufferedWriter writer = null;
        try {

            writer = new BufferedWriter(new FileWriter("ClientsInfo.txt", true));
            System.out.println(client.getInetAddress() + " " + client.getPort() + "\n");
            writer.write(registration);
            writer.close();
        } catch (IOException e) {
            System.err.println("Error in clientsInfo file.");

        }
        try{
            writer = new BufferedWriter(new FileWriter("SocialGraph.txt",true));
            writer.write(clientID+"\n");
            writer.close();
        }catch (IOException e) {
            // TODO Auto-generated catch block
            System.err.println("Error in clientsInfo file.");

        }
        return true;
    }

    public String getNextId(){
        BufferedReader br = null;
        String id=null;
        try {
            br = new BufferedReader(new FileReader(new File("ClientsInfo.txt")));

            String [] st  = null;
            String line = br.readLine();
            while (line!= null) {
                st = line.split(" ");
                id = st[4];
                line = br.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return id;
    }

    public String[] checkForAccount() {
        String entry = null;
        try {
            out.writeObject("Please give your email and passphrase\nTyping form [email passphrase]");
            entry = (String) in.readObject();
        } catch (IOException | ClassNotFoundException e2) {
            // TODO Auto-generated catch block
            System.err.println("Error writing or reading from the socket checkForAccount method.");
        }

        String[] clientInput = entry.split(" ");
        BufferedReader reader = null;

        String st;

        try {
            reader = new BufferedReader(new FileReader("ClientsInfo.txt"));
            while ((st = reader.readLine()) != null) {
                String[] clientInfo = st.split(" ");
                if (clientInfo[2].equals(clientInput[0]) && clientInfo[3].equals(clientInput[1]))
                    return clientInfo;
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            System.out.println("Error on reading clientsInfo.txt");
        }
        return null;
    }

    public void writeToClientProfile(String id, String photoName) {
        try {
            File file = new File("ClientsProfile\\profile_1050" + id + ".txt");
            if (file.createNewFile()) {
                System.out.println("File has been created successfully");
            } else {
                System.out.println("File already present at the specified location");
            }
            BufferedWriter writer = new BufferedWriter(new FileWriter(file, true));
            writer.write(id + " posted " + photoName + ".jpg");
            writer.newLine();
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public ArrayList<String> clientWithCertainImage(String imageName, String clientId) {
        ArrayList<String> clientwithcertainimage = new ArrayList<String>();
        try {
            BufferedReader reader = new BufferedReader(new FileReader("SocialGraph.txt"));
            String st;
            String[] line = null;
            ArrayList<String> follows= new ArrayList<String>();
            while ((st = reader.readLine()) != null) {
                line = st.trim().split(" ");
                if (!line[0].equals(clientId)) {
                    if (st.contains(clientId)) {
                        follows.add(line[0].trim());
                    }
                }

            }


            for (int i = 0; i < follows.size(); i++) {
                File file = new File("ImagesServer\\" + follows.get(i));
                File[] list = file.listFiles();
                if (list != null)
                    for (File fil : list) {
                        if (imageName.equalsIgnoreCase(fil.getName())) {
                            clientwithcertainimage.add(follows.get(i));
                        }
                    }
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            System.out.println("Error on reading SocialGraph.txt");
            e.printStackTrace();
        }
        return clientwithcertainimage;
    }

    public void disconnect() {
        try {
            client.close();
            in.close();
            out.close();
            ;
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void lockTheFile(String name) {
        try {
            RandomAccessFile file = new RandomAccessFile("ClientsProfile\\" + name, "rw");
            FileChannel channel = file.getChannel();
            FileLock lock = null;
            while(true) {
                try {
                    lock = channel.tryLock();
                    out.writeObject("Welcome");
                    out.flush();
                    break;
                } catch (OverlappingFileLockException e) {
                    out.writeObject("The file is locked\nPlease wait.");
                    out.flush();
                    Thread.sleep(12);
                }
            }

            String st;
            while ((st = file.readLine()) != null) {
                out.writeObject(st);
                out.flush();
            }
            out.writeObject("End");
            out.flush();

            TimeUnit.SECONDS.sleep(10);

            out.writeObject("The server will lock the file");
            lock.release();

            file.close();
            channel.close();

        }catch (IOException e){
            e.printStackTrace();
            System.err.println("The file is close");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Done with access profile");
    }

    public void updateRequests(String line,String id){
        File inputFile = new File("ClientsProfile\\Requests_1050"+id+".txt");
        File tempFile = new File("ClientsProfile\\myTempFile.txt");
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(inputFile));
            BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile));
            String currentLine=null;
            int counter=0;
            while((currentLine = reader.readLine()) != null) {
                // trim newline when comparing with lineToRemove
                String trimmedLine = currentLine.trim();
                if((++counter) == Integer.parseInt(line) ) continue;
                writer.write(currentLine + System.getProperty("line.separator"));
            }
            reader.close();
            if(!inputFile.delete()){
                System.out.println("Problem deleting file");
            }
            writer.close();
            boolean successful = tempFile.renameTo(new File("ClientsProfile\\Requests_1050" + id + ".txt"));

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public String updatePhotoAsks(String lineNumb,String id) {
        File inputFile = new File("ClientsProfile\\PhotoAsks_1050_" + id + ".txt");
        File tempFile = new File("ClientsProfile\\myTempFile.txt");
        BufferedReader reader = null;
        String request = null;
        char line;
        try {
            reader = new BufferedReader(new FileReader(inputFile));
            BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile));
            String currentLine;
            while((currentLine = reader.readLine()) != null) {
                // trim newline when comparing with lineToRemove
                String trimmedLine = currentLine.trim();
                line = trimmedLine.charAt(0);
                if((String.valueOf(line).equals(lineNumb)) ){
                    request = trimmedLine;
                    continue;
                }
                writer.write(currentLine + System.getProperty("line.separator"));
            }
            reader.close();
            if(!inputFile.delete()){
                System.out.println("Problem deleting file");
            }
            writer.close();
            boolean successful = tempFile.renameTo(new File("ClientsProfile\\PhotoAsks_1050_" + id + ".txt"));

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return request;
    }

    public void updatePhotoRequests(String id,String answer,String request) throws IOException {
        String[] info = request.split(" ");
        String sender = info[2];
        String action = info[5];
        String photo = info[7];
        File file = new File("ClientsProfile\\PhotoReqs_1050_" + id + ".txt");
        BufferedWriter writer = new BufferedWriter(new FileWriter(file,true));

        if(answer.equals("Y")) {
            if (action.equals("download")) {
                writer.write("Permission for download granted to client "+ sender + " for photo " + photo + "\n");
            } else if (action.equals("view")) {
                writer.write("Permission for view granted to client "+ sender + " for photo " + photo + "\n");
            }
        }
        if(answer.equals("N")) {
            if (action.equals("download")) {
                writer.write("Permission for download denied to client "+ sender + " for photo " + photo + "\n");
            }else if (action.equals("view")) {
                writer.write("Permission for view denied to client "+ sender + " for photo " + photo + "\n");
            }
        }
        writer.close();
    }

        public void writeComment(String info , String comment,String commenter){
        File file = new File("ClientsProfile\\profile_1050"+info.split(" ")[0]+".txt");
        File temp = new File("ClientsProfile\\temp"+info.split(" ")[0]+".txt");
        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            BufferedWriter writer = new BufferedWriter(new FileWriter(temp));
            String line=null;
            while((line=reader.readLine())!=null){
                writer.write(line);
                writer.newLine();
                if(line.contains(info.split(" ")[1]) && line.equals(line.trim())){
                    writer.write("\t"+comment+" posted by "+commenter+" on image "+info.split(" ")[1]);
                    writer.newLine();
                }
            }
            reader.close();
            file.delete();
            writer.close();
            boolean successful = temp.renameTo(new File("ClientsProfile\\profile_1050" + info.split(" ")[0]+ ".txt"));

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void updateClientProfile(String comment, String comm){
        System.out.println(comment);
        System.out.println(comm);
        try {
            File file = new File("ClientsProfile\\profile_1050"+comment.split(" ")[1]+".txt");
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }
            BufferedWriter writer = new BufferedWriter(new FileWriter(new File("ClientsProfile\\profile_1050"+comment.split(" ")[1]+".txt"),true));
            writer.write(comment.split(" ")[1]+" posted on image "+comment.split(" ")[4]+" of "+comment.split(" ")[6]+" "+comm.substring(8));
            writer.newLine();
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    public void start() {
        run();
    }
}