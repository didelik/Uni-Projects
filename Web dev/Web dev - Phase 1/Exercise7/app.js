const container = document.querySelector(".light-container")
const nightButton = document.querySelector(".night-button")


nightButton.addEventListener('click', function() {
  container.classList.toggle("night-view");
})




const infoContainer = document.querySelector(".info")
const nextButton = document.querySelector(".nextButton")

var myFact = document.getElementById("fact")


var answers = [
     {
       text: "As a sign of respect for Bitcoin’s creator, the smallest unit of a bitcoin is known as a satoshi. One satoshi is valued at around 0.00005 U.S. dollars (as on 11th April 2019), which is a very, very low value. To make one bitcoin, you need approximately one hundred million satoshis. According to current bitcoin values, which fluctuate a lot, to make a dollar you need close to 15,800 satoshis."
     },
     {
       text: "Losing your Bitcoin address, which is also known as your private key, not only means losing your unique identification; it also means losing all the bitcoins in your wallet. Research shows that at least 60 percent of all Bitcoin addresses are ghosts, which means a huge chunk of the people using Bitcoins have lost their addresses and have no way to access their wallets."
     },
     {
       text: "Ireland consumes approximately 5,000 kilowatt-hours of electricity each year. All the bitcoin mining farms together consume about 60 terawatt-hours of electricity, which is approximately 6 x 1010 kilowatt-hours—a large amount of power. The entire country of Ireland, which is the second-most-populated city in Europe and has 84,421 square kilometers of area, consumes less electricity than all these farms combined."
     },

     {
       text: "There’s a limit to how many bitcoins can exist in the market: 21 million. As of this moment, 17 million bitcoins are already in circulation; that means almost 80 percent of the 21 million have already been mined. But don’t worry; until 2140, we will still have bitcoins to mine. This is because of how miners are rewarded. Miners are rewarded with 12.5 bitcoins for each block added to the blockchain, and every four years the reward is reduced by half. The next halving is supposed to occur in 2020 when the reward will be reduced to 6.25 bitcoins."
     },

     {
       text: "The world’s fastest supercomputer, the Summit, works at 122.3 petaflops, which is a quadrillion floating-point operations per second. If you look at the entire Bitcoin network, the processing power is about 80,704,290 petaflops. But a supercomputer can do several different things, while the only thing the Bitcoin network does is add blocks to the blockchain."
     }
    ];



nextButton.addEventListener('click', function() {

  var randnum = Math.floor((Math.random() * answers.length));
  document.getElementById("fact").textContent = answers[randnum].text;

})




var d = new Date();

var weekday = new Array(7);

weekday[0] = "Sunday";
weekday[1] = "Monday";
weekday[2] = "Tuesday";
weekday[3] = "Wednesday";
weekday[4] = "Thursday";
weekday[5] = "Friday";
weekday[6] = "Saturday";


var n = weekday[d.getDay()];



if(n == "Sunday"){
  document.getElementById("day-title").textContent = "Start-off Sunday";
  document.getElementById("day-descr").textContent = "Σύμφωνα με στατιστικά δεδομένα οι περισσότεροι χρήστες online brokers ξεκίνησαν τις πρώτες τους επενδύσεις στα cryptos αυτή την ημέρα.Εσύ τι περιμένεις;";

}else if(n == "Monday"){

  document.getElementById("day-title").textContent = "Bad-Luck Monday";
  document.getElementById("day-descr").textContent = "Αν ισχυριστούμε πως η καλή εβδομάδα απ΄την Δευτέρα φαίνεται,τότε αυτά σίγουρα δεν ειναι καλά νέα για τους crypto traders.Κατά μέσο όρο τη ημέρα αυτή παρατηρείται μια πτώση της αξίας των περισσότερων cryptos.Αλλά αν είσαι long-term trader τότε αυτό είναι η άχρηστη πληροφορία της μέρας για εσένα.";

}else if(n == "Tuesday"){

  document.getElementById("day-title").textContent = "Mentor Tuesday";
  document.getElementById("day-descr").textContent ="Κάθε Τρίτη είναι ένα μάθημα για τους traders.Κυρολεκτικά!Τις Τρίτες έχουν καταγραφεί οι περισσότερες πρώτες σωστές επενδύσεις που απέφεραν μελλοντικό κέρδος σε begginner traders!"

}else if(n == "Wednesday"){

    document.getElementById("day-title").textContent = "Sellout Wednesday";
    document.getElementById("day-descr").textContent ="Mε τις περισσότερες καταγεγραμένες πωλήσεις cryptos από τους traders τις Τετάρτες,δικαιολογείται και ο τίτλος 'Sell-out'."

}else if(n == "Thursday"){

  document.getElementById("day-title").textContent = "Ghost Thursday";
  document.getElementById("day-descr").textContent ="Μην σας τρομάζει ο τίτλος.Απλώς τις Πέμπτες πολλοί είναι εκείνοι οι οποίοι αποφασίζουν να έχουν ελάχιστη ή και μηδενική trading δραστηριότητα.Κανείς δεν γνωρίζει ακριβώς τον λόγο,όμως αν έισαι short-term trader αυτό πρέπει να είναι κάτι που να έχεις κατά νου."

}else if(n == "Friday"){

  document.getElementById("day-title").textContent = "Weird Friday";
  document.getElementById("day-descr").textContent ="Σήμερα είναι η μέρα με τις πιο πολλές καταγεγραμένες αλλόκοτες καθημερινές ιστορίες από τον κόσμο του trading.Περίεργα transaction, broker failures , ανεξήγητα σκαμπανεβάσματα τιμών στα cryptos και πολλά άλλα.Tυχαίο; Μπορεί και ναι μπορεί και όχι...προχωράμε."


}else{
  document.getElementById("day-title").textContent = "Gold Saturday";
  document.getElementById("day-descr").textContent ="O παράδεισος των short-term traders,αλλά και πολλών long-term που επέλεξαν να κάνουν sell την ημέρα αυτή.Τα Σάββατα καταγράφουν τη μεγαλύτερη αύξηση κεφαλαίων που επενδύθηκαν στα cryptos.Σίγουρα έχε το υπόψιν σου αν είσαι short-term investor."

}
