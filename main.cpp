/*
- servo ultrasonik (jarak tertentu, servo gerak)
- led ultrasonik (delay)
- lcd  + led (delay + tampilkan warna)
- servo + lcd (servo gerak, lcd menampilkan terbuka/tertutup)
*/

/* Include Library
Digunakan untuk menambahkan library-library yang diperlukan ke projek
- Arduino.h berisi kode-kode bawaan Arduino, seperti method void loop() dan void setup(), serta konstanta pin seperti D0 D1 dst
- Servo.h merupakan library yang memudahkan kontrol servo
*/
#include <Arduino.h>
#include <Servo.h>

/* Deklarasi Pin
- servoPin digunakan untuk mengontrol servo
- trigPin dan echoPin digunakan untuk sensor ultrasonik
*/
int servoPin = D5, trigPin = D1, echoPin = D2;

/* Method untuk menghitung jarak berdasarkan hasil bacaan sensor ultrasonik
1. Pertama-tama, trigPin diset ke LOW untuk memastikan bahwa sensor ultrasonik belum memancarkan gelombang
2. Kemudian, trigPin diset ke HIGH untuk memancarkan gelombang ultrasonik, kemudian diset ke LOW untuk menghentikan pancaran gelombang
3. pulseIn(echoPin, HIGH) digunakan untuk menghitung seberapa lama gelombang ultrasonik terpantul dan kembali tertangkap sensor
4. Kemudian, menggunakan rumus S = V * T, dihitunglah jarak objeknya. 0.034 merupakan kecepatan gelombang ultrasonik, durasi dibagi dua karena kita hanya menghitung jarak satu arah
5. Hasil perhitungan berupa jarak objek direturn.
*/
int distance;
int hitungJarak() {
  int _distance;
  long _duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  _duration = pulseIn(echoPin, HIGH);
  _distance = 0.034 * _duration / 2;

  return _distance;
}

/* Deklarasi objek dengan kelas Servo
Digunakan untuk mengontrol servo nantinya.
*/
Servo servo;

/* Method void setup() dijalankan ketika mikrokontroller pertama menyala */
void setup() {
  /* Pengaturan PinMode untuk mengatur pin digital yang digunakan sebagai OUTPUT atau INPUT
  trigPin diatur sebagai OUTPUT karena digunakan untuk mengirim sinyal ke sensor ultrasonik untuk memancarkan gelombang ultrasonik
  echoPin diatur sebagai INPUT untuk menerima bacaan dari sensor ultrasonik
  */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  /* Konfigurasi servo
  Library Servo.h sudah menyiapkan method attach yang dapat digunakan untuk mengatur pin mana yang tersambung dengan servo
  */
  servo.attach(servoPin);
}

/* Method void loop() akan terus dijalankan selama mikrokontroller menyala */
void loop() {
  /* Memanggil method hitung jarak yang sebelumnya telah didefinisikan
  hasil hitung jarak disimpan dalam sebuah variabel distance
  */
  distance = hitungJarak();

  /* Logika Servo
  Apabila jarak objek kurang dari 10cm, maka servo digerakkan ke posisi 90 derajat.
  Selain itu, servo digerakkan ke posisi 0 derajat.
  */
  if (distance <= 10) {
    servo.write(90);
  } else {
    servo.write(0);
  }

  /* Delay 100ms supaya program tidak berjalan terlalu cepat demi keawetan alat dan komponen */
  delay(100);
}