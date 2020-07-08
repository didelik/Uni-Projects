import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.*;

public class mainApp {

    public static void main(String[] args) {
        Item products[] = new Item[12];
        products[0] = new DVD(80, "In Time", " Action,Crime,Drama", "Andrew Niccol", "Andrew Niccol", " Justin Timberlake,Amanda Seyfried,Cillian Murphy ", "Regency Enterprises", "8 December 2011", "1h 49min", 25, 1.5, 1, true);
        products[1] = new DVD(81, "Transformers", "Action,Adventure,Sci-fi", "Michael Bay", "Roberto Orci,Alex Kurtzman", "Shia Lebouf,Megan Fox,Josh Duhamel", "DreamWorks,Hasbro,Paramount Pictures", "3 July 2007", "2h 24min", 22, 3.5, 1, false);
        products[2] = new BlueRay(82, "It", "Horror,Thriller", "Andy Muschietti", "Stephen King", "Bill SkarsgÃ¥rd, Jaeden Martell, Finn Wolfhard", "Vertigo Entertainment", "28 September 2017", "2h 15min", 13, 1.5, 2, false);
        products[3] = new BlueRay(83, "Avengers:Endgame", "Action,Adventure,Fantasy", "Anthony Russo,Joe Russo", "Robert Downey Jr. ,Chris Evans,Mark Ruffalo", "Marvel Studios", "Marvel Studios", "26 April 2019", "3h 1min", 10, 2, 2, false);
        products[4] = new Games(50, "Assasin's Creed Odyssey", "PC", "Action,Adventure", "Ubisoft", "5 October 2018", 35, 5, 1, false);
        products[5] = new Games(51, "The Witcher 3:Wild Hunt", "PC", "Action,Adventure,Fantasy", "CD Project", "19 May 2015", 8, 5, 1, false);
        products[6] = new Games(52, "Metal Gear Solid V: The Phantom Pain", "PlayStation", "Action,Adventure,Stealth", "Konami", "1 September 2015", 30, 5, 1, false);
        products[7] = new Games(53, "Uncharted 4 :A Thief's End", "PlayStation", "Action,Adventure", "Naughty Dog", "10 May 2016", 45, 5, 1, false);
        products[8] = new Games(54, "Halo 5", "Xbox", "Action,Sci-fi", "Microsoft Studios", "27 October 2015", 32, 5, 1, false);
        products[9] = new Games(55, "Destiny 2", "Xbox", "Action,Sci-fi,FPS", "Bungie", "6 September 2017", 11, 5, 1, false);
        products[10] = new Games(56, "Super Mario 64 DS", "Nintendo", "Action,Multiplayer", "Nintendo", "4 June 2005", 28, 5, 1, false);
        products[11] = new Games(57, "The Legend Of Zelda:Breath of The Wild", "Nintendo", "Action,Adventure", "Nintendo Entertainment Planning & Development", "3 March 2017", 15, 5, 1, false);


        Rentings storeRents = new Rentings();

        Scanner in = new Scanner(System.in);
        boolean done = false;
        int rentCode = 0, rentDays;
        String renterName, renterNumber, rentDate;
        while (!done) {
            System.out.println("Press 0 to view all movies");
            System.out.println("Press 1 to view all games");
            System.out.println("Press 2 to view all rents");
            System.out.println("Press 3 to exit");
            String answer = in.next();
            if (answer.equals("0")) {
                System.out.println("Select the type of the movie(type either DVD or BlueRay)");
                String type = in.next();
                if (type.equalsIgnoreCase("DVD")) {
                    int i = 0;
                    for (Item product : products) {
                        if (product instanceof DVD)
                            System.out.println(product.getItemCode() + " " + product.getTitle());
                    }
                    System.out.println("Type the code of the DVD you want");
                    int moviecode = in.nextInt();
                    for (Item product : products)
                        if (product.getItemCode() == moviecode) {
                            System.out.println(product.toString());
                            if (product.getNumOfCopies() > 0) {
                                System.out.println("Do you want to rent this DVD?(Y/N)");
                                String ans = in.next();
                                if (ans.equals("Y")) {
                                    System.out.println("Enter your name:");
                                    renterName = in.next();
                                    System.out.println("Enter your phone number");
                                    renterNumber = in.next();
                                    System.out.println("Enter the date you want to rent this DVD(dd/m/yyyy)");
                                    rentDate = in.next();
                                    if (product.getIsNewDVD()) {
                                        System.out.println("For how many days you want to rent this DVD?(Rent cost per week)" +
                                                "(Can't be rented for more than 30 days)(type an integer)");
                                        rentDays = in.nextInt();
                                    } else {
                                        System.out.println("For how many weeks you want to rent this DVD?(Rent cost per day)" +
                                                "(Can't be rented for more than 30 days)(type and integer)");
                                        rentDays = in.nextInt() * 7;
                                    }
                                    if (rentDays <= 30) {
                                        product.setNumOfCopies(product.getNumOfCopies() - 1);
                                        System.out.println("Copies left:" + product.getNumOfCopies());
                                        Rents customer = new Rents(rentCode, product.getTitle(), renterName, renterNumber, rentDate, rentDays, product.getCost(), product.getExtraDayCost());
                                        storeRents.addRent(customer);
                                        storeRents.printArrayList();
                                        System.out.println("\n\nRent complete");
                                    } else {
                                        System.out.println("Select a valid number of rent days or rent weeks");
                                    }
                                } else if (ans.equals("N"))
                                    System.out.println("Returning to main menu");
                                break;
                            } else {
                                System.out.println("There ane no more copies left");
                            }
                        } else {
                            i++;
                            if (i == 12)
                                System.out.println("No movie found");
                        }

                } else if (type.equalsIgnoreCase("BlueRay")) {
                    int i = 0;
                    for (Item product : products) {
                        if (product instanceof BlueRay)
                            System.out.println(product.getItemCode() + " " + product.getTitle());
                    }
                    System.out.println("Type the code of the BlueRay you want");
                    int moviecode = in.nextInt();
                    for (Item product : products)
                        if (product.getItemCode() == moviecode) {
                            System.out.println(product.toString());
                            if (product.getNumOfCopies() > 0) {
                                System.out.println("Do you want to rent this BlueRay?(Y/N)");
                                String ans = in.next();
                                if (ans.equals("Y"))
                                    System.out.println("Enter your name:");
                                renterName = in.next();
                                System.out.println("Enter your phone number");
                                renterNumber = in.next();
                                System.out.println("Enter the date you want to rent this DVD(dd/m/yyyy)");
                                rentDate = in.next();
                                System.out.println("For how many days you want to rent this BlueRay?(Rent cost per day)" +
                                        "(Can't be rented for more than 30 days)(type an integer)");
                                rentDays = in.nextInt();
                                if (rentDays <= 30) {
                                    product.setNumOfCopies(product.getNumOfCopies() - 1);
                                    System.out.println("Copies left:" + product.getNumOfCopies());
                                    Rents customer = new Rents(rentCode, product.getTitle(), renterName, renterNumber, rentDate, rentDays, product.getCost(), product.getExtraDayCost());
                                    storeRents.addRent(customer);
                                    storeRents.printArrayList();
                                    System.out.println("\n\nRent complete");

                                } else {
                                    System.out.println("Select a valid number of rent days or rent weeks");
                                }
                            } else {
                                System.out.println("There ane no more copies left");
                            }
                        } else {
                            i++;
                            if (i == 12)
                                System.out.println("No movie found");
                        }
                } else {
                    System.out.println("No such type found");
                }

            } else if (answer.equals("1")) {
                int i = 0;
                int y = 0;
                System.out.println("Select the console");
                for (Item product : products) {
                    i++;
                    if (product instanceof Games)
                        if (i % 2 == 0)
                            System.out.println(((Games) product).getConsole());
                }
                String gameConsole = in.next();
                for (Item product : products) {
                    if (product instanceof Games)
                        if (((Games) product).getConsole().equalsIgnoreCase(gameConsole))
                            System.out.println(product.getItemCode() + " " + product.getTitle());
                }
                System.out.println("Type the game's code");
                int gamecode = in.nextInt();
                for (Item product : products)
                    if (product.getItemCode() == gamecode) {
                        System.out.println(product.toString());
                        if (product.getNumOfCopies() > 0) {
                            System.out.println("Do you want to rent this game?(Y/N)");
                            String ans = in.next();
                            if (ans.equals("Y"))
                                System.out.println("Enter your name:");
                            renterName = in.next();
                            System.out.println("Enter your phone number");
                            renterNumber = in.next();
                            System.out.println("Enter the date you want to rent this DVD(dd/m/yyyy)");
                            rentDate = in.next();
                            System.out.println("For how many days you want to rent this game?(Rent cost per day)" +
                                    "(Can't be rented for more than 30 days)(type an integer)");
                            rentDays = in.nextInt();
                            if (rentDays <= 30) {
                                product.setNumOfCopies(product.getNumOfCopies() - 1);
                                System.out.println("Copies left:" + product.getNumOfCopies());
                                Rents customer = new Rents(rentCode, product.getTitle(), renterName, renterNumber, rentDate, rentDays, product.getCost(), product.getExtraDayCost());
                                storeRents.addRent(customer);
                                storeRents.printArrayList();
                                System.out.println("\n\nRent complete");
                            } else
                                System.out.println("Select a valid number of rent Days");
                        } else
                            System.out.println("No more copies of this game are left");

                    } else
                        y++;
                if (y == 12)
                    System.out.println("No game found");

            } else if (answer.equals("2")) {
                int y = 0;
                System.out.println("Type your rent code");
                int typed_code = in.nextInt();
                System.out.println("Type the code of your product");
                int typed_prod_code = in.nextInt();
                storeRents.printArrayList();
                System.out.println("Do you want to return the item?(Y/N)");
                String reply = in.next();
                if (reply.equals("Y")) {
                    System.out.println("Type the date you returned the product: (dd/m/yy)");
                    String returned_date = in.next();
                    for (Item product : products) {
                        if (product.getItemCode() == typed_prod_code)
                            storeRents.Find_Cost(typed_code, returned_date, product.getCost(), product.getExtraDayCost());
                        product.setNumOfCopies(product.getNumOfCopies() + 1);
                    }

                } else {
                    y++;
                    if (y == storeRents.ArraySize())
                        System.out.println("Returning to main menu");
                }

            } else if (answer.equals("3"))
                done = true;


        }



    }
}



