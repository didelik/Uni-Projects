public class Item {
    private int itemCode;
    private String title;
    private String category;
    private String company;
    private String prodDate;
    private int numOfcopies;
    private double cost;
    private double extraDayCost;
    private boolean isNewDVD;

    public Item(int itemCode,String title,String category,String company,String prodDate,int numOfcopies,double cost,double extraDayCost,boolean isNewDVD){
        this.itemCode = itemCode;
        this.title = title;
        this.category = category;
        this.company = company;
        this.prodDate = prodDate;
        this.numOfcopies = numOfcopies;
        this.cost = cost;
        this.extraDayCost = extraDayCost;
        this.isNewDVD = this.isNewDVD;
    }
    public int getItemCode(){
        return itemCode;
    }


    public String getTitle(){
        return title;
    }


    public void setNumOfCopies(int newNum){
        numOfcopies = newNum;
    }

    public int getNumOfCopies(){
        return numOfcopies;
    }

    public double getCost(){
        return cost;
    }

    public double getExtraDayCost(){
        return extraDayCost;
    }

    public boolean getIsNewDVD(){
        return isNewDVD;
    }

    public String toString(){
        return 	"\nMovie code:" + itemCode + " Title:" + title + "\nCategory: " + category + "\nCompany: " + company + "\nprodDate: " + prodDate + "\nNumber of copies:" + numOfcopies
                +"\nCost :" + cost + "\nExtra day cost:" + extraDayCost;
    }
}
