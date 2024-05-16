#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266TrueRandom.h>
#include <Wire.h>  // This library is already built in to the Arduino IDE
#include <ArduinoJson.h>

const uint8_t PROGMEM _5bite_rus[] = {
  'F', 1, 0, 255, 8,
  0,                           // 0 - Empty Cell
  5, 62, 91, 79, 91, 62,       // 1 - Sad Smiley
  5, 62, 107, 79, 107, 62,     // 2 - Happy Smiley
  5, 28, 62, 124, 62, 28,      // 3 - Heart
  5, 24, 60, 126, 60, 24,      // 4 - Diamond
  5, 28, 87, 125, 87, 28,      // 5 - Clubs
  5, 28, 94, 127, 94, 28,      // 6 - Spades
  3, 24, 60, 24,               // 7 - Bullet Point
  5, 255, 231, 195, 231, 255,  // 8 - Rev Bullet Point
  3, 24, 36, 24,               // 9 - Hollow Bullet Point
  5, 255, 231, 219, 231, 255,  // 10 - Rev Hollow BP
  5, 48, 72, 58, 6, 14,        // 11 - Male
  5, 38, 41, 121, 41, 38,      // 12 - Female
  5, 64, 127, 5, 5, 7,         // 13 - Music Note 1
  5, 64, 127, 5, 37, 63,       // 14 - Music Note 2
  5, 90, 60, 231, 60, 90,      // 15 - Snowflake
  5, 127, 62, 28, 28, 8,       // 16 - Right Pointer
  5, 8, 28, 28, 62, 127,       // 17 - Left Pointer
  5, 20, 34, 127, 34, 20,      // 18 - UpDown Arrows
  5, 95, 95, 0, 95, 95,        // 19 - Double Exclamation
  5, 6, 9, 127, 1, 127,        // 20 - Paragraph Mark
  4, 102, 137, 149, 106,       // 21 - Section Mark
  5, 96, 96, 96, 96, 96,       // 22 - Double Underline
  5, 148, 162, 255, 162, 148,  // 23 - UpDown Underlined
  5, 8, 4, 126, 4, 8,          // 24 - Up Arrow
  5, 16, 32, 126, 32, 16,      // 25 - Down Arrow
  5, 8, 8, 42, 28, 8,          // 26 - Right Arrow
  5, 8, 28, 42, 8, 8,          // 27 - Left Arrow
  5, 30, 16, 16, 16, 16,       // 28 - Angled
  5, 12, 30, 12, 30, 12,       // 29 - Squashed #
  5, 48, 56, 62, 56, 48,       // 30 - Up Pointer
  5, 6, 14, 62, 14, 6,         // 31 - Down Pointer
  2, 0, 0,                     // 32 - Space
  1, 95,                       // 33 - !
  3, 3, 0, 3,                  // 34 - "
  5, 20, 62, 20, 62, 20,       // 35 - #
  4, 36, 106, 43, 18,          // 36 - $
  5, 99, 19, 8, 100, 99,       // 37 - %
  5, 54, 73, 86, 32, 80,       // 38 - &
  1, 3,                        // 39 - '
  3, 28, 34, 65,               // 40 - (
  3, 65, 34, 28,               // 41 - )
  5, 40, 24, 14, 24, 40,       // 42 - *
  5, 8, 8, 62, 8, 8,           // 43 - +
  2, 176, 112,                 // 44 - ,
  4, 8, 8, 8, 8,               // 45 - -
  2, 96, 96,                   // 46 - .
  4, 96, 24, 6, 1,             // 47 - /
  4, 62, 65, 65, 62,           // 48 - 0
  3, 66, 127, 64,              // 49 - 1
  4, 98, 81, 73, 70,           // 50 - 2
  4, 34, 65, 73, 54,           // 51 - 3
  4, 24, 20, 18, 127,          // 52 - 4
  4, 39, 69, 69, 57,           // 53 - 5
  4, 62, 73, 73, 48,           // 54 - 6
  4, 97, 17, 9, 7,             // 55 - 7
  4, 54, 73, 73, 54,           // 56 - 8
  4, 6, 73, 73, 62,            // 57 - 9
  1, 80,                       // 58 - :
  2, 128, 80,                  // 59 - ;
  3, 16, 40, 68,               // 60 - <
  3, 20, 20, 20,               // 61 - =
  3, 68, 40, 16,               // 62 - >
  4, 2, 89, 9, 6,              // 63 - ?
  5, 62, 73, 85, 93, 14,       // 64 - @
  4, 126, 17, 17, 126,         // 65 - A
  4, 127, 73, 73, 54,          // 66 - B
  4, 62, 65, 65, 34,           // 67 - C
  4, 127, 65, 65, 62,          // 68 - D
  4, 127, 73, 73, 65,          // 69 - E
  4, 127, 9, 9, 1,             // 70 - F
  4, 62, 65, 73, 122,          // 71 - G
  4, 127, 8, 8, 127,           // 72 - H
  3, 65, 127, 65,              // 73 - I
  4, 48, 64, 65, 63,           // 74 - J
  4, 127, 8, 20, 99,           // 75 - K
  4, 127, 64, 64, 64,          // 76 - L
  5, 127, 2, 12, 2, 127,       // 77 - M
  5, 127, 4, 8, 16, 127,       // 78 - N
  4, 62, 65, 65, 62,           // 79 - O
  4, 127, 9, 9, 6,             // 80 - P
  4, 62, 65, 65, 190,          // 81 - Q
  4, 127, 9, 9, 118,           // 82 - R
  4, 70, 73, 73, 50,           // 83 - S
  5, 1, 1, 127, 1, 1,          // 84 - T
  4, 63, 64, 64, 63,           // 85 - U
  5, 15, 48, 64, 48, 15,       // 86 - V
  5, 63, 64, 56, 64, 63,       // 87 - W
  5, 99, 20, 8, 20, 99,        // 88 - X
  5, 7, 8, 112, 8, 7,          // 89 - Y
  4, 97, 81, 73, 71,           // 90 - Z
  2, 127, 65,                  // 91 - [
  4, 1, 6, 24, 96,             // 92 - \ backslash
  2, 65, 127,                  // 93 - ]
  3, 2, 1, 2,                  // 94 - ^
  4, 64, 64, 64, 64,           // 95 - _
  2, 1, 2,                     // 96 - `
  4, 32, 84, 84, 120,          // 97 - a
  4, 127, 68, 68, 56,          // 98 - b
  4, 56, 68, 68, 40,           // 99 - c
  4, 56, 68, 68, 127,          // 100 - d
  4, 56, 84, 84, 24,           // 101 - e
  3, 4, 126, 5,                // 102 - f
  4, 152, 164, 164, 120,       // 103 - g
  4, 127, 4, 4, 120,           // 104 - h
  3, 68, 125, 64,              // 105 - i
  4, 64, 128, 132, 125,        // 106 - j
  4, 127, 16, 40, 68,          // 107 - k
  3, 65, 127, 64,              // 108 - l
  5, 124, 4, 124, 4, 120,      // 109 - m
  4, 124, 4, 4, 120,           // 110 - n
  4, 56, 68, 68, 56,           // 111 - o
  4, 252, 36, 36, 24,          // 112 - p
  4, 24, 36, 36, 252,          // 113 - q
  4, 124, 8, 4, 4,             // 114 - r
  4, 72, 84, 84, 36,           // 115 - s
  3, 4, 63, 68,                // 116 - t
  4, 60, 64, 64, 124,          // 117 - u
  5, 28, 32, 64, 32, 28,       // 118 - v
  5, 60, 64, 60, 64, 60,       // 119 - w
  5, 68, 40, 16, 40, 68,       // 120 - x
  4, 156, 160, 160, 124,       // 121 - y
  3, 100, 84, 76,              // 122 - z
  5, 0, 69, 124, 65, 0,        // 123 - { ї
  1, 127,                      // 124 - |
  5, 62, 73, 73, 65, 34,       // 125 - } Є
  5, 0, 56, 84, 84, 68,        // 126 - ~ є
  0,                           // 127 - 0
  4, 252, 36, 36, 24,          // 128 - р
  4, 56, 68, 68, 40,           // 129 - с
  3, 4, 124, 4,                // 130 - т
  4, 156, 160, 160, 124,       // 131 - у
  5, 24, 36, 252, 36, 24,      // 132 - ф
  5, 68, 40, 16, 40, 68,       // 133 - х
  5, 124, 64, 64, 124, 192,    // 134 - ц
  4, 28, 16, 16, 124,          // 135 - ч
  5, 124, 64, 112, 64, 124,    // 136 - ш
  5, 124, 64, 112, 64, 252,    // 137 - щ
  5, 4, 124, 72, 72, 48,       // 138 - ъ
  5, 124, 72, 48, 0, 124,      // 139 - ы
  4, 124, 72, 72, 48,          // 140 - ь
  4, 68, 84, 84, 56,           // 141 - э
  5, 124, 16, 56, 68, 56,      // 142 - ю
  4, 72, 52, 20, 124,          // 143 - я
  4, 126, 17, 17, 126,         // 144 - А
  4, 127, 73, 73, 49,          // 145 - Б
  4, 127, 73, 73, 54,          // 146 - В
  4, 127, 1, 1, 1,             // 147 - Г
  5, 192, 126, 65, 127, 192,   // 148 - Д
  4, 127, 73, 73, 65,          // 149 - Е
  5, 119, 8, 127, 8, 119,      // 150 - Ж
  4, 34, 65, 73, 54,           // 151 - З
  4, 127, 32, 16, 127,         // 152 - И
  4, 127, 32, 17, 125,         // 153 - Й
  4, 127, 8, 20, 99,           // 154 - К
  4, 64, 60, 2, 127,           // 155 - Л
  5, 127, 2, 12, 2, 127,       // 156 - М
  4, 127, 8, 8, 127,           // 157 - Н
  4, 62, 65, 65, 62,           // 158 - О
  4, 127, 1, 1, 127,           // 159 - П
  4, 127, 9, 9, 6,             // 160 - Р
  4, 62, 65, 65, 34,           // 161 - С
  5, 1, 1, 127, 1, 1,          // 162 - Т
  4, 71, 72, 72, 63,           // 163 - У
  5, 14, 17, 127, 17, 14,      // 164 - Ф
  5, 99, 20, 8, 20, 99,        // 165 - Х
  5, 127, 64, 64, 127, 192,    // 166 - Ц
  4, 15, 8, 8, 127,            // 167 - Ч
  5, 127, 64, 124, 64, 127,    // 168 - Ш
  5, 127, 64, 124, 64, 255,    // 169 - Щ
  5, 1, 127, 72, 72, 48,       // 170 - Ъ
  5, 127, 72, 48, 0, 127,      // 171 - Ы
  4, 127, 72, 72, 48,          // 172 - Ь
  4, 65, 73, 73, 62,           // 173 - Э
  5, 127, 8, 62, 65, 62,       // 174 - Ю
  4, 70, 41, 25, 127,          // 175 - Я
  4, 32, 84, 84, 120,          // 176 - а
  4, 60, 74, 74, 49,           // 177 - б
  4, 126, 89, 86, 32,          // 178 - в
  4, 124, 4, 4, 4,             // 179 - г
  5, 192, 120, 68, 124, 192,   // 180 - д
  4, 56, 84, 84, 24,           // 181 - е
  5, 108, 16, 124, 16, 108,    // 182 - ж
  4, 72, 132, 148, 104,        // 183 - з
  4, 124, 32, 16, 124,         // 184 - и
  4, 124, 33, 17, 124,         // 185 - й
  4, 124, 16, 40, 68,          // 186 - к
  4, 64, 56, 4, 124,           // 187 - л
  5, 124, 8, 16, 8, 124,       // 188 - м
  4, 124, 16, 16, 124,         // 189 - н
  4, 56, 68, 68, 56,           // 190 - о
  4, 124, 4, 4, 124,           // 191 - п
  4, 125, 84, 84, 85,          // 192 - Ё
  4, 57, 84, 84, 73,           // 193 - ё
  5, 0, 0, 0, 255, 16,         // 194 - Left T
  5, 16, 16, 16, 16, 16,       // 195 - Top side
  5, 16, 16, 16, 255, 16,      // 196 - Center +
  5, 0, 0, 0, 255, 20,         // 197 - Left side double H
  5, 0, 0, 255, 0, 255,        // 198 - Left side double
  5, 0, 0, 31, 16, 23,         // 199 - Bot Left double V
  5, 0, 0, 252, 4, 244,        // 200 - Top Left double V
  5, 20, 20, 23, 16, 23,       // 201 - Bot T double
  5, 20, 20, 244, 4, 244,      // 202 - Top T double
  5, 0, 0, 255, 0, 247,        // 203 - Left Side double spl
  5, 20, 20, 20, 20, 20,       // 204 - Center double
  5, 20, 20, 247, 0, 247,      // 205 - Center + double
  5, 20, 20, 20, 23, 20,       // 206 - Bot T double H
  5, 16, 16, 31, 16, 31,       // 207 - Bot Right double V
  0,                           // 208 - for rus fonts UTF-8
  0,                           // 209 - for rus fonts UTF-8
  5, 0, 0, 31, 16, 31,         // 210 - Bot Left double V
  5, 0, 0, 0, 31, 20,          // 211 - Bot Right double H
  5, 0, 0, 0, 252, 20,         // 212 - Top Right double H
  5, 0, 0, 240, 16, 240,       // 213 - Top Right double V
  5, 16, 16, 255, 16, 255,     // 214 - Center + double V
  5, 20, 20, 20, 255, 20,      // 215 - Center + double H
  5, 16, 16, 16, 16, 31,       // 216 - Bot Right
  5, 0, 0, 0, 240, 16,         // 217 - Top Left
  5, 255, 255, 255, 255, 255,  // 218 - Full Block
  5, 240, 240, 240, 240, 240,  // 219 - Half Block Bottom
  3, 255, 255, 255,            // 220 - Half Block LHS
  5, 0, 0, 0, 255, 255,        // 221 - Half Block RHS
  5, 15, 15, 15, 15, 15,       // 222 - Half Block Top
  5, 56, 68, 68, 56, 68,       // 223 - Alpha
  5, 124, 42, 42, 62, 20,      // 224 - Beta
  5, 126, 2, 2, 6, 6,          // 225 - Gamma
  5, 2, 126, 2, 126, 2,        // 226 - Pi
  5, 99, 85, 73, 65, 99,       // 227 - Sigma
  5, 56, 68, 68, 60, 4,        // 228 - Theta
  5, 64, 126, 32, 30, 32,      // 229 - mu
  5, 6, 2, 126, 2, 2,          // 230 - Tau
  5, 153, 165, 231, 165, 153,  // 231 - 0
  5, 28, 42, 73, 42, 28,       // 232 - 0
  5, 76, 114, 1, 114, 76,      // 233 - 0
  5, 48, 74, 77, 77, 48,       // 234 - 0
  5, 48, 72, 120, 72, 48,      // 235 - 0
  5, 188, 98, 90, 70, 61,      // 236 - Zero Slashed  
  4, 62, 73, 73, 73,           // 237 - 0
  5, 126, 1, 1, 1, 126,        // 238 - 0
  5, 42, 42, 42, 42, 42,       // 239 - 3 Bar Equals
  5, 68, 68, 95, 68, 68,       // 240 - +/-
  5, 64, 81, 74, 68, 64,       // 241 - >=
  5, 64, 68, 74, 81, 64,       // 242 - <=
  5, 0, 0, 255, 1, 3,          // 243 - Top of Integral
  3, 224, 128, 255,            // 244 - Bot of Integral
  5, 8, 8, 107, 107, 8,        // 245 - Divide
  5, 54, 18, 54, 36, 54,       // 246 - Wavy =
  5, 6, 15, 9, 15, 6,          // 247 - Degree
  4, 0, 0, 24, 24,             // 248 - Math Product
  4, 0, 0, 16, 16,             // 249 - Short Dash
  5, 48, 64, 255, 1, 1,        // 250 - Square Root
  5, 0, 31, 1, 1, 30,          // 251 - Superscript n
  5, 0, 25, 29, 23, 18,        // 252 - Superscript 2
  5, 0, 60, 60, 60, 60,        // 253 - Centered Square
  5, 255, 129, 129, 129, 255,  // 254 - Full Frame
  5, 255, 255, 255, 255, 255,  // 255 - Full Block
};

// Include the required Arduino libraries:
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define hardware type, size, and output pins:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, D7, D5, D2, MAX_DEVICES);

const char* ssid = "TP-Link_2901";  // put your router name
const char* password = "eugene01";  // put your password

const char* ssid2 = "Galaxy A35";  // put your router name
const char* password2 = "11111111";  // put your password

char Buf[10000]; char Result[15000];
int i = 0;

StaticJsonDocument<10000> parsed;

Ticker queries, queriesUpdate;


bool ICACHE_RAM_ATTR getRandomSeed() {
bool result = false;
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    String url = "https://budka.org/rand.php";
    Serial.println(url);
    http.begin(client, url);
    // start connection and send HTTP header and body
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      Serial.println();
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        int rndSeed = http.getString().toInt();
        Serial.println(rndSeed);
        randomSeed(rndSeed);
        result = true;
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  return result;
}


void ICACHE_RAM_ATTR printUpdate() {
  myDisplay.displayText(Buf, PA_CENTER, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  myDisplay.displayClear();
}

bool ICACHE_RAM_ATTR httpUpdate() {
  bool result = false;
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    String url = "https://newsapi.org/v2/top-headlines?country=ua&apiKey=07c0ced1e3184108b0e96136886d5743&pageSize=1&page=";
    url += String(random(0, 30));
    Serial.println(url);
    http.begin(client, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // start connection and send HTTP header and body
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      Serial.println();
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        http.getString().toCharArray(Result, 15000);
        DeserializationError error = deserializeJson(parsed, Result);
        String news = String(parsed["articles"][0]["title"]) + " " + String(parsed["articles"][0]["description"]);
        news.replace("І", "I");
        news.replace("і", "i");
        news.replace("Ї", "I");
        
        news.replace("Є", "}");
        news.replace("ї", "{");
        news.replace("є", "~");
        news.replace("—", "-");
        news.replace("–", "-");
        news.replace("`", "'");
        news.replace("«", "\"");
        news.replace("»", "\"");

        news.toCharArray(Buf, 10000);
        Serial.printf(Buf);
        Serial.println();
        result = true;
      } else {
        String(httpCode).toCharArray(Buf, 10000);
        Serial.printf(Buf);
        Serial.println();
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      
      String(http.errorToString(httpCode).c_str()).toCharArray(Buf, 10000);
      Serial.printf(Buf);
      Serial.println();
    }

    http.end();
  }

  return result;
}

void ICACHE_RAM_ATTR onQuery() {

  if (httpUpdate()) {
    myDisplay.displayText("Апдейт", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    myDisplay.displayClear();
  } 
  queriesUpdate.once(5.0, printUpdate);
}

void setup() {

  myDisplay.begin();
  myDisplay.setFont(_5bite_rus);
  myDisplay.setIntensity(0);
  myDisplay.displayClear();

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid2);

  WiFi.begin(ssid2, password2);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    i++;
    if (i == 15) {

      Serial.println();
      Serial.println();
      Serial.print("Connecting to ");
      Serial.println(ssid);

      WiFi.begin(ssid, password);
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  getRandomSeed();

  httpUpdate();
  printUpdate();
  queries.attach(60, onQuery); 
}

void loop() {
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }
}
