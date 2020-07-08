import java.io.*;
import java.net.Socket;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Scanner;

public class KDClient implements java.io.Serializable {


    private static final long serialVersionUID = 1L;
    private String serverAddress = "192.168.1.25";
    private int serverPort = 5600;
    private Socket socket;
    private ObjectOutputStream out = null;
    private ObjectInputStream in = null;
    private int max_file_data_packet_size = 255;
    private int CLIENTID;


    public void followReq() {
        System.out.println("Please write (your ID)_(Other acc's ID)");
        Scanner input = new Scanner(System.in);
        String str = input.nextLine();
        try {
            out.writeObject("Follow");
            out.flush();
            out.writeObject(str);
            out.flush();
            System.out.println(in.readObject());
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public String prompt() {
        System.out.println("Write your account's ID");
        Scanner input = new Scanner(System.in);
        String id = input.nextLine();
        return id;
    }

    public void unfollowReq() {
        System.out.println("Please write (your ID)_(Other acc's ID)");
        Scanner input = new Scanner(System.in);
        String str = input.nextLine();
        try {
            out.writeObject("Unfollow");
            out.flush();
            out.writeObject(str);
            out.flush();
            System.out.println(in.readObject());
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
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
                    resend = false;
                } else {
                    image.read(b, 0, b.length - 1);
                    b[b.length - 1] = (byte) sequence;
                    out.write(b, 0, b.length);
                    out.flush();
                }

                try {
                    // System.out.println("Waiting for ack....");
                    Thread.sleep(3);
                    ack = (String) in.readObject();
                } catch (Exception e) {
                    System.out.println("Exception in getting ack");
                }
                if (ack != null) {
                    sequence = (sequence == 0) ? 1 : 0;
                } else {
                    System.out.println("Time out resending data....\n\n");
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

    public void receiveFile(String name) {
        try {
            int sequence = 0;
            byte[] b = new byte[max_file_data_packet_size + 1];

            FileOutputStream fr = new FileOutputStream("Images\\" + name);
            while (true) {
                in.read(b, 0, b.length);
                if ((int) b[b.length - 1] == (sequence)) {

                    // System.out.println("The packet received properly");
                    fr.write(b, 0, b.length - 1);
                    out.writeObject(String.valueOf(sequence));
                    // System.out.println("Sending ACK :"+sequence);
                    out.flush();
                    sequence = (sequence == 0) ? 1 : 0;
                } else if (b[b.length - 1] == (byte) 2) {
                    break;
                } else {
                    System.out.println("Synchronization Failed");
                    System.out.println("Sequence Number Received :" + (int) b[b.length - 1]);
                    System.out.println("Waiting Sequence Number :" + sequence);
                    System.out.println("Server should send the packet again");
                    out.writeObject(null);
                    out.flush();
                }

            }
            System.out.println("File received");
            fr.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public void communication() {

        String str = "";
        int menuOption;
        Scanner input = new Scanner(System.in);
        ;
        try {

            connect();
            while (true) {
                System.out.println("Do you want to sign in or sign up?(Type signin/signup)");

                //Sign in or sign up.
                str = input.nextLine();
                out.writeObject(str);

                System.out.println((String) in.readObject());

                //Personal info.
                str = input.nextLine();
                out.writeObject(str);

                str = (String) in.readObject();

                if (str.substring(0, 7).compareToIgnoreCase("Welcome") == 0) {
                    System.out.println(str);
                    this.CLIENTID = (int) in.readObject();

                    File profile = new File("Profile\\Info" + this.CLIENTID);
                    if (!profile.isDirectory()) {
                        new File("Profile\\Info" + this.CLIENTID).mkdir();
                    }

                    break;
                } else {
                    System.out.println(str);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        while (!str.equals("11")) {
            getMenu();

            str = input.nextLine();

            menuOption = Integer.parseInt(str);
            try {
                switch (menuOption) {
                    case 1:
                        out.writeObject("Upload");
                        out.flush();
                        String photoName = upload();
                        writeProfile(photoName);
                        break;
                    case 2:
                        out.writeObject("Download");
                        Download();
                        System.out.println("Download Completed Successfully!");
                        break;
                    case 3:
                        out.writeObject("Access_Profile");
                        accessProfile();
                        break;
                    case 4:
                        out.writeObject("Search_Image");
                        searchImage();
                        break;
                    case 5:
                        followReq();
                        break;
                    case 6:
                        unfollowReq();
                        break;
                    case 7:
                        out.writeObject("View_Request");
                        viewRequests();
                        break;
                    case 8:
                        out.writeObject("Comment");
                        comment();
                        break;
                    case 9:
                        out.writeObject("View_Comment_Requests");
                        viewCommentRequests();
                        break;
                    case 10:
                        out.writeObject("Others_Profile");
                        othersProfile();
                        break;
                    case 11:
                        out.writeObject("viewPhoto");
                        viewPhoto();
                        break;
                    case 12:
                        out.writeObject("askPerm");
                        askPerm();
                        break;
                    case 13:
                        out.writeObject("viewPerm");
                        viewPerm();
                        break;
                    default:
                        out.writeObject("Disconnect");
                        break;
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        //input.close();
        disconnect();
    }

    public void connect() {
        try {
            socket = new Socket(serverAddress, serverPort);
            out = new ObjectOutputStream(socket.getOutputStream());
            in = new ObjectInputStream(socket.getInputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void disconnect() {
        try {
            socket.close();
            out.close();
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void getMenu() {
        System.out.println("1.Upload\n2.Download\n3.Access_Profile\n4.Search Image\n5.Follow User\n" +
                "6.Unfollow User\n7.View requests\n8.Comment\n9.View Comment Requests\n10.Others Profile\n11.View Photo\n12.Ask access permission\n13.View photo asks\n14.Exit");
    }

    public String upload() {
        String path, name;
        Scanner in = new Scanner(System.in);
        System.out.println("\nPlease give the path of the image you want to upload.");
        path = in.nextLine();
        System.out.println("Please give the name of the image");
        name = in.nextLine();
        try {
            Files.copy(Paths.get(path), Paths.get("Images\\" + name + ".jpg"));
            Thread.sleep(1000);
            System.out.println("Image stored locally.Image will be upload to the server.");

            out.writeObject(name); //Send the name of the image.
            out.flush();
            sendFile("Images\\" + name + ".jpg");


        } catch (FileAlreadyExistsException e) {
            System.out.println("File already exists");
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return name + ".jpg";
        //in.close(); Don't!

    }


    public void Download() {
        Scanner in = new Scanner(System.in);
        System.out.println("Please give your ID");
        String requester = in.nextLine();
        System.out.println("Please give the owner's ID");
        String owner = in.nextLine();
        System.out.println("Please give the name of the photo");
        String photoName = in.nextLine();
        try {
            out.writeObject(requester);
            out.flush();
            out.writeObject(owner);
            out.flush();
            out.writeObject(photoName);
            out.flush();
            receiveFile(photoName);

        } catch (IOException e) {
            e.printStackTrace();
        }
        //in.close(); Don't!
    }


    public void init() {
        File directory = new File("Images");
        if (!directory.isDirectory()) {
            new File("Images").mkdir();
        }

        File profile = new File("Profile");
        if (!profile.isDirectory()) {
            new File("Profile").mkdir();
        }


    }


    public void writeProfile(String photoName) {
        File file = new File("Profile\\Info" + this.CLIENTID + "\\profile_1050" + this.CLIENTID + ".txt");

        try {
            if (file.createNewFile()) {
                System.out.println("File has been created successfully");
            } else {
                System.out.println("File already present at the specified location");
            }
            FileWriter writer = new FileWriter("Profile\\Info" + this.CLIENTID + "\\profile_1050" + this.CLIENTID + ".txt", true);
            writer.write(this.CLIENTID + " posted " + photoName + "\n");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public void accessProfile() {
        while (true) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Please give the id of client you want to view the profile");
            String id = scanner.nextLine();

            boolean follows = false;
            try {
                out.writeObject(id);
                follows = (Boolean) in.readObject();

            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            if (follows) {
                try {
                    System.out.println("********Social profile of " + id + "**********");
                    try {
                        String input = (String) in.readObject();

                        while (input.equals("The file is locked\nPlease wait.")) {
                            input = (String) in.readObject();
                        }

                        while (!input.equals("End")) {
                            System.out.println(input);
                            input = (String) in.readObject();
                        }
                        System.out.println(in.readObject());
                    } catch (ClassNotFoundException e) {
                        e.printStackTrace();
                    }
                    System.out.println("******************************************");
                } catch (IOException e) {
                    e.printStackTrace();
                }
                break;
            } else {
                System.out.println("You typed a client ID you don't follow");
            }
        }

    }

    public void searchImage() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please give the name of the photo you want to search to your social graph(name.jpg).");
        String name = scanner.nextLine();
        try {
            out.writeObject(name);
            ArrayList<String> followerThatHashTheImage = (ArrayList<String>) in.readObject();
            System.out.println("Follows that has the image you want: ");
            for (int i = 0; i < followerThatHashTheImage.size(); i++) {
                System.out.println(followerThatHashTheImage.get(i));

            }
            System.out.println("**************************************\n");
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (NullPointerException e) {
            System.err.println("Noone of your follower has the name of the image you type ");
        }
    }

    public void viewRequests() {
        try {
            String request = (String) in.readObject();
            System.out.println("\n******************************Requests*************************************");
            while (request != null) {
                System.out.println(request);
                request = (String) in.readObject();
            }
            System.out.println("*****************************************************************************");
            System.out.println("Please give the number, type Y or N and clientID.(X  Y/N  ID)");
            Scanner input = new Scanner(System.in);

            out.writeObject((String) input.nextLine());
            out.flush();
            //input.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void comment() {
        Scanner input = new Scanner(System.in);

        System.out.println("Please give the ID of the client and the name of the photo(name.jpg)");
        String info = input.nextLine();
        System.out.println("Please give the comment you want to make.");
        String comment = input.nextLine();

        try {
            out.writeObject(info);
            out.writeObject(comment);

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void viewCommentRequests() {
        try {
            String request = (String) in.readObject();
            System.out.println("\n******************************Requests*************************************");
            while (request != null) {
                System.out.println(request);
                request = (String) in.readObject();
            }
            System.out.println("*****************************************************************************");
            System.out.println("Please give the number, type Y or N and clientID and image name (image.jpg).(X  Y/N  ID NAME)");
            Scanner input = new Scanner(System.in);

            out.writeObject((String) input.nextLine());
            out.flush();
            //input.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void othersProfile() {
        BufferedWriter writer = null;
        try {
            File file = new File("Profile\\Info" + this.CLIENTID + "\\Others_1050" + this.CLIENTID + ".txt");
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());

            } else {
                System.out.println("File already exists.");
            }
            writer = new BufferedWriter(new FileWriter(file));
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            String infoProfile = null;
            while ((infoProfile = (String) in.readObject()) != null) {
                System.out.println(infoProfile);
                writer.write(infoProfile);
                writer.newLine();

            }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

    }


    public void viewPhoto() throws IOException {
        Scanner input = new Scanner(System.in);
        System.out.println("Type your ID");
        String requester = input.nextLine();
        out.writeObject(requester);
        out.flush();
        System.out.println("Type owner's ID");
        String owner = input.nextLine();
        out.writeObject(owner);
        out.flush();
        System.out.println("Type the name of the photo you want to view");
        String photo = input.nextLine();
        out.writeObject(photo);
        out.flush();
    }

    public void askPerm() {
        Scanner in = new Scanner(System.in);
        System.out.println("Type your ID");
        String sender = in.nextLine();
        System.out.println("Type the ID of the client you want to access his/her photo");
        String receiver = in.nextLine();
        System.out.println("Give the name of the photo you want to access");
        String photo = in.nextLine();
        System.out.println("Do you want to view or download this photo?(Type V/D)");
        String answer = in.nextLine();
        try {
            out.writeObject(sender);
            out.flush();
            out.writeObject(receiver);
            out.flush();
            out.writeObject(photo);
            out.flush();
            out.writeObject(answer);
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void viewPerm() throws IOException {
        Scanner input = new Scanner(System.in);
        System.out.println("Type your ID");
        String id = input.nextLine();
        out.writeObject(id);
        out.flush();
        File file = new File("ClientsProfile\\PhotoAsks_1050_" + id + ".txt");
        if (file.createNewFile()) {
            System.out.println("File created: " + file.getName());
        }
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while((line = in.readLine()) != null)
        {
            System.out.println(line + "\n");
        }
        in.close();
        System.out.println("Type the the line number and the answer to the request(Y/N)");
        String answer = input.nextLine();
        out.writeObject(answer);
        out.flush();
    }



    public static void main(String args[]){
        KDClient client = new KDClient();
        client.init();
        client.communication();

    }
}