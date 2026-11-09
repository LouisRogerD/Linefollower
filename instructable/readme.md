Een instructable is een stappenplan - zonder verdere uitleg - hoe je vertrekkend van de bill of materials en gebruik makend van de technische tekeningen de robot kan nabouwen. Ook de nodige stappen om de microcontroller te compileren en te uploaden staan beschreven.

**stap 1**
Bestel alle componenten uit de bill of materials

**stap 2**
Test alle componenten aan de hand van de proof of concepts.

**stap 3**
Verbind de arduino met de PC. Selecteer de juiste com poort en het juiste bord. Druk op uploaden. Zorg dat de seriele monitor in arduino IDE op de juiste baudrate staat (115200).
En dat de seriele monitor op Both NL & CR staat.

**stap 4**
Soldeer alle componenten op de printplaat zoals op de elektrische schema's
Voorzie 10 male headers op de pcb voor het connectoren met de sensor via dupont draadjes. Voorzie ook de nodige female headers voor de arduino, motor driver, bluetooth module zodat je eenvoudig kan verwisselen indien kapot.

**stap 5**
Test ofdat alles werkt na het solderen, de commands, het eeprom geheugen, de knop.
Controleer ofdat de motoren in de juiste richting draait, maak gebruik van het test blad

**stap 6**
Calibreer de sensor door linefollower op zwarte lijn te plaatsen en via Seriele Bluetooth terminal calibrate black te sturen.
Plaats hem nu op de witte achtergrond en gebruik calibrate white.

**stap 7**
Verbind via arduino IDE en geef het command debug in. Zet nu de cycle time iets groter dan de calc tijd.

**stap 8**
Gebruik nu de commands voor kp = 1 , diff = 0,1 , ki en kd = 0, power = 100.
Controleer met debug of er nergen Nan staat.

**stap 9**
Test nu ofdat de motoren in de juiste richting draait door middel van het test blad. In het midden => beiden draaien vooruit
Links => Linkerwiel sneller dan rechter of rechter draait trager/achteruit.
Rechts => Rechterwiel sneller dan linker of linker draait trager/achteruit. Afhankerlijk van je diff zal hij trager of achteruit gaan.

**stap 10**
Begin nu met instellen van PID regelaar.
Speel met Kp, diff en power hiermee zou hij al 3 toeren moeten kunnen rijden.

**stap 11**
Introduceer nu de Kd en/of ki zodat hij soepeler rijd.
Ki heb ik niet gebruikt. Nu je power omhoog en blijven tunen todat hij stabiel rijdt.
