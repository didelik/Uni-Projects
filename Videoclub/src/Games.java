public class Games extends Item{
    private String console;

    public Games(int itemCode,String title,String console,String category,String company,String prodDate, int numOfcopies,double cost,double extraDayCost,boolean isNewDVD){
        super(itemCode,title,category,company,prodDate,numOfcopies,cost,extraDayCost,isNewDVD);
        this.console = console;
    }


    public String getConsole(){
        return console;
    }
    public String toString(){
        return "\nGAME DETAILS" +"\nConsole:" + console + super.toString();
    }
}
