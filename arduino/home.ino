#include <ESP8266WiFi.h>

// Nom et mot de passe du réseau WIFI
const char* ssid = "ESTIAM Wifi";
const char* password = "r8d8c3p0r2d2";

// Creation d un serveur qui ecoute sur le port 80
WiFiServer server(80);

const byte ledHall = D0;
const byte ledDouche = D1;
const byte ledCuisine = D2;
const byte ledChambre = D3;
const byte fenetre = D4;
int etat [5] = {0};
const int sensorValue = A0; 


const int TRIGGER_PIN = D5; // Broche TRIGGER
const int ECHO_PIN = D6;    // Broche ECHO
int vSon=59; //valeur de temps en µs d'un aller retour du son sur 1cm

/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);

  // Declaration port  en sortie
  pinMode(ledHall,OUTPUT);
  pinMode(ledDouche,OUTPUT);
  pinMode(ledCuisine,OUTPUT);
  pinMode(ledChambre,OUTPUT);
  pinMode(fenetre,OUTPUT);
  pinMode(sensorValue,INPUT);


 /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


   // Connection au réseau WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connection a ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi OK");
  
  // demarrage du serveur
  server.begin();
  Serial.println("Server OK");

  // Adresse IP locale attribuee
  Serial.println(WiFi.localIP());

}


void loop() {
  // put your main code here, to run repeatedly:

  int distance=mesureDistance(); //on

 Serial.print(F("Distance: "));
  Serial.println(distance);


    // Un client est-il connecte ?
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Attente donnees envoyees par un client
  Serial.println("Nouveau client");
  while(!client.available()){
    delay(1);
  }
  
  // Lecture premiere ligne de la requete
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Decodage de la requete recue
  int etatHall,etatChambre,etatCuisine,etatDouche,etatFenetre;


  //controle lampe du hall
  if (req.indexOf("/gpio/h0") != -1 || req.indexOf("/gpio/?=h0") != -1){
     digitalWrite(D0, 0);
     etat[0] = 0;
    Serial.println("Demande extinction LED hall");}
 else if (req.indexOf("/gpio/h1") != -1 || req.indexOf("/gpio/?=h1") != -1){
     digitalWrite(D0, 1);
      etat[0] = 1;
    Serial.println("Demande allumage LED hall");}
    
//controle lampe douche
 else if (req.indexOf("/gpio/d0") != -1 || req.indexOf("/gpio/?=d0") != -1){
     digitalWrite(D1, 0);
      etat[1] = 0;
    Serial.println("Demande extinction LED douche");}
 else if (req.indexOf("/gpio/d1") != -1 || req.indexOf("/gpio/?=d1") != -1){
     digitalWrite(D1, 1);
      etat[1] = 1;
    Serial.println("Demande allumage LED douche");}


//controle lampe cuisine
     else if (req.indexOf("/gpio/c0") != -1 || req.indexOf("/gpio/?=c0") != -1){
     digitalWrite(D2, 0);
      etat[2] = 0;
    Serial.println("Demande extinction LED cuisine");}
  else if (req.indexOf("/gpio/c1") != -1 || req.indexOf("/gpio/?=c1") != -1){
     digitalWrite(D2, 1);
      etat[2] = 1;
    Serial.println("Demande allumage LED cuisine");}

//controle lampe chambre
 else if (req.indexOf("/gpio/C0") != -1 || req.indexOf("/gpio/?=C0") != -1){
     digitalWrite(D3, 0);
      etat[3] = 0;
    Serial.println("Demande extinction LED chambre");}
 else if (req.indexOf("/gpio/C1") != -1 || req.indexOf("/gpio/?=C1") != -1){
     digitalWrite(D3, 1);
      etat[3] = 1;
    Serial.println("Demande allumage LED chambre");}



//controle fenetre
 else if (req.indexOf("/gpio/f0") != -1 || req.indexOf("/gpio/?=f0") != -1){
     digitalWrite(D4, 0);
      etat[4] = 0;
    Serial.println("Demande ouverture fenetre");}
 else if (req.indexOf("/gpio/f1") != -1 || req.indexOf("/gpio/?=f1") != -1){
     digitalWrite(D4, 1);
      etat[4] = 1;
    Serial.println("Demande fermeture fenetre");}

    
    
  else {
    Serial.println("Requete invalide");
    client.stop();
    return;
  }

  
  client.flush();

  // Prepararation de la reponse au client WEB Refresh: 0.005\r\n
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<meta charset='UTF-8'>\r\n<html>\r\n";
 /* s += (val)?"allumee":"eteinte";*/

 s+="<br />";//retour à la ligne
 s+="<center><table>";//border=3 border cellpading=5>"); //Ajout d'un tableau
 s+="<table border width=800 height=400> ";
 s+="<tr><th>Action</th><th>Équipement</th><th>Etat</th></tr>";

 for(int i = 0;i < 5; i++ ){
  s+="<tr>";

  switch (i) {
  case 0:
      s += (etat[i])?"<td><a href='http://172.16.198.146/gpio/h0'>Eteindre</a></td>":"<td><a href='http://172.16.198.146/gpio/h1'>Allumer</a></td>"; 
      s+="<td>Hall</td> ";
    break;
  case 1:
      s += (etat[i])?"<td><a href='http://172.16.198.146/gpio/d0'>Eteindre</a></td>":"<td><a href='http://172.16.198.146/gpio/d1'>Allumer</a></td>"; 
      s+="<td>Douche</td>";
    break;
  case 2:
      s += (etat[i])?"<td><a href='http://172.16.198.146/gpio/c0'>Eteindre</a></td>":"<td><a href='http://172.16.198.146/gpio/c1'>Allumer</a></td>"; 
      s+="<td>Cuisine</td>";
    break;
  case 3:
      s += (etat[i])?"<td><a href='http://172.16.198.146/gpio/C0'>Eteindre</a></td>":"<td><a href='http://172.16.198.146/gpio/C1'>Allumer</a></td>"; 
      s+="<td>Chambre</td>";
    break;
 default:
      s += (etat[i])?"<td><a href='http://172.16.198.146/gpio/f0'>Fermer</a></td>":"<td><a href='http://172.16.198.146/gpio/f1'>Ouvrir</a></td>"; 
      s+="<td>fenêtre</td>";

}

  if(i==4)
  {
    s += (etat[i])?"<td><font color='blue'>ouverte</td>":"<td><font color='black'>fermée</td>";
  }
  else
  {
    s += (etat[i])?"<td><font color='green'>allumee</td>":"<td><font color='red'>eteinte</td>";    
  }

  s+="</tr>";
  
   
 }



          
s+="</table></center><br />";
s+="La porte est : ";
s += distance < 0.20 ?"ouverte":"fermée";

s+="<br/>Intensité : ";

int sensorValue = analogRead(A0);
  s+= String(sensorValue);

   s += sensorValue ?"<br/><font color='green'>allumee":"<font color='red'>eteinte"; 
  
 s += "</html>\n";
  // Envoi de la reponse au client
  client.print(s);
  delay(1);
  Serial.println("Client deconnecte");


}




//fonction de mesure de distance avec SRF05

long mesureDistance() {

  unsigned long mesure = 0; // variable de mesure

 
 digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2); //on attend que le signal soit clair

  digitalWrite(TRIGGER_PIN, HIGH);

    delayMicroseconds(10); //pendant 10 µs

  digitalWrite(TRIGGER_PIN, LOW);



    mesure = pulseIn(ECHO_PIN, HIGH); // fonction pulseIn qui attend un état haut et renvoie le temps d'attente

     long Distance_mm = Distance(mesure); 


}


long Distance(long time)
{
    // Calculates the Distance in mm
    // ((time)*(Speed of sound))/ toward and backward of object) * 10
   
    long DistanceCalc;                      // Calculation variable
    DistanceCalc = ((time /2.9) / 2);     // Actual calculation in mm
    //DistanceCalc = time / 74 / 2;         // Actual calculation in inches
    return DistanceCalc;                    // return calculated value
}


