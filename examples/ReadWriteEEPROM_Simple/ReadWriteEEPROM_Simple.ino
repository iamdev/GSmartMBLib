#include <GSmartMBLib.h>
GSmartMB mb;
void setup(){
  Serial.begin(115200);
  Serial.print("\nInitializing...");
  mb.begin(true);
  Serial.println("Done.");
  uint16_t data_address = mb.getTime()%10000;//Random Address
  uint16_t data_in = mb.getTime()&0xFFFF;//Random Data
  uint16_t data_out = 0;
  Serial.printf("Write data [%u] to address [%u]\n",data_in,data_address);
  mb.writeData(data_address,data_in);
  data_out = mb.readData(data_address);
  Serial.printf("Read data from address [%u] = [%u]\n",data_address,data_out);
}
void loop() {
  
}