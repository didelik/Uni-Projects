public class Rents  {
    private String title;
    private static int nextRentCode = 0;
    private int rentCode = 0;
    private String renterName;
    private String renterNumber;
    private String rentDate;
    private int rentDays;
    private double rentCost ;
    private double extraDayCost;

    public Rents(int rentCode,String title,String renterName,String renterNumber,String rentDate,int rentDays,double rentCost,double extraDayCost) {

        rentCode = nextRentCode;
        nextRentCode++;
        this.title = title;
        this.rentCode = rentCode;
        this.renterName = renterName;
        this.renterNumber = renterNumber;
        this.rentDate = rentDate;
        this.rentDays = rentDays;
        this.rentCost = rentCost;
        this.extraDayCost = extraDayCost;
        this.rentCode = rentCode++;

    }

    public int getRentCode(){
        return rentCode;
    }

    public String getRentDate() {
        return rentDate;
    }

    public int getRentDays() {
        return rentDays;
    }


    public String toString(){
        return 	"\nRentCode: "+ rentCode + "\nRenterName: " + renterName + "\nRenterNumber: " + renterNumber + "\nRentDate: " +

                rentDate +"\nRentDays:"+ rentDays + "\nRentCost:"+ rentCost + "\nExtraDayCost:"+ extraDayCost ;
    }
}
