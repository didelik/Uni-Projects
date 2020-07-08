import java.util.*;

public class Rentings {

    private ArrayList<Rents> RentingList = new ArrayList<Rents>();

    public void addRent(Rents r) {
        RentingList.add(r);
    }

    public void printArrayList() {
        for (Rents storedRents : RentingList) {
            System.out.println(storedRents.toString());
        }
    }

    public void Find_Cost(int rentCode,String return_date,double cost,double extra_cost) {
        for (Rents storedRents : RentingList) {

            if(storedRents.getRentCode() == rentCode) {
                int rentDays = storedRents.getRentDays();
                System.out.println(storedRents.toString());

                int rented_days = Integer.parseInt(storedRents.getRentDate().substring(0, 1));
                int rented_month = Integer.parseInt(storedRents.getRentDate().substring(3, 4));
                int rented_year = Integer.parseInt(storedRents.getRentDate().substring(6, 7));

                int returned_days = Integer.parseInt(return_date.substring(0, 1));
                int returned_month = Integer.parseInt(return_date.substring(3, 4));
                int returned_year = Integer.parseInt(return_date.substring(6, 7));
                int extra_days = 0;

                if (rented_year == returned_year) {
                    if (rented_month == returned_month) {
                        extra_days = returned_days - (rented_days + rentDays);
                    } else if (rented_month != returned_month && rented_month == 1 || rented_month == 3 || rented_month == 5
                            || rented_month == 7 || rented_month == 8 || rented_month == 10 || rented_month == 12) {
                        if (rented_days + rentDays <= 31) {
                            extra_days = returned_days + (31 - rented_days + rentDays);
                        } else {
                            extra_days = returned_days - (rentDays - 31 - rented_days);
                        }
                    } else if (rented_month != returned_month && rented_month == 4 || rented_month == 6 || rented_month == 9
                            || rented_month == 11) {
                        if (rented_days + rentDays <= 30) {
                            extra_days = returned_days + (30 - rented_days + rentDays);
                        } else {
                            extra_days = returned_days - (rentDays - 31 - rented_days);
                        }
                    } else if (rented_month != returned_month && rented_month == 2) {
                        if (rented_days + rentDays <= 29) {
                            extra_days = returned_days + (29 - rented_days + rentDays);
                        } else {
                            extra_days = returned_days - (rentDays - 29 - rented_days);
                        }

                    }
                }

                double item_cost = cost * rentDays;
                double extra_item_cost = extra_cost * extra_days;
                double total_cost = 0;
                if (extra_item_cost >= 0){
                    total_cost = item_cost + extra_item_cost;
                    System.out.println("Item cost is :" + item_cost + "\nExtra item cost is " + extra_item_cost + "\nTotal item cost is :" + total_cost);
                }else
                    total_cost = item_cost;
                System.out.println("Item cost is :" + item_cost + "\nExtra item cost is: 0" + "\nTotal item cost is :" + total_cost);





            }
        }


    }

    public int ArraySize(){
        return RentingList.size();

    }
}
