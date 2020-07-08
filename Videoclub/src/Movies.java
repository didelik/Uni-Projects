public class Movies extends Item {
    private String director;
    private String writer;
    private String actors;
    private String playingTime;

    public Movies(int itemCode,String title,String category,String director,String writer,String actors,String company,String prodDate,String playingTime,int numOfcopies,double cost,
                  double extraDayCost,boolean isNewDVD){
        super(itemCode,title,category,company,prodDate,numOfcopies,cost,extraDayCost,isNewDVD);
        this.director= director;
        this.writer=writer;
        this.actors=actors;
        this.playingTime=playingTime;
    }

    public String toString(){
        return "\nMOVIE DETAILS" + super.toString() + "\nDirector: " + director + "\nWriter:"+ writer +"\nActors:"+ actors +"\nPlaying time:"+ playingTime;

    }
}
