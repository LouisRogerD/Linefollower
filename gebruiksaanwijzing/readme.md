# Gebruiksaanwijzing

### opladen / vervangen batterijen
Wanneer de batterijen leeg zijn moeten ze vervangen worden. De batterijhouder dient voor Lipo-batterijen, deze kunnen worden opgeladen met een externe batterij-lader.

### draadloze communicatie
#### verbinding maken
De app waarmee we verbinden met de Linefollower is de "Serial Bluetooth Terminal". De Bluetooth module waarmee geconnecteerd moet worden is de "HC-05" met als code "1234". Om verbinding te maken met de module drukt u op het stekker-icoon rechtsboven in de app, tik daarna op de "HC-05" en geef de code in.

#### commando's
debug [on/off] : Toon eenmaalig de debug waardes
start : Start de linefollower 
stop : Stopt de linefollower
set cycle [µs] : Stelt de cyclus tijd in 
set power [0..255] : Stelt de power in (255 => 8.4V) 
set diff [0..1] : Stelt de diff in
set kp [0..] : Stelt de kp in
set ki [0..] : Stelt de ki in
set kd [0..] : Stelt de kd in
calibrate black : Calibreer de zwarte waardes
calibrate white : Calibreer de witte waardes

### kalibratie
Er zijn 2 commando's voor de kalibratie waaronder één voor wit te kalibreren van de Linefollower en één voor zwart te kalibreren. Zet de robot op een schoon wit vlak en geef in de Serial Bluetooth Terminal het commando "calibrate white", om de kalibratie voor wit uit te voeren. Idem voor zwart maar op een zwart vlak en met het commando "calibrate black".

### settings
De robot rijdt stabiel met volgende parameters: **Cycle time: 2500, Power: 200, diff: 0.48, kp: 14, ki: 0.03, kd: 0.25, dAlpha: 0.7**

### start/stop button
Er is geen fysieke knop met een start/stop functie, dit wordt gedaan via de draadloze communicatie en een run on en run off commando. Ook zal de Linefollower stoppen als er geen duidelijke zwarte lijn aanwezig is
